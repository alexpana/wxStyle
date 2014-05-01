#include "style/draw/DrawRectangleInstruction.h"

namespace wxstyle {

typedef DrawRectangleInstruction::Builder Builder;

	Builder::Builder() : 
		m_rect(0, 0, Dimension(0, 1), Dimension(0, 1)), m_color(0x000000ul), m_penSize(0), m_penColor(0x000000ul), m_penStyle(wxPENSTYLE_TRANSPARENT), m_cornerRadius(0) 
	{}

	Builder::Builder(const DimRect& rect, const wxColor& color, int penSize, const wxColor& penColor, const wxPenStyle penStyle, const int cornerRadius) :
		m_rect(rect), m_color(color), m_penSize(penSize), m_penColor(penColor), m_penStyle(penStyle), m_cornerRadius(cornerRadius)
	{}

	Builder* Builder::newBuilder() {
		return new Builder();
	}

	Builder* Builder::SetRect(const DimRect& rect) {
		m_rect = rect;
		return this;
	}

	Builder* Builder::SetColor(const wxColor& color) {
		m_color = color;
		return this;
	}

	Builder* Builder::SetPenSize(const int penSize) {
		m_penSize = penSize;
		return this;
	}

	Builder* Builder::SetPenColor(const wxColor& penColor) {
		m_penColor = penColor;
		return this;
	}

	Builder* Builder::SetPenStyle(const wxPenStyle penStyle) {
		m_penStyle = penStyle;
		return this;
	}

	Builder* Builder::SetCornerRadius(const int cornerRadius) {
		m_cornerRadius = cornerRadius;
		return this;
	}

	DrawRectangleInstruction Builder::Build() {
		return DrawRectangleInstruction(m_rect, m_color, m_penSize, m_penColor, m_penStyle, m_cornerRadius);
	}

	void DrawRectangleInstruction::Draw(wxGraphicsContext* g, const wxSize& windowSize) const {
		g->SetBrush(wxBrush(m_color));
		g->SetPen(wxPen(m_penColor, m_penSize, m_penStyle));

		wxRect computedRect = m_rect.GetValue(windowSize);

		if (m_cornerRadius <= 0) {
			g->DrawRectangle(
				computedRect.GetX(),
				computedRect.GetY(),
				computedRect.GetWidth(),
				computedRect.GetHeight());
		} else {
			g->DrawRoundedRectangle(
				computedRect.GetX(),
				computedRect.GetY(),
				computedRect.GetWidth(),
				computedRect.GetHeight(),
				m_cornerRadius);
		}
	}

	std::ostream& operator<<(std::ostream& lhs, const DrawRectangleInstruction& rhs) {
		return lhs << "DrawRectangleInstruction("
			<< "rect:" << rhs.GetRect() << " "
			<< "color:" << std::hex << rhs.GetColor().GetRGB() << std::dec << " "
			<< "penSize:" << rhs.GetPenSize() << " "
			<< "penColor:" << std::hex << rhs.GetPenColor().GetRGB() << std::dec << " "
			<< "penStyle:" << rhs.GetPenStyle() << " "
			<< "cornerRadius:" << rhs.GetCornerRadius() << ")";
	}

	bool operator==(const DrawRectangleInstruction& lhs, const DrawRectangleInstruction& rhs) {
		return lhs.GetRect() == rhs.GetRect() && lhs.GetColor() == rhs.GetColor() && lhs.GetPenColor() == rhs.GetPenColor()
			&& lhs.GetPenSize() == rhs.GetPenSize() && lhs.GetPenStyle() == rhs.GetPenStyle() && lhs.GetCornerRadius() == rhs.GetCornerRadius();
	}

} // namespace wxstyle