//
// Created by Jack Gu on 12/30/21.
//

#include "../include/ls.h"

std::unique_ptr <sqlite3> open_db_or_initialize(const char *filename) {
    // create the database object in heap; will be returned
    auto db = std::make_unique<sqlite3>();

    std::filesystem::path db_file{filename};
    bool file_exist = std::filesystem::exists(db_file);

    // try to open the db file
    // create an empty file if not exist
    {
        int err = sqlite3_open(filename, db.get());
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

        sqlite3_exec(db, create_table_query.c_str(), nullptr, nullptr, &errmsg);

        if (err != SQLITE_OK) {
            throw std::runtime_error(errmsg);
            sqlite3_free(errmsg);
        }

    }

    return db;
}