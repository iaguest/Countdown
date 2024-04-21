#include "catch.hpp"

#include "TestUtils.h"
#include "../Countdown/ParenthesizedExpressionsGenerator.h"

#include <sstream>
#include <string>
#include <vector>

namespace ParenthesizedExpressionsGeneratorTest
{

static const std::vector<std::string> threeNumExpression { "", "1", "+", "2", "+", "3", "" };

static const std::vector<std::string> fourNumExpression{ "", "1", "+", "2", "+", "3", "+", "4", "" };

std::vector<std::string> toResultStringVector(ParenthesizedExpressionsGenerator& gen) {
    std::vector<std::string> output;
    for (gen.first(); !gen.isDone(); gen.next())
    {
        std::vector<std::string> current = gen.currentItem();
        std::ostringstream os;
        for (const auto& item : current)
            os << item;
        output.push_back(os.str());
    }

    return output;
}

}

TEST_CASE("ParenthesizedExpressionsGenerator is constructable") {
    REQUIRE_NOTHROW(ParenthesizedExpressionsGenerator(ParenthesizedExpressionsGeneratorTest::threeNumExpression));
}

TEST_CASE("Validate parenthesized expressions generated in three number case") {
    const std::vector<std::string> expected = std::vector<std::string>{ "(1+2)+3", "(1+2+3)", "1+(2+3)" };

    auto gen = ParenthesizedExpressionsGenerator(ParenthesizedExpressionsGeneratorTest::threeNumExpression);
    const auto& output = ParenthesizedExpressionsGeneratorTest::toResultStringVector(gen);

    REQUIRE(TestUtils::containsSubset(output, expected));
}

TEST_CASE("Validate parenthesized expressions generated in four number case") {
    const std::vector<std::string> expected = std::vector<std::string>{ "(1+2)+3+4", "(1+2+3)+4", "(1+2+3+4)", "1+(2+3)+4", "1+(2+3+4)", "1+2+(3+4)" };

    auto gen = ParenthesizedExpressionsGenerator(ParenthesizedExpressionsGeneratorTest::fourNumExpression);
    const auto& output = ParenthesizedExpressionsGeneratorTest::toResultStringVector(gen);

    REQUIRE(TestUtils::containsSubset(output, expected));
}
