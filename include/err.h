//
// Created by Jack Gu on 12/31/21.
//

#ifndef LOGIN_SYSTEM_ERR_H
#define LOGIN_SYSTEM_ERR_H

#include <stdexcept>

namespace ls {
    struct sqlite3_error : public virtual std::runtime_error {
        using std::runtime_error::runtime_error;
    };

}

#endif //LOGIN_SYSTEM_ERR_H
