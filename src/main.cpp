//
// Created by Jack Gu on 12/30/21.
//

#include "../include/ls.h"

int main(int argc, char **argv) {
    const char *db_file = "example.db";

    // parse command line arguments
    while (true) {
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
            default:
                break;
        }
    }

    std::clog << "Data will write to " << db_file << std::endl;

    auto cm = ls::CredentialManager(db_file);

    // infinite loop until termination
    while (0 == ls::prompt(&cm));

    return 0;
}
