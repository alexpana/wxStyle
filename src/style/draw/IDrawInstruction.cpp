#include "style/DrawInstruction.h"

namespace wxstyle {

	std::ostream& operator<<(std::ostream& lhs, const DrawRectangleInstruction& rhs) {
		return lhs << "DrawRectangleInstruction("
			<< "rect:" << rhs.GetRect() << " "
			<< "color:" << std::hex << rhs.GetColor().GetRGB() << std::dec << " "
			<< "penSize:" << rhs.GetPenSize() << " "
			<< "penColor:" << std::hex << rhs.GetPenColor().GetRGB() << std::dec << " "
			<< "penStyle:" << rhs.GetPenStyle() << " "
			<< "cornerRadius:" << rhs.GetCornerRadius() << ")";
	}

	bool operator==(const DrawRectangleInstruction& lhs, const DrawRectangleInstruction& rhs) {
		return lhs.GetRect() == rhs.GetRect() && lhs.GetColor() == rhs.GetColor() && lhs.GetPenColor() == rhs.GetPenColor()
			&& lhs.GetPenSize() == rhs.GetPenSize() && lhs.GetPenStyle() == rhs.GetPenStyle() && lhs.GetCornerRadius() == rhs.GetCornerRadius();
	}

} // namespace wxstyle