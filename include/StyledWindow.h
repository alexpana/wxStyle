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
    public:

        /**
         *  Default constructor.Every window must have a parent on which to
         *  draw itself.
         */
        StyledWindow(wxWindow* parent = nullptr, wxString text = "", wxStandardID id = wxID_ANY);

        virtual ~StyledWindow() {}

        /**
         *  Sets the opacity of the window.
         *  
         *  Non-opaque windows inherit their parent's background color. Opaque windows
         *  use their own background color.
         */
        virtual void SetOpaque(bool opaque) {
            m_isOpaque = opaque;
        }

        /**
         *  Returns whether or not the window is opaque.
         */
        virtual bool IsOpaque() {
            return m_isOpaque;
        }

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

        /**
         *  Assigns the renderer to the window.
         *
         *  The renderer will be used starting with the next paint event to
         *  draw the contents of this window.
         */
        void SetRenderer(std::shared_ptr<IRenderer> renderer) {
            m_renderer = renderer;
        }

        /**
         *  Returns a shared pointer to the renderer currently assigned to this window.
         */
        std::shared_ptr<IRenderer> GetRenderer() {
            return m_renderer;
        }

        /**
         *  Returns whether or not this window has focus. There can be only one focused
         *  window at any given time. Focused windows receive keyboard events and are drawn
         *  slightly highlighted.
         */
        bool IsFocused() { 
            return m_isFocused; 
        }

        bool IsHovered() {
            return m_isHovered;
        }

		bool IsPressed() {
			return m_isPressed;
		}

        virtual void SetText(const wxString& text) {
            m_text = text;
        }

        /**
         *  Returns the text of the window.
         */
        virtual wxString GetText() {
            return m_text;
        }

        /**
         *  Sets the style of the window.
         *  Note that styles can be shared between windows.
         */
        virtual void SetStyle(std::shared_ptr<Style> style) {
            m_style = style;
        }

        /**
         *  Returns the style used by the window.
         */
        virtual std::shared_ptr<Style> GetStyle() {
            return m_style;
        }

		/**
		 *	Searches for a property from its name.
		 *
		 *	Some components define custom properties to be queried
		 *	by the style system: a combobox can be checked or unchecked,
		 *	a loading bar has a fill percentage, etc.
		 *
		 *	Clients can define their own custom properties to be used
		 *	inside styles, or other situations.
		 */
		boost::optional<wxString> GetProperty(const wxString& propertyName);

		/**
		 *	Sets the value of a user-defined property. This is overridden
		 *	by any component specific properties.
		 */
		void SetProperty(const wxString& propertyName, const wxString& propertyValue);

		/**
		 *	Unset a user-defined property. This does not work for component-
		 *	specific properties.
		 */
		void UnsetProperty(const wxString& propertyName);

    protected:

        /* Handling method for mouse motion events. */
        virtual void OnMouseMoved(wxMouseEvent& mouseEvent) { Refresh(); }

        /* Handle method for mouse button press events. */
        virtual void OnMouseDown(wxMouseEvent& mouseEvent) { Refresh(); }

        /**
         *  Handle method for mouse double click events. This method is called
         *  on the second mouse down event, not up!
         *
         *  NOTE: Double click events are forcedly interpreted by wxWidgets
         *  and we cannot avoid them. They may interfere with the window's basic
         *  mouse down process, so it's not uncommon to delegate the event
         *  to the mouse down handle method.
         */
        virtual void OnMouseDoubleClick(wxMouseEvent& mouseEvent) { Refresh(); }

        /* Handle method for mouse wheel events. */
        virtual void OnMouseWheelMoved(wxMouseEvent& mouseEvent) { Refresh(); }

        /* Handle method for mouse button release events. */
        virtual void OnMouseReleased(wxMouseEvent& mouseEvent) { Refresh(); }

        /* Handle method for mouse right click events. */
        virtual void OnRightClick(wxMouseEvent& mouseEvent) { Refresh(); }

        /**
         *  Handle method for mouse leave events. These events occur when the mouse
         *  cursor leaves the surface of the window.
         */
        virtual void OnMouseLeaveWindow(wxMouseEvent& mouseEvent) { Refresh(); }

        /**
         *  Handle method for mouse enter events. These events occur when the mouse
         *  enters the surface of the window.
         */
        virtual void OnMouseEnterWindow(wxMouseEvent& mouseEvent) { Refresh(); }

        /* Convenience method for handling ALL mouse events. */
        virtual void OnMouseEvents(wxMouseEvent& mouseEvent) { Refresh(); }

    
        /* Handle method for keyboard a key press events. */
        virtual void OnKeyPressed(wxKeyEvent& keyEvent) { Refresh(); }

        /* Handle method for keyboard a key release events. */
        virtual void OnKeyReleased(wxKeyEvent& keyEvent) { Refresh(); }

        /* Handle method for focus gained events. */
        virtual void OnFocusGained(wxFocusEvent& focusEvent) { Refresh(); }

        /* Handle method for focus lost events. */
        virtual void OnFocusLost(wxFocusEvent& focusEvent) { Refresh(); }

        /* Handle method for paint events. */
        virtual void OnPaint(wxPaintEvent& paintEvent) {
            m_renderer->Render(this);
            paintEvent.Skip(false);
        };

        /* Handle method for resize events. */
        virtual void OnResize(wxSizeEvent& resizeEvent) { Refresh(); };

		/**
		 *	Allows inheriting windows to define dynamic properties. 
		 *	The properties defined by every window are:
		 *	'hovered', 'focused' and 'pressed'.
		 *
		 *	In order to keep these definitions, and all the definitions
		 *	of parent windows, implementers of this method must call
		 *	the super definition.
		 */
		virtual boost::optional<wxString> GetComponentProperty(const wxString& propertyName);

        wxGraphicsContext* CreateGraphicsContext();

        static const int DEFAULT_WIDTH = 100;
        static const int DEFAULT_HEIGHT = 30;

    private:
        void Init();

        void MouseMoved(wxMouseEvent& mouseEvent) { OnMouseMoved(mouseEvent); }
        void MouseDown(wxMouseEvent& mouseEvent) { 
			m_isPressed = true;
			OnMouseDown(mouseEvent); 
		}
        void MouseDoubleClick(wxMouseEvent& mouseEvent) {
			m_isPressed = true;
			OnMouseDoubleClick(mouseEvent); 
		}
		void MouseReleased(wxMouseEvent& mouseEvent) { 
			m_isPressed = false;
			OnMouseReleased(mouseEvent); 
		}
        void MouseWheelMoved(wxMouseEvent& mouseEvent) { OnMouseWheelMoved(mouseEvent); }
        void RightClick(wxMouseEvent& mouseEvent) { OnRightClick(mouseEvent); }

        void MouseEnterWindow(wxMouseEvent& mouseEvent) { 
            m_isHovered = true;
            OnMouseEnterWindow(mouseEvent); 
        }

        void MouseLeaveWindow(wxMouseEvent& mouseEvent) { 
            m_isHovered = false;
            OnMouseLeaveWindow(mouseEvent); 
        }

        void MouseEvents(wxMouseEvent& mouseEvent) { OnMouseEvents(mouseEvent); }

        void KeyPressed(wxKeyEvent& keyEvent) { OnKeyPressed(keyEvent); }
        void KeyReleased(wxKeyEvent& keyEvent) { OnKeyReleased(keyEvent); }

        void FocusGained(wxFocusEvent& focusEvent) { 
            m_isFocused = true;
            OnFocusGained(focusEvent); 
        }

        void FocusLost(wxFocusEvent& focusEvent) { 
            m_isFocused = false;
            OnFocusLost(focusEvent); 
        }

        void Resize(wxSizeEvent& resizeEvent) { 
            Layout();
            OnResize(resizeEvent); 
        }

        void Paint(wxPaintEvent& paintEvent) { OnPaint(paintEvent); };

	private:
		/** Hash function for wxString objects. **/
		struct wxStringHash {
		public:
			std::size_t operator()(const wxString& s) {
				return std::hash<const char*>()(s.GetData().AsChar());
			}
		};

    private:
        bool m_isOpaque;

        wxColor m_backgroundColor;

        std::shared_ptr<IRenderer> m_renderer;

        std::shared_ptr<Style> m_style;

        bool m_isFocused;

        bool m_isHovered;

		bool m_isPressed;

        wxString m_text;

		std::unordered_map<wxString, wxString, wxStringHash> m_propertyMap;

        DECLARE_EVENT_TABLE()
    };

} // namespace wxstyle