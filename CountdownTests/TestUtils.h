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

}

#endif /* TestUtils_hpp */
