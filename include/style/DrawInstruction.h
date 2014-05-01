#pragma once

#include <wx/brush.h>
#include <wx/colour.h>
#include <wx/gdicmn.h>
#include <wx/graphics.h>
#include <wx/pen.h>

#include "DimRect.h"

namespace wxstyle {    

    class DrawInstruction {
	public:
		virtual void Draw(wxGraphicsContext* g, const wxRect& windowSize) const = 0;
    };

	class DrawRectangleInstruction : public DrawInstruction {
	private:
		class Builder {
		public:
			static Builder* newBuilder() {
				return new Builder();
			}

			Builder* SetRect(const DimRect& rect) {
				m_rect = rect;
				return this;
			}

			Builder* SetColor(const wxColor& color) {
				m_color = color;
				return this;
			}

			Builder* SetPenSize(const int penSize) {
				m_penSize = penSize;
				return this;
			}

			Builder* SetPenColor(const wxColor& penColor) {
				m_penColor = penColor;
				return this;
			}

			Builder* SetPenStyle(const wxPenStyle penStyle) {
				m_penStyle = penStyle;
				return this;
			}

			DrawRectangleInstruction Build() {
				return DrawRectangleInstruction(m_rect, m_color, m_penSize, m_penColor, m_penStyle);
			}

		private:
			Builder() : m_color(0x000000ul), m_penSize(1), m_penColor(0x000000ul), m_penStyle(wxPENSTYLE_SOLID) {}

			DimRect m_rect;
			wxColor m_color;
			int m_penSize;
			wxColor m_penColor;
			wxPenStyle m_penStyle;
		};

	public:
		DrawRectangleInstruction(const DimRect& rect, const wxColor& color, const int penSize, const wxColor& penColor, const wxPenStyle penStyle) :
			m_rect(rect), m_color(color), m_penSize(penSize), m_penColor(penColor), m_penStyle(penStyle)
		{}

		void Draw(wxGraphicsContext* g, const wxRect& windowSize) const {
			g->SetBrush(wxBrush(m_color));
			g->SetPen(wxPen(m_penColor, m_penSize, m_penStyle));

			wxRect computedRect = m_rect.GetValue(windowSize);

			g->DrawRectangle(computedRect.GetX(),
				computedRect.GetY(),
				computedRect.GetWidth(),
				computedRect.GetHeight());
		}

		static Builder* newBuilder() {
			return Builder::newBuilder();
		}

		DimRect GetRect() const {
			return m_rect;
		}

		wxColor GetColor() const {
			return m_color;
		}

		int GetPenSize() const {
			return m_penSize;
		}

		wxColor GetPenColor() const {
			return m_penColor;
		}

		wxPenStyle GetPenStyle() const {
			return m_penStyle;
		}

	private:
		const DimRect m_rect;
		const wxColor m_color;
		const int m_penSize;
		const wxColor m_penColor;
		const wxPenStyle m_penStyle;
	};

	std::ostream& operator<<(std::ostream& lhs, const DrawRectangleInstruction& rhs);
	bool operator==(const DrawRectangleInstruction& lhs, const DrawRectangleInstruction& rhs);

} // namespace wxstyle