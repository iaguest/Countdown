//
//  AbstractGame.h
//  countdown
//
//  Created by Ian Guest on 22/01/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#ifndef AbstractGame_h
#define AbstractGame_h

#include <chrono>
#include <random>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include "IGame.h"
#include "Timer.h"

template <typename T>
class AbstractGame : public IGame
{
public:
    AbstractGame(std::mt19937 gen)
    : gen(gen)
    {
    }
    std::string startMessage() const override { return std::string(); };
    std::string getGameBoard() const override;
    virtual void onStartRun() { };
    // 30 second wait, optionally interruptable
    void run() override;
    virtual void onEndRun() { };
    std::string endMessage() const override { return std::string(); };
    // Returns -1 if answer time too long
    int getScore(const std::string& answer, const double answerTime) const override;
    virtual int getScore(const std::string& answer) const = 0;
    
private:
    virtual bool allowInterrupts() const { return false; };
    virtual int maxAnswerTime() const { return 10; };
    
protected:
    std::mt19937 gen; //Standard mersenne_twister_engine
    std::vector<T> gameBoard;
};

template <typename T>
int AbstractGame<T>::getScore(const std::string& answer, const double answerTime) const
{
    if (answerTime > maxAnswerTime())
        return -1;
    
    return getScore(answer);
}

template <typename T>
std::string AbstractGame<T>::getGameBoard() const
{
    std::stringstream board;
    std::for_each(begin(gameBoard), end(gameBoard),
                  [&board](const auto& elem){ board << elem << " "; });
    std::string boardStr = board.str();
    return boardStr.empty() ? boardStr : std::string(begin(boardStr), --end(boardStr));
}

template<typename T>
void AbstractGame<T>::run()
{
    onStartRun();
    
    Timer t1;
    bool isInterruptable = allowInterrupts();
    while (t1.elapsed() < 30)
    {
        if (isInterruptable) //&& anyKeyPress)
          break;
        std::this_thread::sleep_for (std::chrono::seconds(1));
    }

    onEndRun();
}

#endif /* AbstractGame_h */
