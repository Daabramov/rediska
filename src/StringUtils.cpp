//
// Created by d.abramov on 06.09.2022.
//

#include <regex>
#include <numeric>
#include "StringUtils.h"

std::vector<std::string> StringUtils::split(const std::string &input, const std::string &regex) {
    std::regex re(regex);
    std::sregex_token_iterator
            first{input.begin(), input.end(), re, -1},
            last;
    return {first, last};
}

std::string StringUtils::join(std::vector<std::string> const &strings)
{
    if (strings.empty()) {
        return std::string();
    }
    auto delim = " ";
    auto result = std::accumulate(strings.begin() + 1, strings.end(), strings[0],
                           [&delim](std::string x, std::string y) {
                               return x + delim + y;
                           }
    );

    return result;
}
