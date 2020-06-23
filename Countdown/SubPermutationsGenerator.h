//
//  SubPermutationsGenerator.h
//  LazyEval
//
//  Created by Ian Guest on 25/03/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#ifndef SubPermutationsGenerator_h
#define SubPermutationsGenerator_h

#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "IGenerator.h"
#include "Timer.h"

// Return successive r-length permutations of elements in the sequence.
template <class T>
class SubPermutationsGenerator : public IGenerator<T>
{
public:
    SubPermutationsGenerator(const T& sequence, std::size_t r)
      : IGenerator<T>(),
        sequence(sequence),
        r(r),
        cacheKey(makeCacheKey(sequence, r)),
        isUseCachedValues(cache.find(cacheKey) != end(cache))
    {
        assert (r <= sequence.size());
        
        reset();
    }
    
    void first() override {
        reset();
    }
    
    void next() override {
        
        if (isUseCachedValues) {
            cacheValueIndex += 1;
            return;
        }
        
        valuesToCache.push_back(currentItem());
        
        while (true) {
            hasNext = std::next_permutation(begin(sequence), end(sequence));
            const std::string& sequenceStr = currentItemString();
            if (isDone() || seen.find(sequenceStr) == end(seen)) {
                seen.insert(sequenceStr);
                break;
            }
        }
        
        if (isDone())
            cache[cacheKey] = valuesToCache;        
    }
    
    bool isDone() const override {
        
        if (isUseCachedValues)
            return cacheValueIndex >= cache[cacheKey].size();
        
        return !hasNext;
    }
    
    T currentItem() const override {
        
        if (isUseCachedValues) {
            return cache[cacheKey][cacheValueIndex];
        }
        
        return T(begin(sequence), begin(sequence) + r);
    }
    
private:
    void reset() {

        if (isUseCachedValues) {
            cacheValueIndex = 0;
            valuesToCache.clear();
            return;
        }
        
        std::sort(begin(sequence), end(sequence));
        hasNext = sequence.size();
        seen.clear();
        seen.insert(currentItemString());
    }
    
    std::string currentItemString() const {
        const T& seq = currentItem();
        return std::string(begin(seq), end(seq));
    }
    
    std::string makeCacheKey(const T& seq, std::size_t r) {
        std::ostringstream os;
        os << std::string(begin(seq), end(seq)) << "_" << r;
        return os.str();
    }

private:
    static std::map<std::string, std::vector<T>> cache;
    
private:
    T sequence;
    std::size_t r;
    
    std::string cacheKey;
    bool isUseCachedValues;  // member holding values, just null if no cache available?
    std::size_t cacheValueIndex;
    std::vector<T> valuesToCache;
    
    bool hasNext;
    std::unordered_set<std::string> seen;
    
    int count{0};
};

template <class T>
std::map<std::string, std::vector<T>>
SubPermutationsGenerator<T>::cache = std::map<std::string, std::vector<T>>();

#endif /* SubPermutationsGenerator_h */
