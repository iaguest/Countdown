//
//  LettersGame.cpp
//  countdown
//
//  Created by Ian Guest on 24/01/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#include <algorithm>
#include <cctype>
#include <random>
#include <sstream>

#include "Io.h"
#include "LettersGame.h"

namespace
{
const std::size_t lettersBoardSize = 9;
const int maxInitializationTime = 60;

char getSingleCharacterInput(std::istream& is)
{
    char c;
    is >> c;
    is.clear();
    is.ignore();
    return std::tolower(c);
}

}   // end namespace


LettersGame::LettersGame(std::mt19937 gen,
                         const std::vector<char>& vowels,
                         const std::vector<char>& consonants,
                         const std::vector<std::string>& words)
  : AbstractGame(gen),
    vowels(vowels),
    consonants(consonants),
    words(words),
    isInitializationTimeOut(false)
{
}

bool LettersGame::initialize(std::ostream& os, std::istream& is)
{
    while (gameBoard.size() != lettersBoardSize && !is.eof())
    {
        os << "Vowel(v)/Consonant(c)? ";
        const char charIn = getSingleCharacterInput(is);

        if (initializationTimer == nullptr) {
            initializationTimer = std::make_unique<Timer>();
        }

        char charOut;
        if (charIn == 'v' || charIn == 'V') {
            int randomVowelIndex =
                std::uniform_int_distribution<>(0, static_cast<int>(vowels.size() - 1))(gen);
            charOut = vowels.at(randomVowelIndex);;
        }
        else {
            int randomConsonantIndex =
                std::uniform_int_distribution<>(0, static_cast<int>(consonants.size() - 1))(gen);
            charOut = consonants.at(randomConsonantIndex);
        }
        gameBoard.push_back(charOut);
        os << charOut << std::endl;
    }
    
    solutionWords.clear();

    isInitializationTimeOut = initializationTimer->elapsed() > maxInitializationTime;

    return gameBoard.size() == lettersBoardSize;
}

void LettersGame::onStartRun()
{
    solverThread = std::thread(
        [this]()
        {
            solutionWords = getSolutionWords(words, gameBoard);
            std::sort(begin(solutionWords), end(solutionWords));
            std::stable_sort(begin(solutionWords), end(solutionWords),
                             [](const auto& elem1, const auto elem2) { return elem1.size() < elem2.size(); });
        });
}

void LettersGame::onEndRun()
{
    solverThread.join();
}

int LettersGame::getScore(const std::string& answer) const
{
    if (!isInitializationTimeOut &&
        std::find(begin(solutionWords), end(solutionWords), answer) != end(solutionWords))
    {
        return static_cast<int>(answer.size());
    }
    
    return 0;
}

std::vector<std::string> LettersGame::getSolutionWords(const std::vector<std::string>& words,
                                                       std::vector<char> gameBoard) const
{
    std::vector<std::string> solutionWords;
    std::sort(begin(gameBoard), end(gameBoard));
    for (const auto& word: words)
    {
        std::string wordCopy = word;
        std::sort(begin(wordCopy), end(wordCopy));
        if (std::includes(begin(gameBoard), end(gameBoard), begin(wordCopy), end(wordCopy)))
            solutionWords.push_back(word);
    }
    return solutionWords;
}

std::string LettersGame::endMessage() const
{
    std::stringstream ss;

    if (isInitializationTimeOut) {
        ss << "You took longer than " << std::to_string(maxInitializationTime) <<
            " seconds to pick your letters, so score is zero!" << std::endl <<
            std::endl;
    }

    ss << "Possible words are: ";
    const int maxWords = 5;
    auto possibleWords = (solutionWords.size() < maxWords)
        ? solutionWords
        : std::vector(rbegin(solutionWords), rbegin(solutionWords) + maxWords);
    for (const auto& word: possibleWords)
        ss << word << " ";

    return ss.str();
}
