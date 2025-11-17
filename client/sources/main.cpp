#include <string>
#include <cstdint>
#include <iostream>

#include <spdlog/spdlog.h>
#include <boost/program_options.hpp>

namespace bpo = boost::program_options;

int main(int argc, char** argv)
{
    spdlog::set_pattern("[%T](%l): %v");

    try
    {
        bpo::options_description desc("Allowed options");
        desc.add_options()
            ("help,h", "Print help message")
            ("protocol,p", bpo::value<std::string>()->required(), "IP protocol: TCP or UDP")
            ("address", bpo::value<std::string>(), "Server address")
            ("port", bpo::value<uint16_t>(), "Server port")
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
    }
    catch (...)
    {
    }

    return 0;
}
