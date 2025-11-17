#include <string>
#include <cstdint>
#include <iostream>

#include <spdlog/spdlog.h>
#include <boost/program_options.hpp>

#include "Utils.hpp"

namespace bpo = boost::program_options;

int main(int argc, char** argv)
{
    spdlog::set_pattern("[%T](%l): %v");

    try
    {
        std::string protocol {};
        std::string serverAddr {};
        uint16_t serverPort {0};

        bpo::options_description desc("Allowed options");
        desc.add_options()
            ("help,h", "Print help message")
            ("protocol,p", bpo::value<std::string>(&protocol)->required(), "IP protocol: TCP or UDP")
            ("address", bpo::value<std::string>(&serverAddr)->required(), "Server address")
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

        if (vm.contains("address"))
        {
            // const auto r = ndm::client::ipStrToNum(serverAddr);
        }

        if (vm.contains("debug"))
            spdlog::set_level(spdlog::level::debug);

        SPDLOG_CRITICAL(serverAddr);
    }
    catch (const bpo::error& ex)
    {
        SPDLOG_ERROR("Command line args error: {}", ex.what());
        return 1;
    }
    catch (const std::exception& ex)
    {
        SPDLOG_ERROR("Error occured: {}", ex.what());
        return 1;
    }

    return 0;
}
