#pragma once

#include "wx/window.h"

#include "StyledWindow.h"

namespace wxstyle {

class StyledButton : public StyledWindow {
public:
    enum State
    {
        DISABLED = 0x0, 
        IDLE = 0x1, 
        HOVERED = 0x2, 
        ARMED = 0x4
    };

    StyledButton();
    StyledButton(wxWindow* parent, wxString text);
    virtual ~StyledButton();

protected:
    void OnMouseDown(wxMouseEvent& mouseEvent) override;
    void OnMouseDoubleClick(wxMouseEvent& mouseEvent) override;
    void OnMouseReleased(wxMouseEvent& mouseEvent) override;

    void OnMouseMoved(wxMouseEvent& mouseEvent) override;
    void OnMouseLeaveWindow(wxMouseEvent& mouseEvent) override;
    void OnMouseEnterWindow(wxMouseEvent& mouseEvent) override;

private:
    void ClearBackground(wxGraphicsContext *g);
    void SendClickEvent();

private:
    State m_state;
};

} // namespace wxstyle