#include "pch.h" 

#include "CGameCaller.h"


CLettersGame* CreateLettersGame()
{
    return new CLettersGame();
}

void DisposeLettersGame(CLettersGame* pLettersGame)
{
    if (pLettersGame != nullptr)
    {
        delete pLettersGame;
        pLettersGame = nullptr;
    }
}

bool InitializeLettersGame(CLettersGame* pLettersGame,
                           const char* input,
                           int inputSize,
                           char* output,
                           int* outputSize)
{
    if (pLettersGame != nullptr)
    {
        return pLettersGame->initialize(input, inputSize, output, outputSize);
    }
    throw std::runtime_error("Invalid call to CallInitialize.");
}

char* GetLettersGameStartMessage(CLettersGame* pLettersGame)
{
    if (pLettersGame != nullptr)
    {
        return pLettersGame->startMessage();
    }
    throw std::runtime_error("Invalid call to CallStartMessage.");
}

char* GetLettersGameBoard(CLettersGame* pLettersGame)
{
    if (pLettersGame != nullptr)
    {
        return pLettersGame->getGameBoard();
    }
    throw std::runtime_error("Invalid call to CallGetGameBoard.");
}

void RunLettersGame(CLettersGame* pLettersGame)
{
    if (pLettersGame != nullptr)
    {
        return pLettersGame->run();
    }
    throw std::runtime_error("Invalid call to CallRun.");
}

char* GetLettersGameEndMessage(CLettersGame* pLettersGame)
{
    if (pLettersGame != nullptr)
    {
        return pLettersGame->endMessage();
    }
    throw std::runtime_error("Invalid call to CallEndMessage.");
}

int GetLettersGameScore(CLettersGame* pLettersGame,
    const char* answer,
    int answerSize)
{
    if (pLettersGame != nullptr)
    {
        return pLettersGame->getScore(answer, answerSize);
    }
    throw std::runtime_error("Invalid call to CallGetScore.");
}