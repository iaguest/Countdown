#include <iostream>
#include <random>
#include <sstream>
#include <string>

#include "pch.h" 

#include "CLettersGame.h"
#include "../Countdown/Io.h"

namespace
{

// Copy string to a newly allocated char pointer (owned by caller).
char* makeStringCopy(const std::string& str)
{
    const std::size_t cstrSize = str.length() + 1;
    char* cstr = new char[cstrSize];
    strcpy_s(cstr, cstrSize, str.c_str());
    return cstr;
}

}  // end namespace


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

char* CLettersGame::getGameBoard() const
{
    return makeStringCopy(lettersGame.getGameBoard());
}

void CLettersGame::run()
{
    lettersGame.run();
}

char* CLettersGame::endMessage() const
{
    return makeStringCopy(lettersGame.endMessage());
}

int CLettersGame::getScore(const char* answer,
                           int answerSize) const
{
    const std::string s(answer, answerSize);
    return lettersGame.getScore(s);
}