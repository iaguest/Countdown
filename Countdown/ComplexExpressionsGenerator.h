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

class ComplexExpressionsGenerator : public IGenerator<std::string>
{
public:
    
    ComplexExpressionsGenerator(const std::vector<std::string>& simpleExpression)
      : IGenerator::IGenerator(),
        simpleExpression(simpleExpression),
        maxIterations(maxAllowableIterations(simpleExpression))
    {
        if (!canHandleExpression(simpleExpression))
        {
            throw new std::invalid_argument("Invalid expression");
        }

        reset();
    }
 
    static bool canHandleExpression(const std::vector<std::string>& expression)
    {
        return expression.size() > MIN_EXPRESSION_SIZE;
    }

    void first() override {
        reset();
    }
    
    void next() override {
        parenGenPtr->next();
        if (!parenGenPtr->isDone())
            return;
        
        iteration += 1;

        parenGenPtr = std::make_unique<ParenthesizedExpressionsGenerator>(expressions.front(), iteration);
    }
    
    bool isDone() const override {
        return iteration > maxIterations;
    }
    
    std::string currentItem() const override {
        return parenGenPtr->currentItem();
    }
    
private:
    void reset() {
        iteration = 1;
        expressions.clear();
        auto current = simpleExpression;
        std::ostringstream os;
         for (const auto& item: current)
             os << item;

        expressions.push_back(os.str());

        parenGenPtr = std::make_unique<ParenthesizedExpressionsGenerator>(expressions.front(), iteration);
    }
   
    std::size_t maxAllowableIterations(const std::vector<std::string>& expression) const
    {
        return ((expression.size() - 3) / 2) - 1;
    }
    
private:
    static constexpr int MIN_EXPRESSION_SIZE = 3;
    const std::vector<std::string> simpleExpression;
    std::vector<std::string> expressions;
    const std::size_t maxIterations;
    int iteration;
    std::unique_ptr<ParenthesizedExpressionsGenerator> parenGenPtr;
};

#endif /* ComplexExpressionsGenerator_h */
