#include <string>
#include <cstdint>
#include <iostream>
#include <algorithm>

#include <spdlog/spdlog.h>
#include <boost/program_options.hpp>

#include "Utils.hpp"

namespace bpo = boost::program_options;
using namespace ndm::utils;

int main(int argc, char** argv)
{
    spdlog::set_pattern("[%T](%l): %v");

    try
    {
        std::string protocol {};
        std::string serverAddrStr {};
        uint16_t serverPort {0};

        bpo::options_description desc("Allowed options");
        desc.add_options()
            ("help,h", "Print help message")
            ("protocol,p", bpo::value<std::string>(&protocol)->required(), "IP protocol: TCP or UDP")
            ("address", bpo::value<std::string>(&serverAddrStr)->required(), "Server address")
            ("port", bpo::value<uint16_t>(&serverPort)->required(), "Server port")
            ("debug,d", bpo::bool_switch(), "Enable debug logs");

        bpo::variables_map vm;
        bpo::store(bpo::parse_command_line(argc, argv, desc), vm);

        if (vm.count("help") || argc < 2)
        {
            desc.print(std::cerr, 0);
            return 0;
        }

        bpo::notify(vm);

        if (vm.contains("debug"))
            spdlog::set_level(spdlog::level::debug);

        const auto serverAddr = ipStrToNum(serverAddrStr);
        std::for_each(protocol.begin(), protocol.end(), [](auto& ch){ ch = std::tolower(ch); });

        if ("udp" == protocol)
        {
            // TODO: udp socket
        }
        else if ("tcp" == protocol)
        {
            // TODO: tcp socket
        }
        else
        {
            throw std::invalid_argument("Wrong protocol value");
        }
    }
    catch (const bpo::error& ex)
    {
        SPDLOG_ERROR("Command line args error: {}", ex.what());
        return 1;
    }
    catch (const std::invalid_argument& ex)
    {
        SPDLOG_ERROR("Failed to validate input params: {}", ex.what());
        return 1;
    }
    catch (const std::exception& ex)
    {
        SPDLOG_ERROR("Error occured: {}", ex.what());
        return 1;
    }

    return 0;
}
