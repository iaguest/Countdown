//
//  io.cpp
//  countdown
//
//  Created by Ian Guest on 24/01/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#include "Io.h"

std::string Io::makeFilePath(const std::string& path, const std::string& fileName)
{
    return path + "/" + fileName;
}

std::vector<char> Io::getLetters(const std::string& path, const std::string& fileName)
{
    const std::string letterDistributionPath = makeFilePath(path, fileName);
    std::vector<char> letters;
    std::ifstream is(letterDistributionPath);
    if (is.is_open())
    {
        std::string line;
        while (std::getline(is, line))
        {
            if (line.empty())
                continue;
            const char letter = line[0];
            if (letter == '#')
                continue;
            auto sepIt = std::find(begin(line), end(line), ',');
            const int numLetters = std::stoi(std::string(++sepIt, end(line)));
            std::generate_n(std::back_inserter(letters), numLetters,
                            [&](){ return std::tolower(letter); });
        }
    }
    return letters;
}

std::vector<std::string> Io::getWords(const std::string& path, const std::string& fileName)
{
    const std::string wordsPath = makeFilePath(path, fileName);
    std::vector<std::string> words;
    std::ifstream is(wordsPath);
    if (is.is_open())
    {
        std::string line;
        while (std::getline(is, line))
            words.push_back(line);
    }
    return words;
}
