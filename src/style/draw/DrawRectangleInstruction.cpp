#include "style/draw/DrawRectangleInstruction.h"

namespace wxstyle {

typedef DrawRectangleInstruction::Builder Builder;

	Builder::Builder() : 
		m_rect(0, 0, Dimension(0, 1), Dimension(0, 1)), m_brush(0x000000ul), m_penSize(0), m_penColor(0x000000ul), m_penStyle(wxPENSTYLE_TRANSPARENT), m_cornerRadius(0) 
	{}

	Builder::Builder(const DimRect& rect, const wxBrush& brush, int penSize, const wxColor& penColor, const wxPenStyle penStyle, const int cornerRadius, boost::optional<GradientDefinitionPtr> gradientDefinition) :
		m_rect(rect), m_brush(brush), m_penSize(penSize), m_penColor(penColor), m_penStyle(penStyle), m_cornerRadius(cornerRadius), m_gradientDefinition(gradientDefinition)
	{}

	Builder Builder::newBuilder() {
		return Builder();
	}

	Builder& Builder::SetRect(const DimRect& rect) {
		m_rect = rect;
		return *this;
	}

	Builder& Builder::SetColor(const wxColor& color) {
		m_brush = wxBrush(color);
		return *this;
	}

	Builder& Builder::SetGradientDefinition(const GradientDefinitionPtr gradientDefinition) {
		m_gradientDefinition = gradientDefinition;
		return *this;
	}

	Builder& Builder::SetBrush(const wxBrush& brush) {
		m_brush = brush;
		return *this;
	}

	Builder& Builder::SetPenSize(const int penSize) {
		m_penSize = penSize;
		return *this;
	}

	Builder& Builder::SetPenColor(const wxColor& penColor) {
		m_penColor = penColor;
		return *this;
	}

	Builder& Builder::SetPenStyle(const wxPenStyle penStyle) {
		m_penStyle = penStyle;
		return *this;
	}

	Builder& Builder::SetCornerRadius(const int cornerRadius) {
		m_cornerRadius = cornerRadius;
		return *this;
	}

	DrawRectangleInstruction Builder::Build() {
		return DrawRectangleInstruction(m_rect, m_brush, m_penSize, m_penColor, m_penStyle, m_cornerRadius, m_gradientDefinition);
	}

	void DrawRectangleInstruction::Draw(wxGraphicsContext* g, const wxSize& windowSize) const {
		wxRect computedRect = m_rect.GetValue(windowSize);

		if (HasGradientDefinition()) {
			g->SetBrush(m_gradientDefinition.get()->CreateBrush(*g, computedRect));
		} else {
			g->SetBrush(m_brush);
		}

		if (m_penStyle > 0) {
			g->SetPen(wxPen(m_penColor, m_penSize, m_penStyle));
		}

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
			//<< "color:" << std::hex << rhs.GetBrush() << std::dec << " "
			<< "penSize:" << rhs.GetPenSize() << " "
			<< "penColor:" << std::hex << rhs.GetPenColor().GetRGB() << std::dec << " "
			<< "penStyle:" << rhs.GetPenStyle() << " "
			<< "cornerRadius:" << rhs.GetCornerRadius() << ")";
	}

	bool operator==(const DrawRectangleInstruction& lhs, const DrawRectangleInstruction& rhs) {
		return lhs.GetRect() == rhs.GetRect() && lhs.GetBrush() == rhs.GetBrush() && lhs.GetPenColor() == rhs.GetPenColor()
			&& lhs.GetPenSize() == rhs.GetPenSize() && lhs.GetPenStyle() == rhs.GetPenStyle() && lhs.GetCornerRadius() == rhs.GetCornerRadius()
			&& lhs.HasGradientDefinition() == rhs.HasGradientDefinition() 
			&& lhs.HasGradientDefinition() ? lhs.GetGradientDefinition() == rhs.GetGradientDefinition() : true;
	}

} // namespace wxstyle