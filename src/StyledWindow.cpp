#pragma once

#include "StyledWindow.h"
#include "wx\graphics.h"
#include "wx\dcbuffer.h"

 namespace wxstyle {

BEGIN_EVENT_TABLE(StyledWindow, wxWindow)

    // Input Events
    EVT_MOTION(StyledWindow::OnMouseMoved)
    EVT_LEFT_DOWN(StyledWindow::OnMouseDown)
    EVT_LEFT_DCLICK(StyledWindow::OnMouseDoubleClick)
    EVT_LEFT_UP(StyledWindow::OnMouseReleased)
    EVT_RIGHT_DOWN(StyledWindow::OnRightClick)
    EVT_LEAVE_WINDOW(StyledWindow::OnMouseLeaveWindow)
    EVT_ENTER_WINDOW(StyledWindow::OnMouseEnterWindow)
    EVT_KEY_DOWN(StyledWindow::OnKeyPressed)
    EVT_KEY_UP(StyledWindow::OnKeyReleased)
    EVT_MOUSEWHEEL(StyledWindow::OnMouseWheelMoved)
    EVT_MOUSE_EVENTS(StyledWindow::OnMouseEvents)

    EVT_SET_FOCUS(StyledWindow::OnFocusGained)
    EVT_KILL_FOCUS(StyledWindow::OnFocusLost)

    // Render Events
    EVT_PAINT(StyledWindow::OnPaint)
END_EVENT_TABLE()
 
StyledWindow::StyledWindow(wxWindow* parent) : 
    wxWindow(parent, wxID_ANY)
{
    Init();
}
 
StyledWindow::StyledWindow(wxWindow* parent, wxString text) :
    wxWindow(parent, wxID_ANY)
{
    Init();
}
 
StyledWindow::StyledWindow(wxWindow* parent, wxStandardID id, wxString text) :
    wxWindow(parent, id)
{
    Init();
}

void StyledWindow::Init() {
    SetMinSize(wxSize(DEFAULT_WIDTH, DEFAULT_HEIGHT));
    SetBackgroundStyle(wxBG_STYLE_PAINT);
}

void StyledWindow::OnPaint(wxPaintEvent& paintEvent) {
    paintEvent.Skip(true);
};

wxColor StyledWindow::GetInheritedBackgroundColor() {
    if (m_isOpaque || GetParent() == nullptr) {
        return GetBackgroundColour();
    }

    StyledWindow *styledWindowParent = dynamic_cast<StyledWindow*>(GetParent());
    if (styledWindowParent != nullptr) {
        return styledWindowParent->GetInheritedBackgroundColor();
    }

    return GetParent()->GetBackgroundColour();
}

} // namespace wxstyle