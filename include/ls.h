//
// Created by Jack Gu on 12/30/21.
//

#ifndef LOGIN_SYSTEM_LS_H
#define LOGIN_SYSTEM_LS_H

#define MAX_LENGTH 64

#include <cstdio>
#include <exception>
#include <filesystem>
#include <getopt.h>
#include <iostream>
#include <sqlite3.h>

/*
 * Open the sqlite db given the filename
 * Initialize it if not exist
 */
int open_db_or_initialize(sqlite3 *db, const char *filename);
int add_user(sqlite3 *db, const char *username, const char *password, const int *id);
int check_password(sqlite3 *db, const char *username, const char *password);

#endif //LOGIN_SYSTEM_LS_H
