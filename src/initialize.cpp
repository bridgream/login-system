//
// Created by Jack Gu on 12/30/21.
//

#include "../include/ls.h"

int open_db_or_initialize(sqlite3 *&db, const char *filename) {
    // try to open the db file
    // create an empty file if not exist
    {
        int err = sqlite3_open(filename, &db);
        if (err != SQLITE_OK) {
            throw std::runtime_error("Database Open Failed");
        }
    }


    {
        std::string create_table_query(
                "CREATE TABLE IF NOT EXISTS  'credentials' ("
                "'_id' INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                "'username'	TEXT NOT NULL UNIQUE,"
                "'password'	TEXT);"
        );
        char *errmsg;

        int err = sqlite3_exec(db, create_table_query.c_str(), nullptr, nullptr, &errmsg);

        if (err != SQLITE_OK) {
            throw std::runtime_error(errmsg);
        }

    }

    return 0;
}

int add_user(sqlite3 *db, const std::string &username, const std::string &password) {
    std::string insert_command(
            "INSERT INTO credentials (username, password) VALUES ('" + username + "', '" + password + "');"
    );

    std::clog << insert_command << std::endl;

    char *errmsg;

    int err = sqlite3_exec(db, insert_command.c_str(), nullptr, nullptr, &errmsg);

    if (err != SQLITE_OK) {
        throw std::runtime_error(errmsg);
    }

    return 0;
}

int check_password(sqlite3 *db, const std::string &username, const std::string &password) {
    std::string select_command(
            "SELECT * FROM credentials WHERE username = '" + username + "';"
    );

    std::clog << select_command << std::endl;

    char *errmsg;

    int err = sqlite3_exec(
            db,
            select_command.c_str(),
            check_callback,
            nullptr,
            &errmsg);

    if (err != SQLITE_OK) {
        throw std::runtime_error(errmsg);
    }

    return 0;

}
