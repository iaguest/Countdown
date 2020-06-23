//
//  IGame.h
//  countdown
//
//  Created by Ian Guest on 26/01/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#ifndef IGame_h
#define IGame_h

#include <iostream>
#include <string>

class IGame
{
public:
    IGame() = default;
    virtual ~IGame() {}
    
    IGame(IGame&) = delete;
    IGame& operator=(const IGame&) = delete;
    
    // Set up for gameboard
    virtual void initialize(std::ostream& os, std::istream& is) = 0;
    // Start message related to game setup
    virtual std::string startMessage() const = 0;
    // Get the gameboard itself
    virtual std::string getGameBoard() const = 0;
    // Run the game
    virtual void run() = 0;
    // End message after game has run and answer entered
    virtual std::string endMessage() const = 0;
    // Get score for answer, taking into account answer time
    virtual int getScore(const std::string& answer,
                         const double answerTime) const = 0;
};

#endif /* IGame_h */
