#ifndef __YREDIS_H__
#define __YREDIS_H__

#include "redis_ctx.h"

#define REDIS_RETRY_INTERVAL (10*1000)
#define GET_CONN_ERR "get connection failed(off limits)"

class yredis {
private:
    /* <"ip:port", redis_ctx_sp> */
    std::map<std::string, redis_ctx_sp> map_;
    std::string last_conn_str_;
    redis_ctx_sp last_rdx_;

    bool with_up_time_;
    int rcnt_;
    int rmax_;

private:
    redis_ctx_sp get_rdx_sp() {
        return last_rdx_;
    }

    redis_ctx_sp get_rdx_sp(const std::string &conn_str) {
        redis_ctx_sp rcs;
        auto it = map_.find(conn_str);
        if (it != map_.end()) {
            return it->second;
        }
        int s = conn_str.find(":");
        if (s == std::string::npos) {
            return rcs;
        }
        
        std::string ip = conn_str.substr(0, s);
        std::string sport = conn_str.substr(s+1, conn_str.length()-s-1); 
        LOG(INFO) << "ip:port " << ip << ":" << sport;  
        
        int p = 0;
        try {
            p = std::stoi(sport); 
        }
        catch (const std::exception &e) {
            return rcs;
        }

        const struct timeval tmval = {120, 500000};
        last_rdx_.reset(new redis_ctx(ip, p, tmval));
        last_rdx_->connect(); 
        last_conn_str_ = ip;
        last_conn_str_ += std::to_string(p);
        map_.insert(std::make_pair(last_conn_str_, last_rdx_));

        LOG(INFO) << __FUNCTION__ << ", str " << conn_str ;
        return last_rdx_;
    }

public:
    yredis(bool with_up_time = true) {
        with_up_time_ = with_up_time;
        rcnt_ = 0; 
        rmax_ = 5; 
    }

    yredis(const std::string &ip, const int port, const struct timeval &tmval={120,500000}) {
        with_up_time_ = false;
        rmax_ = 5; 

        last_rdx_.reset(new redis_ctx(ip, port, tmval));
        last_rdx_->connect(); 
        last_conn_str_ = ip;
        last_conn_str_ += std::to_string(port);
        map_.insert(std::make_pair(last_conn_str_, last_rdx_));
    }

    ~yredis() {
        release_rdx();
    }

    bool with_up_time() const{
        return with_up_time_;
    }

    void release_rdx() {
        map_.clear();
        last_conn_str_.clear();
        last_rdx_.reset();
    }
        
    int64_t rdx_re_i64(const std::string &cmd,
                       const std::vector<std::string> &params,
                       std::string &estr) {
        redis_resp_code err_code = RDCTX_REP_OK;
        int64_t re = 0;
        rcnt_ = 0;
        redis_ctx_sp rdx = get_rdx_sp();
        if (!rdx.get()) {
            estr = GET_CONN_ERR;
            return re;
        }
        while (rdx.get()) {
            err_code = rdx->cmd_re_i64(cmd, params, re, estr);
            ERR_CODE_ANALYSIS;
        }
        return re;
    }

    int64_t setddl(const std::string& ddlkey,
                   const std::string& ddlopt,
                   std::string& estr) {
        std::string cmd("setddl");
        std::vector<std::string> params = {ddlkey, ddlopt};
        int64_t re = rdx_re_i64(cmd, params, estr);
    }
};

typedef boost::shared_ptr<yredis> yredis_sp;

#endif
