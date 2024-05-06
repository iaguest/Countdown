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

/// <summary>
/// Generates all "possible" parenthesized and non parenthesized
/// expressions based on the number sequence. This includes 
/// sub expressions that do not use all of the available numbers.
/// </summary>
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

        if (complexGenPtr == nullptr) {
            const auto simpleExpression = simpleGen.currentItem();
            if (!NumbersGameUtils::isIntegerNumber(simpleExpression)) {
                complexGenPtr = std::make_unique<ComplexExpressionsGenerator>(simpleExpression);
            }
            else {
                simpleGen.next();
            }

            return;
        }

        complexGenPtr->next();
        if (complexGenPtr->isDone()) {
            complexGenPtr = nullptr;
            simpleGen.next();
        }
    };
    
    bool isDone() const override {
        return simpleGen.isDone();
    }
    
    std::string currentItem() const override {
        return complexGenPtr == nullptr ? simpleGen.currentItem() : complexGenPtr->currentItem();
    }

private:
    void reset() {
        simpleGen.first();
        complexGenPtr = nullptr;
    }
    
private:
    SimpleExpressionsGenerator simpleGen;
    std::unique_ptr<ComplexExpressionsGenerator> complexGenPtr;
};

#endif /* ExpressionsGenerator_h */
