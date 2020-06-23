//
//  PermutationsGenerator.h
//  LazyEval
//
//  Created by Ian Guest on 26/03/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#ifndef PermutationsGenerator_h
#define PermutationsGenerator_h

#include <deque>
#include <queue>

#include "SubPermutationsGenerator.h"

template <class T>
class PermutationsGenerator : public IGenerator<T> {  
public:
    PermutationsGenerator(const T& sequence)
      : IGenerator<T>(), sequence(sequence)
    {
        reset();
    }

    void first() override { reset(); }
    
    void next() override {
        permutationGenerators.front().next();
        if (permutationGenerators.size() > 1 &&
            permutationGenerators.front().isDone()) {
            permutationGenerators.pop();
        }
    }
    
    bool isDone() const override {
        return permutationGenerators.empty() ||
               (permutationGenerators.size() == 1 &&
                permutationGenerators.front().isDone());
    }
    
    T currentItem() const override {
        return permutationGenerators.front().currentItem();
    }    

private:
    typedef std::queue<SubPermutationsGenerator<T>,
                       std::deque<SubPermutationsGenerator<T>>> Queue;

private:
    void reset() {
        std::sort(begin(sequence), end(sequence));
        
        Queue empty;
        std::swap(permutationGenerators, empty);
        for (int r = 0; r < sequence.size(); ++r) {
            auto gen = SubPermutationsGenerator(sequence, r+1);
            permutationGenerators.push(std::move(gen));
        }
    }
    
private:
    T sequence;
    Queue permutationGenerators;
};

#endif /* PermutationsGenerator_h */
