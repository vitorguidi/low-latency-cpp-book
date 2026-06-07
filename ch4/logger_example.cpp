#include "logger.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    using namespace Common;

    char tmp_path[] = "/tmp/logger_example_XXXXXX";
    int fd = mkstemp(tmp_path);
    close(fd);

    char c = 'd';
    int i = 3;
    unsigned long ul = 65;
    float f = 3.4f;
    double d = 34.56;
    const char *s = "test C-string";
    std::string ss = "test string";

    {
        Logger logger(tmp_path);
        logger.log("Logging a char:% an int:% and an unsigned:%\n", c, i, ul);
        logger.log("Logging a float:% and a double:%\n", f, d);
        logger.log("Logging a C-string:'%'\n", s);
        logger.log("Logging a string:'%'\n", ss);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    std::ifstream result(tmp_path);
    std::cout << result.rdbuf();
    std::remove(tmp_path);
    return 0;
}
