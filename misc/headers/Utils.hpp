#ifndef UTILS_HPP
#define UTILS_HPP

#include <cmath>
#include <cstdint>
#include <stdexcept>
#include <string_view>

namespace ndm::utils
{

inline uint32_t ipStrToNum(std::string_view ipStr)
{
    if (ipStr.empty())
        throw std::invalid_argument("IP string is empty");

    uint32_t res {0};

    auto octetNum {0};
    auto currOctet {3};
    const auto strLen = ipStr.length();
    for (size_t i {0}; i < strLen; ++i)
    {
        const int digit = ipStr[i] - '0';
        if (0 <= digit && digit <= 9)
        {
            octetNum *= 10;
            octetNum += digit;
            continue;
        }

        if ('.' != ipStr[i])
            throw std::invalid_argument("Invalid symbol in IP string");

        if (octetNum > 255)
            throw std::invalid_argument("Wrong octet value");

        res += octetNum * std::pow(256, currOctet--);
        octetNum = 0;
    }

    res += octetNum * std::pow(256, currOctet--);

    if (currOctet != -1)
        throw std::invalid_argument("Wrong IP format");

    return res;
}
} // namespace ndm::utils

#endif // UTILS_HPP
