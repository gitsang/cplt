
#include <iostream>

int main() {

    std::string key = "ypush:route-info:t3";
    std::string field = "c3";
    std::string value = "xxxxxxxxrif3";

    std::string tid = key.substr(17, key.length()-17);
    std::string cid = field;
    std::string rif = value.substr(8, value.length()-8);
    std::string stretm = value.substr(0,8);
    //uint64_t etm = std::stoi(value.substr(0, 8));

    std::cout << "tid:" << tid << "\ncid:" << cid
              << "\nroute_info:" << rif << "\nendtime:" << stretm << std::endl;

    return 0;

}


