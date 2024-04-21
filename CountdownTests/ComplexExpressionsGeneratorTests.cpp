#include "catch.hpp"

#include "TestUtils.h"
#include "../Countdown/ComplexExpressionsGenerator.h"

#include <sstream>
#include <string>
#include <vector>

namespace ComplexExpressionsGeneratorTest
{

    static const std::vector<std::string> simpleExpressions{ "1+2", "1+2+3" };

}

TEST_CASE("ComplexExpressionsGenerator is constructable") {
    REQUIRE_NOTHROW(ComplexExpressionsGenerator(ComplexExpressionsGeneratorTest::simpleExpressions));
}
