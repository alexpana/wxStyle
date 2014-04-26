#include "StyledLabel.h"

#include <wx/window.h>
#include <wx/dcbuffer.h>
#include <wx/graphics.h>

#include "FunctionRederer.h"

namespace wxstyle {

StyledLabel::StyledLabel(wxWindow *parent) : StyledWindow(parent) {
    Init();
}

void StyledLabel::Init() {
    SetOpaque(false);
    SetTextAlignment(wxALIGN_CENTER_VERTICAL);

    SetRenderer(std::make_shared<FunctionRenderer>([this](StyledWindow* window) {
        wxAutoBufferedPaintDC deviceContext(window);
        auto g = wxGraphicsContext::Create(deviceContext);
        wxString text = GetLabel();

        g->SetBrush(g->CreateBrush(GetInheritedBackgroundColor()));
        g->DrawRectangle(0, 0, GetSize().GetWidth(), GetSize().GetHeight());

        int fontFlags = wxFONTFLAG_DEFAULT;
        if (GetFont().GetWeight() == wxFONTWEIGHT_BOLD) {
            fontFlags = fontFlags | wxFONTFLAG_BOLD;
        }

        g->SetFont(g->CreateFont(12, "Tahoma", fontFlags, GetForegroundColour()));
        g->SetBrush(g->CreateBrush(GetForegroundColour()));

        wxSize textSize = deviceContext.GetTextExtent(text);
        wxSize labelSize = GetSize();
        wxPoint textPosition(0, 0);

        // calculate text alignment
        if (GetTextAlignment() & wxAlignment::wxALIGN_CENTER_HORIZONTAL) {
            textPosition.x = (labelSize.GetWidth() - textSize.GetWidth()) / 2;
        }
        if (GetTextAlignment() & wxAlignment::wxALIGN_RIGHT) {
            textPosition.x = labelSize.GetWidth() - textSize.GetWidth();
        }

        if (GetTextAlignment() & wxAlignment::wxALIGN_CENTER_VERTICAL) {
            textPosition.y = (labelSize.GetHeight() - textSize.GetHeight()) / 2;
        }
        if (GetTextAlignment() & wxAlignment::wxALIGN_BOTTOM) {
            textPosition.y = labelSize.GetHeight() - textSize.GetHeight();
        }

        // Draw the text
        g->DrawText(text, textPosition.x, textPosition.y);

        g->SetFont(g->CreateFont(12, "Tahoma", fontFlags, 0x161616));
        g->DrawText(text, textPosition.x + 1, textPosition.y + 1);

        g->SetFont(g->CreateFont(12, "Tahoma", fontFlags, GetForegroundColour()));

        g->DrawText(text, textPosition.x, textPosition.y);
    }));
}

} // namespace wxstyle