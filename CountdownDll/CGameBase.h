#pragma once

#include <algorithm>
#include <memory>
#include <sstream>
#include <string>

template <class T>
class CGameBase
{
public:
    CGameBase(): pGame(nullptr)
    {
    }

    bool initialize(const char* input,
                    int inputSize,
                    char* output,
                    int* outputSize)
    {
        if (input == nullptr || output == nullptr || outputSize == nullptr)
            throw std::runtime_error("Unexpected null pointers.");

        std::istringstream is(std::string(input, inputSize));
        std::ostringstream os;
        const bool isInitialized = pGame->initialize(os, is);
        const std::string outStr(os.str());

        if (outStr.size() > *outputSize)
            throw std::runtime_error("Output buffer overrun encountered.");

        std::copy(begin(outStr), end(outStr), output);
        (*outputSize) = outStr.size();

        return isInitialized;
    }

    char* getGameBoard() const
    {
        return makeStringCopy(pGame->getGameBoard());
    }

    void run()
    {
        pGame->run();
    }

    char* endMessage() const
    {
        return makeStringCopy(pGame->endMessage());
    }

    int getScore(const char* answer, int answerSize) const
    {
        const std::string s(answer, answerSize);
        return pGame->getScore(s);
    }

private:

    // Copy string to a newly allocated char pointer (owned by caller).
    char* makeStringCopy(const std::string& str) const
    {
        const std::size_t cstrSize = str.length() + 1;
        char* cstr = new char[cstrSize];
        strcpy_s(cstr, cstrSize, str.c_str());
        return cstr;
    }

protected:
    std::unique_ptr<T> pGame;
};

