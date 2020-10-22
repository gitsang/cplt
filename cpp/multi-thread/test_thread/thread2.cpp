#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

std::mutex g_mutex;
std::mutex g_io_mutex;
int g_count = 0;

void Counter() {
    int i;
    {
        std::unique_lock<std::mutex> lock(g_mutex);
        i = ++g_count;
    }
    {
        std::unique_lock<std::mutex> lock(g_io_mutex);
        std::cout << "count: " << i << std::endl;
    }
}

int main(int argc, char* argv[]) {
    const std::size_t SIZE = 4;

    std::vector<std::thread> v;
    v.reserve(SIZE);

    for(std::size_t i = 0; i < SIZE; ++i) {
        v.emplace_back(&Counter);
    }

    for(std::thread& t : v) {
        t.join(); 
    }

    return 0;
}
