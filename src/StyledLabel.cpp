#include "StyledLabel.h"

#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include <wx/window.h>

namespace wxstyle {

class DefaultLabelRenderer : public IRenderer {
public:
    DefaultLabelRenderer() {};
    ~DefaultLabelRenderer() {};

    virtual void Render(StyledWindow* window) const {

        wxAutoBufferedPaintDC deviceContext(window);
        auto g = wxGraphicsContext::Create(deviceContext);
        wxString text = window->GetLabel();
        std::shared_ptr<Style> style = window->GetStyle();

        int fontFlags = wxFONTFLAG_DEFAULT;
        if (window->GetFont().GetWeight() == wxFONTWEIGHT_BOLD) {
            fontFlags = fontFlags | wxFONTFLAG_BOLD;
        }

        g->SetFont(g->CreateFont(12, "Tahoma", fontFlags, window->GetForegroundColour()));
        g->SetBrush(g->CreateBrush(window->GetForegroundColour()));

        wxSize textSize = deviceContext.GetTextExtent(text);
        wxSize labelSize = window->GetSize();
        wxAlignment textAlignment = dynamic_cast<StyledLabel*>(window)->GetTextAlignment();
        wxPoint textPosition = GetTextPositionFromAlignment(textAlignment, labelSize, textSize);

        RenderBackground(g, window);
        RenderText(g, text, textPosition, fontFlags, window);
    }

    void RenderBackground( wxGraphicsContext * g, StyledWindow* window ) const
    {
        g->SetBrush(g->CreateBrush(window->GetInheritedBackgroundColor()));
        g->DrawRectangle(0, 0, window->GetSize().GetWidth(), window->GetSize().GetHeight());
    }

    wxPoint GetTextPositionFromAlignment(wxAlignment textAlignment, wxSize &labelSize, wxSize &textSize) const
    {
        wxPoint textPosition(0, 0);

        if (textAlignment & wxAlignment::wxALIGN_CENTER_HORIZONTAL) {
            textPosition.x = (labelSize.GetWidth() - textSize.GetWidth()) / 2;
        }

        if (textAlignment & wxAlignment::wxALIGN_RIGHT) {
            textPosition.x = labelSize.GetWidth() - textSize.GetWidth();
        }

        if (textAlignment & wxAlignment::wxALIGN_CENTER_VERTICAL) {
            textPosition.y = (labelSize.GetHeight() - textSize.GetHeight()) / 2;
        }

        if (textAlignment & wxAlignment::wxALIGN_BOTTOM) {
            textPosition.y = labelSize.GetHeight() - textSize.GetHeight();
        }

        return textPosition;
    }

    void RenderText(wxGraphicsContext *g, wxString text, wxPoint &textPosition, int fontFlags, StyledWindow *window) const
    {
//         g->SetFont(g->CreateFont(12, "Tahoma", fontFlags, 0x161616));
//         g->DrawText(text, textPosition.x + 1, textPosition.y + 1);

        g->SetFont(g->CreateFont(11, "Tahoma", fontFlags, window->GetForegroundColour()));
        g->DrawText(text, textPosition.x, textPosition.y);
    }
};

StyledLabel::StyledLabel(wxWindow *parent) : StyledWindow(parent) {
    Init();
}

void StyledLabel::Init() {
    SetOpaque(false);
    SetTextAlignment(wxALIGN_CENTER_VERTICAL);
    SetRenderer(std::shared_ptr<DefaultLabelRenderer>(new DefaultLabelRenderer()));
}

} // namespace wxstyle