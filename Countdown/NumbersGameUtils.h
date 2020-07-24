//
//  NumbersGameUtils.hpp
//  countdown
//
//  Created by Ian Guest on 29/01/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#ifndef NumbersGameUtils_hpp
#define NumbersGameUtils_hpp

#include <deque>
#include <functional>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>

namespace NumbersGameUtils
{

std::vector<std::string> tokenizeExpression(const std::string& expression);

std::vector<std::string> getPostFixExpression(const std::vector<std::string>& inFixExpression);

//Returns false if the current running total becomes negative or involves a fraction.
bool tryEvaluateExpression(const std::string& expression, double& result);

bool isIntegerNumber(const std::string& s);

}

#endif /* NumbersGameUtils_hpp */
