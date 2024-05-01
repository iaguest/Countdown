#include "catch.hpp"

#include "TestUtils.h"
#include "../Countdown/ParenthesizedExpressionsGenerator.h"

#include <sstream>
#include <string>
#include <vector>

namespace ParenExpGenTest
{

static const std::string threeNumExpression{ "1+2+3" };

static const std::string fourNumExpression{ "1+2+3+4" };

}

TEST_CASE("ParenthesizedExpressionsGenerator is constructable") {
    REQUIRE_NOTHROW(ParenthesizedExpressionsGenerator(ParenExpGenTest::threeNumExpression, 1));
}

TEST_CASE("Validate parenthesized expressions generated in three number case") {
    const std::vector<std::string> expected = std::vector<std::string>{ "(1+2)+3", "(1+2+3)", "1+(2+3)" };

    auto gen = ParenthesizedExpressionsGenerator(ParenExpGenTest::threeNumExpression, 1);
    const auto& output = TestUtils::toResultVector(gen);

    REQUIRE(expected.size() == output.size());
    REQUIRE(TestUtils::containsSubset(output, expected));
}

TEST_CASE("Validate parenthesized expressions generated in four number case") {
    const std::vector<std::string> expected = std::vector<std::string>{
        "(1+2)+3+4", "(1+2+3)+4", "(1+2+3+4)", "1+(2+3)+4", "1+(2+3+4)", "1+2+(3+4)" };

    auto gen = ParenthesizedExpressionsGenerator(ParenExpGenTest::fourNumExpression, 1);
    const auto& output = TestUtils::toResultVector(gen);

    REQUIRE(expected.size() == output.size());
    REQUIRE(TestUtils::containsSubset(output, expected));
}
