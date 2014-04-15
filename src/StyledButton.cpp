#include "StyledButton.h"

#include <memory>
#include <wx/graphics.h>
#include "wx/dcbuffer.h"
#include "wx/font.h"

namespace wxstyle {

StyledButton::StyledButton() : StyledWindow(nullptr, "") {
}

StyledButton::StyledButton(wxWindow* parent, wxString text) : StyledWindow(parent, text) {
    m_text = text;
    SetBackgroundColour(parent->GetBackgroundColour());
    SetMinSize(wxSize(10, 30));
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

void StyledButton::OnPaint(wxPaintEvent& paint) {
    wxAutoBufferedPaintDC deviceContext(this);
    auto g = wxGraphicsContext::Create(deviceContext);

    int w = GetSize().GetWidth();
    int h = GetSize().GetHeight();

    int radius = 0;
    wxColor startColor = wxColor(0x303030);
    wxColor endColor = wxColor(0x505050);
    wxColor highlight = wxColor(0xa585858);
        
    wxBrush brush;

    ClearBackground(g);

    // bottom highlight
    brush.SetColour(0x454545);
    g->SetBrush(g->CreateBrush(brush));
    g->DrawRoundedRectangle(0, 0, w, h, radius);

    // border
    if (HasFocus()) {
        brush.SetColour(0x904040);
    } else {
        brush.SetColour(0x191919);
    }
    g->SetBrush(g->CreateBrush(brush));
    g->DrawRoundedRectangle(0, 0, w, h-1, radius);

    // top highlight
    brush.SetColour(highlight);
    g->SetBrush(g->CreateBrush(brush));
    g->DrawRoundedRectangle(1, 1, w-2, h-3, radius);

    // gradient
    int textOffset = 0;
    if (m_state != ARMED) {
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
    g->DrawRoundedRectangle(1, 2, w-2, h-4, radius);

    // TODO: Font not properly measured

    g->SetFont(g->CreateFont(12, "Tahoma", wxFONTFLAG_BOLD, 0x161616));
    wxSize textSize = deviceContext.GetTextExtent(m_text);

    g->DrawText(m_text, (w - textSize.GetWidth()) / 2, (h - textSize.GetHeight()) / 2 + 1 + textOffset);

    g->SetFont(g->CreateFont(12, "Tahoma", wxFONTFLAG_BOLD, 0xAAAAAA));

    g->DrawText(m_text, (w - textSize.GetWidth()) / 2, (h - textSize.GetHeight()) / 2 + textOffset);

    delete g;
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