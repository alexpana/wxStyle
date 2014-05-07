#include "style/draw/DrawEllipseInstruction.h"

#include <wx/brush.h>

#include "DimRect.h"

namespace wxstyle {

    DrawEllipseInstruction::DrawEllipseInstruction(const DrawShapeInstruction::Params& params) : DrawShapeInstruction(params) {}

    void DrawEllipseInstruction::Draw(wxGraphicsContext* g, const wxSize& windowSize) const {
        wxRect computedRect = GetParams().GetRect().GetValue(wxRect(windowSize.GetWidth(), windowSize.GetHeight(), windowSize.GetWidth(), windowSize.GetHeight()));
        wxPoint offset = ComputeOffset(computedRect.GetWidth(), computedRect.GetHeight(), GetParams().GetHorizontalAnchor(), GetParams().GetVerticalAnchor());

        if (GetParams().HasGradientDefinition()) {
            g->SetBrush(GetParams().GetGradientDefinition().get()->CreateBrush(*g, computedRect));
        } else {
            g->SetBrush(GetParams().GetBrush());
        }

        if (GetParams().GetPenSize() > 0) {
            wxPen *pen = wxThePenList->FindOrCreatePen(GetParams().GetPenColor(), GetParams().GetPenSize(), GetParams().GetPenStyle());
            g->SetPen(*pen);
        }

        g->DrawEllipse(
            computedRect.GetX() + offset.x,
            computedRect.GetY() + offset.y,
            computedRect.GetWidth(),
            computedRect.GetHeight());
    }

} // namespace wxstyle