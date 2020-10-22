#ifndef __REDIS_CTX_H__
#define __REDIS_CTX_H__

//#include "base.h"
extern "C" {
    #include <hiredis/hiredis.h>
}
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>


/*key has moved to ip:port*/
static const std::string REDIS_MOVED = "MOVED";
/*cluster is migrating, ask ip:port*/
static const std::string REDIS_ASK = "ASK";
/*try again with same ip:port*/
static const std::string REDIS_TRYAGAIN = "TRYAGAIN";
/*at MULTI situation, key in different slots*/
static const std::string REDIS_CROSSSLOT= "CROSSSLOT";
/*case: more then half master down, or master down without slaver
  current: RETRY, or what to do ???*/
static const std::string REDIS_CLUSTERDOWN = "CLUSTERDOWN";

enum redis_resp_code {
    RDCTX_REP_FAILED = -1, //redis request failed, dont try
    RDCTX_REP_OK = 0,  //redis request success

    //redis default error codes;
    RDCTX_REP_MOVED,
    RDCTX_REP_ASK,
    RDCTX_REP_TRYAGAIN,
    RDCTX_REP_CROSSSLOT,
    RDCTX_REP_CLUSTERDOWN,

    //local error
    RDCTX_REP_REPLYNULL,   //while redisReply *rep = NULL, retry with same redis_ctx_sp
    RDCTX_REP_PARSEFAILED, //parse redisReply failed, dont retry
};

/*read.h
 50 #define REDIS_REPLY_STRING 1
 51 #define REDIS_REPLY_ARRAY 2
 52 #define REDIS_REPLY_INTEGER 3
 53 #define REDIS_REPLY_NIL 4
 54 #define REDIS_REPLY_STATUS 5
 55 #define REDIS_REPLY_ERROR 6
*/

class redis_ctx {
friend class yredis;
friend class redis_pool_mgr;
friend class redis_ctx_pool;

private:
    std::string ip_;
    int port_;
    redisContext *rctx_; /* the last redisContext* */
    struct timeval tmval_;
    bool asking_;
    int reconn_cnt_;
    bool is_using_;
private:
    bool reconnect() {
        if (rctx_) {
            redisFree(rctx_);
            rctx_ = NULL;
        }
        return connect();
    }

    /* When an error occurs, the err flag in a context is set to hold the type of
     * error that occurred. REDIS_ERR_IO means there was an I/O error and you
     * should use the "errno" variable to find out what is wrong.
     * For other values, the "errstr" field will hold a description. */
    //#define REDIS_ERR_IO 1 /* Error in read or write */
    //#define REDIS_ERR_EOF 3 /* End of file */
    //#define REDIS_ERR_PROTOCOL 4 /* Protocol error */
    //#define REDIS_ERR_OOM 5 /* Out of memory */
    //#define REDIS_ERR_OTHER 2 /* Everything else... */
    bool reconnect_if() {
        if (rctx_->err == 3 ||//Server closed the connection
            rctx_->err == 1) {//Server reset the connection
            reconn_cnt_ ++;
            if (reconn_cnt_ % 5 == 0) {
                LOG(WARNING) << __FUNCTION__ << " " << ip_ << ":" << port_
                             << ", cnt " << reconn_cnt_;
            }
            return reconnect();
        }
        return false;
    }

    /*
        MOVED: just redirect to new ip:port
        ASK: redirect and send ASKING and then cmds, reply with ASKING and response
        return : enum redis_resp_code
    */
    redis_resp_code trans_rep_err_code(redisReply *rep, std::string &estr) {
        if (rep->type != REDIS_REPLY_ERROR) {
            return RDCTX_REP_OK;
        }
        std::string err(rep->str, rep->len);
        estr = err;
        redis_resp_code err_code = RDCTX_REP_OK;

        std::string::size_type pos = err.find(" ");
        if (pos == std::string::npos) {
            //parsed failed
            err_code = RDCTX_REP_PARSEFAILED;
            return err_code;
        }
        std::string sub = err.substr(0, pos);
        if (sub == REDIS_MOVED) {
            err_code = RDCTX_REP_MOVED;
        }
        else if (sub == REDIS_ASK) {
            err_code = RDCTX_REP_ASK;
        }
        else if (sub == REDIS_TRYAGAIN) {
            err_code = RDCTX_REP_TRYAGAIN;
        }
        else if (sub == REDIS_CROSSSLOT) {
            err_code = RDCTX_REP_CROSSSLOT;
            LOG(ERROR) << "ERROR CALL, RDCTX_REP_CROSSSLOT, PLEASE CHECK THE KEYS.";
            exit(0);
        }
        else if (sub == REDIS_CLUSTERDOWN) {
            err_code = RDCTX_REP_CLUSTERDOWN;
        }
        else {
            //LOG(ERROR) << __FUNCTION__ << " sub " << sub;
            err_code = RDCTX_REP_PARSEFAILED; //our comand fails~
        }

        if (RDCTX_REP_ASK == err_code || RDCTX_REP_MOVED == err_code) {
            std::string::size_type m = err.rfind(" ");
            std::string::size_type n = err.rfind(":");
            estr = err.substr(m + 1);
        }

        return err_code;
    }

    redisReply *redis_cmd_argv(const std::string &cmd,
                               const std::vector<std::string> &params) {
        redisReply *rep = NULL;

        /* ASKING here? */
        if (asking_) {
            redisAppendCommand(rctx_, "asking");
        }

        int sz = params.size() + 1;
        const char *argv[sz];
        size_t argvlen[sz];
        argv[0] = cmd.c_str();
        argvlen[0] = cmd.length();
        for (int i = 0; i < params.size(); i++) {
            argv[i + 1] = params[i].c_str();
            argvlen[i + 1] = params[i].length();
        } 
        
        rep = (redisReply*)redisCommandArgv(rctx_, sz, argv, argvlen);

        return rep;
    }

public:
    ~redis_ctx() {
        if (rctx_) {
            redisFree(rctx_);
            rctx_ = NULL;
        }
    }

protected:
    redis_ctx(const std::string &ip, const int port, const struct timeval &tmval) {
        ip_ = ip;
        port_ = port;
        rctx_ = NULL;
        tmval_ = tmval;
        asking_ = false;
        reconn_cnt_ = 0;
        is_using_ = false;
    }

    void set_asking(bool t) {
        asking_ = t;
    }

    bool get_asking() {
        return asking_;
    }

    void set_using(bool u) {
        is_using_ = u;
    }

    bool is_using() {
        return is_using_;
    }

    std::string get_conn_str() {
        return ip_ + ":" + std::to_string(port_);
    }

    bool connect() {
        rctx_ = redisConnectWithTimeout(ip_.c_str(), port_, tmval_);
        if (NULL == rctx_) {
            LOG(ERROR) << "connect to [" << ip_ << ":" << port_ << "] failed";
            return false;
        }
        reconn_cnt_ = 0;
        return true;
    }
#define TRY_RECONNECT(EXPRS) \
        if (NULL == rep) { \
            return RDCTX_REP_REPLYNULL; \
        } \
        if (EXPRS) { \
            redis_resp_code err_code = trans_rep_err_code(rep, estr);\
            if (err_code != RDCTX_REP_OK) {\
                if (RDCTX_REP_CLUSTERDOWN == err_code) {\
                    LOG(INFO) << __FUNCTION__ << " cmd " << cmd << REDIS_CLUSTERDOWN \
                                 << " " << ip_ << ":" << port_;\
                }\
                if (err_code != RDCTX_REP_MOVED) {\
                    LOG(INFO) << __FUNCTION__ << " cmd " << cmd << ", OTHER ERROR: " \
                               << estr << ", err_code:" << err_code;\
                }\
                freeReplyObject((void*)rep);\
                return err_code;\
            }\
            LOG(ERROR) << __FUNCTION__ << " error, cmd " << cmd << " rep->type: " \
                       << rep->type << ", err_code:" << err_code;\
            freeReplyObject((void*)rep);\
            return RDCTX_REP_FAILED;\
        }
  
    redis_resp_code cmd_re_str(const std::string &cmd,
                               const std::vector<std::string> &params,
                               std::string &re,
                               bool &is_nil,
                               std::string &estr) {
        redisReply *rep = redis_cmd_argv(cmd, params);

        TRY_RECONNECT(rep->type != REDIS_REPLY_STRING &&
                      rep->type != REDIS_REPLY_STATUS &&
                      rep->type != REDIS_REPLY_NIL);

        if (rep->type == REDIS_REPLY_NIL) {
            is_nil = true; 
        }
        else {
            re = std::string(rep->str, rep->len);
        }
        freeReplyObject((void*)rep);
        return RDCTX_REP_OK;
    }

    redis_resp_code cmd_re_i64(const std::string &cmd,
                               const std::vector<std::string> &params,
                               int64_t &re,
                               std::string &estr) {
        re = 0;
        redisReply *rep = redis_cmd_argv(cmd, params);
        
        TRY_RECONNECT(rep->type != REDIS_REPLY_INTEGER &&
                      rep->type != REDIS_REPLY_STATUS);
        re = rep->integer;
        freeReplyObject((void*)rep);
        return RDCTX_REP_OK;
    }

    bool parse_array(redisReply *rep, std::vector<std::string> &rvt) {
        if (!rep) { return true; }
        std::string sbk;
        for (int i = 0; i < (int)rep->elements; i++) {
            redisReply *tmp = rep->element[i];
            if (rvt.size() > 0) {
                sbk = rvt.back();
            }
            LOG(INFO) << __FUNCTION__ << " " << rep->elements << ", i " << i  << ", type " << tmp->type << ", rvt.size " << rvt.size() << ", back: " << sbk;
            if (tmp->type == REDIS_REPLY_INTEGER) { std::string line = std::to_string(tmp->integer);rvt.push_back(line);}
            if (tmp->type == REDIS_REPLY_STRING) { std::string line(tmp->str, tmp->len);rvt.push_back(line);}
            if (tmp->type == REDIS_REPLY_NIL) { rvt.push_back("");}
            if (tmp->type == REDIS_REPLY_ARRAY) {
                parse_array(tmp, rvt);
            }
        }
        if (rvt.size() > 0) {
            sbk = rvt.back();
        }
        LOG(INFO) << __FUNCTION__ << " " << rep->elements << ", rvt.size " << rvt.size() << ", back: " << sbk;
        return true;
    }

    redis_resp_code cmd_re_vector(const std::string &cmd,
                                  const std::vector<std::string> &params,
                                  std::vector<std::string> &re_vec_str,
                                  std::string &estr,
                                  bool clusterSlots) {
        redisReply *rep = redis_cmd_argv(cmd, params);
        
        TRY_RECONNECT(rep->type != REDIS_REPLY_ARRAY &&
                      rep->type != REDIS_REPLY_STATUS);
        if (clusterSlots) {
            return cluster_slots(rep, re_vec_str);
        }

        parse_array(rep, re_vec_str);
        freeReplyObject((void*)rep);
        return RDCTX_REP_OK;
    }
 
    redis_resp_code cmd_re_vector_with_nil(const std::string &cmd,
                                           const std::vector<std::string> &params,
                                           std::vector<std::pair<bool, std::string>> &re_vec_str,
                                           std::string &estr) {
        redisReply *rep = redis_cmd_argv(cmd, params);
        TRY_RECONNECT(rep->type != REDIS_REPLY_ARRAY &&
                      rep->type != REDIS_REPLY_STATUS);

        for (int i = 0; i < (int)rep->elements; i++) {
            redisReply *tmp = rep->element[i];
            if (tmp->type != REDIS_REPLY_STRING) {
                re_vec_str.push_back(std::make_pair(false, ""));
                continue;
            }
            std::string line(tmp->str, tmp->len);
            re_vec_str.push_back(std::make_pair(true, line));
        }
        freeReplyObject((void*)rep);
        return RDCTX_REP_OK;
    }

    redis_resp_code cluster_slots(redisReply *rep, std::vector<std::string> &re_vec_str) {
        for (int i = 0; i < (int)rep->elements; i++) {
            redisReply *arr = rep->element[i];
            if (arr->type != REDIS_REPLY_ARRAY) {
                continue;
            }
            if (arr->elements < 2) {
                LOG(WARNING) << __FUNCTION__ << " in cluster_slots arr.size()<2, continue.";
                continue;
            }
            for (int n = 0; n < 2; n++) { 
                redisReply *tmp = arr->element[n];
                if (tmp->type != REDIS_REPLY_INTEGER) {
                    return RDCTX_REP_FAILED;
                } 
                std::string line = std::to_string((uint64_t)tmp->integer);
                re_vec_str.push_back(line);
            }
        }
        return RDCTX_REP_OK;
    }

public:
    redis_resp_code keys(const std::string &lua,
                         const std::string &node_key,
                         const std::string &reg, 
                         std::vector<std::string> &re_vec_str,
                         std::string &estr) {
        redisReply *rep = NULL;
        std::string str("eval %s 1 %s %s");
        rep = (redisReply *)redisCommand(rctx_,
                                         str.c_str(),
                                         lua.c_str(),
                                         node_key.c_str(),
                                         reg.c_str());
        const std::string &cmd = lua;
        TRY_RECONNECT(rep->type != REDIS_REPLY_ARRAY &&
                      rep->type != REDIS_REPLY_STATUS);

        for (int i = 0; i < (int)rep->elements; i++) {
            redisReply *tmp = rep->element[i];
            if (tmp->type != REDIS_REPLY_STRING) {
                re_vec_str.push_back("");
                continue;
            }
            std::string line(tmp->str);
            re_vec_str.push_back(line);
        }
        freeReplyObject((void*)rep);
        return RDCTX_REP_OK;
    }

    redis_resp_code ping(const std::string &lua,
                         const std::string &node_key,
                         std::string &re_str,
                         std::string &estr) {
        redisReply *rep = NULL;
        std::string str("eval %s 1 %s");
        rep = (redisReply *)redisCommand(rctx_,
                                         str.c_str(),
                                         lua.c_str(),
                                         node_key.c_str());
        const std::string &cmd = lua;
        TRY_RECONNECT(rep->type != REDIS_REPLY_STRING &&
                      rep->type != REDIS_REPLY_STATUS);
    
        re_str = std::string(rep->str, rep->len);
        freeReplyObject((void*)rep);
        return RDCTX_REP_OK;
    }

private:
    void parse_reply_element(redisReply* rr, std::vector<std::string>& rvct) {
        if (rr->type != REDIS_REPLY_ARRAY) {
            return;
        }
        for (int i = 0; i < rr->elements; i++) {
            redisReply* r = rr->element[i];
            LOG(WARNING) << __FUNCTION__ << " i " << i << ", type " << r->type;
            std::string s;
            switch (r->type) {
                case REDIS_REPLY_STRING:
                    s = std::string(r->str, r->len);
                    rvct.push_back(s);
                    break;
                case REDIS_REPLY_INTEGER:
                    s = std::to_string(r->integer);
                    break;
                case REDIS_REPLY_ARRAY: {
                    std::vector<std::string> v;
                    parse_reply_element(r, v);
                    LOG(WARNING) << __FUNCTION__ << " i " << i << ", type " << r->type;
                    break;
                }
                default:
                    LOG(WARNING) << __FUNCTION__ << " i " << i << ", type " << r->type;
                    break;
            }
        }
    }

protected:
    redis_resp_code get_route(const std::string& cmd,
                              const std::vector<std::string>& params,
                              int64_t &ooff, int64_t &omz, int64_t &osbjz,
                              std::vector<std::string> &vrif,
                              std::vector<std::string> &vnif,
                              std::string &estr) {
        estr.clear();
        vrif.clear();
        vnif.clear();
        ooff = -2;
        omz = osbjz = 0;
        redisReply* rep = redis_cmd_argv(cmd, params);
        TRY_RECONNECT(rep->type != REDIS_REPLY_ARRAY &&
            rep->type != REDIS_REPLY_STATUS);

        if (rep->elements != 5) {
            freeReplyObject((void*)rep);
            estr = "ERR redis reply format error";
            LOG(ERROR) << __FUNCTION__ << " " << estr;
            return RDCTX_REP_FAILED;
        }

        std::string s;
        redisReply* e = rep->element[0];
        ooff = e->integer;
        e = rep->element[1];
        omz = e->integer;
        e = rep->element[2];
        osbjz = e->integer;
        e = rep->element[3];
        parse_reply_element(e, vrif);
        e = rep->element[4];
        parse_reply_element(e, vnif);

        freeReplyObject((void*)rep);
        return RDCTX_REP_OK;
    }
};

typedef boost::shared_ptr<redis_ctx> redis_ctx_sp;

#endif
