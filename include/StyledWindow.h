#pragma once

#include <wx/dcbuffer.h>
#include <wx/sizer.h>
#include <wx/colour.h>

namespace wxstyle {

/**
 *  Base class for styled controls.
 */
class StyledWindow : public wxWindow
{ 
public:
    StyledWindow(wxWindow* parent);
    StyledWindow(wxWindow* parent, wxString text);
    StyledWindow(wxWindow* parent, wxStandardID id, wxString text);

    virtual ~StyledWindow() {}

    virtual void SetOpaque(bool opaque) {
        m_isOpaque = opaque;
    }

    virtual bool IsOpaque() {
        return m_isOpaque;
    }

    /* Paint this window on the device context. */
    virtual void Paint() {};

    virtual wxColor GetInheritedBackgroundColor();

protected:
    // mouse events
    virtual void OnMouseMoved(wxMouseEvent& mouseEvent) { Refresh(); }
    virtual void OnMouseDown(wxMouseEvent& mouseEvent) { Refresh(); }
    virtual void OnMouseDoubleClick(wxMouseEvent& mouseEvent) { Refresh(); }
    virtual void OnMouseWheelMoved(wxMouseEvent& mouseEvent) { Refresh(); }
    virtual void OnMouseReleased(wxMouseEvent& mouseEvent) { Refresh(); }
    virtual void OnRightClick(wxMouseEvent& mouseEvent) { Refresh(); }
    virtual void OnMouseLeaveWindow(wxMouseEvent& mouseEvent) { Refresh(); }
    virtual void OnMouseEnterWindow(wxMouseEvent& mouseEvent) { Refresh(); }
    virtual void OnMouseEvents(wxMouseEvent& mouseEvent) { Refresh(); }

    // keyboard events
    virtual void OnKeyPressed(wxKeyEvent& keyEvent) { Refresh(); }
    virtual void OnKeyReleased(wxKeyEvent& keyEvent) { Refresh(); }

    // focus events
    virtual void OnFocusGained(wxFocusEvent& focusEvent) { Refresh(); }
    virtual void OnFocusLost(wxFocusEvent& focusEvent) { Refresh(); }

    // paint event
    virtual void OnPaint(wxPaintEvent& paintEvent);

    wxGraphicsContext* CreateGraphicsContext();

    static const int DEFAULT_WIDTH = 200;
    static const int DEFAULT_HEIGHT = 30;

private:
    void Init();


private:
    bool m_isOpaque;
    wxColor m_backgroundColor;

    DECLARE_EVENT_TABLE()
};

} // namespace wxstyle