#include <memory>
#include <random>

#include "pch.h"
#include "CNumbersGame.h"

CNumbersGame::CNumbersGame()
    : CGameBase(std::make_unique<NumbersGame>(std::mt19937(std::random_device{}())))
{
}