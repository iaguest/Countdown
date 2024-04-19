//
//  ExpressionsGenerator.h
//  LazyEval
//
//  Created by Ian Guest on 06/04/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#ifndef ExpressionsGenerator_h
#define ExpressionsGenerator_h

#include <iterator>
#include <memory>
#include <string>
#include <vector>

#include "IGenerator.h"
#include "SimpleExpressionsGenerator.h"
#include "ComplexExpressionsGenerator.h"
#include "NumbersGameUtils.h"

class ExpressionsGenerator : public IGenerator<std::string>
{
public:
    
    ExpressionsGenerator(const std::vector<int>& numberSequence)
      : IGenerator(),
        simpleGen(numberSequence)
    {
        reset();
    }
    
    void first() override {
        reset();
    }
    
    void next() override {

        if (complexGenPtr == nullptr)
        {
            auto tokenized = tokenizeExpression(simpleGen.currentItem());
            if (ComplexExpressionsGenerator::canHandleExpression(tokenized))
            {
                complexGenPtr = std::make_unique<ComplexExpressionsGenerator>(tokenized);
            }
            else
            {
                simpleGen.next();
            }

            return;
        }

        if (complexGenPtr->isDone())
        {
            complexGenPtr = nullptr;
            simpleGen.next();
            return;
        }

        complexGenPtr->next();
    };
    
    bool isDone() const override {
        return simpleGen.isDone();
    }
    
    std::string currentItem() const override {
        return complexGenPtr == nullptr ? simpleGen.currentItem() : complexGenPtr->currentItem();
    }

    std::vector<std::string> tokenizeExpression(const std::string& expression) const {
        std::vector<std::string> tokenized{ "" };
        for (auto& item : NumbersGameUtils::tokenizeExpression(expression))
            tokenized.push_back(item);
        tokenized.push_back("");
        return tokenized;
    }

private:
    void reset() {
        simpleGen.first();
        complexGenPtr.reset(nullptr);
    }
    
private:
    SimpleExpressionsGenerator simpleGen;
    std::unique_ptr<ComplexExpressionsGenerator> complexGenPtr;
};

#endif /* ExpressionsGenerator_h */
