#pragma once

#include <ostream>

#include "style/DrawInstruction.h"

namespace wxstyle {

	// this operator is needed to use BOOST_CHECK_EQUAL with DrawRectangleInstruction objects
	std::ostream& operator<<(std::ostream& lhs, const DrawRectangleInstruction& rhs);

	// this operator is needed to use BOOST_CHECK_EQUAL with DimRect objects
	std::ostream& operator<<(std::ostream& lhs, const DimRect& rhs);

	// this operator is needed to use BOOST_CHECK_EQUAL with boost::optional objects
	template<typename T>
	std::ostream& operator<<(std::ostream& lhs, const boost::optional<T>& rhs) {
		static std::string empty = "<>";
		if (rhs) {
			lhs << "[" << rhs.get() << "]";
		} else {
			lhs << empty;
		}
		return lhs;
	}

} // namespace wxstyle