#ifndef LOGIN_MANAGER_H
#define LOGIN_MANAGER_H

class LoginManager {
    private:
        bool auth_flag = false;
        std::string auth_username;
        int selection;
    public:
        void displayMenu();
        bool getStatus();
        std::string getUsername();
};

#endif
