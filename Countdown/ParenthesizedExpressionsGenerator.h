//
//  ParenthesizedExpressionsGenerator.h
//  LazyEval
//
//  Created by Ian Guest on 01/04/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#ifndef ParenthesizedExpressionsGenerator_h
#define ParenthesizedExpressionsGenerator_h

#include <regex>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

#include "IGenerator.h"

// Return the parenthesized permutations of an input expression achieved through adding a single pair of 
// opening and closing brackets.
class ParenthesizedExpressionsGenerator : public IGenerator<std::string>
{
public:
    ParenthesizedExpressionsGenerator(const std::string& simpleExpression,
                                      const int numParenPairs)
      : IGenerator::IGenerator(),
        simpleExpression(simpleExpression),
        nextExpressionIndex(0)
    {
        std::set<std::string> expressions;
        generateExpressions(simpleExpression, numParenPairs, expressions);
        parenthesizedExpressions = std::vector<std::string>(expressions.begin(), expressions.end());

        reset();
    }
    
    void first() override
    {
        reset();
    }
    
    void next() override
    {
        nextExpressionIndex += 1;
    }
    
    bool isDone() const override
    {
        return nextExpressionIndex >= parenthesizedExpressions.size();
    }
    
    std::string currentItem() const override
    {
        return parenthesizedExpressions.at(nextExpressionIndex);
    }
    
private:
    
    static std::string insertParentheses(const std::string& input, int openIndex, int closeIndex) {
        if (openIndex > closeIndex || openIndex < 0 || closeIndex > input.length()) {
            // Handle error: indices are out of order or out of bounds
            throw std::out_of_range("Error: Invalid indices for parentheses insertion.");
        }

        std::string result = input;
        result.insert(closeIndex + 1, ")");
        result.insert(openIndex, "(");
        return result;
    }

    static bool containsSingleNumberInParentheses(const std::string& input) {
        // Regex pattern to match a number enclosed in parentheses
        std::regex pattern(R"(\(\d+\))");

        // Check if the input string contains a number in parentheses
        return std::regex_search(input, pattern);
    }

    // Recursive function to generate all expressions with 'n' pairs of parentheses
    static void generateExpressions(const std::string& currentExpr, int n, std::set<std::string>& results) {
        if (n == 0) {
            if (!containsSingleNumberInParentheses(currentExpr))
            {
                results.insert(currentExpr);
            }
            return;
        }

        // Try placing a new pair of parentheses in every possible position
        int len = currentExpr.length();
        for (int i = 0; i < len; ++i) {
            if (isdigit(currentExpr[i])) {
                for (int j = i + 1; j < len; ++j) {
                    if (isdigit(currentExpr[j])) {
                        std::string newExpr = insertParentheses(currentExpr, i, j);
                        generateExpressions(newExpr, n - 1, results);
                    }
                }
            }
        }
    }

    void reset()
    {
        nextExpressionIndex = 0;
    }
    
private:
    const std::string simpleExpression;
    std::vector<std::string> parenthesizedExpressions;
    int nextExpressionIndex;
};

#endif /* ParenthesizedExpressionsGenerator_h */
