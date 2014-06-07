#include <boost/test/unit_test.hpp>
#include <boost/test/parameterized_test.hpp>
#include <boost/optional/optional.hpp>

#include <vector>
#include <tuple>
#include <string>

#include "style/StyleDefinitions.h"

BOOST_AUTO_TEST_SUITE(style_definition_suite)

using namespace wxstyle;
using namespace std;

BOOST_AUTO_TEST_CASE(test_value_definition) {
    ValueDefinition<int> intValueDefinition;

    BOOST_REQUIRE(!intValueDefinition.value);

    intValueDefinition.value = 10;

    BOOST_REQUIRE(intValueDefinition.value);
    BOOST_REQUIRE_EQUAL(intValueDefinition.value.get(), 10);
}

BOOST_AUTO_TEST_CASE(test_merge_value_definition) {
}

BOOST_AUTO_TEST_CASE(test_merge_font_definition) {
}

BOOST_AUTO_TEST_CASE(test_merge_definitions) {
}

BOOST_AUTO_TEST_SUITE_END()