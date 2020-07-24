//
//  GameRunner.h
//  countdown
//
//  Created by Ian Guest on 22/01/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#ifndef GameRunner_h
#define GameRunner_h

#include <vector>

#include "IGame.h"
#include "Timer.h"

class GameRunner
{
public:
    
    GameRunner(const std::vector<IGame*>& games)
      : games(games)
    {
    }

    int execute()
    {
        int score = 0;
        for (auto& game: games) {
            game->initialize(std::cout, std::cin);
            
            const std::string& startMessage = game->startMessage();
            if (!startMessage.empty())
                std::cout << startMessage << std::endl;
            
            std::cout << "[ " << game->getGameBoard() << " ]";
            
            std::cout << std::endl;
            std::cout << "Start 30 second countdown!" << std::endl;
            game->run();
            std::cout << "Times up!" << std::endl;
            
            Timer t;
            std::string answer;
            std::cout << "Enter answer: ";
            std::getline(std::cin, answer);
                      
            const double elapsed = t.elapsed();
            
            const int gameScore = game->getScore(answer, elapsed);
            if (gameScore < 0) {
                std::cout << "You took " << std::to_string(elapsed) << " seconds to answer" <<
                             " which exceeds the time limit, sorry!" << std::endl;
            }
            else {
                score += gameScore;
            }
            std::cout << "Current score: " << score << std::endl << std::endl;

            std::string endMessage = game->endMessage();
            if (!endMessage.empty())
                std::cout << game->endMessage() << std::endl << std::endl;
        }
        return score;
    }
    
private:
    
    const std::vector<IGame*>& games;
};

#endif /* GameRunner_h */
