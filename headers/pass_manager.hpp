#ifndef PASS_MANAGER_H
#define PASS_MANAGER_H

#include <fstream>

class PassManager {
    private:
        bool auth_flag = false;
        std::string auth_username;
        ifstream usr_file;
        int selection;
    public:
        int run();
        int login();
        int loginMenu();
};

#endif
