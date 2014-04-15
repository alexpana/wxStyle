#include "Dimension.h"

#include <boost/optional/optional.hpp>
#include <boost/lexical_cast.hpp>

#include <regex>
#include <iosfwd>

namespace wxstyle {

/* Matches only compound dimensions
/* Group 1 matches the relative part not including the '%' sign
/* Group 2 matches the sign of the absolute part including the sign */
static const std::regex COMPOUND_REGEX("^(?:((?:\\+|\\-)?\\d+)\\%)((?:\\+|\\-)\\d+)$");

/* Matches only relative dimensions
/* Group 1 matches the relative value without the '%' sign */
static const std::regex RELATIVE_REGEX("^((?:\\+|\\-)?\\d+)\\%$");

/* Matches only absolute dimensions */
static const std::regex ABSOLUTE_REGEX("^(?:\\+|\\-)?\\d+$");

boost::optional<Dimension> Dimension::ValueOf(std::string val)
{
	std::smatch match;

	if (std::regex_match(val, match, ABSOLUTE_REGEX)) {
		return boost::optional<Dimension>(Dimension(boost::lexical_cast<int>(val)));
	}

	if (std::regex_match(val, match, RELATIVE_REGEX)) {
		return boost::optional<Dimension>(Dimension(0, boost::lexical_cast<int>(match.str(1)) / 100.0f));
	}

	if (std::regex_match(val, match, COMPOUND_REGEX)) {
		return boost::optional<Dimension>(Dimension(
			boost::lexical_cast<int>(match.str(2)), 
			boost::lexical_cast<float>(match.str(1)) / 100.0f));
	}

	return boost::optional<Dimension>();
}

std::ostream& operator<<(std::ostream& lhs, const Dimension& rhs) {
	return lhs << "Dimension(" << rhs.GetAbsolute() << ", " << rhs.GetRelative() << ")";
}

bool operator==(const Dimension& lhs, const Dimension& rhs) {
	return lhs.GetAbsolute() == rhs.GetAbsolute() && 
		lhs.GetRelative() == rhs.GetRelative();
}

}