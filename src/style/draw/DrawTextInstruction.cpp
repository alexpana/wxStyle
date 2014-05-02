#include "style/draw/DrawTextInstruction.h"

#include <memory>

namespace wxstyle {

	typedef DrawTextInstruction::Builder Builder;

	Builder& Builder::SetText(const wxString& text) {
		m_text = text;
		return *this;
	}

	Builder& Builder::SetShadowDefinition(const ShadowDefinition& shadowDefinition) {
		m_shadowDefinition = shadowDefinition;
		return *this;
	}

	Builder& Builder::SetFontDefinition(const FontDefinition& fontDefinition) {
		m_fontDefinition = fontDefinition;
		return *this;
	}

	Builder& Builder::SetTextColor(const wxColor& color) {
		m_textColor = color;
		return *this;
	}

	Builder& Builder::SetHorizontalAnchor(const HorizontalTextAnchor horizontalAnchor) {
		m_horizontalTextAnchor = horizontalAnchor;
		return *this;
	}

	Builder& Builder::SetVerticalAnchor(const VerticalTextAnchor verticalAnchor) {
		m_verticalTextAnchor = verticalAnchor;
		return *this;
	}

	Builder& Builder::SetTextPosition(const DimPoint& position) {
		m_textPosition = position;
		return *this;
	}

	DrawTextInstruction Builder::Build() {
		return DrawTextInstruction(m_text, m_shadowDefinition, m_fontDefinition, m_textColor, m_horizontalTextAnchor, m_verticalTextAnchor, m_textPosition);
	}

	Builder::Builder(const wxString& text, const ShadowDefinition& shadowDefinition, const FontDefinition& fontDefinition,
		const wxColor& textColor, const HorizontalTextAnchor& horizontalTextAnchor, const VerticalTextAnchor verticalTextAnchor,
		const DimPoint& textPosition) : 
		m_text(text), m_shadowDefinition(shadowDefinition), m_fontDefinition(fontDefinition), m_textColor(textColor), m_horizontalTextAnchor(horizontalTextAnchor),
		m_verticalTextAnchor(verticalTextAnchor), m_textPosition(textPosition)
	{}

	DrawTextInstruction::DrawTextInstruction(const wxString& text, const ShadowDefinition& shadowDefinition, const FontDefinition& fontDefinition,
		const wxColor& textColor, const HorizontalTextAnchor& horizontalTextAnchor, const VerticalTextAnchor verticalTextAnchor,
		const DimPoint& textPosition) : 
		m_text(text), m_shadowDefinition(shadowDefinition), m_fontDefinition(fontDefinition), m_textColor(textColor), m_horizontalTextAnchor(horizontalTextAnchor),
		m_verticalTextAnchor(verticalTextAnchor), m_textPosition(textPosition)
	{}

	wxPoint ComputeOffset(double w, double h, HorizontalTextAnchor hta, VerticalTextAnchor vta) {
		int x, y;

		switch(hta) {
		case HTA_LEFT: x = 0; break;
		case HTA_CENTER: x = - w / 2; break;
		case HTA_RIGHT: x = - w; break;
		}

		switch(vta) {
		case VTA_TOP: y = 0; break;
		case VTA_CENTER: y = - h / 2; break;
		case VTA_BOTTOM: y = - h; break;
		}

		return wxPoint(x, y);
	}

	void DrawTextInstruction::Draw(wxGraphicsContext* g, const wxSize& windowSize) const {

		// We need to set the font before computing it's extent
		wxFontInfo fontInfo = m_fontDefinition.CreateFontInfo();
		g->SetFont(fontInfo, m_textColor);

		double w, h;
		g->GetTextExtent(m_text, &w, &h);

		wxPoint offset = ComputeOffset(w, h, m_horizontalTextAnchor, m_verticalTextAnchor);

		wxSize finalPosition = m_textPosition.GetValue(windowSize);
		int x = finalPosition.GetWidth() + offset.x;
		int y = finalPosition.GetHeight() + offset.y;

		// Draw Shadow
		g->SetFont(fontInfo, m_shadowDefinition.m_color);
		g->DrawText(m_text, x + m_shadowDefinition.m_offset.x, y + m_shadowDefinition.m_offset.y);

		// Draw Text
		g->SetFont(fontInfo, m_textColor);
		g->DrawText(m_text, x, y);
	}

} // namespace wxstyle