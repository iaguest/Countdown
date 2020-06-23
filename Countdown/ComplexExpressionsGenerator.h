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
#include <string>
#include <vector>

#include "ParenthesizedExpressionsGenerator.h"
#include "NumbersGameUtils.h"

class ComplexExpressionsGenerator : public IGenerator<std::string>
{
public:
    
    ComplexExpressionsGenerator(const std::vector<std::string>& simpleExpressionStrings)
      : IGenerator::IGenerator(),
        simpleExpressionStrings(simpleExpressionStrings),
        maxIterations(maxAllowableIterations(simpleExpressionStrings))
    {
        reset();
    }
    
    void first() override {
        reset();
    }
    
    void next() override {
        newExpressions.push_back(parenGenPtr->currentItem());
        
        parenGenPtr->next();
        if (!parenGenPtr->isDone())
            return;
        
        expressionIndex += 1;
        if (expressionIndex > maxExpressionIndex) {
            expressionIndex = 0;
            iterations += 1;
            expressions = newExpressions;
            newExpressions.clear();
            maxExpressionIndex = expressions.size() - 1;
        }
        
        parenGenPtr = std::make_unique<ParenthesizedExpressionsGenerator>(expressions.at(expressionIndex));
    }
    
    bool isDone() const override {
        return iterations >= maxIterations;
    }
    
    std::string currentItem() const override {
        const auto& current = parenGenPtr->currentItem();
        std::ostringstream os;
        for (const auto& item: current)
            os << item;
        return os.str();
    }
    
private:
    void reset() {
        expressions.clear();
        for (const auto& simpleExpression: simpleExpressionStrings)
            expressions.push_back(tokenizeExpression(simpleExpression));
        newExpressions.clear();
        iterations = 0;
        maxExpressionIndex = expressions.size() - 1;
        expressionIndex = 0;
        parenGenPtr = std::make_unique<ParenthesizedExpressionsGenerator>(expressions.front());
    }
   
    std::vector<std::string> tokenizeExpression(const std::string& expression) const {
        std::vector<std::string> tokenized{""};
        for (auto& item: NumbersGameUtils::tokenizeExpression(expression))
             tokenized.push_back(item);
        tokenized.push_back("");
        return tokenized;
    }
    
    std::size_t maxAllowableIterations(const std::vector<std::string>& expressionStrings) const
    {
        std::size_t maxOperatorCount = 0;
        for (const auto& s: expressionStrings) {
            const auto& tokenized = tokenizeExpression(s);
            const std::size_t tokensSize = tokenized.size();
            maxOperatorCount = (tokensSize > 3) ? std::max(maxOperatorCount, ((tokensSize - 3) / 2)) : maxOperatorCount;
        }
        return maxOperatorCount - 1;
    }
    
private:
    const std::vector<std::string>& simpleExpressionStrings;
    std::vector<std::vector<std::string>> expressions;
    std::vector<std::vector<std::string>> newExpressions;
    const std::size_t maxIterations;
    std::size_t iterations;
    std::size_t maxExpressionIndex;
    std::size_t expressionIndex;
    std::unique_ptr<ParenthesizedExpressionsGenerator> parenGenPtr;
};

#endif /* ComplexExpressionsGenerator_h */
