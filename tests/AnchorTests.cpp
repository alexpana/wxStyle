#include <boost/test/unit_test.hpp>
#include <boost/test/parameterized_test.hpp>
#include <boost/optional/optional.hpp>

#include "style/draw/Anchor.h"

BOOST_AUTO_TEST_SUITE(anchor_suite)

using namespace wxstyle;
using namespace std;

BOOST_AUTO_TEST_CASE(compute_offset) {
    BOOST_CHECK_EQUAL(ComputeOffset(50, HA_RIGHT), -50);
    BOOST_CHECK_EQUAL(ComputeOffset(50, HA_CENTER), -25);
    BOOST_CHECK_EQUAL(ComputeOffset(50, HA_LEFT), 0);

    BOOST_CHECK_EQUAL(ComputeOffset(50, VA_TOP), 0);
    BOOST_CHECK_EQUAL(ComputeOffset(50, VA_CENTER), -25);
    BOOST_CHECK_EQUAL(ComputeOffset(50, VA_BOTTOM), -50);
}

BOOST_AUTO_TEST_SUITE_END()