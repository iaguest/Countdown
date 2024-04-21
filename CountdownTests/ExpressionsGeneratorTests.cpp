//
//  ExpressionsGeneratorTests.h
//  countdown
//
//  Created by Ian Guest on 09/04/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#include "catch.hpp"

#include "TestUtils.h"
#include "../Countdown/ExpressionsGenerator.h"

#include <algorithm>
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

}

TEST_CASE("ExpressionsGenerator is constructable") {
    REQUIRE_NOTHROW(ExpressionsGenerator(std::vector<int>{1,2,3}));
}

TEST_CASE("Validate expressions generated in two number case") {
    auto gen = ExpressionsGenerator(std::vector<int>{1,2});
    const auto& output = ExpressionsGeneratorTest::toVector(gen);
    
    REQUIRE(TestUtils::containsSubset(
        output, ExpressionsGeneratorTest::twoNumberCaseExpectedValues));
}

TEST_CASE("Validate expressions generated in three number case") {
    auto gen = ExpressionsGenerator(std::vector<int>{1,2,3});
    const auto& output = ExpressionsGeneratorTest::toVector(gen);
        
    REQUIRE(TestUtils::containsSubset(
        output, ExpressionsGeneratorTest::threeNumberCaseExpectedValues));
}

TEST_CASE("Validate expressions generated in four number case") {
    auto gen = ExpressionsGenerator(std::vector<int>{1,2,3,4});
    const auto& output = ExpressionsGeneratorTest::toVector(gen);
    
    REQUIRE(TestUtils::containsSubset(
        output, ExpressionsGeneratorTest::fourNumberCaseExpectedValues));
}
