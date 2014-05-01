#pragma once

#include "style/draw/IDrawInstruction.h"

namespace wxstyle{ 

	class DrawRectangleInstruction : public IDrawInstruction {
	public:
		class Builder {
			friend DrawRectangleInstruction;

		public:
			static Builder* newBuilder();

			Builder* SetRect(const DimRect& rect);

			Builder* SetColor(const wxColor& color);

			Builder* SetBrush(const wxBrush& brush);

			Builder* SetPenSize(const int penSize);

			Builder* SetPenColor(const wxColor& penColor);

			Builder* SetPenStyle(const wxPenStyle penStyle);

			Builder* SetCornerRadius(const int cornerRadius);

			DrawRectangleInstruction Build();

		private:
			Builder();

			Builder(const DimRect& rect, const wxBrush& brush, int penSize, const wxColor& penColor, const wxPenStyle penStyle, const int cornerRadius);

			DimRect m_rect;
			wxBrush m_brush;
			int m_penSize;
			wxColor m_penColor;
			wxPenStyle m_penStyle;
			int m_cornerRadius;
		};

	public:
		DrawRectangleInstruction(const DimRect& rect, const wxBrush& brush, const int penSize, const wxColor& penColor, const wxPenStyle penStyle, int cornerRadius) :
			m_rect(rect), m_brush(brush), m_penSize(penSize), m_penColor(penColor), m_penStyle(penStyle), m_cornerRadius(cornerRadius)
		{}

		void Draw(wxGraphicsContext* g, const wxSize& windowSize) const override;

		static Builder* NewBuilder() {
			return new Builder();
		}

		Builder* ToBuilder() {
			return new Builder(m_rect, m_brush, m_penSize, m_penColor, m_penStyle, m_cornerRadius);
		}

		DimRect GetRect() const {
			return m_rect;
		}

		wxBrush GetBrush() const {
			return m_brush;
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

		int GetCornerRadius() const {
			return m_cornerRadius;
		}

	private:
		const DimRect m_rect;
		const wxBrush m_brush;
		const int m_penSize;
		const wxColor m_penColor;
		const wxPenStyle m_penStyle;
		const int m_cornerRadius;
	};

	std::ostream& operator<<(std::ostream& lhs, const DrawRectangleInstruction& rhs);
	bool operator==(const DrawRectangleInstruction& lhs, const DrawRectangleInstruction& rhs);

} // namespace wxstyle