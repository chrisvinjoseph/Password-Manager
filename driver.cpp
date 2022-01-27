#include <iostream>
#include <vector>

#include "headers/pass_manager.hpp"
#include "headers/misc.hpp"

int main() {
    PassManager manager;
    manager.run();

    Misc::exitText();

    return 0;
}
