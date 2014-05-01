#include "AssertHelper.h"

#include "style\DrawInstruction.h"

namespace wxstyle {

	std::ostream& operator<<(std::ostream& lhs, const DrawRectangleInstruction& rhs) {
		return lhs << "DrawRectangleInstruction("
			<< "rect:" << rhs.GetRect() << " "
			<< "color:" << rhs.GetColor().GetAsString() << " "
			<< "penSize:" << rhs.GetPenSize() << " "
			<< "penColor:" << rhs.GetPenColor().GetAsString() << " "
			<< "penStyle:" << rhs.GetPenStyle() << ")";
	}

	std::ostream& operator<<(std::ostream& lhs, const DimRect& rhs) {
		return lhs << "DimRect(" <<
			"x:" << rhs.m_x << " "
			"x:" << rhs.m_y << " "
			"x:" << rhs.m_w << " "
			"x:" << rhs.m_h << ")";
	}

} // namespace wxstyle