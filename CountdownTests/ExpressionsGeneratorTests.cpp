//
//  ExpressionsGeneratorTests.h
//  countdown
//
//  Created by Ian Guest on 09/04/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#include "catch.hpp"

#include "../Countdown/ExpressionsGenerator.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace ExpressionsGeneratorTest
{

static const std::vector<std::string> twoNumberCaseExpectedValues {
    "1", "2", "1+2", "1-2", "1*2", "1/2", "2+1", "2-1", "2*1", "2/1"
    
};

static const std::vector<std::string> threeNumberCaseExpectedValues { "1", "2", "3", "1+2", "1-2", "1*2", "1/2", "1+3", "1-3", "1*3", "1/3", "2+1", "2-1", "2*1", "2/1", "2+3", "2-3", "2*3", "2/3", "3+1", "3-1", "3*1", "3/1", "3+2", "3-2", "3*2", "3/2", "1+2+3", "1+2-3", "1+2*3", "1+2/3", "1-2+3", "1-2-3", "1-2*3", "1-2/3", "1*2+3", "1*2-3", "1*2*3", "1*2/3", "1/2+3", "1/2-3", "1/2*3", "1+3+2", "1+3-2", "1+3*2", "1+3/2", "1-3+2", "1-3-2", "1-3*2", "1-3/2", "1*3+2", "1*3-2", "1*3*2", "1*3/2", "1/3+2", "1/3-2", "1/3*2", "2+1+3", "2+1-3", "2+1*3", "2+1/3", "2-1+3", "2-1-3", "2-1*3", "2-1/3", "2*1+3", "2*1-3", "2*1*3", "2*1/3", "2/1+3", "2/1-3", "2/1*3", "2+3+1", "2+3-1", "2+3*1", "2+3/1", "2-3+1", "2-3-1", "2-3*1", "2-3/1", "2*3+1", "2*3-1", "2*3*1", "2*3/1", "2/3+1", "2/3-1", "2/3*1", "3+1+2", "3+1-2", "3+1*2", "3+1/2", "3-1+2", "3-1-2", "3-1*2", "3-1/2", "3*1+2", "3*1-2", "3*1*2", "3*1/2", "3/1+2", "3/1-2", "3/1*2", "3+2+1", "3+2-1", "3+2*1", "3+2/1", "3-2+1", "3-2-1", "3-2*1", "3-2/1", "3*2+1", "3*2-1", "3*2*1", "3*2/1", "3/2+1", "3/2-1", "3/2*1", "(1+2)", "(1-2)", "(1*2)", "(1/2)", "(1+3)", "(1-3)", "(1*3)", "(1/3)", "(2+1)", "(2-1)", "(2*1)", "(2/1)", "(2+3)", "(2-3)", "(2*3)", "(2/3)", "(3+1)", "(3-1)", "(3*1)", "(3/1)", "(3+2)", "(3-2)", "(3*2)", "(3/2)", "(1+2)+3", "(1+2+3)", "1+(2+3)", "(1+2)-3", "(1+2-3)", "1+(2-3)", "(1+2)*3", "(1+2*3)", "1+(2*3)", "(1+2)/3", "(1+2/3)", "1+(2/3)", "(1-2)+3", "(1-2+3)", "1-(2+3)", "(1-2)-3", "(1-2-3)", "1-(2-3)", "(1-2)*3", "(1-2*3)", "1-(2*3)", "(1-2)/3", "(1-2/3)", "1-(2/3)", "(1*2)+3", "(1*2+3)", "1*(2+3)", "(1*2)-3", "(1*2-3)", "1*(2-3)", "(1*2)*3", "(1*2*3)", "1*(2*3)", "(1*2)/3", "(1*2/3)", "1*(2/3)", "(1/2)+3", "(1/2+3)", "1/(2+3)", "(1/2)-3", "(1/2-3)", "1/(2-3)", "(1/2)*3", "(1/2*3)", "1/(2*3)", "(1+3)+2", "(1+3+2)", "1+(3+2)", "(1+3)-2", "(1+3-2)", "1+(3-2)", "(1+3)*2", "(1+3*2)", "1+(3*2)", "(1+3)/2", "(1+3/2)", "1+(3/2)", "(1-3)+2", "(1-3+2)", "1-(3+2)", "(1-3)-2", "(1-3-2)", "1-(3-2)", "(1-3)*2", "(1-3*2)", "1-(3*2)", "(1-3)/2", "(1-3/2)", "1-(3/2)", "(1*3)+2", "(1*3+2)", "1*(3+2)", "(1*3)-2", "(1*3-2)", "1*(3-2)", "(1*3)*2", "(1*3*2)", "1*(3*2)", "(1*3)/2", "(1*3/2)", "1*(3/2)", "(1/3)+2", "(1/3+2)", "1/(3+2)", "(1/3)-2", "(1/3-2)", "1/(3-2)", "(1/3)*2", "(1/3*2)", "1/(3*2)", "(2+1)+3", "(2+1+3)", "2+(1+3)", "(2+1)-3", "(2+1-3)", "2+(1-3)", "(2+1)*3", "(2+1*3)", "2+(1*3)", "(2+1)/3", "(2+1/3)", "2+(1/3)", "(2-1)+3", "(2-1+3)", "2-(1+3)", "(2-1)-3", "(2-1-3)", "2-(1-3)", "(2-1)*3", "(2-1*3)", "2-(1*3)", "(2-1)/3", "(2-1/3)", "2-(1/3)", "(2*1)+3", "(2*1+3)", "2*(1+3)", "(2*1)-3", "(2*1-3)", "2*(1-3)", "(2*1)*3", "(2*1*3)", "2*(1*3)", "(2*1)/3", "(2*1/3)", "2*(1/3)", "(2/1)+3", "(2/1+3)", "2/(1+3)", "(2/1)-3", "(2/1-3)", "2/(1-3)", "(2/1)*3", "(2/1*3)", "2/(1*3)", "(2+3)+1", "(2+3+1)", "2+(3+1)", "(2+3)-1", "(2+3-1)", "2+(3-1)", "(2+3)*1", "(2+3*1)", "2+(3*1)", "(2+3)/1", "(2+3/1)", "2+(3/1)", "(2-3)+1", "(2-3+1)", "2-(3+1)", "(2-3)-1", "(2-3-1)", "2-(3-1)", "(2-3)*1", "(2-3*1)", "2-(3*1)", "(2-3)/1", "(2-3/1)", "2-(3/1)", "(2*3)+1", "(2*3+1)", "2*(3+1)", "(2*3)-1", "(2*3-1)", "2*(3-1)", "(2*3)*1", "(2*3*1)", "2*(3*1)", "(2*3)/1", "(2*3/1)", "2*(3/1)", "(2/3)+1", "(2/3+1)", "2/(3+1)", "(2/3)-1", "(2/3-1)", "2/(3-1)", "(2/3)*1", "(2/3*1)", "2/(3*1)", "(3+1)+2", "(3+1+2)", "3+(1+2)", "(3+1)-2", "(3+1-2)", "3+(1-2)", "(3+1)*2", "(3+1*2)", "3+(1*2)", "(3+1)/2", "(3+1/2)", "3+(1/2)", "(3-1)+2", "(3-1+2)", "3-(1+2)", "(3-1)-2", "(3-1-2)", "3-(1-2)", "(3-1)*2", "(3-1*2)", "3-(1*2)", "(3-1)/2", "(3-1/2)", "3-(1/2)", "(3*1)+2", "(3*1+2)", "3*(1+2)", "(3*1)-2", "(3*1-2)", "3*(1-2)", "(3*1)*2", "(3*1*2)", "3*(1*2)", "(3*1)/2", "(3*1/2)", "3*(1/2)", "(3/1)+2", "(3/1+2)", "3/(1+2)", "(3/1)-2", "(3/1-2)", "3/(1-2)", "(3/1)*2", "(3/1*2)", "3/(1*2)", "(3+2)+1", "(3+2+1)", "3+(2+1)", "(3+2)-1", "(3+2-1)", "3+(2-1)", "(3+2)*1", "(3+2*1)", "3+(2*1)", "(3+2)/1", "(3+2/1)", "3+(2/1)", "(3-2)+1", "(3-2+1)", "3-(2+1)", "(3-2)-1", "(3-2-1)", "3-(2-1)", "(3-2)*1", "(3-2*1)", "3-(2*1)", "(3-2)/1", "(3-2/1)", "3-(2/1)", "(3*2)+1", "(3*2+1)", "3*(2+1)", "(3*2)-1", "(3*2-1)", "3*(2-1)", "(3*2)*1", "(3*2*1)", "3*(2*1)", "(3*2)/1", "(3*2/1)", "3*(2/1)", "(3/2)+1", "(3/2+1)", "3/(2+1)", "(3/2)-1", "(3/2-1)", "3/(2-1)", "(3/2)*1", "(3/2*1)", "3/(2*1)"
};

static const std::vector<std::string> fourNumberCaseExpectedValues = {
    "(2*1)+(4-3)", "4+(2+(1-3))", "4*(2/1)+3", "1+2*3/4", "1+(2*3)", "(4/(2*1))-3"
};

std::vector<std::string> toVector(ExpressionsGenerator& gen) {
    std::vector<std::string> output;
    for (gen.first(); !gen.isDone(); gen.next())
        output.push_back(gen.currentItem());
    return output;
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

TEST_CASE("ExpressionsGenerator is constructable") {
    REQUIRE_NOTHROW(ExpressionsGenerator(std::vector<int>{1,2,3}));
}

TEST_CASE("Validate expressions generated in two number case") {
    auto gen = ExpressionsGenerator(std::vector<int>{1,2});
    const auto& output = ExpressionsGeneratorTest::toVector(gen);
    
    REQUIRE(ExpressionsGeneratorTest::containsSubset(
                output, ExpressionsGeneratorTest::twoNumberCaseExpectedValues));
}

bool compareByLength(const std::string& a, const std::string& b) {
    return a.size() < b.size();
}

TEST_CASE("Validate expressions generated in three number case") {
    auto gen = ExpressionsGenerator(std::vector<int>{1,2,3});
    auto output = ExpressionsGeneratorTest::toVector(gen);
    std::sort(output.begin(), output.end(), compareByLength);
    for (auto foo : output)
    {
        std::cout << foo << std::endl;
    }

    REQUIRE(ExpressionsGeneratorTest::containsSubset(
                output, ExpressionsGeneratorTest::threeNumberCaseExpectedValues));
}

TEST_CASE("Validate expressions generated in four number case") {
    auto gen = ExpressionsGenerator(std::vector<int>{1,2,3,4});
    auto output = ExpressionsGeneratorTest::toVector(gen);
    
    //std::sort(output.begin(), output.end(), compareByLength);
    std::ofstream outFile("D:/Dev/4numbers.txt"); // Create an ofstream object and open 'example.txt'

    if (outFile.is_open()) { // Check if the file is successfully opened
        for (auto item : output) {
            outFile << item << std::endl; // Write to the file
        }
        outFile.close(); // Close the file
    }
    else {
        std::cerr << "Unable to open file" << std::endl; // Error message if the file cannot be opened
    }

    REQUIRE(ExpressionsGeneratorTest::containsSubset(
                output, ExpressionsGeneratorTest::fourNumberCaseExpectedValues));
}
