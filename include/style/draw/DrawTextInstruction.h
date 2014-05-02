#pragma once

#include <wx/string.h>
#include <wx/graphics.h>

#include "style/draw/IDrawInstruction.h"
#include "style/StyleDefinitions.h"

#include "DimPoint.h"

namespace wxstyle {

	enum HorizontalTextAnchor {
		HTA_LEFT,
		HTA_CENTER,
		HTA_RIGHT
	};

	enum VerticalTextAnchor {
		VTA_TOP,
		VTA_CENTER,
		VTA_BOTTOM
	};

	class DrawTextInstruction : public IDrawInstruction {

	public:

	class Builder {
	friend DrawTextInstruction;

	public:
		Builder& SetText(const wxString& text);

		Builder& SetShadowDefinition(const ShadowDefinition& shadowDefinition);

		Builder& SetFontDefinition(const FontDefinition& fontDefinition);

		Builder& SetTextColor(const wxColor& color);

		Builder& SetHorizontalAnchor(const HorizontalTextAnchor horizontalAnchor);

		Builder& SetVerticalAnchor(const VerticalTextAnchor verticalAnchor);

		Builder& SetTextPosition(const DimPoint& position);

		DrawTextInstruction Build();

	private:
		Builder() : m_verticalTextAnchor(VTA_CENTER), m_horizontalTextAnchor(HTA_CENTER) {};

		Builder(const wxString& text, const ShadowDefinition& shadowDefinition, const FontDefinition& fontDefinition,
			const wxColor& textColor, const HorizontalTextAnchor& horizontalTextAnchor, const VerticalTextAnchor verticalTextAnchor,
			const DimPoint& textPosition);

		wxString m_text;
		ShadowDefinition m_shadowDefinition;
		FontDefinition m_fontDefinition;
		wxColor m_textColor;
		HorizontalTextAnchor m_horizontalTextAnchor;
		VerticalTextAnchor m_verticalTextAnchor;
		DimPoint m_textPosition;
	};

	public:
		DrawTextInstruction(const wxString& text, const ShadowDefinition& shadowDefinition, const FontDefinition& fontDefinition,
			const wxColor& textColor, const HorizontalTextAnchor& horizontalTextAnchor, const VerticalTextAnchor verticalTextAnchor,
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
		const HorizontalTextAnchor m_horizontalTextAnchor;
		const VerticalTextAnchor m_verticalTextAnchor;
		const DimPoint m_textPosition;
	};

} // namespace wxstyle