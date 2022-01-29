#ifndef MISC_H
#define MISC_H

class Misc {
    public:
        static void introText();
        static void exitText();
        // Definition of user
        // NOTE: Add purge() function to clear vectors
        struct User {
            std::string auth_username;
            std::vector<std::string> target_loc_username_list;
            std::vector<std::string> locations;
            std::vector<size_t> plaintextsizes;
            std::vector<std::string> IVs;
            std::vector<std::string> ciphers;
        }
}

#endif
