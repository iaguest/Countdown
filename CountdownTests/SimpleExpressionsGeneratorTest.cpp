#include "catch.hpp"

#include "TestUtils.h"
#include "../Countdown/SimpleExpressionsGenerator.h"

#include <algorithm>
#include <set>
#include <string>
#include <vector>

namespace SimpleExpGenTest
{
    static const std::vector<std::string> twoNumberCaseExpectedValues{
        "1", "2", "1+2", "1-2", "1*2", "1/2", "2+1", "2-1", "2*1", "2/1"
    };
    // we only allow one division per expression
    static const std::vector<std::string> threeNumberCaseExpectedValues{
        "1","2","3","1*2","1+2","1-2","1/2","1*3","1+3","1-3","1/3","2*1","2+1","2-1",
        "2/1","2*3","2+3","2-3","2/3","3*1","3+1","3-1","3/1","3*2","3+2","3-2","3/2",
        "1*2*3","1*2+3","1*2-3","1*2/3","1+2*3","1+2+3","1+2-3","1+2/3","1-2*3","1-2+3",
        "1-2-3","1-2/3","1/2*3","1/2+3","1/2-3","1*3*2","1*3+2","1*3-2","1*3/2","1+3*2",
        "1+3+2","1+3-2","1+3/2","1-3*2","1-3+2","1-3-2","1-3/2","1/3*2","1/3+2","1/3-2",
        "2*1*3","2*1+3","2*1-3","2*1/3","2+1*3","2+1+3","2+1-3","2+1/3","2-1*3","2-1+3",
        "2-1-3","2-1/3","2/1*3","2/1+3","2/1-3","2*3*1","2*3+1","2*3-1","2*3/1","2+3*1",
        "2+3+1","2+3-1","2+3/1","2-3*1","2-3+1","2-3-1","2-3/1","2/3*1","2/3+1","2/3-1",
        "3*1*2","3*1+2","3*1-2","3*1/2","3+1*2","3+1+2","3+1-2","3+1/2","3-1*2","3-1+2",
        "3-1-2","3-1/2","3/1*2","3/1+2","3/1-2","3*2*1","3*2+1","3*2-1","3*2/1","3+2*1",
        "3+2+1","3+2-1","3+2/1","3-2*1","3-2+1","3-2-1","3-2/1","3/2*1","3/2+1","3/2-1",
    };
}

TEST_CASE("SimpleExpressionsGenerator is constructable") {
    REQUIRE_NOTHROW(SimpleExpressionsGenerator(std::vector<int>{1, 2, 3}));
}

TEST_CASE("SimpleExpressionsGenerator handles vector with single number") {
    const auto seq = std::vector<int>{ 1 };
    auto gen = SimpleExpressionsGenerator(seq);
    const auto& output = TestUtils::toResultVector(gen);

    REQUIRE(output.size() == 1);
    REQUIRE(TestUtils::containsSubset(output, std::vector<std::string>{"1"}));
}

TEST_CASE("SimpleExpressionsGenerator handles vector with two numbers") {
    const std::vector<int> seq = std::vector<int>{ 1, 2 };
    auto gen = SimpleExpressionsGenerator(seq);
    const auto& output = TestUtils::toResultVector(gen);

    REQUIRE(output.size() == SimpleExpGenTest::twoNumberCaseExpectedValues.size());
    REQUIRE(TestUtils::containsSubset(output, SimpleExpGenTest::twoNumberCaseExpectedValues));
}

TEST_CASE("SimpleExpressionsGenerator handles vector with three numbers")
{
    const std::vector<int> seq = std::vector<int>{ 1, 2, 3 };
    auto gen = SimpleExpressionsGenerator(seq);
    const auto& output = TestUtils::toResultVector(gen);

    REQUIRE(output.size() == SimpleExpGenTest::threeNumberCaseExpectedValues.size());
    REQUIRE(TestUtils::containsSubset(output, SimpleExpGenTest::threeNumberCaseExpectedValues));
}

TEST_CASE("SimpleExpressionsGenerator expressions contain no duplicates") {
    const std::vector<int> seq = std::vector<int>{ 1, 2, 3 };
    auto gen = SimpleExpressionsGenerator(seq);
    const auto& output = TestUtils::toResultVector(gen);

    const std::set<std::string> noDuplicates(output.begin(), output.end());
    REQUIRE(TestUtils::containsSubset(std::vector(noDuplicates.begin(), noDuplicates.end()), output));
}
