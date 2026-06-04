#include "macros.h"

int main() {
    ASSERT(1 == 1, "should never fire");
    ASSERT(1 == 2, "1 != 2");
}
