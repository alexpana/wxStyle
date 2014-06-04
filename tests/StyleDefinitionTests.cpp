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
    ValueDefinition<int> vd1(10), vd2, vdr(10);

    BOOST_REQUIRE(vd1.value);
    BOOST_REQUIRE(!vd2.value);

    BOOST_REQUIRE_EQUAL(StyleUtils::MergeDefinitions(vd1, vd2), vdr);
}

BOOST_AUTO_TEST_CASE(test_merge_font_definition) {
    FontDefinition fd1, fd2, fdr;

    fd1.fontFace = "some_font_name";
    fd1.fontSize = 10;

    fd2.fontSize = 12;
    fd2.fontStyle = wxFONTSTYLE_SLANT;

    fdr.fontFace = "some_font_name";
    fdr.fontSize = 12;
    fdr.fontStyle = wxFONTSTYLE_SLANT;

    BOOST_REQUIRE_EQUAL(StyleUtils::MergeDefinitions(fd1, fd2), fdr);
}

BOOST_AUTO_TEST_CASE(test_merge_definitions) {
    typedef ValueDefinition<int> VDI;

    BOOST_REQUIRE_EQUAL(
        StyleUtils::MergeDefinitions(
            boost::optional<VDI>(VDI(4)), 
            boost::optional<VDI>()), 
        boost::optional<VDI>(VDI(4)));

    BOOST_REQUIRE_EQUAL(
        StyleUtils::MergeDefinitions(
        boost::optional<VDI>(), 
        boost::optional<VDI>(VDI(4))), 
        boost::optional<VDI>(VDI(4)));

    BOOST_REQUIRE_EQUAL(
        StyleUtils::MergeDefinitions(
        boost::optional<VDI>(VDI(6)), 
        boost::optional<VDI>(VDI(9))), 
        boost::optional<VDI>(VDI(9)));
}

BOOST_AUTO_TEST_SUITE_END()