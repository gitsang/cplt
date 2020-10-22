#include <iostream>

struct st_max {
    int (*func)(int, int);
};

int t_func(int a, int b) {
    return a > b ? a : b;
}

static struct st_max sm1 = {
    .func = t_func,
};

int main() {
    int res = sm1.func(1, 2);
    std::cout << res << std::endl;
    return 0;
}
