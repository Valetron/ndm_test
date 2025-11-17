#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstdint>
#include <string_view>
#include <string>
#include <sstream>

namespace
{
const auto g_octetsIpv4 {4};
}

namespace ndm::utils
{
inline uint32_t ipStrToNum(std::string_view ipStr)
{
    if (ipStr.empty())
        throw std::invalid_argument("IP string is empty");

    uint32_t res {0};
    const auto strLen = ipStr.length();

}
} // namespace ndm::utils

#endif // UTILS_HPP
