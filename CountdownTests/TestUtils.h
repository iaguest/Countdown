//
//  TestUtils.hpp
//  countdown_tests
//
//  Created by Ian Guest on 11/02/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#ifndef TestUtils_hpp
#define TestUtils_hpp

#include <string>
#include <vector>

namespace TestUtils {

template <typename T>
std::vector<T> stringToVec(const std::string& str)
{
    std::vector<T> tokens;
    std::istringstream ss(str);
    T token;
    while (ss >> token)
        tokens.push_back(token);
    return tokens;
}

template <class T>
bool containsSubset(const T& source, const T& target) {
    T source_copy(begin(source), end(source));
    T target_copy(begin(target), end(target));
    std::sort(begin(source_copy), end(source_copy));
    std::sort(begin(target_copy), end(target_copy));
    return std::includes(begin(source_copy), end(source_copy),
        begin(target_copy), end(target_copy));
}

}

#endif /* TestUtils_hpp */
