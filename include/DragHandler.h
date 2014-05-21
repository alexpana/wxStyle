#pragma once

#include <wx/event.h>
#include <wx/timer.h>
#include <wx/panel.h>
#include <wx/frame.h>

namespace wxstyle {

    class StyledWindow;

    class DragHandler : public wxEvtHandler {
    public:
        DragHandler(wxWindow *const handledWindow);
        void Install(StyledWindow *window);

        void Start(const wxMouseEvent& mouseEvent);
        void Update(const wxMouseEvent& mouseEvent);
        void Stop(const wxMouseEvent& mouseEvent);
        void DoStop();

    private:
        bool m_isDragging;
        wxPoint m_startDragPosition;
        wxPoint m_originalFramePosition;

        wxWindow *m_activeWindow;

        wxWindow *m_handledWindow;
    };

} // namespace wxstyle