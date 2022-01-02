//
// Created by Jack Gu on 12/30/21.
//

#ifndef LOGIN_SYSTEM_LS_H
#define LOGIN_SYSTEM_LS_H

#include <cassert>
#include <climits>
#include <cstdio>
#include <getopt.h>
#include <filesystem>
#include <iostream>
#include <optional>
#include <sqlite3.h>

namespace ls {

    class CredentialManager {
    public:
        explicit CredentialManager(const std::string &filename);

        ~CredentialManager();

        std::optional<std::string> maybe_get_password(const std::string &username);

        void add_user(const std::string &username, const std::string &password);

    private:
        sqlite3 *db = nullptr;
    };

    int prompt(CredentialManager *cm);

}
#endif //LOGIN_SYSTEM_LS_H
