#pragma once

#include <string>

std::string removeLeadingZerosAnd0x(const std::string &hexString) {
    std::string result = hexString;

    // Remove "0x" prefix if present
    if (result.substr(0, 2) == "0x") {
        result = result.substr(2);
    }

    // Remove leading zeros
    while (result.length() > 1 && result[0] == '0') {
        result = result.substr(1);
    }

    return result;
}
