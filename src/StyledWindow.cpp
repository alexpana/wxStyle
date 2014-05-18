#pragma once

#include <wx/graphics.h>
#include <wx/dcbuffer.h>

#include "StyledWindow.h"

 namespace wxstyle {

	/** Hash function for wxString objects. **/
	struct wxStringHash {
	public:
		std::size_t operator()(const wxString& s) {
			return std::hash<const char*>()(s.GetData().AsChar());
		}
	};

	/** Implementation structure containing all private members. **/
	class StyledWindow::Implementation {
	public:
		bool isFocused;
		bool isHovered;
		bool isPressed;
		bool isOpaque;

		wxColor backgroundColor;

		wxString text;

		wxSize minSize;

		std::shared_ptr<IRenderer> renderer;
		std::shared_ptr<Style> style;

		std::unordered_map<wxString, wxString, wxStringHash> propertyMap;

		std::vector<std::shared_ptr<MouseListener>> mouseListeners;
		std::vector<std::shared_ptr<KeyboardListener>> keyboardListeners;
		std::vector<std::shared_ptr<FocusListener>> focusListeners;
		std::vector<std::shared_ptr<SizeListener>> sizeListeners;

	public:
		void NotifyMouseMoved(wxMouseEvent& mouseEvent);
		void NotifyMouseDown(wxMouseEvent& mouseEvent);
		void NotifyMouseDoubleClick(wxMouseEvent& mouseEvent);
		void NotifyMouseWheelMoved(wxMouseEvent& mouseEvent);
		void NotifyMouseReleased(wxMouseEvent& mouseEvent);
		void NotifyMouseLeaveWindow(wxMouseEvent& mouseEvent);
		void NotifyMouseEnterWindow(wxMouseEvent& mouseEvent);
		void NotifyKeyPressed(wxKeyEvent& keyEvent);
		void NotifyKeyReleased(wxKeyEvent& keyEvent);
		void NotifyFocusGained(wxFocusEvent& focusEvent);
		void NotifyFocusLost(wxFocusEvent& focusEvent);
		void NotifyResize(wxSizeEvent& resizeEvent);
	};

	StyledWindow::StyledWindow(wxWindow* parent, wxString text, wxStandardID id):
		wxWindow(parent, id)
	{
		pimpl = std::make_shared<Implementation>();
		pimpl->text = text;

		Init();
	}

	void StyledWindow::Init() {
		pimpl->isFocused = false;
		pimpl->isHovered = false;
		pimpl->isPressed = false;
		pimpl->isOpaque = true;

		SetMinSize(wxSize(DEFAULT_MIN_WIDTH, DEFAULT_MIN_HEIGHT));
		SetBackgroundStyle(wxBG_STYLE_PAINT);
        SetAutoLayout(true);	

		BindEventHandlers();
	}

	void StyledWindow::BindEventHandlers() {
		this->Bind(wxEVT_MOTION, &StyledWindow::MouseMoved, this);
		this->Bind(wxEVT_LEFT_DOWN, &StyledWindow::MouseDoubleClick, this);
		this->Bind(wxEVT_LEFT_DCLICK, &StyledWindow::MouseDoubleClick, this);
		this->Bind(wxEVT_LEFT_UP, &StyledWindow::MouseReleased, this);
		this->Bind(wxEVT_LEAVE_WINDOW, &StyledWindow::MouseLeaveWindow, this);
		this->Bind(wxEVT_ENTER_WINDOW, &StyledWindow::MouseEnterWindow, this);
		this->Bind(wxEVT_MOUSEWHEEL, &StyledWindow::MouseWheelMoved, this);

		this->Bind(wxEVT_KEY_DOWN, &StyledWindow::KeyPressed, this);
		this->Bind(wxEVT_KEY_UP, &StyledWindow::KeyReleased, this);

		this->Bind(wxEVT_SET_FOCUS, &StyledWindow::FocusGained, this);
		this->Bind(wxEVT_KILL_FOCUS, &StyledWindow::FocusLost, this);

		this->Bind(wxEVT_SIZE, &StyledWindow::Resize, this);

		this->Bind(wxEVT_PAINT, &StyledWindow::Paint, this);
	}

	wxColor StyledWindow::GetInheritedBackgroundColor() {
		if (pimpl->isOpaque || GetParent() == nullptr) {
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
		auto p = pimpl->propertyMap.find(propertyName);
		if (p == pimpl->propertyMap.end()) {
			return EMPTY_VALUE;
		} else {
			return p->second;
		}
	}

	void StyledWindow::SetProperty(const wxString& propertyName, const wxString& propertyValue) {
		pimpl->propertyMap[propertyName] = propertyValue;
	}

	void StyledWindow::UnsetProperty(const wxString& propertyName) {
		pimpl->propertyMap.erase(propertyName);
	}

	boost::optional<wxString> StyledWindow::GetComponentProperty(const wxString& propertyName) {
		if (propertyName == "text") {
			return pimpl->text;
		}

		if (propertyName == "focused") {
			return pimpl->isFocused ? "t" : "f";
		}


		if (propertyName == "hovered") {
			return pimpl->isHovered ? "t" : "f";
		}

		if (propertyName == "pressed") {
			return pimpl->isPressed ? "t" : "f";
		}

		return boost::optional<wxString>();
	}

    void StyledWindow::SetText(const wxString& text) {
		pimpl->text = text;
	}

    wxString StyledWindow::GetText() const {
		return pimpl->text;
	}

    void StyledWindow::SetStyle(std::shared_ptr<Style> style) {
		pimpl->style = style;
	}

    std::shared_ptr<Style> StyledWindow::GetStyle() {
		return pimpl->style;
	}

	void StyledWindow::SetMinSize(const wxSize& size) {
		pimpl->minSize = size;
	}

	wxSize StyledWindow::GetMinSize() const {
		return pimpl->minSize;
	}

    void StyledWindow::SetRenderer(std::shared_ptr<IRenderer> renderer) {
		pimpl->renderer = renderer;
	}

	std::shared_ptr<IRenderer> StyledWindow::GetRenderer() {
		return pimpl->renderer;
	}

    void StyledWindow::SetOpaque(bool opaque) {
		pimpl->isOpaque = opaque;
	}

    bool StyledWindow::IsOpaque() const {
		return pimpl->isOpaque;
	}

	bool StyledWindow::IsFocused() const {
		return pimpl->isFocused;
	}

	bool StyledWindow::IsHovered() const {
		return pimpl->isHovered;
	}

	bool StyledWindow::IsPressed() const {
		return pimpl->isPressed;
	}

	void StyledWindow::OnPaint(wxPaintEvent& paintEvent) {
		pimpl->renderer->Render(this);
		paintEvent.Skip(false);
	}

	void StyledWindow::MouseMoved(wxMouseEvent& mouseEvent) { 
		OnMouseMoved(mouseEvent); 
		pimpl->NotifyMouseMoved(mouseEvent);
	}

	void StyledWindow::MouseDown(wxMouseEvent& mouseEvent) { 
		pimpl->isPressed = true;
		OnMouseDown(mouseEvent);
		pimpl->NotifyMouseDown(mouseEvent);
	}

	void StyledWindow::MouseDoubleClick(wxMouseEvent& mouseEvent) {
		pimpl->isPressed = true;
		OnMouseDoubleClick(mouseEvent); 
		pimpl->NotifyMouseDoubleClick(mouseEvent);
	}

	void StyledWindow::MouseReleased(wxMouseEvent& mouseEvent) { 
		pimpl->isPressed = false;
		OnMouseReleased(mouseEvent); 
		pimpl->NotifyMouseReleased(mouseEvent);
	}

	void StyledWindow::MouseWheelMoved(wxMouseEvent& mouseEvent) { 
		OnMouseWheelMoved(mouseEvent); 
		pimpl->NotifyMouseWheelMoved(mouseEvent);
	}

	void StyledWindow::MouseEnterWindow(wxMouseEvent& mouseEvent) { 
		pimpl->isHovered = true;
		if (mouseEvent.ButtonIsDown(wxMOUSE_BTN_LEFT)) {
			pimpl->isPressed = true;
		}

		OnMouseEnterWindow(mouseEvent); 
		pimpl->NotifyMouseEnterWindow(mouseEvent);
	}

	void StyledWindow::MouseLeaveWindow(wxMouseEvent& mouseEvent) { 
		pimpl->isHovered = false;
		pimpl->isPressed = false;

		OnMouseLeaveWindow(mouseEvent); 
		pimpl->NotifyMouseLeaveWindow(mouseEvent);
	}

	void StyledWindow::KeyPressed(wxKeyEvent& keyEvent) { 
		OnKeyPressed(keyEvent); 
		pimpl->NotifyKeyPressed(keyEvent);
	}

	void StyledWindow::KeyReleased(wxKeyEvent& keyEvent) { 
		OnKeyReleased(keyEvent); 
		pimpl->NotifyKeyReleased(keyEvent);
	}

	void StyledWindow::FocusGained(wxFocusEvent& focusEvent) { 
		pimpl->isFocused = true;
		OnFocusGained(focusEvent); 
		pimpl->NotifyFocusGained(focusEvent);
	}

	void StyledWindow::FocusLost(wxFocusEvent& focusEvent) { 
		pimpl->isFocused = false;
		OnFocusLost(focusEvent); 
		pimpl->NotifyFocusLost(focusEvent);
	}

	void StyledWindow::Resize(wxSizeEvent& resizeEvent) { 
		Layout();
		OnResize(resizeEvent); 
		pimpl->NotifyResize(resizeEvent);
	}

	void StyledWindow::Paint(wxPaintEvent& paintEvent) { 
		OnPaint(paintEvent); 
	};

	void StyledWindow::RegisterMouseListener(const std::shared_ptr<MouseListener>& listener) {
		pimpl->mouseListeners.push_back(listener);
	}

	void StyledWindow::UnregisterMouseListener(const std::shared_ptr<MouseListener>& listener) {
		auto v = pimpl->mouseListeners;
		v.erase(std::remove(std::begin(v), std::end(v), listener), v.end());
	}

	void StyledWindow::RegisterKeyboardListener(const std::shared_ptr<KeyboardListener>& listener) {
		pimpl->keyboardListeners.push_back(listener);
	}

	void StyledWindow::UnregisterKeyboardListener(const std::shared_ptr<KeyboardListener>& listener) {
		auto v = pimpl->keyboardListeners;
		v.erase(std::remove(std::begin(v), std::end(v), listener), v.end());
	}

	void StyledWindow::RegisterFocusListener(const std::shared_ptr<FocusListener>& listener) {
		pimpl->focusListeners.push_back(listener);
	}

	void StyledWindow::UnregisterFocusListener(const std::shared_ptr<FocusListener>& listener) {
		auto v = pimpl->focusListeners;
		v.erase(std::remove(std::begin(v), std::end(v), listener), v.end());

	}

	void StyledWindow::RegisterSizeListener(const std::shared_ptr<SizeListener>& listener) {
		pimpl->sizeListeners.push_back(listener);
	}

	void StyledWindow::UnregisterSizeListener(const std::shared_ptr<SizeListener>& listener) {
		auto v = pimpl->sizeListeners;
		v.erase(std::remove(std::begin(v), std::end(v), listener), v.end());
	}

	void StyledWindow::Implementation::NotifyMouseMoved(wxMouseEvent& mouseEvent) {
		for (auto listener : mouseListeners) {
			listener->MouseMoved(mouseEvent);
		}
	}

	void StyledWindow::Implementation::NotifyMouseDown(wxMouseEvent& mouseEvent) {
		for (auto listener : mouseListeners) {
			listener->MouseDown(mouseEvent);
		}
	}

	void StyledWindow::Implementation::NotifyMouseDoubleClick(wxMouseEvent& mouseEvent) {
		for (auto listener : mouseListeners) {
			listener->MouseDoubleClick(mouseEvent);
		}
	}

	void StyledWindow::Implementation::NotifyMouseWheelMoved(wxMouseEvent& mouseEvent) {
		for (auto listener : mouseListeners) {
			listener->MouseWheelMoved(mouseEvent);
		}
	}

	void StyledWindow::Implementation::NotifyMouseReleased(wxMouseEvent& mouseEvent) {
		for (auto listener : mouseListeners) {
			listener->MouseReleased(mouseEvent);
		}
	}

	void StyledWindow::Implementation::NotifyMouseLeaveWindow(wxMouseEvent& mouseEvent) {
		for (auto listener : mouseListeners) {
			listener->MouseLeaveWindow(mouseEvent);
		}
	}

	void StyledWindow::Implementation::NotifyMouseEnterWindow(wxMouseEvent& mouseEvent) {
		for (auto listener : mouseListeners) {
			listener->MouseEnterWindow(mouseEvent);
		}
	}

	void StyledWindow::Implementation::NotifyKeyPressed(wxKeyEvent& keyEvent) {
		for (auto listener : keyboardListeners) {
			listener->KeyPressed(keyEvent);
		}
	}

	void StyledWindow::Implementation::NotifyKeyReleased(wxKeyEvent& keyEvent) {
		for (auto listener : keyboardListeners) {
			listener->KeyReleased(keyEvent);
		}
	}

	void StyledWindow::Implementation::NotifyFocusGained(wxFocusEvent& focusEvent) {
		for (auto listener : focusListeners) {
			listener->FocusGained(focusEvent);
		}
	}

	void StyledWindow::Implementation::NotifyFocusLost(wxFocusEvent& focusEvent) {
		for (auto listener : focusListeners) {
			listener->FocusLost(focusEvent);
		}
	}

	void StyledWindow::Implementation::NotifyResize(wxSizeEvent& resizeEvent) {
		for (auto listener : sizeListeners) {
			listener->Resize(resizeEvent);
		}
	}
} // namespace wxstyle