#ifndef __DDL_H__
#define __DDL_H__

#include "yredis.h"
#include <thread>

class ddl {

private:

    yredis_sp new_rds() {
        yredis_sp yrp;
        bool bre;
        std::string ip = config::inst()->get_str("redis.ip", bre);
        if (!bre) {
            LOG(ERROR) << __FUNCTION__ << " bre " << bre << ", " << ip;
            return yrp;
        } 
        int port = config::inst()->get_i32("redis.port", bre);
        if (!bre) {
            LOG(ERROR) << __FUNCTION__ << " bre " << bre << ", " << port;
            return yrp;
        } 
        yrp.reset(new yredis(ip, port));
        return yrp; 
    }

    void test_setddl(int idx) {
        std::string ddlkey = std::to_string(idx) + std::to_string(time(NULL));
        std::string ddlopt = "This is a ddl option" + std::to_string(idx);
        
        yredis_sp yrp = new_rds();
        std::string estr;
        int64_t ir = yrp->setddl(ddlkey, ddlopt, estr);
    }

    bool test_multi_set_ddl() {
        int th_cnt = 10;
        std::shared_ptr<std::thread> ths[th_cnt];

        for(int i = 0; i < th_cnt; i++) {
            ths[i].reset(new std::thread(&ddl::test_setddl, this, i));
        }
        for (int i = 0; i < th_cnt; i++) {
            ths[i]->join();
        }
        return true;
    }

public:

    bool test_ddl() {
        bool bre;

        FUNC_DETAIL(test_multi_set_ddl());

        return true;
    }
};

#endif
