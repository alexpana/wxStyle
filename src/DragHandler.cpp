#include "DragHandler.h"

#include <wx/gdicmn.h>

namespace wxstyle {

DragHandler::DragHandler(wxWindow *const window) : 
    m_handledWindow(window),
    m_startDragPosition(wxPoint(0, 0)), m_originalFramePosition(wxPoint(0, 0)), m_isDragging(false),
    m_activeWindow(nullptr)
{
}

void DragHandler::Install(wxWindow *window) {
    window->Bind(wxEVT_LEFT_DOWN, &DragHandler::Start, this);
    window->Bind(wxEVT_LEFT_UP, &DragHandler::Stop, this);
    window->Bind(wxEVT_MOTION, &DragHandler::Update, this);
}

void DragHandler::Start(const wxMouseEvent& mouseEvent) {
    m_originalFramePosition = m_handledWindow->GetPosition();
    m_startDragPosition = wxGetMousePosition();
    m_isDragging = true;

    m_activeWindow = dynamic_cast<wxWindow*>(mouseEvent.GetEventObject());
    m_activeWindow->CaptureMouse();
}

void DragHandler::Update(const wxMouseEvent& mouseEvent) {
    if (!wxGetMouseState().LeftIsDown()) {
        DoStop();
    }

    if (m_isDragging) {
        m_handledWindow->SetPosition(m_originalFramePosition + wxGetMousePosition() - m_startDragPosition);
    }
}

void DragHandler::Stop(const wxMouseEvent& mouseEvent) {
    DoStop();
}

void DragHandler::DoStop() {
    m_isDragging = false;

    if( m_activeWindow != nullptr && m_activeWindow->HasCapture()) {
        m_activeWindow->ReleaseMouse();
    }

    m_activeWindow = nullptr;
}

} // namespace wxstyle