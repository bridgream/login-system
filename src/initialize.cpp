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
                "'_id'	INTEGER NOT NULL UNIQUE,"
                "'username'	TEXT NOT NULL UNIQUE,"
                "'password'	TEXT NOT NULL,"
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