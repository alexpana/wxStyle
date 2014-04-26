#include "StyledFrame.h"

#include "DragHandler.h"
#include "ResizeHandler.h"
#include "FrameHeader.h"

#include "wx\event.h"
#include "wx\sizer.h"
#include "wx\timer.h"
#include "wx\dcbuffer.h"
#include "wx\graphics.h"
#include "wx\button.h"

namespace wxstyle {

StyledFrame::StyledFrame() : wxFrame(nullptr, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxNO_BORDER) {
    Init();
}

StyledFrame::~StyledFrame() {
}

wxPanel * StyledFrame::GetContentPanel() {
    return m_contentPanel;
}

void StyledFrame::Init() {
    m_frameSizer = new wxFlexGridSizer(3, 0, 0);
    m_frameInnerSizer = new wxBoxSizer(wxVERTICAL);

    m_framePanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE);
    m_framePanel->SetSizer(m_frameSizer);

    m_frameInnerPanel = new wxPanel(m_framePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE);
    m_frameInnerPanel->SetSizer(m_frameInnerSizer);
    m_frameInnerPanel->SetMinSize(wxSize(0, 0));
    m_frameInnerPanel->SetBackgroundColour("#3e3e42");

    m_headerPanel = new FrameHeader(m_frameInnerPanel, this);
    m_headerPanel->SetTitle("Demo Board");
    m_headerPanel->SetMinSize(wxSize(0, 26));
    m_headerPanel->SetBackgroundColour("#3e3e42");

    m_contentPanel = new wxPanel(m_frameInnerPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE);
    m_contentPanel->SetBackgroundColour("#3e3e42");

    /* Initialize the inner panel */
    m_frameInnerSizer->Add(m_headerPanel, 0, wxEXPAND);
    m_frameInnerSizer->Add(m_contentPanel, 1, wxEXPAND);

    m_resizeHandler = new ResizeHandler(this);

    /* Initialize the borders */
    InitBorders();
    SetBorderSize(3);

    /* Set the default colors */
    SetBackgroundColour("#3e3e42");
    SetBorderColor("#2d2d30");

    /* Fit everything on the frame */
    Fit();
}

bool StyledFrame::SetBackgroundColour(const wxColour &colour) {
    bool result = wxFrame::SetBackgroundColour(colour);
    m_framePanel->SetBackgroundColour(colour);

    return result;
}

void StyledFrame::InitBorders() {
    m_borderTop = new wxPanel(m_framePanel);
    // m_borderTop->SetCursor(wxCURSOR_SIZENS);

    m_borderRight = new wxPanel(m_framePanel);
    m_borderRight->SetCursor(wxCURSOR_SIZEWE);
    m_resizeHandler->Install(m_borderRight, HORIZONTAL);

    m_borderBottom = new wxPanel(m_framePanel);
    m_borderBottom->SetCursor(wxCURSOR_SIZENS);
    m_resizeHandler->Install(m_borderBottom, VERTICAL);

    m_borderLeft = new wxPanel(m_framePanel);
    // m_borderLeft->SetCursor(wxCURSOR_SIZEWE);

    m_borderTopLeft = new wxPanel(m_framePanel);
    // m_borderTopLeft->SetCursor(wxCURSOR_SIZENWSE);

    m_borderTopRight = new wxPanel(m_framePanel);
    // m_borderTopRight->SetCursor(wxCURSOR_SIZENESW);

    m_borderBottomLeft = new wxPanel(m_framePanel);
    // m_borderBottomLeft->SetCursor(wxCURSOR_SIZENESW);

    m_borderBottomRight = new wxPanel(m_framePanel);
    m_borderBottomRight->SetCursor(wxCURSOR_SIZENWSE);
    m_resizeHandler->Install(m_borderBottomRight, DIAGONAL);

    m_borderVector.push_back(m_borderTop);
    m_borderVector.push_back(m_borderTopLeft);
    m_borderVector.push_back(m_borderTopRight);
    m_borderVector.push_back(m_borderLeft);
    m_borderVector.push_back(m_borderRight);
    m_borderVector.push_back(m_borderBottomLeft);
    m_borderVector.push_back(m_borderBottom);
    m_borderVector.push_back(m_borderBottomRight);

    m_frameSizer->AddGrowableCol(1);
    m_frameSizer->AddGrowableRow(1);

    m_frameSizer->Add(m_borderTopLeft);
    m_frameSizer->Add(m_borderTop, 1, wxEXPAND);
    m_frameSizer->Add(m_borderTopRight);
    m_frameSizer->Add(m_borderLeft, 1, wxEXPAND);
    m_frameSizer->Add(m_frameInnerPanel, 1, wxEXPAND);
    m_frameSizer->Add(m_borderRight, 1, wxEXPAND);
    m_frameSizer->Add(m_borderBottomLeft);
    m_frameSizer->Add(m_borderBottom, 1, wxEXPAND);
    m_frameSizer->Add(m_borderBottomRight);
}

} // namespace wxstyle