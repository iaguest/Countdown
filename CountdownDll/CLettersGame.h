#pragma once

#include "../Countdown/LettersGame.h"

class CLettersGame
{
public:
    CLettersGame();

    ~CLettersGame();

	bool initialize(const char* input,
                    int inputSize,
                    char* output,
                    int* outputSize);

    char* getGameBoard() const;

    void run();

    char* endMessage() const;

    int getScore(const char* answer,
                 int answerSize) const;

private:
    std::mt19937 gen;
    const std::string resourcePath;
    std::vector<char> vowels;
    std::vector<char> consonants;
    std::vector<std::string> words;
    LettersGame lettersGame;
};