#include <cassert>
#include <iostream>
#include <sys/time.h>
#include <thread>
#include <memory>
#include <vector>
#include "rocksdb/db.h"
#include "rocksdb/utilities/backupable_db.h"
#include "rocksdb/utilities/checkpoint.h"
#include "rocksdb/table.h"

#define TH 4
#define DATASIZE 400000
#define PROCESSSIZE 10000

#define PERSIZE PROCESSSIZE/TH
#define CNT DATASIZE/PROCESSSIZE

static std::string partstr(const std::string &fullstr) {
    /* only used for log */
    if(fullstr.size() > 50) {
        std::string partstr = fullstr.substr(0, 20);
        partstr += "...";
        partstr += "(size:" + std::to_string(fullstr.size()) + ")";
        return partstr;
    }
    else {
        return fullstr;
    }
}

static uint64_t gtm() {
    struct timeval tm;
    gettimeofday(&tm, 0);
    uint64_t re = ((uint64_t)tm.tv_sec)*1000*1000 + tm.tv_usec;
    return re;
}

struct node {
    std::string key_;
    std::string field_;
    std::string value_;
    std::string aofpos_;

    void init(int i) {
        std::string ssss;
        for(int c = 0; c < 1000; c++) {
            ssss += "ssss";
        }
        std::string key_   = "key_"   + std::to_string(i) + ssss;
        std::string field_ = "field_" + std::to_string(i) + ssss;
        std::string value_ = "value_" + std::to_string(i) + ssss;
        std::string aofpos_ = "10";
    }

    node() {
        std::string key_   = "key_";
        std::string field_ = "field_";
        std::string value_ = "value_";
        std::string aofpos_ = "10";
    }
};

class rocks {
private:
    rocksdb::DB* db_;
    rocksdb::Options options_;

public:
    rocks() {
        db_ = NULL;
    }

    ~rocks() {
        if(db_ != NULL) {
            delete db_; 
        }
    }

    void write_batch(const std::shared_ptr<rocksdb::WriteBatch> &b){
        if(b.get() == NULL){
            return;
        }
        db_->Write(rocksdb::WriteOptions(), b.get());
    }

    void read() {
        std::string ssss;
        for(int c = 0; c < 1000; c++) {
            ssss += "ssss";
        }
        std::string key   = "key_"   + std::to_string(5) + ssss;
        std::string value;
        rocksdb::Status s = db_->Get(rocksdb::ReadOptions(), key, &value);
        assert(s.ok());
        std::cout << value << std::endl;
    }
    
    void setpos() {
        rocksdb::Status s = db_->Put(rocksdb::WriteOptions(), "AOFPOS", "10");
        assert(s.ok());
    }

    void init() {
        rocksdb::Options options;

        rocksdb::SstFileWriter sst_file_writer(rocksdb::EnvOptions(), options);
        std::string file_path = "./data/file1.sst";

        rocksdb::Status s = sst_file_writer.Open(file_path);
        assert(s.ok());

        s = sst_file_writer.Put("key", "value");

        options.create_if_missing = true;
        //rocksdb::Status s = rocksdb::DB::Open(options, "./data", &db_);
        s = rocksdb::DB::Open(options, "./data", &db_);
        assert(s.ok());
    }

};

class bus {
public:
    void process(std::vector<node> &nodes, rocks &ro, int pos) {
        std::shared_ptr<rocksdb::WriteBatch> b;
        uint64_t utm = gtm();

        for(int i = pos * PERSIZE; i < pos * PERSIZE + PERSIZE; i++) {
            /* Put each data into batch */
            std::string &key = nodes[i].key_;
            std::string &field = nodes[i].field_;
            std::string &value = nodes[i].value_;

            if(b.get() == NULL) {
                b.reset(new rocksdb::WriteBatch());
            }
            b->Put(key, field);
            b->Put(field, value);
        }

        utm = gtm() - utm; std::cout << "utm1:" << utm << " us" << std::endl; utm = gtm();

        ro.write_batch(b);

        utm = gtm() - utm; std::cout << "utm2:" << utm << " us" << std::endl; utm = gtm();
    }

    void run(rocks &ro) {
        /* generate 4000 node data */
        std::vector<node> nv;
        for(int i = 0; i < DATASIZE; i++) {
            node n;
            n.init(i);
            nv.push_back(n);
        }

        for(int x = 0; x < CNT; x++) {
            std::vector<node> nodes;
            nodes.insert(nodes.begin(), nv.begin() + x * PROCESSSIZE, nv.begin() + x * PROCESSSIZE + PROCESSSIZE); 

            std::cout << "                    | " << "DATASIZE:" << DATASIZE << ", PROCESSSIZE:" << PROCESSSIZE << ", TH:" << TH << std::endl;

            /* use 4 thread to process, each thread will process 1000 data */
            std::vector< std::shared_ptr<std::thread> > ths;
            for(int i = 0; i < TH; i++) {
                std::shared_ptr<std::thread> th(
                    new std::thread(&bus::process, this, std::ref(nodes), std::ref(ro), i)
                );
                ths.push_back(th);
            }

            for(int i = 0; i < TH; i++) {
                ths[i]->join();
            }
        }
    }
};

int main() {

    rocks ro;
    bus b;

    ro.init();
    b.run(ro);
    
    return 0;
}

