#include <iostream>

int main()
{
    std::ostream &log = std::cout;

    log << "hello world\n";

    log.flush();

    return EXIT_FAILURE;
}