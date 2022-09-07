//
// Created by d.abramov on 06.09.2022.
//

#ifndef REDISCLIENT_STRINGUTILS_H
#define REDISCLIENT_STRINGUTILS_H


#include <vector>
#include <string>

class StringUtils {
public:
    static std::vector<std::string> split(const std::string &input, const std::string &regex);
    static std::string join(const std::vector<std::string> &vec);
};


#endif //REDISCLIENT_STRINGUTILS_H
