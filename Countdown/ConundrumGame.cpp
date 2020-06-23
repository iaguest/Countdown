//
//  ConundrumGame.cpp
//  countdown
//
//  Created by Ian Guest on 26/01/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#include <algorithm>
#include <cassert>
#include <iterator>

#include "ConundrumGame.h"

namespace
{
    const int conundrumBoardSize = 9;
}

ConundrumGame::ConundrumGame(std::mt19937& gen,
                             const std::vector<std::string>& words)
  : AbstractGame(gen), words(words)
{
}

void ConundrumGame::initialize(std::ostream& os, std::istream& ios)
{
    std::vector<std::string> nineLetterWords;
    std::copy_if(begin(words), end(words), std::back_inserter(nineLetterWords),
             [](const auto& elem) { return elem.size() == conundrumBoardSize; } );
    
    assert (!nineLetterWords.empty());
    
    int randomIndex = std::uniform_int_distribution<>(0, static_cast<int>(nineLetterWords.size()-1))(gen);
    nineLetterWord = nineLetterWords[randomIndex];
    
    std::string randomWordCopy(begin(nineLetterWord), end(nineLetterWord));
    std::shuffle(begin(randomWordCopy), end(randomWordCopy), gen);
    std::copy(begin(randomWordCopy), end(randomWordCopy), std::back_inserter(gameBoard));
}

std::string ConundrumGame::endMessage() const
{
    return std::string("The correct word was " + nineLetterWord);
}

int ConundrumGame::getScore(const std::string& answer) const
{
    // additional size check needed in MSVC(?!)
    return (answer.size() == nineLetterWord.size() &&
            std::equal(begin(nineLetterWord), end(nineLetterWord), begin(answer)))
        ? 10
        : 0;
}
