#include "pch.h" 

#include "CLettersGameCaller.h"


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

bool CallInitialize(CLettersGame* pLettersGame,
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

char* CallGetGameBoard(CLettersGame* pLettersGame)
{
    if (pLettersGame != nullptr)
    {
        return pLettersGame->getGameBoard();
    }
    throw std::runtime_error("Invalid call to CallGetGameBoard.");
}

void CallRun(CLettersGame* pLettersGame)
{
    if (pLettersGame != nullptr)
    {
        return pLettersGame->run();
    }
    throw std::runtime_error("Invalid call to CallRun.");
}

char* CallEndMessage(CLettersGame* pLettersGame)
{
    if (pLettersGame != nullptr)
    {
        return pLettersGame->endMessage();
    }
    throw std::runtime_error("Invalid call to CallEndMessage.");
}

int CallGetScore(CLettersGame* pLettersGame,
    const char* answer,
    int answerSize)
{
    if (pLettersGame != nullptr)
    {
        return pLettersGame->getScore(answer, answerSize);
    }
    throw std::runtime_error("Invalid call to CallGetScore.");
}