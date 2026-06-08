#include "socket_utils.h"


int main() {
    std::cout << "eth0 " << Common::getIfaceIP("eth0") << std::endl;
    std::cout << "lo " << Common::getIfaceIP("lo") << std::endl;
    std::cout << "wlx6c1ff7894ad5 " << Common::getIfaceIP("wlx6c1ff7894ad5") << std::endl;
    std::cout << "docker0 " << Common::getIfaceIP("docker0") << std::endl;
    return 0;
}