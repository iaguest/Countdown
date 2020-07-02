#include "pch.h" 

#include "CGameCaller.h"

// LettersGame

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
        return;
    }
    throw std::runtime_error("Invalid call.");
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
    throw std::runtime_error("Invalid call.");
}

char* GetLettersGameStartMessage(CLettersGame* pLettersGame)
{
    if (pLettersGame != nullptr)
    {
        return pLettersGame->startMessage();
    }
    throw std::runtime_error("Invalid call.");
}

char* GetLettersGameBoard(CLettersGame* pLettersGame)
{
    if (pLettersGame != nullptr)
    {
        return pLettersGame->getGameBoard();
    }
    throw std::runtime_error("Invalid call.");
}

void RunLettersGame(CLettersGame* pLettersGame)
{
    if (pLettersGame != nullptr)
    {
        return pLettersGame->run();
    }
    throw std::runtime_error("Invalid call.");
}

char* GetLettersGameEndMessage(CLettersGame* pLettersGame)
{
    if (pLettersGame != nullptr)
    {
        return pLettersGame->endMessage();
    }
    throw std::runtime_error("Invalid call.");
}

int GetLettersGameScore(CLettersGame* pLettersGame,
    const char* answer,
    int answerSize)
{
    if (pLettersGame != nullptr)
    {
        return pLettersGame->getScore(answer, answerSize);
    }
    throw std::runtime_error("Invalid call.");
}

// NumbersGame

CNumbersGame* CreateNumbersGame()
{
    return new CNumbersGame();
}

void DisposeNumbersGame(CNumbersGame* pNumbersGame)
{
    if (pNumbersGame != nullptr)
    {
        delete pNumbersGame;
        pNumbersGame = nullptr;
        return;
    }
    throw std::runtime_error("Invalid call.");
}

bool InitializeNumbersGame(CNumbersGame* pNumbersGame,
    const char* input,
    int inputSize,
    char* output,
    int* outputSize)
{
    if (pNumbersGame != nullptr)
    {
        return pNumbersGame->initialize(input, inputSize, output, outputSize);
    }
    throw std::runtime_error("Invalid call.");
}

char* GetNumbersGameStartMessage(CNumbersGame* pNumbersGame)
{
    if (pNumbersGame != nullptr)
    {
        return pNumbersGame->startMessage();
    }
    throw std::runtime_error("Invalid call.");
}

char* GetNumbersGameBoard(CNumbersGame* pNumbersGame)
{
    if (pNumbersGame != nullptr)
    {
        return pNumbersGame->getGameBoard();
    }
    throw std::runtime_error("Invalid call.");
}

void RunNumbersGame(CNumbersGame* pNumbersGame)
{
    if (pNumbersGame != nullptr)
    {
        return pNumbersGame->run();
    }
    throw std::runtime_error("Invalid call.");
}

char* GetNumbersGameEndMessage(CNumbersGame* pNumbersGame)
{
    if (pNumbersGame != nullptr)
    {
        return pNumbersGame->endMessage();
    }
    throw std::runtime_error("Invalid call.");
}

int GetNumbersGameScore(CNumbersGame* pNumbersGame,
    const char* answer,
    int answerSize)
{
    if (pNumbersGame != nullptr)
    {
        return pNumbersGame->getScore(answer, answerSize);
    }
    throw std::runtime_error("Invalid call.");
}

// ConundrumGame

CConundrumGame* CreateConundrumGame()
{
    return new CConundrumGame();
}

void DisposeConundrumGame(CConundrumGame* pConundrumGame)
{
    if (pConundrumGame != nullptr)
    {
        delete pConundrumGame;
        pConundrumGame = nullptr;
        return;
    }
    throw std::runtime_error("Invalid call.");
}

bool InitializeConundrumGame(CConundrumGame* pConundrumGame,
    const char* input,
    int inputSize,
    char* output,
    int* outputSize)
{
    if (pConundrumGame != nullptr)
    {
        return pConundrumGame->initialize(input, inputSize, output, outputSize);
    }
    throw std::runtime_error("Invalid call.");
}

char* GetConundrumGameStartMessage(CConundrumGame* pConundrumGame)
{
    if (pConundrumGame != nullptr)
    {
        return pConundrumGame->startMessage();
    }
    throw std::runtime_error("Invalid call.");
}

char* GetConundrumGameBoard(CConundrumGame* pConundrumGame)
{
    if (pConundrumGame != nullptr)
    {
        return pConundrumGame->getGameBoard();
    }
    throw std::runtime_error("Invalid call.");
}

void RunConundrumGame(CConundrumGame* pConundrumGame)
{
    if (pConundrumGame != nullptr)
    {
        return pConundrumGame->run();
    }
    throw std::runtime_error("Invalid call.");
}

char* GetConundrumGameEndMessage(CConundrumGame* pConundrumGame)
{
    if (pConundrumGame != nullptr)
    {
        return pConundrumGame->endMessage();
    }
    throw std::runtime_error("Invalid call.");
}

int GetConundrumGameScore(CConundrumGame* pConundrumGame,
    const char* answer,
    int answerSize)
{
    if (pConundrumGame != nullptr)
    {
        return pConundrumGame->getScore(answer, answerSize);
    }
    throw std::runtime_error("Invalid call.");
}
