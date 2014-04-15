#include "ResizeHandler.h"

#include <algorithm>

#include <wx/gdicmn.h>

namespace wxstyle {

ResizeHandler::ResizeHandler(wxFrame *const frame) : 
    m_handledFrame(frame),
    m_startDragPosition(wxPoint(0, 0)), m_originalFrameSize(wxSize(0, 0)), m_isDragging(false),
    m_currentlyActivePanel(nullptr)
{
}

void ResizeHandler::Install(wxPanel *panel, ResizeConstraint resizeConstraints) {
    panel->Bind(wxEVT_LEFT_DOWN, &ResizeHandler::Start, this);
    panel->Bind(wxEVT_LEFT_UP, &ResizeHandler::Stop, this);
    panel->Bind(wxEVT_MOTION, &ResizeHandler::Update, this);

    m_constraintMap[panel] = resizeConstraints;
}

void ResizeHandler::Start(const wxMouseEvent& mouseEvent) {
    m_currentlyActivePanel = dynamic_cast<wxPanel*>(mouseEvent.GetEventObject());
    m_currentlyActivePanel->CaptureMouse();

    m_originalFrameSize = m_handledFrame->GetSize();
    m_startDragPosition = wxGetMousePosition();
    m_isDragging = true;
}

void ResizeHandler::Update(const wxMouseEvent& timerEvent) {
    if (!wxGetMouseState().LeftIsDown()) {
        DoStop();
    }

    if (!m_isDragging) {
        return;
    }

    ResizeConstraint resizeConstraint = m_constraintMap.find(m_currentlyActivePanel)->second;
    int dx = wxGetMousePosition().x - m_startDragPosition.x;
    int dy = wxGetMousePosition().y - m_startDragPosition.y;

    int w = m_originalFrameSize.GetWidth();
    int h = m_originalFrameSize.GetHeight();

    int minW = m_handledFrame->GetMinSize().GetWidth();
    int minH = m_handledFrame->GetMinSize().GetHeight();

    switch (resizeConstraint) {
    case VERTICAL:
        m_handledFrame->SetSize(wxSize(w, std::max(minH, h + dy)));
        break;
    case HORIZONTAL:
        m_handledFrame->SetSize(wxSize(std::max(minW, w + dx), h));
        break;
    case DIAGONAL:
        m_handledFrame->SetSize(wxSize(std::max(minW, w + dx), std::max(minH, h + dy)));
        break;
    }
}

void ResizeHandler::Stop(const wxMouseEvent& mouseEvent) {
    DoStop();
}

void ResizeHandler::DoStop() {
    m_isDragging = false;

    if (m_currentlyActivePanel != nullptr && m_currentlyActivePanel->HasCapture()) {
        m_currentlyActivePanel->ReleaseMouse();
    }

    m_currentlyActivePanel = nullptr;
}

} // namespace wxstyle