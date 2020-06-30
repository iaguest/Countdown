#pragma once

#include "CGameBase.h"
#include "../Countdown/Io.h"
#include "../Countdown/LettersGame.h"

class CLettersGame : public CGameBase<LettersGame>
{
public:
    CLettersGame() :
        gen(std::random_device{}()),
        resourcePath("./"),
        vowels(Io::getLetters(resourcePath, "vowels.txt")),
        consonants(Io::getLetters(resourcePath, "consonants.txt")),
        words(Io::getWords(resourcePath, "UK_english_truncated.txt"))
    {
        pGame = std::make_unique<LettersGame>(gen, vowels, consonants, words);
    }

private:
    std::mt19937 gen;
    const std::string resourcePath;
    std::vector<char> vowels;
    std::vector<char> consonants;
    std::vector<std::string> words;
};