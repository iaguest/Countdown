#include <iostream>
#include <random>
#include <sstream>
#include <string>

#include "pch.h" 

#include "CLettersGame.h"
#include "../Countdown/Io.h"


CLettersGame::CLettersGame() :
    gen(std::random_device{}()),
    resourcePath("./"),
    vowels(Io::getLetters(resourcePath, "vowels.txt")),
    consonants(Io::getLetters(resourcePath, "consonants.txt")),
    words(Io::getWords(resourcePath, "UK_english_truncated.txt")),
    lettersGame(gen, vowels, consonants, words)
{
}

CLettersGame::~CLettersGame()
{
}

bool CLettersGame::initialize(const char* input,
                              int inputSize,
                              char* output,
                              int* outputSize)
{
    if (input == nullptr || output == nullptr || outputSize == nullptr)
        throw std::runtime_error("Unexpected null pointers.");

    std::istringstream is(std::string(input, inputSize));
    std::ostringstream os;
    const bool isInitialized = lettersGame.initialize(os, is);
    const std::string outStr(os.str());

    if (outStr.size() > *outputSize)
        throw std::runtime_error("Output buffer overrun encountered.");

    std::copy(begin(outStr), end(outStr), output);
    (*outputSize) = outStr.size();

    return isInitialized;
}

char* CLettersGame::getGameBoard()
{
    const std::string str = lettersGame.getGameBoard();
    const std::size_t cstrSize = str.length() + 1;
    char* cstr = new char[cstrSize];
    strcpy_s(cstr, cstrSize, str.c_str());
    return cstr;
}
