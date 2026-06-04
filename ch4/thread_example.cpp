#include <iostream>
#include "thread_utils.h"

void printNumbers(int start, int count) {
    for (int i = start; i < start + count; ++i)
        std::cout << "thread: " << i << "\n";
}

int main() {
    auto t = createAndStartThread(0, "printer", printNumbers, 1, 5);

    t->join();
    delete t;
}
