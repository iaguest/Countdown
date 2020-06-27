#include <random>
#include <string>
#include <vector>

#include "pch.h" 

#include "CLettersGameCaller.h"
#include "../Countdown/Io.h"

CLettersGame* CreateLettersGame()
{
    std::mt19937 gen(std::random_device{}());

    const std::string resourcePath = "./";

    std::vector<char> vowels = Io::getLetters(resourcePath, "vowels.txt");
    std::vector<char> consonants = Io::getLetters(resourcePath, "consonants.txt");
    std::vector<std::string> words = Io::getWords(resourcePath, "UK_english_truncated.txt");
    return new CLettersGame(gen, vowels, consonants, words);
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


const char* CallGetGameBoard(CLettersGame* pLettersGame)
{
    if (pLettersGame != nullptr)
    {
        pLettersGame->getGameBoard();
    }
    throw std::runtime_error("Invalid call to CallGetGameBoard.");
}