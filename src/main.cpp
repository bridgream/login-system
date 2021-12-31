//
// Created by Jack Gu on 12/30/21.
//

#include "../include/ls.h"

int main(int argc, char **argv) {
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

    auto db = open_db_or_initialize(db_file.c_str());

    char username[MAX_LENGTH], password[MAX_LENGTH];
    char mode[1];

    while (1) {
        std::cout << "Enter 1 to register, 2 to login. " << std::endl;
        fgets(mode, 1, stdin);

        switch (mode[0]) {
            case '1':
                // register
                break;
            case '2':
                // login
                break;
            default:
                std::cout << "Unrecognized mode: " << mode[0] << std::endl;
                break;
        }
    }

    return 0;
}