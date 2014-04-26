#pragma once

#include "StyledWindow.h"
#include "wx\graphics.h"
#include "wx\dcbuffer.h"

 namespace wxstyle {

BEGIN_EVENT_TABLE(StyledWindow, wxWindow)

    // Input Events
    EVT_MOTION(StyledWindow::MouseMoved)
    EVT_LEFT_DOWN(StyledWindow::MouseDown)
    EVT_LEFT_DCLICK(StyledWindow::MouseDoubleClick)
    EVT_LEFT_UP(StyledWindow::MouseReleased)
    EVT_RIGHT_DOWN(StyledWindow::RightClick)
    EVT_LEAVE_WINDOW(StyledWindow::MouseLeaveWindow)
    EVT_ENTER_WINDOW(StyledWindow::MouseEnterWindow)
    EVT_KEY_DOWN(StyledWindow::KeyPressed)
    EVT_KEY_UP(StyledWindow::KeyReleased)
    EVT_MOUSEWHEEL(StyledWindow::MouseWheelMoved)
    EVT_MOUSE_EVENTS(StyledWindow::MouseEvents)

    EVT_SET_FOCUS(StyledWindow::FocusGained)
    EVT_KILL_FOCUS(StyledWindow::FocusLost)

    // Render Events
    EVT_PAINT(StyledWindow::Paint)
END_EVENT_TABLE()
 
StyledWindow::StyledWindow(wxWindow* parent, wxString text, wxStandardID id):
    wxWindow(parent, id),
    m_text(text)
{
    Init();
}

void StyledWindow::Init() {
    SetMinSize(wxSize(DEFAULT_WIDTH, DEFAULT_HEIGHT));
    SetBackgroundStyle(wxBG_STYLE_PAINT);
}

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