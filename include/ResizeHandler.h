#pragma once

#include <unordered_map>

#include "wx\event.h"
#include "wx\frame.h"
#include "wx\panel.h"

namespace wxstyle {

enum ResizeConstraint {
    VERTICAL,
    HORIZONTAL,
    DIAGONAL
};

class ResizeHandler : public wxEvtHandler {
public:
    ResizeHandler(wxFrame *const frame);
    void Install(wxPanel *panel, ResizeConstraint resizeConstraint);

private:
    void Start(const wxMouseEvent& mouseEvent);
    void Update(const wxMouseEvent& timerEvent);
    void Stop(const wxMouseEvent& mouseEvent);
    void DoStop();

private:
    bool m_isDragging;
    wxPoint m_startDragPosition;
    wxSize m_originalFrameSize;

    wxPanel *m_currentlyActivePanel;

    wxFrame *m_handledFrame;

    std::unordered_map<wxPanel*, ResizeConstraint> m_constraintMap;
};

} // namespace wxstyle