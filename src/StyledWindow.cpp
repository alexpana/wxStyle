#pragma once

#include <wx/graphics.h>
#include <wx/dcbuffer.h>

#include "StyledWindow.h"

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
		m_isFocused = false;
		m_isHovered = false;
		m_isPressed = false;
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

	boost::optional<wxString> StyledWindow::GetProperty(const wxString& propertyName) {
		static const auto EMPTY_VALUE = boost::optional<wxString>();
		
		// check for component-defined properties
		auto componentProperty = GetComponentProperty(propertyName);
		if (componentProperty) {
			return componentProperty.get();
		}

		// check for user-defined properties
		auto p = m_propertyMap.find(propertyName);
		if (p == m_propertyMap.end()) {
			return EMPTY_VALUE;
		} else {
			return p->second;
		}
	}

	void StyledWindow::SetProperty(const wxString& propertyName, const wxString& propertyValue) {
		m_propertyMap[propertyName] = propertyValue;
	}

	void StyledWindow::UnsetProperty(const wxString& propertyName) {
		m_propertyMap.erase(propertyName);
	}

	boost::optional<wxString> StyledWindow::GetComponentProperty(const wxString& propertyName) {

		if (propertyName == "text") {
			return m_text;
		}

		if (propertyName == "focused") {
			return m_isFocused ? "t" : "f";
		}

		if (propertyName == "hovered") {
			return m_isHovered ? "t" : "f";
		}

		if (propertyName == "pressed") {
			return m_isPressed ? "t" : "f";
		}

		return boost::optional<wxString>();
	}

} // namespace wxstyle