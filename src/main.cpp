//
// Created by Jack Gu on 12/30/21.
//

#include "../include/ls.h"

int main(int argc, char **argv) {
    sqlite3 *db;
    std::string db_file("example.db");

    // parse command line arguments
    while (1) {
        int optcode = getopt(argc, argv, "hf:");
        if (optcode == -1) {
            break;
        }

        switch (optcode) {
            case 'h':
                std::cout << ("-f specify database file path, example.db by default. ") << std::endl;
                return 0;  // early exit
            case 'f':
                db_file = optarg;
        }
    }

    std::clog << db_file.c_str() << std::endl;

    assert(0 == open_db_or_initialize(db, db_file.c_str()));

    std::string username, password;
    char mode;

    while (1) {
        std::cout << "Enter 1 to register, 2 to login, 3 to terminate. " << std::endl;
        std::cin >> mode;

        switch (mode) {
            case '1':
                // register
                std::cout << "Username: ";
                std::cin >> username;
                std::cout << "Password: ";
                std::cin >> password;
                std::cout << username << ' ' << password << std::endl;
                add_user(db, username, password);
                continue;
            case '2':
                // login
                std::cout << "Username: ";
                std::cin >> username;
                std::cout << "Password: ";
                std::cin >> password;
                std::cout << username << ' ' << password << std::endl;
                continue;
            case '3':
                break;
            default:
                std::cout << "Unrecognized mode: " << mode << std::endl;
                continue;
        }
        break;
    }

    sqlite3_close(db);
    return 0;
}