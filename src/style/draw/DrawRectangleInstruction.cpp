#include "style/draw/DrawRectangleInstruction.h"

#include <wx/brush.h>

#include "DimRect.h"

namespace wxstyle {

    DrawRectangleInstruction::DrawRectangleInstruction(const DrawShapeInstruction::Params& params) : DrawShapeInstruction(params) {};

	void DrawRectangleInstruction::Draw(wxGraphicsContext* g, const wxSize& windowSize) const {
		wxRect computedRect = GetParams().GetRect().GetValue(windowSize);
        wxPoint offset = ComputeOffset(computedRect.GetWidth(), computedRect.GetHeight(), GetParams().GetHorizontalAnchor(), GetParams().GetVerticalAnchor());

        computedRect.Offset(offset);

		if (GetParams().HasGradientDefinition()) {
			g->SetBrush(GetParams().GetGradientDefinition().get()->CreateBrush(*g, computedRect));
		} else {
			g->SetBrush(GetParams().GetBrush());
		}

		if (GetParams().GetPenSize() > 0) {
			wxPen *pen = wxThePenList->FindOrCreatePen(GetParams().GetPenColor(), GetParams().GetPenSize(), GetParams().GetPenStyle());
			g->SetPen(*pen);
		}

		if (GetParams().GetCornerRadius() <= 0) {
			g->DrawRectangle(
				computedRect.GetX(),
				computedRect.GetY(),
				computedRect.GetWidth(),
				computedRect.GetHeight());
 		} else {
 			g->DrawRoundedRectangle(
 				computedRect.GetX(),
 				computedRect.GetY(),
 				computedRect.GetWidth(),
 				computedRect.GetHeight(),
 				GetParams().GetCornerRadius());
 		}
	}

} // namespace wxstyle