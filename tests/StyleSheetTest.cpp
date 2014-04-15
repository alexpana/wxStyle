#include <boost/test/unit_test.hpp>
#include <boost/test/parameterized_test.hpp>
#include <boost/optional/optional.hpp>

#include <vector>
#include <tuple>
#include <string>

#include "style/StyleSheet.h"

BOOST_AUTO_TEST_SUITE(style_sheet_suite)

using namespace wxstyle;
using namespace std;

BOOST_AUTO_TEST_CASE(style_property) {
	StyleProperty stringProperty = "value";
	BOOST_CHECK(stringProperty.IsString());
	BOOST_CHECK(!stringProperty.IsInt());
	BOOST_CHECK(!stringProperty.IsDimension());
	BOOST_CHECK_EQUAL(stringProperty.ToString(), "value");

	StyleProperty intProperty = 42;
	BOOST_CHECK(!intProperty.IsString());
	BOOST_CHECK(intProperty.IsInt());
	BOOST_CHECK(!intProperty.IsDimension());
	BOOST_CHECK_EQUAL(intProperty.ToInt(), 42);

	StyleProperty dimensionProperty = Dimension(6, 9);
	BOOST_CHECK(!dimensionProperty.IsString());
	BOOST_CHECK(!dimensionProperty.IsInt());
	BOOST_CHECK(dimensionProperty.IsDimension());
	BOOST_CHECK_EQUAL(dimensionProperty.ToDimension(), Dimension(6, 9));
}

BOOST_AUTO_TEST_CASE(property_map) {
	StyleSheet styleSheet;
	boost::optional<StyleProperty> val;

	/* Verify set / unset actions */
	BOOST_CHECK(!styleSheet.GetProperty("p_name"));

	styleSheet.SetProperty("p_name", std::string("p_value"));
	val = styleSheet.GetProperty("p_name");
	BOOST_CHECK(val);
	BOOST_REQUIRE(val.get().IsString());
	BOOST_CHECK_EQUAL(val.get().ToString(), "p_value");

	styleSheet.UnsetProperty("p_name");
	val = styleSheet.GetProperty("p_name");
	BOOST_CHECK(!val);

	/* Verify proper types are stored in the property map */
	styleSheet.SetProperty("p_name", 0);
	BOOST_REQUIRE(styleSheet.GetProperty("p_name").get().IsInt());
	BOOST_REQUIRE_EQUAL(styleSheet.GetProperty("p_name").get().ToInt(), 0);

	styleSheet.SetProperty("p_name", "0");
	BOOST_REQUIRE(styleSheet.GetProperty("p_name").get().IsString());
	BOOST_REQUIRE_EQUAL(styleSheet.GetProperty("p_name").get().ToString(), "0");

	styleSheet.SetProperty("p_name", Dimension(0, 1));
	BOOST_REQUIRE(styleSheet.GetProperty("p_name").get().IsDimension());
	BOOST_REQUIRE_EQUAL(styleSheet.GetProperty("p_name").get().ToDimension(), Dimension(0, 1));
}

BOOST_AUTO_TEST_SUITE_END()