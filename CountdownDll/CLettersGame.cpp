#include <memory>
#include <random>

#include "pch.h" 

#include "../Countdown/Io.h"
#include "CLettersGame.h"

CLettersGame::CLettersGame()
    : CGameBase(std::make_unique<LettersGame>(std::mt19937(std::random_device{}()),
                                              Io::getLetters("./", "vowels.txt"),
                                              Io::getLetters("./", "consonants.txt"),
                                              Io::getWords("./", "UK_english_truncated.txt")))
{
}
