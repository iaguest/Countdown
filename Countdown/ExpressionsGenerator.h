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
        if (!simpleGen.isDone()) {
            simpleExpressions.push_back(simpleGen.currentItem());
            simpleGen.next();
            if (simpleGen.isDone()) {
                std::vector<std::string> filteredExpressions;
                std::copy_if(begin(simpleExpressions), end(simpleExpressions), std::back_inserter(filteredExpressions),
                             [&](const auto& elem) { return !NumbersGameUtils::isIntegerNumber(elem); });
                
                complexGenPtr = std::make_unique<ComplexExpressionsGenerator>(filteredExpressions);
            }
            return;
        }
        complexGenPtr->next();
    };
    
    bool isDone() const override {
        return complexGenPtr != nullptr && complexGenPtr->isDone();
    }
    
    std::string currentItem() const override {
        return complexGenPtr == nullptr ? simpleGen.currentItem() : complexGenPtr->currentItem();
    }

private:
    void reset() {
        simpleGen.first();
        simpleExpressions.clear();
        complexGenPtr.reset(nullptr);
    }
    
private:
    SimpleExpressionsGenerator simpleGen;
    std::vector<std::string> simpleExpressions;
    std::unique_ptr<ComplexExpressionsGenerator> complexGenPtr;
};

#endif /* ExpressionsGenerator_h */
