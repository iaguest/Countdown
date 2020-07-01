#include <memory>
#include <random>

#include "pch.h"
#include "../Countdown/Io.h"
#include "CConundrumGame.h"

CConundrumGame::CConundrumGame()
    : CGameBase(std::make_unique<ConundrumGame>(std::mt19937(std::random_device{}()),
                                                Io::getWords("./", "UK_english_truncated.txt")))
{
}