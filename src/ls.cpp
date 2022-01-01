//
// Created by Jack Gu on 12/30/21.
//

#include "../include/err.h"
#include "../include/ls.h"

namespace ls {
    CredentialManager::CredentialManager(const std::string &filename) {
        std::filesystem::path f{filename};
        if (not std::filesystem::exists(f)) {
            std::clog << "Database not exist. Creating a new file. " << std::endl;
        }

        // a new sqlite3 db file will be created if not exist
        int rc = sqlite3_open(filename.c_str(), &db);
        if (rc != SQLITE_OK) {
            // no need to clean up
            throw std::runtime_error("Failed to open database. ");
        }

        // try to create a new table if not exist in the opened file
        const char *create_table_query =
                "CREATE TABLE IF NOT EXISTS  'credentials' ("
                "'_id' INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                "'username'	TEXT NOT NULL UNIQUE,"
                "'password'	TEXT);";
        char *errmsg;

        rc = sqlite3_exec(db, create_table_query, nullptr, nullptr, &errmsg);
        if (rc != SQLITE_OK) {
            // should I close the database here?
            sqlite3_close(db);
            throw sqlite3_error(errmsg);
        }

        // done initializing database; nothing else is needed
    }

    CredentialManager::~CredentialManager() {
        int rc = sqlite3_close(db);
        // let's hope it won't fail
        assert(SQLITE_OK == rc);
    }

    std::optional<std::string> CredentialManager::maybe_get_password(const std::string &username) {
        sqlite3_stmt *stmt = nullptr;
        std::string query(
                "SELECT * FROM credentials WHERE username = ?;"
        );

        // prepare the statement
        int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            throw sqlite3_error(sqlite3_errmsg(db));
        }

        // blob the query with desired username
        assert(username.length() < INT_MAX);
        // TODO: fix casting from string::length to int
        rc = sqlite3_bind_text(stmt, 1, username.c_str(), username.length(), nullptr);
        if (rc != SQLITE_OK) {
            const char *err_msg = sqlite3_errmsg(db);
            sqlite3_finalize(stmt);
            throw sqlite3_error(err_msg);
        }

        rc = sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if (rc == SQLITE_DONE) {
            // not found in the database
            return {};
        } else if (rc == SQLITE_ROW) {
            // found the record
            // TODO: SIGILL here
            const unsigned char *raw_password = sqlite3_column_text(stmt, 2);
            return std::string(reinterpret_cast<char *>(const_cast<unsigned char *>(raw_password)));
        } else {
            const char *err_msg = sqlite3_errmsg(db);
            throw sqlite3_error(err_msg);
        }
    }

    void CredentialManager::add_user(const std::string &username, const std::string &password) {
        sqlite3_stmt *stmt = nullptr;
        std::string query(
                "INSERT INTO credentials (username, password) VALUES (?, ?);"
        );

        // prepare the statement
        int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            throw sqlite3_error(sqlite3_errmsg(db));
        }

        // blob the query with desired username and password
        assert(username.length() < INT_MAX);
        // TODO: fix casting from string::length to int
        rc = sqlite3_bind_text(stmt, 1, username.c_str(), username.length(), nullptr);
        if (rc != SQLITE_OK) {
            const char *err_msg = sqlite3_errmsg(db);
            sqlite3_finalize(stmt);
            throw sqlite3_error(err_msg);
        }

        assert(password.length() < INT_MAX);
        rc = sqlite3_bind_text(stmt, 2, password.c_str(), password.length(), nullptr);
        if (rc != SQLITE_OK) {
            const char *err_msg = sqlite3_errmsg(db);
            sqlite3_finalize(stmt);
            throw sqlite3_error(err_msg);
        }

        rc = sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if (rc != SQLITE_DONE) {
            const char *err_msg = sqlite3_errmsg(db);
            throw sqlite3_error(err_msg);
        }
    }

    int prompt(CredentialManager *cm) {
        std::string username, password;
        char mode;
        std::optional<std::string> maybe_true_password;

        std::cout << "Enter 1 to register, 2 to login, 3 to terminate. " << std::endl;
        std::cin >> mode;

        switch (mode) {
            case '3':
                // terminate
                return 1;
            case '1':
                // register
                std::cout << "Username: ";
                std::cin >> username;
                if (cm->maybe_get_password(username).has_value()) {
                    std::cerr << "User exists. " << std::endl;
                    break;
                }

                std::cout << "Password: ";
                std::cin >> password;
                cm->add_user(username, password);
                std::clog << "Insert success. " << std::endl;
                break;
            case '2':
                // login
                std::cout << "Username: ";
                std::cin >> username;
                std::cout << "Password: ";
                std::cin >> password;
                maybe_true_password = cm->maybe_get_password(username);
                if (maybe_true_password.has_value() and (password == maybe_true_password.value())) {
                    std::clog << "Login success. " << std::endl;
                } else {
                    std::cerr << "Login failed. " << std::endl;
                    if (not maybe_true_password.has_value()) {
                        std::clog << "User not exist. " << std::endl;
                    } else if (password == maybe_true_password.value()) {
                        std::clog << "Incorrect password. " << std::endl;
                    }
                }
                break;
            default:
                std::cout << "Unrecognized mode: " << mode << std::endl;
                break;
        }
        return 0;
    }
}
