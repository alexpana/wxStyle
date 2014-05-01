#include "StyledButton.h"

#include <memory>

#include <wx/graphics.h>
#include <wx/dcbuffer.h>
#include <wx/font.h>
#include "style/draw/DrawRectangleInstruction.h"

namespace wxstyle {

class DefaultButtonRenderer : public IRenderer {
public:
    virtual void Render(StyledWindow* window) const {
        wxAutoBufferedPaintDC deviceContext(window);
        auto g = wxGraphicsContext::Create(deviceContext);

        int w = window->GetSize().GetWidth();
        int h = window->GetSize().GetHeight();

        int radius = 0;
        wxColor startColor = wxColor(0x303030);
        wxColor endColor = wxColor(0x505050);
        wxColor highlight = wxColor(0xa585858);

        wxBrush brush;

        ClearBackground(window, g);

        //// bottom highlight
        //brush.SetColour(0x454545);
        //g->SetBrush(g->CreateBrush(brush));
        //g->DrawRoundedRectangle(0, 0, w, h, radius);

        //// border
        //if (window->HasFocus()) {
        //    brush.SetColour(0x904040);
        //} else {
        //    brush.SetColour(0x191919);
        //}
        //g->SetBrush(g->CreateBrush(brush));
        //g->DrawRoundedRectangle(0, 0, w, h-1, radius);

        //// top highlight
        //brush.SetColour(highlight);
        //g->SetBrush(g->CreateBrush(brush));
        //g->DrawRoundedRectangle(1, 1, w-2, h-3, radius);

        // gradient
        int textOffset = 0;
        if (dynamic_cast<StyledButton*>(window)->GetState() != StyledButton::ARMED) {
            wxGraphicsGradientStops stops;
            stops.Add(startColor, 1);
            stops.Add(endColor, 0);
            g->SetBrush(g->CreateLinearGradientBrush(0, 0, 0, h, stops));
        } else {
            wxGraphicsGradientStops stops;
            stops.Add(startColor, 0);
            stops.Add(endColor, 1);
            g->SetBrush(g->CreateLinearGradientBrush(0, 0, 0, h, stops));
            textOffset = 1;
        }

		//g->SetPen(*wxBLACK_PEN);

		g->SetBrush(*wxBLUE_BRUSH);
		g->DrawRectangle(0, 0, w, h);

		g->SetBrush(*wxRED_BRUSH);
        g->DrawRectangle(2, 2, w-4, h-4);

		DrawRectangleInstruction borderInstruction = DrawRectangleInstruction::NewBuilder()
			->SetColor("#0000FF")
			->SetPenSize(0)
			->Build();

		DrawRectangleInstruction backgroundInstruction = DrawRectangleInstruction::NewBuilder()
			->SetRect(DimRect(2, 2, Dimension(-4, 1), Dimension(-4, 1)))
			->SetColor("#FF0000")
			->SetPenSize(0)
			->SetCornerRadius(2)
			->Build();

		//borderInstruction.Draw(g, window->GetSize());
		//backgroundInstruction.Draw(g, window->GetSize());

        RenderText(g, deviceContext, window, w, h, textOffset);

        delete g;   
    }

    void ClearBackground(StyledWindow *window, wxGraphicsContext *g) const {
        wxRect clientRect = window->GetClientRect();
        g->SetBrush(g->CreateBrush(window->GetBackgroundColour()));
        g->DrawRectangle(clientRect.GetX(), clientRect.GetY(), clientRect.GetWidth(), clientRect.GetHeight());
    }

    void RenderText(wxGraphicsContext *g, wxAutoBufferedPaintDC &deviceContext, StyledWindow *window, int w, int h, int textOffset) const {
        g->SetFont(g->CreateFont(12, "Tahoma", wxFONTFLAG_BOLD, 0x161616));
        wxSize textSize = deviceContext.GetTextExtent(window->GetText());

        g->DrawText(window->GetText(), (w - textSize.GetWidth()) / 2, (h - textSize.GetHeight()) / 2 + 1 + textOffset);

        g->SetFont(g->CreateFont(12, "Tahoma", wxFONTFLAG_BOLD, 0xAAAAAA));

        g->DrawText(window->GetText(), (w - textSize.GetWidth()) / 2, (h - textSize.GetHeight()) / 2 + textOffset);
    }
};

StyledButton::StyledButton() : StyledWindow(nullptr, "") {
}

StyledButton::StyledButton(wxWindow* parent, wxString text) : StyledWindow(parent, text) {
    SetBackgroundColour(parent->GetBackgroundColour());
    SetMinSize(wxSize(10, 30));

    SetRenderer(std::make_shared<DefaultButtonRenderer>());
}

StyledButton::~StyledButton() {
}

void StyledButton::OnMouseDown(wxMouseEvent& mouseEvent) {
    m_state = ARMED;
    Refresh();
}

void StyledButton::OnMouseReleased(wxMouseEvent& mouseEvent) {
    if (m_state == ARMED) {
        SendClickEvent();
    }

    m_state = IDLE;
    Refresh();
}

void StyledButton::ClearBackground(wxGraphicsContext *g) {
    wxRect clientRect = GetClientRect();

    g->SetBrush(g->CreateBrush(GetBackgroundColour()));
    g->DrawRectangle(clientRect.GetX(), clientRect.GetY(), clientRect.GetWidth(), clientRect.GetHeight());
}

void StyledButton::OnMouseMoved(wxMouseEvent& mouseEvent) {
    if (mouseEvent.ButtonDown(wxMOUSE_BTN_LEFT)) {
        m_state = ARMED;
    }
}

void StyledButton::OnMouseLeaveWindow(wxMouseEvent& mouseEvent) {
    m_state = IDLE;
    Refresh();
}

void StyledButton::OnMouseEnterWindow(wxMouseEvent& mouseEvent) {
    if (mouseEvent.ButtonIsDown(wxMOUSE_BTN_LEFT)) {
        m_state = ARMED;
    }
    Refresh();
}

void StyledButton::SendClickEvent() {
    wxCommandEvent event(wxEVT_BUTTON, GetId());
    event.SetEventObject(this);
    ProcessWindowEvent(event);
}

void StyledButton::OnMouseDoubleClick(wxMouseEvent& mouseEvent) {
    OnMouseDown(mouseEvent);
}

} // namespace wxstyle