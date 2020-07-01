//
//  ConundrumGame.h
//  countdown
//
//  Created by Ian Guest on 26/01/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#ifndef ConundrumGame_h
#define ConundrumGame_h

#include <string>

#include "AbstractGame.h"

class ConundrumGame : public AbstractGame<char>
{
public:
    explicit ConundrumGame(std::mt19937 gen, const std::vector<std::string>& words);
    
    bool initialize(std::ostream& os, std::istream& is) override;
    
    std::string endMessage() const override;
    
    int getScore(const std::string& answer) const override;
    
private:
    const std::vector<std::string> words;
    std::string nineLetterWord;
};

#endif /* ConundrumGame_h */
