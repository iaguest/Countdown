//
//  SimpleExpressionsGenerator.h
//  LazyEval
//
//  Created by Ian Guest on 26/03/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#ifndef SimpleExpressionsGenerator_h
#define SimpleExpressionsGenerator_h

#include <iterator>
#include <sstream>
#include <vector>

#include "PermutationsGenerator.h"

class SimpleExpressionsGenerator : public IGenerator<std::string>
{
public:
    SimpleExpressionsGenerator(const std::vector<int>& numberSequence)
      : IGenerator::IGenerator(),
        numGen(NumberSequenceGenerator(numberSequence)),
        opGen(makeOperatorSequenceGenerator(0))
    {
        reset();
    }
    
    void first() override {
        reset();
    }
    
    void next() override {
        opGen.next();
        if (opGen.isDone() && !numGen.isDone()) {
            numGen.next();
            if (!numGen.isDone())
            {
                opGen = makeOperatorSequenceGenerator(numGen.currentItem().size() - 1);
            }
            return;
        }
    }
    
    bool isDone() const override {
        return numGen.isDone();
    }
    
    std::string currentItem() const override {
        std::ostringstream os;
        const auto& numSeq = numGen.currentItem();
        const auto& opSeq = opGen.currentItem();
        for (auto i = 0; i != opSeq.size(); ++i)
            os << numSeq.at(i) << opSeq.at(i);
        os << numSeq.back();
        return os.str();
    }

private:
    // Solve using permutations from this subsequence - NB: we limit the available options for
    // performance reasons with the brute force solution approach.
    inline static const std::vector<char> opChars {'+', '+', '-', '-', '*', '*', '/'};
    
private:
    typedef PermutationsGenerator<std::vector<int>> NumberSequenceGenerator;
    typedef SubPermutationsGenerator<std::vector<char>> OperatorSequenceGenerator;
    
private:
    void reset() {
        numGen.first();
        opGen.first();
        expressions.clear();
    }

    OperatorSequenceGenerator makeOperatorSequenceGenerator(const std::size_t numOps) const
    {
        return OperatorSequenceGenerator(opChars, numOps);
    }
    
private:
    NumberSequenceGenerator numGen;
    OperatorSequenceGenerator opGen;
    std::vector<std::vector<std::string>> expressions;
};

#endif /* SimpleExpressionsGenerator_h */
