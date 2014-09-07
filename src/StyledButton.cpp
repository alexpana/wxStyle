#include "StyledButton.h"

#include <algorithm>
#include <memory>

#include <wx/dcbuffer.h>
#include <wx/font.h>
#include <wx/graphics.h>
#include <wx/icon.h>
#include <wx/dcclient.h>

#include "Dimension.h"
#include "DimPoint.h"
#include "DimRect.h"
#include "FontMetrics.h"
#include "Insets.h"
#include "style/StylesheetRenderer.h"
#include "style/draw/DrawImageInstruction.h"
#include "style/draw/DrawEllipseInstruction.h"
#include "style/draw/DrawRectangleInstruction.h"
#include "style/draw/DrawTextInstruction.h"

namespace wxstyle {

    struct StyledButton::StyledButtonImpl {
    public:
        bool isArmed;
        std::shared_ptr<wxImage> icon;
        StyledButtonImpl() : isArmed(false) {}
    };

    class DefaultButtonRenderer : public StylesheetRenderer {
    public:
        void Render(StyledWindow* window) const override {
            StyledButton* button = (StyledButton*) window;

            wxAutoBufferedPaintDC deviceContext(button);
            auto g = std::unique_ptr<wxGraphicsContext>(wxGraphicsContext::Create(deviceContext));

            DrawBackground(g.get(), button);

            // Should go together into "content" maybe ?

            RenderIcon(g.get(), button);

            RenderText(g.get(), button);
        }

    private:

        void RenderIcon(wxGraphicsContext* g, StyledButton *button) const {
            auto icon = button->GetIcon();

            if (icon) {
                wxRect textSize = button->GetTextMetrics();

                DrawImageInstruction(DrawImageInstruction::Params()
                    .SetImage(icon)
                    .SetImageSize(DimPoint(Dimension(0, 1), Dimension(0, 1)))
                    .SetPosition(DimPoint(Dimension(- textSize.GetWidth() / 2 - 3, 0.5), Dimension(0, 0.5)))
                    .SetVerticalAnchor(VA_CENTER)
                    .SetHorizontalAnchor(HA_CENTER))
                .Draw(g, button->GetSize());
            }
        }

        void RenderText(wxGraphicsContext* g, StyledButton *button) const {
            int iconWidth = button->GetIcon() ? button->GetIcon()->GetWidth() : 0;

            DefinitionBundle bundle = button->GetDefinitionBundle();

            DrawTextInstruction(DrawTextInstruction::Params()
                .SetText(button->GetText())
                .SetFontDefinition(bundle.GetFont())
                .SetTextColor(bundle.GetForegroundColor())
                .SetShadowDefinition(bundle.GetTextShadow())
                .SetTextPosition(DimPoint(Dimension( iconWidth / 2 + 3, 0.5), Dimension(-2, 0.5))))
                .Draw(g, button->GetSize());
        }
    };

    StyledButton::StyledButton(wxWindow* parent, wxString text) : StyledWindow(parent, text),
        pimpl(new StyledButtonImpl)
    {
        SetRenderer(std::make_shared<DefaultButtonRenderer>());
    }
    
    StyledButton::~StyledButton() {
    }
    
    const std::shared_ptr<wxImage> StyledButton::GetIcon() const {
        return pimpl->icon;
    }

    void StyledButton::SetIcon(const std::shared_ptr<wxImage> icon) {
        pimpl->icon = icon;
    }

    bool StyledButton::IsArmed() {
        return pimpl->isArmed;
    }

    wxSize StyledButton::GetMinSize() const {
        int width = 0;
        int height = 0;

        int iconWidth = 0;
        int iconHeight = 0;
        if (GetIcon()) {
            iconWidth = GetIcon()->GetWidth();
            iconHeight = GetIcon()->GetHeight();
        }

        TextMetrics textMetrics(const_cast<StyledButton*>(this));
        wxSize textSize;

        textSize = textMetrics.GetTextSize(GetText(), GetDefinitionBundle().GetFont());

        width += GetInsets().Width();
        width += iconWidth;
        width += GetTextMetrics().GetWidth();

        height += GetInsets().Height();
        height += std::max(iconHeight, GetTextMetrics().GetHeight());

        wxSize userMinSize = StyledWindow::GetMinSize();
        return wxSize(std::max(width, userMinSize.GetWidth()), std::max(height, userMinSize.GetHeight()));
    }

    wxSize StyledButton::GetTextMetrics() const {
        wxWindowDC dc(const_cast<StyledButton*>(this));

        wxFont font(FontDefinition().SetSize(10).SetFace("Tahoma").SetWeight(wxFONTWEIGHT_BOLD).CreateFontInfo());
        
        int width, height;
        wxString text = GetText();
        dc.GetTextExtent(text, &width, &height, 0, 0, &font);

        return wxSize(width, height);
    }

    void StyledButton::OnMouseDown(wxMouseEvent& mouseEvent) {
        pimpl->isArmed = true;
        Refresh();
    }

    void StyledButton::OnMouseReleased(wxMouseEvent& mouseEvent) {
        if (IsArmed()) {
            SendClickEvent();
        }

        pimpl->isArmed = false;
        Refresh();
    }

    void StyledButton::OnMouseDoubleClick(wxMouseEvent& mouseEvent) {
        OnMouseDown(mouseEvent);
    }

    void StyledButton::OnMouseLeaveWindow(wxMouseEvent& mouseEvent) {
        pimpl->isArmed = false;
        Refresh();
    }

    void StyledButton::OnMouseEnterWindow(wxMouseEvent& mouseEvent) {
        if (mouseEvent.ButtonIsDown(wxMOUSE_BTN_LEFT)) {
            pimpl->isArmed = true;
        }
        Refresh();
    }

    void StyledButton::SendClickEvent() {
        wxCommandEvent event(wxEVT_BUTTON, GetId());
        event.SetEventObject(this);
        ProcessWindowEvent(event);
    }

} // namespace wxstyle