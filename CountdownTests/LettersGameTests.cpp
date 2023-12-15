//
//  LettersGameTests.cpp
//  countdown_tests
//
//  Created by Ian Guest on 11/02/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#include "catch.hpp"

#include "../Countdown/LettersGame.h"
#include "TestUtils.h"

#include <random>
#include <vector>

TEST_CASE("Validate LettersGame behavior.")
{
    // initialization
    std::mt19937 gen(1);
    std::ostringstream oss;
    std::istringstream iss;
    
    const std::vector<char> vowels{'a','e','i','o','u'};
    const std::vector<char> consonants{'p','s','t','c','h'};
    const std::vector<std::string> words{"cup", "cuppas", "push"};

    auto isVowel = [&vowels](char& c)
        { return std::find(begin(vowels), end(vowels), c) != end(vowels); };
    auto isConsonant = [&consonants](char& c)
        { return std::find(begin(consonants), end(consonants), c) != end(consonants); };
    
    SECTION("LettersGame construction success")
    {
        REQUIRE_NOTHROW(LettersGame(gen, vowels, consonants, words));
    }
    
    SECTION("Game board is initially empty.")
    {
        LettersGame game(gen, vowels, consonants, words);
        REQUIRE(game.getGameBoard().empty());
    }
    
    SECTION("Initialize returns false for fully partially initialized board")
    {
        LettersGame game(gen, vowels, consonants, words);
        iss.str("c v v v c v v v");  // one letter missing
        REQUIRE(false == game.initialize(oss, iss));
    }

    SECTION("Initialize returns true for fully initialized board")
    {
        LettersGame game(gen, vowels, consonants, words);
        iss.str("v c v v v c v v v");
        REQUIRE(true == game.initialize(oss, iss));
    }

    SECTION("Game board is filled on initialize.")
    {
        LettersGame game(gen, vowels, consonants, words);
        iss.str("c v c v c v c v c");
        
        game.initialize(oss, iss);
        
        REQUIRE_THAT("t u c u p a s u p", Catch::Equals(game.getGameBoard()));
    }
    
    SECTION("Game board can be initialized in steps.")
    {
        LettersGame game(gen, vowels, consonants, words);
        iss.str("c v c v c v c v");
        game.initialize(oss, iss);
        std::istringstream iss2("c");
        game.initialize(oss, iss2);
        REQUIRE_THAT("t u c u p a s u p", Catch::Equals(game.getGameBoard()));
    }

    SECTION("Game board has expected number of vowels and consonants after initialization.")
    {
        LettersGame game(gen, vowels, consonants, words);
        iss.str("v c v c c c v c v");
        
        game.initialize(oss, iss);
        
        auto gameBoard = TestUtils::stringToVec<char>(game.getGameBoard());
        CHECK(4 == std::count_if(begin(gameBoard), end(gameBoard),
                                 [&isVowel](auto& elem) { return isVowel(elem); }));
        REQUIRE(5 == std::count_if(begin(gameBoard), end(gameBoard),
                                   [&isConsonant](auto& elem) { return isConsonant(elem); }));
    }
    
    SECTION("Score for a 'valid' answer equals number of letters in word")
    {
        LettersGame game(gen, vowels, consonants, words);
        iss.str("c v c v c v c c c");        
        game.initialize(oss, iss);
        CHECK_THAT("t u c u p a s h p", Catch::Equals(game.getGameBoard()));
        
        // Evaluate possible words.
        game.onStartRun();
        game.onEndRun();
        
        CHECK(3 == game.getScore("cup"));
        CHECK(6 == game.getScore("cuppas"));
        REQUIRE(4 == game.getScore("push"));
    }
    
    SECTION("Score for an 'invalid' answer is zero")
    {
        LettersGame game(gen, vowels, consonants, words);
        iss.str("c v c v c v c c c");        
        game.initialize(oss, iss);
        CHECK_THAT("t u c u p a s h p", Catch::Equals(game.getGameBoard()));
  
        // Evaluate possible words.
        game.onStartRun();
        game.onEndRun();
        
        CHECK(0 == game.getScore("hopes"));  // letter missing from board
        CHECK(0 == game.getScore("soup"));  // valid letters but shape not in words list
        CHECK(0 == game.getScore("p ush")); // valid word but with erroneous space
        CHECK(0 == game.getScore("g0bb*ldeGoo&k"));
        REQUIRE(0 == game.getScore(""));
    }
}
