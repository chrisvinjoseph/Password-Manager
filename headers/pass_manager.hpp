#ifndef PASS_MANAGER_H
#define PASS_MANAGER_H

#include <fstream>

#include "misc.hpp"

class PassManager {
    private:
        bool auth_flag = false;
        ifstream usr_file;
        int selection;
        Misc::User auth_user_detail_list;
    public:
        int run();
        int login();
        int loginMenu();
        int managerMenu();
        int retrievePassword(std::string*);
        int addPassword();
        // ALL FUNCS BELOW NEED TO BE COMPLETED
        int copyToClipboard(std::string*);
        void showHelpPasswordFound();
        void showHelpLogin();
};

#endif
