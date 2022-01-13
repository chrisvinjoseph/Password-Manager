#ifndef PASS_MANAGER_H
#define PASS_MANAGER_H

class PassManager {
    private:
        bool* auth_flag;
    public:
        PassManager(bool*);
        void test();
};

#endif
