#include "StyledLabel.h"

#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include <wx/window.h>
#include <wx/fontenum.h>

#include "DimPoint.h"
#include "DimRect.h"

#include "Algorithms.h"
#include "FontMetrics.h"
#include "StylesheetRenderer.h"
#include "style/draw/DrawTextInstruction.h"
#include "style/draw/DrawRectangleInstruction.h"
#include "style/draw/DrawImageInstruction.h"
#include "style/draw/ImageRepository.h"

namespace wxstyle {

	class DefaultLabelRenderer : public StylesheetRenderer {
	public:
		static const int ICON_TEXT_GAP = 8;

		DefaultLabelRenderer() {};
		~DefaultLabelRenderer() {};

		virtual void Render(StyledWindow* window) const {
			StyledLabel* label = (StyledLabel*) window;

			wxAutoBufferedPaintDC deviceContext(label);
			auto g = std::unique_ptr<wxGraphicsContext>(wxGraphicsContext::Create(deviceContext));

			DrawBackground(g.get(), label);

			RenderIcon(g.get(), label);

			RenderText(g.get(), label);
		}

	private:
		void RenderIcon(wxGraphicsContext* g, StyledLabel *label) const {
			DefinitionBundle bundle = label->GetDefinitionBundle();

			if (bundle.HasIconDefinition()) {
				auto icon = ImageRepository::GetInstance()->GetImage(bundle.GetIcon().iconName.get());

				wxPoint contentPosition = GetContentGroupPosition(label);

				DrawImageInstruction(DrawImageInstruction::Params()
					.SetVerticalAnchor(VA_TOP).SetHorizontalAnchor(HA_LEFT)
					.SetImage(icon)
					.SetImageSize(DimPoint(Dimension(0, 1), Dimension(0, 1)))
					.SetPosition(DimPoint(contentPosition.x, contentPosition.y)))
					.Draw(g, label->GetSize());
			}
		}

		void RenderText(wxGraphicsContext* g, StyledLabel *label) const {
			DefinitionBundle bundle = label->GetDefinitionBundle();

			wxPoint contentPosition = GetContentGroupPosition(label);

			DrawTextInstruction(DrawTextInstruction::Params()
				.SetVerticalAnchor(VA_TOP)
				.SetHorizontalAnchor(HA_LEFT)
				.SetText(label->GetText())
				.SetFontDefinition(bundle.GetFont())
				.SetTextColor(bundle.GetForegroundColor())
				.SetShadowDefinition(bundle.GetTextShadow())
				.SetTextPosition(DimPoint(contentPosition.x + GetIconSize(label).GetWidth() + GetIconTextGap(label), contentPosition.y)))
				.Draw(g, label->GetSize());
		}
	};


	Style StyledLabel::GetDefaultStyle() {
		DefinitionBundle defaultBundle = StyledWindow::GetDefaultStyle().GetBundle(Style::CAT_DEFAULT);
		defaultBundle
			.SetTextAlignment(AlignmentDefinition().Horizontal(HA_CENTER).Vertical(VA_CENTER))
			.SetFont(FontDefinition().SetSize(9).SetFace("Tahoma").SetWeight(wxFONTWEIGHT_NORMAL))
			.SetForegroundColor("#929395");

		return Style().AddBundle(Style::CAT_DEFAULT, defaultBundle);
	}

	StyledLabel::StyledLabel(wxWindow *parent) : StyledWindow(parent) {
		Init();
	}

	void StyledLabel::Init() {
		SetOpaque(false);

		SetRenderer(std::shared_ptr<DefaultLabelRenderer>(new DefaultLabelRenderer()));
		SetStyle(StyledLabel::GetDefaultStyle());
	}

} // namespace wxstyle