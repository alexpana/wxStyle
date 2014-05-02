#pragma once

#include "style/draw/IDrawInstruction.h"
#include "style/StyleDefinitions.h"

namespace wxstyle {

	class DrawTextInstruction : public IDrawInstruction {
	public:
		void Draw(wxGraphicsContext* g, const wxSize& windowSize) const override;

	private:
		const wxString m_text;
		const ShadowDefinition m_shadowDefinition;
		const FontDefinition m_fontDefinition;
		const wxColor m_textColor;
	};

} // namespace wxstyle