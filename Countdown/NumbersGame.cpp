//
//  NumbersGame.cpp
//  countdown
//
//  Created by Ian Guest on 24/01/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#include <array>
#include <iostream>
#include <random>
#include <regex>
#include <string>

#include "NumbersGame.h"
#include "NumbersGameUtils.h"

namespace {

constexpr int numbersBoardSize = 6;
constexpr int minTarget = 100;
constexpr int maxTarget = 999;
std::array largeNumbers{ 25, 50, 75, 100 };
std::array smallNumbers{ 1 , 1 , 2 , 2 , 3 , 3 , 4 , 4 , 5 , 5 , 6 , 6 , 7 , 7 , 8 , 8 , 9 , 9 , 10 , 10 };

int getSingleIntegerInputOrDefault(std::istream& is, int intDefault = 0)
{
    std::string line;
    std::getline(is, line);
    
    try {
        return std::stoi(line);
    }
    catch (std::invalid_argument&) {
    }
    catch (std::out_of_range&) {
    }
    
    return intDefault;
}

}  // end namespace


NumbersGame::NumbersGame(std::mt19937& gen)
  : AbstractGame(gen)
{
}

void NumbersGame::initialize(std::ostream& os, std::istream& is)
{
    target = std::uniform_int_distribution<>(minTarget, maxTarget)(gen); 
    
    os << "Enter number of large numbers (0->4): ";
    int numLarge = getSingleIntegerInputOrDefault(is);
    
    std::shuffle(begin(smallNumbers), end(smallNumbers), gen);

    std::sample(rbegin(largeNumbers), rend(largeNumbers), std::back_inserter(gameBoard),
                numLarge, gen);
    std::sample(smallNumbers.begin(), smallNumbers.end(), std::back_inserter(gameBoard),
                numbersBoardSize - numLarge, gen);
    
    expGen = std::make_unique<ExpressionsGenerator>(gameBoard);
    
    isRunning = false;
    
    bestScore = 0;
}

void NumbersGame::onStartRun()
{
    isRunning = true;
    
    solverThread = std::thread(
        [this]()
        {
            while (isRunning) {
                expGen->next();
                auto currentItem = expGen->currentItem();
                int score = getScore(currentItem);
                if (score > bestScore) {
                    bestScore = score;
                    bestSolution = currentItem;
                }
            }
        });
}

void NumbersGame::onEndRun()
{
    isRunning = false;
    solverThread.join();
}

std::string NumbersGame::startMessage() const
{
    return std::string("Target is: " + std::to_string(target));
}

std::string NumbersGame::endMessage() const
{
    if (bestScore == 0)
        return std::string();
    return "Best solver score: " + std::to_string(bestScore) + " with " + bestSolution;
}

int NumbersGame::getScore(const std::string& answer) const
{
    double value;
    if (validNumbersInAnswer(answer) &&
        NumbersGameUtils::tryEvaluateExpression(answer, value))
    {
        double abs_diff = abs(target - value);
        return abs_diff < 10 ? 10 - abs_diff : 0;
    }
    return 0;
}

int NumbersGame::maxAnswerTime() const
{
    return 30;
}

int NumbersGame::getTarget() const
{
    if (target >= minTarget && target <= maxTarget)
        return target;
    throw std::runtime_error("NumbersGame is uninitialized.");
}

bool NumbersGame::validNumbersInAnswer(const std::string& answer) const
{
    typedef std::sregex_iterator regex_iter;
    
    std::vector<int> answer_nums;
    std::regex re("\\d+");
    for (auto i = regex_iter(begin(answer), end(answer), re); i != regex_iter(); ++i)
        answer_nums.push_back(std::stoi(i->str())); 
    std::sort(begin(answer_nums), end(answer_nums));
    
    std::vector<int> gameBoardCopy(begin(gameBoard), end(gameBoard));
    std::sort(begin(gameBoardCopy), end(gameBoardCopy));
    
    std::vector<int> diffs;
    std::set_difference(begin(answer_nums), end(answer_nums), begin(gameBoardCopy), end(gameBoardCopy),                         std::back_inserter(diffs));
    
    return diffs.empty();
}
