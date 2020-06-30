#pragma once

#include <memory>
#include <random>

#include "CGameBase.h"
#include "../Countdown/Io.h"
#include "../Countdown/LettersGame.h"

class CLettersGame : public CGameBase<LettersGame>
{
public:
    CLettersGame();

private:
    static std::mt19937 gen;
    static std::string path;
    static std::vector<char> vowels;
    static std::vector<char> consonants;
    static std::vector<std::string> words;
};