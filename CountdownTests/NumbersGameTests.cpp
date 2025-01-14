//
//  NumbersGameTests.cpp
//  countdown_tests
//
//  Created by Ian Guest on 07/02/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#include <random>
#include <sstream>

#include "catch.hpp"

#include "../countdown/NumbersGame.h"
#include "TestUtils.h"

constexpr double EPSILON = 1.0E-9;

TEST_CASE("Validate NumbersGame behavior.")
{
    // initialization
    std::mt19937 gen(0);
    std::ostringstream oss;
    std::istringstream iss;
    
    SECTION("NumbersGame construction succeeds.")
    {
        REQUIRE_NOTHROW(NumbersGame(gen));
    }

    SECTION("Game board initially empty.")
    {
        NumbersGame game(gen);
        REQUIRE(game.getGameBoard().empty());
    }

    SECTION("Game board filled on initialize.")
    {
        NumbersGame game(gen);
        iss.str("1");
        game.initialize(oss, iss); 
        REQUIRE_THAT("25 4 4 8 3 7", Catch::Equals(game.getGameBoard()));
    }
    
    SECTION("getTarget returns game target value")
    {
        NumbersGame game(gen);
        game.initialize(oss, iss);
        REQUIRE(593 == game.getTarget());
    }
    
    SECTION("getScore returns score of 7 when 3 away from target.")
    {
        NumbersGame game(gen);
        iss.str("2");
        game.initialize(oss, iss); 
        CHECK_THAT("50 25 4 5 10 6", Catch::Equals(game.getGameBoard()));
        CHECK(593 == game.getTarget());
        REQUIRE_THAT(game.getScore("(50+5+4)*10"), Catch::WithinRel(7.0, EPSILON));
    }

    SECTION("getScore returns score of 10 for valid answer")
    {
        NumbersGame game(gen);
        iss.str("1");
        game.initialize(oss, iss);
        CHECK_THAT("25 4 4 8 8 3", Catch::Equals(game.getGameBoard()));
        CHECK(593 == game.getTarget());
        REQUIRE_THAT(game.getScore("(25*3*8)-8+(4/4)"), Catch::WithinRel(10.0, EPSILON));
    }

    SECTION("getScore returns score of 0 when 10 or more away from target.")
    {
        NumbersGame game(gen);
        iss.str("2");
        game.initialize(oss, iss); 
        CHECK_THAT("50 25 4 1 3 7", Catch::Equals(game.getGameBoard()));
        CHECK(593 == game.getTarget());
        CHECK_THAT(game.getScore("((50*4)+1)*3"), Catch::WithinRel(0.0, EPSILON));
        REQUIRE_THAT(game.getScore("(((50*4)+1)*3)+7"), Catch::WithinRel(0.0, EPSILON));
    }
    
    SECTION("getScore returns 0 for invalid answers.")
    {
        NumbersGame game(gen);
        iss.str("4");
        game.initialize(oss, iss);
        CHECK(593 == game.getTarget());
        // empty expression
        CHECK_THAT(game.getScore(""), Catch::WithinRel(0.0, EPSILON));
        // number not in gameboard
        CHECK_THAT(game.getScore("593"), Catch::WithinRel(0.0, EPSILON));
        // invalid expression
        CHECK_THAT(game.getScore("+/-100"), Catch::WithinRel(0.0, EPSILON));
    }
    
    SECTION("startMessage includes target value.")
    {
        NumbersGame game(gen);
        game.initialize(oss, iss);
        CHECK(593 == game.getTarget());

        REQUIRE(game.startMessage().find("593") != std::string::npos);
    }
    
    SECTION("picking 3 large numbers yields a gameboard with 3 numbers greater than 10")
    {
        NumbersGame game(gen);
        iss.str("3");
        game.initialize(oss, iss);
        auto gameBoard = TestUtils::stringToVec<std::string>(game.getGameBoard());
        REQUIRE(3 == std::count_if(begin(gameBoard), end(gameBoard),
                                   [](std::string& elem) { return std::stoi(elem) > 10; }));
    }
    
    SECTION("picking 0 large numbers yields a gameboard with no numbers larger than 10")
    {
        NumbersGame game(gen);
        game.initialize(oss, iss);
        auto gameBoard = TestUtils::stringToVec<std::string>(game.getGameBoard());
        REQUIRE(0 == std::count_if(begin(gameBoard), end(gameBoard),
                                   [](std::string& elem) { return std::stoi(elem) > 10; }));
    }
}
