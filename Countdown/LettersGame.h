//
//  LettersGame.h
//  countdown
//
//  Created by Ian Guest on 22/01/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#ifndef LettersGame_h
#define LettersGame_h

#include <string>
#include <thread>
#include <vector>

#include "AbstractGame.h"

class LettersGame : public AbstractGame<char>
{
public:
    explicit LettersGame(std::mt19937& gen,
                         const std::vector<char>& vowels,
                         const std::vector<char>& consonants,
                         const std::vector<std::string>& words);
    
    bool initialize(std::ostream& os, std::istream& is) override;

    void onStartRun() override;
    
    void onEndRun() override;    
    
    std::string endMessage() const override;
    
    int getScore(const std::string& answer) const override;

private:
    
    std::vector<std::string> getSolutionWords(const std::vector<std::string>& words,
                                              std::vector<char> lettersBoard) const;
private:
    std::vector<char> vowels;
    std::vector<char> consonants;
    const std::vector<std::string>& words;
    std::thread solverThread;
    std::vector<std::string> solutionWords;
};

#endif /* LettersGame_h */
