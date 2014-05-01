#include "style/DrawInstruction.h"

namespace wxstyle {

	std::ostream& operator<<(std::ostream& lhs, const DimRect& rhs) {
		return lhs << "DimRect(" <<
			"x:" << rhs.m_x << " "
			"x:" << rhs.m_y << " "
			"x:" << rhs.m_w << " "
			"x:" << rhs.m_h << ")";
	}

	std::ostream& operator<<(std::ostream& lhs, const DrawRectangleInstruction& rhs) {
		return lhs << "DrawRectangleInstruction("
			<< "rect:" << rhs.GetRect() << " "
			<< "color:" << std::hex << rhs.GetColor().GetRGB() << std::dec << " "
			<< "penSize:" << rhs.GetPenSize() << " "
			<< "penColor:" << std::hex << rhs.GetPenColor().GetRGB() << std::dec << " "
			<< "penStyle:" << rhs.GetPenStyle() << ")";
	}

	bool operator==(const DrawRectangleInstruction& lhs, const DrawRectangleInstruction& rhs) {
		return lhs.GetRect() == rhs.GetRect() && lhs.GetColor() == rhs.GetColor() && lhs.GetPenColor() == rhs.GetPenColor()
			&& lhs.GetPenSize() == rhs.GetPenSize() && lhs.GetPenStyle() == rhs.GetPenStyle();
	}

} // namespace wxstyle