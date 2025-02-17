#include "catch.hpp"

#include "TestUtils.h"
#include "../Countdown/ComplexExpressionsGenerator.h"

#include <set>
#include <sstream>
#include <string>
#include <vector>

namespace ComplexExpGenTest
{
    static const std::string threeNumExpression{"1*2*3"};
    static const std::vector<std::string> threeNumExpressionResults = std::vector<std::string>{
        "(1*2*3)", "(1*2)*3", "1*(2*3)",
    };
    static const std::string fourNumExpression{ "1+2+3+4"};
    static const std::vector<std::string> fourNumExpressionResults = std::vector<std::string>{
        "((1+2))+3+4", "((1+2+3))+4", "((1+2+3+4))", "1+((2+3+4))", "1+2+((3+4))", "1+((2+3))+4",
        "((1+2)+3)+4", "((1+2)+3+4)",  "((1+2+3)+4)", "(1+(2+3))+4", "(1+(2+3)+4)", "(1+(2+3+4))",
        "(1+2)+(3+4)",  "1+(2+(3+4))", "(1+2+(3+4))", "1+((2+3)+4)", "(1+2)+3+4", "(1+2+3)+4",
        "(1+2+3+4)", "1+(2+3)+4", "1+(2+3+4)",  "1+2+(3+4)", };
}

TEST_CASE("ComplexExpressionsGenerator is constructable") {
    REQUIRE_NOTHROW(ComplexExpressionsGenerator("1+2"));
}

TEST_CASE("Validate complex expressions generated for single three number expression") {

    auto gen = ComplexExpressionsGenerator(ComplexExpGenTest::threeNumExpression);

    const auto& output = TestUtils::toResultVector(gen);

    REQUIRE(ComplexExpGenTest::threeNumExpressionResults.size() == output.size());
    REQUIRE(TestUtils::containsSubset(output, ComplexExpGenTest::threeNumExpressionResults));
}

TEST_CASE("Validate complex expressions contain no duplicates") {
    auto gen = ComplexExpressionsGenerator(ComplexExpGenTest::fourNumExpression);

    const auto& output = TestUtils::toResultVector(gen);

    const std::set<std::string> noDuplicates(output.begin(), output.end());
    REQUIRE(TestUtils::containsSubset(std::vector(noDuplicates.begin(), noDuplicates.end()), output));
}

TEST_CASE("Validate complex expressions generated for single four number expression") {

    auto gen = ComplexExpressionsGenerator(ComplexExpGenTest::fourNumExpression);

    auto output = TestUtils::toResultVector(gen);

    REQUIRE(ComplexExpGenTest::fourNumExpressionResults.size() == output.size());
    REQUIRE(TestUtils::containsSubset(output, ComplexExpGenTest::fourNumExpressionResults));
}

TEST_CASE("Complex expressions generator handles five number expression")
{
    auto gen = ComplexExpressionsGenerator("1+2+3+4+5");

    REQUIRE_NOTHROW(TestUtils::toResultVector(gen));
}

TEST_CASE("Complex expressions generator handles six number expression")
{
    auto gen = ComplexExpressionsGenerator("1+2+3+4+5+6");

    REQUIRE_NOTHROW(TestUtils::toResultVector(gen));
}
