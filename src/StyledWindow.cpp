#pragma once

#include <wx/graphics.h>
#include <wx/dcbuffer.h>

#include "Insets.h"
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
        bool isDisabled;

		wxColor backgroundColor;

		wxString text;

		wxSize minSize;

        Insets insets;

		std::shared_ptr<IRenderer> renderer;
		Style style;

		std::unordered_map<wxString, wxString, wxStringHash> propertyMap;

		std::vector<std::shared_ptr<MouseListener>> mouseListeners;
		std::vector<std::shared_ptr<KeyboardListener>> keyboardListeners;
		std::vector<std::shared_ptr<FocusListener>> focusListeners;
		std::vector<std::shared_ptr<SizeListener>> sizeListeners;

	public:
		void NotifyMouseMoved(const wxMouseEvent& mouseEvent);
		void NotifyMouseDown(const wxMouseEvent& mouseEvent);
		void NotifyMouseDoubleClick(const wxMouseEvent& mouseEvent);
		void NotifyMouseWheelMoved(const wxMouseEvent& mouseEvent);
		void NotifyMouseReleased(const wxMouseEvent& mouseEvent);
		void NotifyMouseLeaveWindow(const wxMouseEvent& mouseEvent);
		void NotifyMouseEnterWindow(const wxMouseEvent& mouseEvent);
		void NotifyKeyPressed(const wxKeyEvent& keyEvent);
		void NotifyKeyReleased(const wxKeyEvent& keyEvent);
		void NotifyFocusGained(const wxFocusEvent& focusEvent);
		void NotifyFocusLost(const wxFocusEvent& focusEvent);
		void NotifyResize(const wxSizeEvent& resizeEvent);
	};

    Style StyledWindow::GetDefaultStyle() {
        DefinitionBundle defaultBundle;
        defaultBundle.SetBackgroundColor("#2B2A2A");
        defaultBundle.SetForegroundColor("#AFAFAF");
        defaultBundle.SetOpacity(true);
        defaultBundle.SetFont(FontDefinition().SetFace("Tahoma").SetSize(9).SetStyle(wxFONTSTYLE_NORMAL).SetWeight(wxFONTWEIGHT_BOLD));
        defaultBundle.SetShadow(ShadowDefinition().SetColor(wxTRANSPARENT).SetOffset(wxPoint(0, 0)));
        return Style().AddBundle(Style::CAT_DEFAULT, defaultBundle);
    }

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
        pimpl->isDisabled = false;
        pimpl->minSize = wxSize(DEFAULT_MIN_WIDTH, DEFAULT_MIN_HEIGHT);

        SetStyle(StyledWindow::GetDefaultStyle());

		SetMinSize(pimpl->minSize);
		SetBackgroundStyle(wxBG_STYLE_PAINT);
        SetAutoLayout(true);	

		BindEventHandlers();
	}

	void StyledWindow::BindEventHandlers() {
		this->Bind(wxEVT_MOTION, &StyledWindow::MouseMoved, this);
		this->Bind(wxEVT_LEFT_DOWN, &StyledWindow::MouseDown, this);
		this->Bind(wxEVT_LEFT_DCLICK, &StyledWindow::MouseDoubleClick, this);
		this->Bind(wxEVT_LEFT_UP, &StyledWindow::MouseReleased, this);
		this->Bind(wxEVT_LEAVE_WINDOW, &StyledWindow::MouseLeaveWindow, this);
		this->Bind(wxEVT_ENTER_WINDOW, &StyledWindow::MouseEnterWindow, this);
		this->Bind(wxEVT_MOUSEWHEEL, &StyledWindow::MouseWheelMoved, this);

		this->Bind(wxEVT_KEY_DOWN, &StyledWindow::KeyPressed, this);
		this->Bind(wxEVT_KEY_UP, &StyledWindow::KeyReleased, this);
        this->Bind(wxEVT_CHAR, &StyledWindow::KeyChar, this);

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

    void StyledWindow::SetText(const wxString& text) {
		pimpl->text = text;
	}

    wxString StyledWindow::GetText() const {
		return pimpl->text;
	}

    void StyledWindow::SetStyle(const Style& style) {
		pimpl->style = style;
	}

    Style StyledWindow::GetStyle() const {
        return pimpl->style;
    }

    DefinitionBundle StyledWindow::GetDefinitionBundle() const {
        DefinitionBundle resultBundle = GetStyle().GetBundle(Style::CAT_DEFAULT);
        DefinitionBundle modifierBundle;

        if (IsFocused()) 
            resultBundle = DefinitionBundle::Merge(resultBundle, GetStyle().GetBundle(Style::CAT_FOCUSED));

        if (IsPressed())
            resultBundle = DefinitionBundle::Merge(resultBundle, GetStyle().GetBundle(Style::CAT_PRESSED));

        if (IsHovered())
            resultBundle = DefinitionBundle::Merge(resultBundle, GetStyle().GetBundle(Style::CAT_HOVERED));

        if (IsDisabled())
            resultBundle = DefinitionBundle::Merge(resultBundle, GetStyle().GetBundle(Style::CAT_DISABLED));

		return resultBundle;
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

    Insets StyledWindow::GetInsets() const {
        return pimpl->insets;
    }

    void StyledWindow::SetInsets(const Insets& insets) {
        pimpl->insets = insets;
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

    void StyledWindow::SetDisabled(bool disabled) {
        pimpl->isDisabled = disabled;
    }

    bool StyledWindow::IsDisabled() const {
        return pimpl->isDisabled;
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

    void StyledWindow::KeyChar(wxKeyEvent& keyEvent) {
        OnKeyChar(keyEvent);
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

	void StyledWindow::Implementation::NotifyMouseMoved(const wxMouseEvent& mouseEvent) {
		for (auto listener : mouseListeners) {
			listener->MouseMoved(mouseEvent);
		}
	}

	void StyledWindow::Implementation::NotifyMouseDown(const wxMouseEvent& mouseEvent) {
		for (auto listener : mouseListeners) {
			listener->MouseDown(mouseEvent);
		}
	}

	void StyledWindow::Implementation::NotifyMouseDoubleClick(const wxMouseEvent& mouseEvent) {
		for (auto listener : mouseListeners) {
			listener->MouseDoubleClick(mouseEvent);
		}
	}

	void StyledWindow::Implementation::NotifyMouseWheelMoved(const wxMouseEvent& mouseEvent) {
		for (auto listener : mouseListeners) {
			listener->MouseWheelMoved(mouseEvent);
		}
	}

	void StyledWindow::Implementation::NotifyMouseReleased(const wxMouseEvent& mouseEvent) {
		for (auto listener : mouseListeners) {
			listener->MouseReleased(mouseEvent);
		}
	}

	void StyledWindow::Implementation::NotifyMouseLeaveWindow(const wxMouseEvent& mouseEvent) {
		for (auto listener : mouseListeners) {
			listener->MouseLeaveWindow(mouseEvent);
		}
	}

	void StyledWindow::Implementation::NotifyMouseEnterWindow(const wxMouseEvent& mouseEvent) {
		for (auto listener : mouseListeners) {
			listener->MouseEnterWindow(mouseEvent);
		}
	}

	void StyledWindow::Implementation::NotifyKeyPressed(const wxKeyEvent& keyEvent) {
		for (auto listener : keyboardListeners) {
			listener->KeyPressed(keyEvent);
		}
	}

	void StyledWindow::Implementation::NotifyKeyReleased(const wxKeyEvent& keyEvent) {
		for (auto listener : keyboardListeners) {
			listener->KeyReleased(keyEvent);
		}
	}

	void StyledWindow::Implementation::NotifyFocusGained(const wxFocusEvent& focusEvent) {
		for (auto listener : focusListeners) {
			listener->FocusGained(focusEvent);
		}
	}

	void StyledWindow::Implementation::NotifyFocusLost(const wxFocusEvent& focusEvent) {
		for (auto listener : focusListeners) {
			listener->FocusLost(focusEvent);
		}
	}

	void StyledWindow::Implementation::NotifyResize(const wxSizeEvent& resizeEvent) {
		for (auto listener : sizeListeners) {
			listener->Resize(resizeEvent);
		}
	}
} // namespace wxstyle