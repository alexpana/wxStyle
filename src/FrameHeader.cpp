#include "FrameHeader.h"

#include "DragHandler.h"

#include <wx/sizer.h>
#include <wx/graphics.h>

namespace wxstyle {

wxByte FrameHeader::ACTION_CLOSE = 0x01;
wxByte FrameHeader::ACTION_MINIMIZE = 0x02;
wxByte FrameHeader::ACTION_MAXIMIZE = 0x04;

void FrameHeader::Init(wxWindow *parent, wxWindow *topLevelWindow) {
    wxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    SetSizer(sizer);

    m_titleLabel = new StyledLabel(this);
    m_titleLabel->SetFont(m_titleLabel->GetFont().Bold());
    m_titleLabel->SetForegroundColour("#DADADA");

    sizer->Add(m_titleLabel, wxSizerFlags().Center().Border(wxLEFT, 4).Expand());

    /* Install the drag handler on the header panel */
    m_dragHandler = new DragHandler(topLevelWindow);
    m_dragHandler->Install(this);
    m_dragHandler->Install(m_titleLabel);

    SetOpaque(false);
}

void FrameHeader::OnPaint(wxPaintEvent& paintEvent) {
    wxAutoBufferedPaintDC dc(this);
    auto g = wxGraphicsContext::Create(dc);

    g->SetBrush(g->CreateBrush(GetInheritedBackgroundColor()));
    g->DrawRectangle(0, 0, GetSize().GetWidth(), GetSize().GetHeight());
}

} // namespace wxstyle