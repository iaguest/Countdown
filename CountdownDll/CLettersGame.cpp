#include <sstream>
#include <string>

#include "pch.h" 

#include "CLettersGame.h"

CLettersGame::CLettersGame(std::mt19937& gen,
                           const std::vector<char>& vowels,
                           const std::vector<char>& consonants,
                           const std::vector<std::string>& words)
    : lettersGame(gen, vowels, consonants, words)
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

const char* CLettersGame::getGameBoard()
{
    return lettersGame.getGameBoard().c_str();
}
