#pragma once

#include <memory>
#include <unordered_map>

#include <boost/optional.hpp>

#include <wx/dcbuffer.h>
#include <wx/sizer.h>
#include <wx/colour.h>


#include "Renderer.h"
#include "style/Style.h"

namespace wxstyle {

    /**
     *  Abstract Base Class for styled windows.
     *
     *  All windows that support custom renderers must inherit from this class.
     *  The StyledWindow class offers virtual methods for handling mouse, keyboard,
     *  focus, and rendering events, as well as offering basic support for 
     *  transparency.
     */
    class StyledWindow : public wxWindow
    { 
	protected:
		static const int DEFAULT_MIN_WIDTH = 100;
		static const int DEFAULT_MIN_HEIGHT = 30;

	public:
		class MouseListener {
		public:
			virtual void MouseMoved(wxMouseEvent& mouseEvent) {}
			virtual void MouseDown(wxMouseEvent& mouseEvent) {}
			virtual void MouseDoubleClick(wxMouseEvent& mouseEvent) {}
			virtual void MouseWheelMoved(wxMouseEvent& mouseEvent) {}
			virtual void MouseReleased(wxMouseEvent& mouseEvent) {}

			virtual void MouseLeaveWindow(wxMouseEvent& mouseEvent) {}
			virtual void MouseEnterWindow(wxMouseEvent& mouseEvent) {}
		};

		class KeyboardListener {
		public:
			virtual void KeyPressed(wxKeyEvent& keyEvent) {}
			virtual void KeyReleased(wxKeyEvent& keyEvent) {}
		};

		class FocusListener {
		public:
			virtual void FocusGained(wxFocusEvent& focusEvent) {}
			virtual void FocusLost(wxFocusEvent& focusEvent) {}
		};

		class SizeListener {
		public:
			virtual void Resize(wxSizeEvent& resizeEvent) {}
		};

    public:
        StyledWindow(wxWindow* parent = nullptr, wxString text = "", wxStandardID id = wxID_ANY);
        virtual ~StyledWindow() {}

		/** Opacity **/
        virtual void SetOpaque(bool opaque);
        virtual bool IsOpaque() const;

        /**
         *  Returns the background color of the window.
         *
         *  This method is intended to be a replacement for wxWindow's 
         *  GetBackground, because that method is not virtual and doesn't allow
         *  for transparency considerations.
         *
         *  The name "Inherited" is meant to indicate the fact that
         *  StyledWindows inherit the background color of their parents if not opaque.
         */
        virtual wxColor GetInheritedBackgroundColor();

        /** Renderer **/
        void SetRenderer(std::shared_ptr<IRenderer> renderer);
        std::shared_ptr<IRenderer> GetRenderer();

		/** Insets **/
		wxRect GetInsets() const;
		void SetInsets(const wxRect& insets);

		wxSize GetTextMetrics() const;

		/** Focus **/
        bool IsFocused() const;

		/** Hover state **/
        bool IsHovered() const;

		/** Press state **/
		bool IsPressed() const;

		/** Mouse Listeners **/
		void RegisterMouseListener(const std::shared_ptr<MouseListener>& listener);
		void UnregisterMouseListener(const std::shared_ptr<MouseListener>& listener);

		/** Mouse Listeners **/
		void RegisterKeyboardListener(const std::shared_ptr<KeyboardListener>& listener);
		void UnregisterKeyboardListener(const std::shared_ptr<KeyboardListener>& listener);

		/** Mouse Listeners **/
		void RegisterFocusListener(const std::shared_ptr<FocusListener>& listener);
		void UnregisterFocusListener(const std::shared_ptr<FocusListener>& listener);

		/** Mouse Listeners **/
		void RegisterSizeListener(const std::shared_ptr<SizeListener>& listener);
		void UnregisterSizeListener(const std::shared_ptr<SizeListener>& listener);

		/** Text **/
        virtual void SetText(const wxString& text);
        virtual wxString GetText() const;

		/** Style **/
        virtual void SetStyle(std::shared_ptr<Style> style);
        virtual std::shared_ptr<Style> GetStyle();

		/** MinSize **/
		wxSize GetMinSize() const override;
		void SetMinSize(const wxSize& size) override;

		/** Property **/
		boost::optional<wxString> GetProperty(const wxString& propertyName);
		void SetProperty(const wxString& propertyName, const wxString& propertyValue);
		void UnsetProperty(const wxString& propertyName);

    protected:
        virtual void OnMouseMoved(wxMouseEvent& mouseEvent) { Refresh(); }
        virtual void OnMouseDown(wxMouseEvent& mouseEvent) { Refresh(); }
        virtual void OnMouseDoubleClick(wxMouseEvent& mouseEvent) { Refresh(); }
        virtual void OnMouseWheelMoved(wxMouseEvent& mouseEvent) { Refresh(); }
        virtual void OnMouseReleased(wxMouseEvent& mouseEvent) { Refresh(); }
        virtual void OnRightClick(wxMouseEvent& mouseEvent) { Refresh(); }
        virtual void OnMouseLeaveWindow(wxMouseEvent& mouseEvent) { Refresh(); }
        virtual void OnMouseEnterWindow(wxMouseEvent& mouseEvent) { Refresh(); }
        virtual void OnMouseEvents(wxMouseEvent& mouseEvent) { Refresh(); }
        virtual void OnKeyPressed(wxKeyEvent& keyEvent) { Refresh(); }
        virtual void OnKeyReleased(wxKeyEvent& keyEvent) { Refresh(); }
        virtual void OnFocusGained(wxFocusEvent& focusEvent) { Refresh(); }
        virtual void OnFocusLost(wxFocusEvent& focusEvent) { Refresh(); }
        virtual void OnPaint(wxPaintEvent& paintEvent);
        virtual void OnResize(wxSizeEvent& resizeEvent) { Refresh(); };

		virtual boost::optional<wxString> GetComponentProperty(const wxString& propertyName);

    private:
        void Init();
		void BindEventHandlers();

	private:
        void MouseMoved(wxMouseEvent& mouseEvent);
        void MouseDown(wxMouseEvent& mouseEvent);
        void MouseDoubleClick(wxMouseEvent& mouseEvent);
		void MouseReleased(wxMouseEvent& mouseEvent);
        void MouseWheelMoved(wxMouseEvent& mouseEvent);
        void MouseEnterWindow(wxMouseEvent& mouseEvent);
        void MouseLeaveWindow(wxMouseEvent& mouseEvent);
        void KeyPressed(wxKeyEvent& keyEvent);
        void KeyReleased(wxKeyEvent& keyEvent);
        void FocusGained(wxFocusEvent& focusEvent);
        void FocusLost(wxFocusEvent& focusEvent);
        void Resize(wxSizeEvent& resizeEvent);
        void Paint(wxPaintEvent& paintEvent);

    private:
		class Implementation;
		std::shared_ptr<Implementation> pimpl;
    };

} // namespace wxstyle