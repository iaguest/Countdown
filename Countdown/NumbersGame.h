//
//  NumbersGame.hpp
//  countdown
//
//  Created by Ian Guest on 24/01/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#ifndef NumbersGame_hpp
#define NumbersGame_hpp

#include <memory>
#include <thread>

#include "AbstractGame.h"
#include "ExpressionsGenerator.h"

class ExpressionsGenerator;

class NumbersGame : public AbstractGame<int>
{
public:
    explicit NumbersGame(std::mt19937 gen);

    bool initialize(std::ostream& os, std::istream& is) override;
    
    void onStartRun() override;
    
    void onEndRun() override;
    
    std::string startMessage() const override;
    
    std::string endMessage() const override;

    int getScore(const std::string& answer) const override;
    
    int getTarget() const;

private:
    
    int maxAnswerTime() const override;
    
    bool validNumbersInAnswer(const std::string& answer) const;
    
private:
    int target;
    std::unique_ptr<ExpressionsGenerator> expGen;
    bool isRunning;
    std::thread solverThread;
    int bestScore;
    std::string bestSolution;
};


#endif /* NumbersGame_hpp */
