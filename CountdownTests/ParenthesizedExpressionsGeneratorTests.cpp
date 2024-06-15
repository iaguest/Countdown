#include "catch.hpp"

#include "TestUtils.h"
#include "../Countdown/ParenthesizedExpressionsGenerator.h"

#include <sstream>
#include <string>
#include <vector>

namespace ParenExpGenTest
{
static const std::string threeNumExpression{ "1+2+3" };
static const std::string threeNumExpressionNotAllSingleDigits{"100+20+30"};
static const std::string fourNumExpression{ "1+2+3+4" };
static const std::string fourNumExpressionNotAllSingleDigits("100+200+30+400");
}

TEST_CASE("ParenthesizedExpressionsGenerator is constructable") {
    REQUIRE_NOTHROW(ParenthesizedExpressionsGenerator(ParenExpGenTest::threeNumExpression, 1));
}

TEST_CASE("Validate parenthesized expressions for three number case with one pair of parentheses") {
    const std::vector<std::string> expected = std::vector<std::string>{ "(1+2)+3", "(1+2+3)", "1+(2+3)" };

    auto gen = ParenthesizedExpressionsGenerator(ParenExpGenTest::threeNumExpression, 1);
    const auto& output = TestUtils::toResultVector(gen);

    REQUIRE(expected.size() == output.size());
    REQUIRE(TestUtils::containsSubset(output, expected));
}

TEST_CASE("Validate parenthesized expressions for non single digits three number case with one pair of parentheses") {
    const std::vector<std::string> expected = std::vector<std::string>{ "(100+20)+30", "(100+20+30)", "100+(20+30)" };

    auto gen = ParenthesizedExpressionsGenerator(ParenExpGenTest::threeNumExpressionNotAllSingleDigits, 1);
    const auto& output = TestUtils::toResultVector(gen);

    REQUIRE(expected.size() == output.size());
    REQUIRE(TestUtils::containsSubset(output, expected));
}

TEST_CASE("Validate parenthesized expressions for four number case with one pair of parentheses") {
    const std::vector<std::string> expected = std::vector<std::string>{
        "(1+2)+3+4", "(1+2+3)+4", "(1+2+3+4)", "1+(2+3)+4", "1+(2+3+4)", "1+2+(3+4)" };

    auto gen = ParenthesizedExpressionsGenerator(ParenExpGenTest::fourNumExpression, 1);
    const auto& output = TestUtils::toResultVector(gen);

    REQUIRE(expected.size() == output.size());
    REQUIRE(TestUtils::containsSubset(output, expected));
}

TEST_CASE("Validate parenthesized expressions for non single digits four number case with one pair of parentheses") {
    const std::vector<std::string> expected = std::vector<std::string>{
        "(100+200)+30+400", "(100+200+30)+400", "(100+200+30+400)", "100+(200+30)+400", "100+(200+30+400)", "100+200+(30+400)" };

    auto gen = ParenthesizedExpressionsGenerator(ParenExpGenTest::fourNumExpressionNotAllSingleDigits, 1);
    const auto& output = TestUtils::toResultVector(gen);

    REQUIRE(expected.size() == output.size());
    REQUIRE(TestUtils::containsSubset(output, expected));
}

TEST_CASE("Validate parenthesized expressions for four number case with two pairs of parentheses") {
    const std::vector<std::string> expected = std::vector<std::string>{
        "((1+2))+3+4", "((1+2)+3)+4", "((1+2)+3+4)", "((1+2+3))+4",
        "((1+2+3)+4)", "((1+2+3+4))", "(1+(2+3))+4", "(1+(2+3)+4)",
        "(1+(2+3+4))", "(1+2+(3+4))", "1+((2+3))+4", "1+((2+3)+4)",
        "1+((2+3+4))", "1+(2+(3+4))", "1+2+((3+4))", "(1+2)+(3+4)"};

    auto gen = ParenthesizedExpressionsGenerator(ParenExpGenTest::fourNumExpression, 2);
    const auto& output = TestUtils::toResultVector(gen);

    REQUIRE(expected.size() == output.size());
    REQUIRE(TestUtils::containsSubset(output, expected));
}

TEST_CASE("Validate parenthesized expressions for non single digits four number case with two pairs of parentheses") {
    const std::vector<std::string> expected = std::vector<std::string>{
        "((100+200))+30+400", "((100+200)+30)+400", "((100+200)+30+400)", "((100+200+30))+400",
        "((100+200+30)+400)", "((100+200+30+400))", "(100+(200+30))+400", "(100+(200+30)+400)",
        "(100+(200+30+400))", "(100+200+(30+400))", "100+((200+30))+400", "100+((200+30)+400)",
        "100+((200+30+400))", "100+(200+(30+400))", "100+200+((30+400))", "(100+200)+(30+400)" };

    auto gen = ParenthesizedExpressionsGenerator(ParenExpGenTest::fourNumExpressionNotAllSingleDigits, 2);
    const auto& output = TestUtils::toResultVector(gen);

    REQUIRE(expected.size() == output.size());
    REQUIRE(TestUtils::containsSubset(output, expected));
}