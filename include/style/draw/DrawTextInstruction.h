#pragma once

#include <wx/string.h>
#include <wx/graphics.h>

#include "style/draw/Anchor.h"
#include "style/draw/DrawInstruction.h"
#include "style/StyleDefinitions.h"

#include "DimPoint.h"

namespace wxstyle {

	class DrawTextInstruction : public DrawInstruction {

	public:

	class Builder {
	friend DrawTextInstruction;

	public:
		Builder& SetText(const wxString& text);

		Builder& SetShadowDefinition(const ShadowDefinition& shadowDefinition);

		Builder& SetFontDefinition(const FontDefinition& fontDefinition);

		Builder& SetTextColor(const wxColor& color);

		Builder& SetHorizontalAnchor(const HorizontalAnchor horizontalAnchor);

		Builder& SetVerticalAnchor(const VerticalAnchor verticalAnchor);

		Builder& SetTextPosition(const DimPoint& position);

		DrawTextInstruction Build();

	private:
		Builder() : m_verticalTextAnchor(VA_CENTER), m_horizontalTextAnchor(HA_CENTER) {};

		Builder(const wxString& text, const ShadowDefinition& shadowDefinition, const FontDefinition& fontDefinition,
			const wxColor& textColor, const HorizontalAnchor& horizontalTextAnchor, const VerticalAnchor verticalTextAnchor,
			const DimPoint& textPosition);

		wxString m_text;
		ShadowDefinition m_shadowDefinition;
		FontDefinition m_fontDefinition;
		wxColor m_textColor;
		HorizontalAnchor m_horizontalTextAnchor;
		VerticalAnchor m_verticalTextAnchor;
		DimPoint m_textPosition;
	};

	public:
		DrawTextInstruction(const wxString& text, const ShadowDefinition& shadowDefinition, const FontDefinition& fontDefinition,
			const wxColor& textColor, const HorizontalAnchor& horizontalTextAnchor, const VerticalAnchor verticalTextAnchor,
			const DimPoint& textPosition);

		void Draw(wxGraphicsContext* g, const wxSize& windowSize) const override;

		static Builder NewBuilder() {
			return Builder();
		}

		Builder ToBuilder() {
			return Builder(m_text, m_shadowDefinition, m_fontDefinition, m_textColor, m_horizontalTextAnchor, m_verticalTextAnchor, m_textPosition);
		}

	private:
		const wxString m_text;
		const ShadowDefinition m_shadowDefinition;
		const FontDefinition m_fontDefinition;
		const wxColor m_textColor;
		const HorizontalAnchor m_horizontalTextAnchor;
		const VerticalAnchor m_verticalTextAnchor;
		const DimPoint m_textPosition;
	};

} // namespace wxstyle