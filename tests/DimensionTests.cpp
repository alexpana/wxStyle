#include <boost/test/unit_test.hpp>
#include <boost/test/parameterized_test.hpp>
#include <boost/optional/optional.hpp>

#include <vector>
#include <tuple>
#include <string>

#include "asserthelper.h"
#include "Dimension.h"
#include "DimPoint.h"

BOOST_AUTO_TEST_SUITE(dimension_suite)

using namespace wxstyle;
using namespace std;

void require_valid(const tuple<string, float, int>& arg) {
	auto dim = Dimension::ValueOf(std::get<0>(arg));
	BOOST_CHECK_MESSAGE(dim, "Requiring " + std::get<0>(arg) + " to be a valid Dimension.");
	BOOST_REQUIRE_EQUAL(dim->GetRelative(), std::get<1>(arg));
	BOOST_REQUIRE_EQUAL(dim->GetAbsolute(), std::get<2>(arg));
}

void require_invalid(const string& val) {
	auto dim = Dimension::ValueOf(val);
	BOOST_CHECK_MESSAGE(!dim, "Requiring " + val + " to be a an invalid Dimension.");
}

BOOST_AUTO_TEST_CASE(parse_from_string)
{
	string invalid_values[] = {"10%-", "%", "-", "-45%43", "-%", "+", "1%3", "%2"};

	BOOST_PARAM_TEST_CASE(&require_invalid, invalid_values, invalid_values + 8);

	for (auto& val : invalid_values) {
		require_invalid(val);
	}

	tuple<string, float, int> valid_values[] = {
		make_tuple("10%+43", 0.1f, 43),
		make_tuple("-43", .0f, -43),
		make_tuple("43%", 0.43f, 0),
		make_tuple("634", .0f, 634),
		make_tuple("-1%", -0.01f, 0),
		make_tuple("+1%", 0.01f, 0),
		make_tuple("12", .0f, 12)
	};

	for (auto& val : valid_values) {
		require_valid(val);
	}
}

BOOST_AUTO_TEST_CASE(value_calculation)
{
	BOOST_REQUIRE_EQUAL(Dimension(4, 0.5f).GetValue(100), 54);
	BOOST_REQUIRE_EQUAL(Dimension(4, 0.5f).GetValue(200), 104);
	BOOST_REQUIRE_EQUAL(Dimension(4).GetValue(100), 4);
	BOOST_REQUIRE_EQUAL(Dimension(4).GetValue(10), 4);
	BOOST_REQUIRE_EQUAL(Dimension(4).GetValue(0), 4);
	BOOST_REQUIRE_EQUAL(Dimension(0, 0.1f).GetValue(0), 0);
	BOOST_REQUIRE_EQUAL(Dimension(0, 0.5f).GetValue(0), 0);
	BOOST_REQUIRE_EQUAL(Dimension(0, 0.5f).GetValue(2), 1);
	BOOST_REQUIRE_EQUAL(Dimension(0, 1).GetValue(15), 15);
	BOOST_REQUIRE_EQUAL(Dimension(0, 2).GetValue(4), 8);
	BOOST_REQUIRE_EQUAL(Dimension(20, 2).GetValue(4), 28);
}

BOOST_AUTO_TEST_CASE(dim_point) {
	DimPoint point(Dimension(5, 0.1f), Dimension(-1, 1));
	BOOST_REQUIRE_EQUAL(point.GetValue(wxSize(100, 50)), wxSize(15, 49));
	BOOST_REQUIRE_EQUAL(point.GetValue(wxPoint(100, 50)), wxPoint(15, 49));
}

BOOST_AUTO_TEST_SUITE_END()