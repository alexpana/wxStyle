#pragma once

#include "style/draw/DrawShapeInstruction.h"

namespace wxstyle{ 

	class DrawRectangleInstruction : public DrawShapeInstruction {
	public:
		DrawRectangleInstruction(const DrawShapeInstruction::Params& params);

		void Draw(wxGraphicsContext* g, const wxSize& windowSize) const override;
	};

// 	std::ostream& operator<<(std::ostream& lhs, const DrawRectangleInstruction& rhs);
// 	bool operator==(const DrawRectangleInstruction& lhs, const DrawRectangleInstruction& rhs);

} // namespace wxstyle