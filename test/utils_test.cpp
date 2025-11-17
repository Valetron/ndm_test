#include <utility>
#include <string>
#include <cstdint>
#include <limits>

#include <gtest/gtest.h>

#include <Utils.hpp>

namespace ndm::utils
{

struct TestUtilsIpConverter : public testing::TestWithParam<std::tuple<std::string, bool, uint32_t>> {};
TEST_P(TestUtilsIpConverter, ipStrToNumTest)
{
    const auto [strIp, expectException, expectIpNum] = GetParam();
    if (expectException)
    {
        EXPECT_THROW(ipStrToNum(strIp), std::exception);
    }
    else
    {
        const auto res = ipStrToNum(strIp);
        EXPECT_EQ(res, expectIpNum);
    }
}
INSTANTIATE_TEST_SUITE_P(UtilsTest, TestUtilsIpConverter, testing::Values(
    std::make_tuple("", true, 0),
    std::make_tuple("a.b.c.d", true, 0),
    std::make_tuple("1234", true, 0),
    std::make_tuple("1.2.3", true, 0),
    std::make_tuple("1.2.3.q", true, 0),
    std::make_tuple("127.0.0.1", false, 2130706433),
    std::make_tuple("255.255.255.255", false, std::numeric_limits<uint32_t>::max()),
    std::make_tuple("0.0.0.0", false, std::numeric_limits<uint32_t>::min()),
    std::make_tuple("1.2.3.4", false, 16909060),
    std::make_tuple("192.168.0.1", false, 3232235521)
));

} // namespace ndm::utils
