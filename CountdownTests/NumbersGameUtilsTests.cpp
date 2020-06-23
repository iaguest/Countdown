//
//  FirstCatchTest.cpp
//  countdown_tests
//
//  Created by Ian Guest on 29/01/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#include "catch.hpp"

#include <iterator>
#include <string>
#include <vector>

#include "../Countdown/NumbersGameUtils.h"

using namespace NumbersGameUtils;

constexpr double EPSILON = 1.0E-9;

TEST_CASE("tokenizeExpression splits simple expression into tokens.")
{    
    REQUIRE_THAT(std::vector<std::string>(
                     { "(", "9", "+", "99", ")", "*", "(", "1", "-", "2", "/", "32", ")" }), 
                 Catch::Equals(tokenizeExpression("(9+99)*(1-2/32)")));
}

TEST_CASE("tokenizeExpression ignores spaces.")
{
    REQUIRE_THAT(std::vector<std::string>({ "(", "9", "+", "99", ")" }), 
                 Catch::Equals(tokenizeExpression(" ( 9 + 99) ")));
}

TEST_CASE("tokenizeExpression handles empty expression.")
{
    REQUIRE_NOTHROW(tokenizeExpression(""));
}

TEST_CASE("getPostFixExpression converts trivial infix expression with one operator.")
{
    const std::vector<std::string>& result = getPostFixExpression(tokenizeExpression("3+4"));
    REQUIRE_THAT(std::vector<std::string>({"3","4","+"}), Catch::Equals(result));
}

TEST_CASE("getPostFixExpression converts simple infix expression with balanced parentheses.")
{
    const std::vector<std::string>& result = getPostFixExpression(tokenizeExpression("4+18/(9-3)"));
    
    REQUIRE_THAT(std::vector<std::string>({"4","18","9","3","-","/","+"}), Catch::Equals(result));
}

TEST_CASE("getPostFixExpression converts complicated infix expression with balanced parentheses")
{
    const std::vector<std::string>& result =
        getPostFixExpression(tokenizeExpression("((15 / (7 - (1 + 1))) * 3) - (2 + (1 + 1)) "));
    
    REQUIRE_THAT(std::vector<std::string>(
                     {"15","7","1","1","+","-","/","3","*","2","1","1","+","+","-"}),
                 Catch::Equals(result));
}

TEST_CASE("getPostFixExpression handles empty infix expression.")
{
    REQUIRE_NOTHROW(getPostFixExpression(std::vector<std::string>()));
}

TEST_CASE("tryEvaluateExpression returns correct result for trivial expression.")
{
    double result = 0;
    
    SECTION("Single value.") {
        CHECK(tryEvaluateExpression("42", result));
        REQUIRE_THAT(result, Catch::WithinRel(42.0, EPSILON));
    }
    
    SECTION("Single value with balanced parentheses.") {
        CHECK(tryEvaluateExpression("(999)", result));
        REQUIRE_THAT(result, Catch::WithinRel(999.0, EPSILON));
    }
}

TEST_CASE("tryEvaluateExpression returns correct result for simple expression.")
{
    double result;
    bool isSuccess = tryEvaluateExpression("1+2", result);
    
    CHECK(isSuccess);
    REQUIRE_THAT(result, Catch::WithinRel(3.0, EPSILON));
}

TEST_CASE("tryEvaluateExpression returns correct result for expression.")
{
    double result;
    bool isSuccess = tryEvaluateExpression("((25+8)*10)-1", result);
    
    CHECK(isSuccess);
    REQUIRE_THAT(result, Catch::WithinRel(329.0, EPSILON));
}

TEST_CASE("tryEvaluateExpression returns correct result for complex expression.")
{
    double result;
    bool isSuccess = tryEvaluateExpression("((15 / (7 - (1 + 1))) * 3) - (2 + (1 + 1)) ", result);
    
    CHECK(isSuccess);
    REQUIRE_THAT(result, Catch::WithinRel(5.0, EPSILON));
}

TEST_CASE("tryEvaluateExpression returns false for empty expression.")
{
    double result = 0;
    REQUIRE(!tryEvaluateExpression("", result));
}

TEST_CASE("tryEvaluateExpression fails for malformed expression.")
{
    double result = 0;
    
    SECTION("Insufficient arguments for operator test 1.") {
        REQUIRE(!tryEvaluateExpression("+", result));
    }
    
    SECTION("Insufficient arguments for operator test 2.") {
        REQUIRE(!tryEvaluateExpression("1+", result));
    }
    
    SECTION("Insufficient arguments for operator test 3.") {
        REQUIRE(!tryEvaluateExpression("+1", result));
    }
    
    SECTION("Unbalanced parentheses test 1.") {
        REQUIRE(!tryEvaluateExpression("1+1)", result));
    }
    
    SECTION("Unbalanced parentheses test 2.") {
        REQUIRE(!tryEvaluateExpression("(1+1", result));
    }
    
    SECTION("Unbalanced parentheses test 3.") {
        REQUIRE(!tryEvaluateExpression("((9/27 )+7))", result));
    }
    
    SECTION("Invalid operator test 1.") {
        REQUIRE(!tryEvaluateExpression("1**2", result));
    }
    
    SECTION("Invalid operator test 2.") {
        REQUIRE(!tryEvaluateExpression("1+-2", result));
    }
    
    SECTION("Invalid operator test 3.") {
        REQUIRE(!tryEvaluateExpression("3^2", result));
    }
    
    SECTION("Invalid characters.") {
        REQUIRE(!tryEvaluateExpression("bob", result));
    }
}
