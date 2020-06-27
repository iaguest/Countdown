#pragma once

#include "../Countdown/LettersGame.h"

class CLettersGame
{
public:
    CLettersGame(std::mt19937& gen,
                 const std::vector<char>& vowels,
                 const std::vector<char>& consonants,
                 const std::vector<std::string>& words);
    ~CLettersGame();

	bool initialize(const char* input,
                    int inputSize,
                    char* output,
                    int* outputSize);

    const char* getGameBoard();

private:
    LettersGame lettersGame;
};