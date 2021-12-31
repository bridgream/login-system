//
// Created by Jack Gu on 12/30/21.
//

#include "../include/ls.h"

int open_db_or_initialize(sqlite3 *db, const char *filename) {
    std::filesystem::path db_file{filename};
    bool file_exist = std::filesystem::exists(db_file);

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
                "'_id'	INTEGER IDENTITY(1,1),"
                "'username'	VARCHAR(" + std::to_string(MAX_LENGTH) + ") NOT NULL UNIQUE,"
                "'password'	VARCHAR(" + std::to_string(MAX_LENGTH) + ") NOT NULL UNIQUE,"
                "PRIMARY KEY('_id') );"
        );
        char *errmsg;

        int err = sqlite3_exec(db, create_table_query.c_str(), nullptr, nullptr, &errmsg);

        if (err != SQLITE_OK) {
            throw std::runtime_error(errmsg);
            sqlite3_free(errmsg);
        }

    }

    return 0;
}

int add_user(sqlite3 *db, const std::string &username, const std::string &password) {
    std::string insert_command(
            "INSERT INTO credentials VALUES (" + username + ", " + password + ")"
    );
    char *errmsg;

    int err = sqlite3_exec(db, insert_command.c_str(), nullptr, nullptr, &errmsg);

    if (err != SQLITE_OK) {
        throw std::runtime_error(errmsg);
    }

    return 0;
}
