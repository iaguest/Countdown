//
//  ComplexExpressionsGenerator.h
//  LazyEval
//
//  Created by Ian Guest on 30/03/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#ifndef ComplexExpressionsGenerator_h
#define ComplexExpressionsGenerator_h

#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "ParenthesizedExpressionsGenerator.h"
#include "NumbersGameUtils.h"

/// <summary>
/// Generate a set of possible parenthesized expressions from the simple expression
/// </summary>
class ComplexExpressionsGenerator : public IGenerator<std::string>
{
public:
    
    ComplexExpressionsGenerator(const std::string& simpleExpression)
      : IGenerator::IGenerator(),
        simpleExpression(simpleExpression),
        maxParenPairCount(calculateMaxParenPairCount(simpleExpression))
    {
        reset();
    }
 
    void first() override {
        reset();
    }
    
    void next() override {
        parenGenPtr->next();
        if (!parenGenPtr->isDone())
            return;
        
        parenGenPtr = std::make_unique<ParenthesizedExpressionsGenerator>(simpleExpression, ++currentParenPairCount);
    }
    
    bool isDone() const override {
        return currentParenPairCount > maxParenPairCount;
    }
    
    std::string currentItem() const override {
        return parenGenPtr->currentItem();
    }
    
private:
    void reset() {
        currentParenPairCount = 1;
        parenGenPtr = std::make_unique<ParenthesizedExpressionsGenerator>(simpleExpression, currentParenPairCount);
    }
   
    std::size_t calculateMaxParenPairCount(const std::string& simpleExpression) const
    {
        const auto tokenised = NumbersGameUtils::tokenizeExpression(simpleExpression);
        return tokenised.size() >= 3 ? ((tokenised.size() - 1) / 2) - 1 : 0;
    }

private:
    const std::string simpleExpression;
    const std::size_t maxParenPairCount;
    int currentParenPairCount;
    std::unique_ptr<ParenthesizedExpressionsGenerator> parenGenPtr;
};

#endif /* ComplexExpressionsGenerator_h */
