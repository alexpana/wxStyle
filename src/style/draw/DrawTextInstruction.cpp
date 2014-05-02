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

	DrawTextInstruction::Builder::Builder() {}

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

	void DrawTextInstruction::Draw(wxGraphicsContext* g, const wxSize& windowSize) const {
		double w, h;
		//g->Create()->GetTextExtent(m_text, &w, &h);
		wxSize finalPosition = m_textPosition.GetValue(windowSize);
		int x = finalPosition.GetWidth(), y = finalPosition.GetHeight();

		wxFontInfo fontInfo = m_fontDefinition.CreateFontInfo();

		// Draw Shadow
		g->SetFont(fontInfo, m_shadowDefinition.m_color);
		g->DrawText(m_text, x + m_shadowDefinition.m_offset.x, y + m_shadowDefinition.m_offset.y);

		// Draw Text
		g->SetFont(fontInfo, m_textColor);
		g->DrawText(m_text, x, y);
	}

} // namespace wxstyle