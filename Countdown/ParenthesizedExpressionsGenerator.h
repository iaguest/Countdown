//
//  ParenthesizedExpressionsGenerator.h
//  LazyEval
//
//  Created by Ian Guest on 01/04/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#ifndef ParenthesizedExpressionsGenerator_h
#define ParenthesizedExpressionsGenerator_h

#include <string>
#include <vector>

#include "IGenerator.h"

// Return the parenthesized permutations of an input expression achieved through adding a single pair of 
// opening and closing brackets.
class ParenthesizedExpressionsGenerator : public IGenerator<std::vector<std::string>>
{
public:
    ParenthesizedExpressionsGenerator(const std::vector<std::string>& tokenizedExpression)
      : IGenerator::IGenerator(),
        expression(tokenizedExpression),
        expressionSize(tokenizedExpression.size())
    {
        reset();
    }
    
    void first() override
    {
        reset();
    }
    
    void next() override
    {
        rightIter += 2;
        if (rightIter >= expressionSize) {
            leftIter += 2;
            rightIter = leftIter + 4;
        }
    }
    
    bool isDone() const override
    {
        return (leftIter >= (expressionSize - 2) || rightIter >= expressionSize);
    }
    
    std::vector<std::string> currentItem() const override
    {
        auto current = expression;
        current[leftIter] += "(";
        current[rightIter] = ")" + current[rightIter];
        return current;
    }    
    
private:
    
    void reset()
    {
        leftIter = 0;
        rightIter = leftIter + 4;
    }
    
private:
    const std::vector<std::string> expression;
    const std::size_t expressionSize;
    std::size_t leftIter;
    std::size_t rightIter;
};

#endif /* ParenthesizedExpressionsGenerator_h */
