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
};