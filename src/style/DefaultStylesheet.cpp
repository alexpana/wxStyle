#include "DimRect.h"
#include "StyledWindow.h"
#include "style/DefinitionBundle.h"
#include "style/draw/DrawRectangleInstruction.h"
#include "style/draw/DrawShapeInstruction.h"
#include "style/Style.h"
#include "style/Stylesheet.h"

#include <memory>
#include <wx/colour.h>

namespace wxstyle {

    std::shared_ptr<Style> CreateLabelStyle();
    std::shared_ptr<Style> CreateTextBoxStyle();
    std::shared_ptr<Style> CreateButtonStyle();
    std::shared_ptr<Style> CreateCheckBoxStyle();

    std::shared_ptr<Stylesheet> CreateDefaultStylesheet()
    {
        auto stylesheet = std::make_shared<Stylesheet>();
        stylesheet->AddStyle("label.default", CreateLabelStyle());
        stylesheet->AddStyle("textbox.default", CreateTextBoxStyle());
        stylesheet->AddStyle("button.default", CreateButtonStyle());
        stylesheet->AddStyle("checkbox.default", CreateCheckBoxStyle());

        stylesheet->SetClassDefaultStyle("label", "label.default");
        stylesheet->SetClassDefaultStyle("textbox", "textbox.default");
        stylesheet->SetClassDefaultStyle("button", "button.default");
        stylesheet->SetClassDefaultStyle("checkbox", "checkbox.default");

        return stylesheet;
    }

    DefinitionBundle CreateDefaultBundle()
    {
        static DefinitionBundle defaultBundle = DefinitionBundle()
            .SetTextAlignment(AlignmentDefinition()
            .Horizontal(HA_CENTER)
            .Vertical(VA_CENTER))
            .SetFont(FontDefinition().SetSize(9).SetFace("Tahoma").SetWeight(wxFONTWEIGHT_NORMAL))
            .SetForegroundColor("#929395")
            .SetBackgroundColor("#000000")
            .SetOpacity(false)
            .SetShadow(
                ShadowDefinition().SetOffset(wxPoint(0, 0)).SetColor("#000000"));

        return defaultBundle;
    }

    std::shared_ptr<Style> CreateLabelStyle()
    {
        DefinitionBundle defaultBundle = CreateDefaultBundle();
        defaultBundle
            .SetTextAlignment(AlignmentDefinition()
            .Horizontal(HA_LEFT)
            .Vertical(VA_CENTER))
            .SetFont(FontDefinition().SetSize(9).SetFace("Tahoma").SetWeight(wxFONTWEIGHT_NORMAL))
            .SetForegroundColor("#929395");

        auto result = std::make_shared<Style>();
        result->AddBundle(Style::CAT_DEFAULT, defaultBundle);

        return result;
    }

    std::shared_ptr<Style> CreateCheckBoxStyle()
    {
        return std::make_shared<Style>();
    }

    std::shared_ptr<Style> CreateTextBoxStyle() 
    {
        auto result = std::make_shared<Style>(); // = GetStyle();

        // DEFAULT
        DefinitionBundle defaultBundle = CreateDefaultBundle();

        std::vector<DrawInstruction*> defaultDrawInstructions;

        defaultDrawInstructions.push_back(
            new DrawRectangleInstruction(DrawRectangleInstruction::Params()
            .SetRect(DimRect(0, 0, Dimension(0, 1), Dimension(0, 1)))
            .SetColor("#4e4c4c")));

        defaultDrawInstructions.push_back(
            new DrawRectangleInstruction(DrawRectangleInstruction::Params()
            .SetInsets(0, 0, 0, 1)
            .SetColor("#1c1617")));

        defaultDrawInstructions.push_back(
            new DrawRectangleInstruction(DrawRectangleInstruction::Params()
            .SetInsets(1, 1, 1, 2)
            .SetColor("#2b2a2a")));

        defaultBundle.SetDrawInstructions(defaultDrawInstructions);

        // FOCUSED
        DefinitionBundle focusedBundle = CreateDefaultBundle();

        std::vector<DrawInstruction*> focusedDrawInstructions;

        focusedDrawInstructions.push_back(
            new DrawRectangleInstruction(DrawRectangleInstruction::Params()
            .SetRect(DimRect(0, 0, Dimension(0, 1), Dimension(0, 1)))
            .SetColor("#4e4c4c")));

        focusedDrawInstructions.push_back(
            new DrawRectangleInstruction(DrawRectangleInstruction::Params()
            .SetInsets(0, 0, 0, 1)
            .SetColor("#007acc")));

        focusedDrawInstructions.push_back(
            new DrawRectangleInstruction(DrawRectangleInstruction::Params()
            .SetInsets(1, 1, 1, 2)
            .SetColor("#2b2a2a")));

        focusedBundle.SetDrawInstructions(focusedDrawInstructions);

        result->AddBundle(Style::CAT_DEFAULT, defaultBundle);
        result->AddBundle(Style::CAT_FOCUSED, focusedBundle);

        return result;
    }

    std::shared_ptr<Style> CreateButtonStyle() 
    {
        static const int radius = 0;
        static const wxColour borderColor = "#2c2c2c";
        static const wxColour bottomHighlight = "#46474B";
        static const wxColour topHighlight = "#606268";
        static const wxColour pressedColor = "#35363A";
        DefinitionBundle defaultBundle = CreateDefaultBundle();

        defaultBundle
            .SetOpacity(false)
            .SetForegroundColor("#BABCC0")
            .SetFont(
            FontDefinition()
            .SetFace("Tahoma")
            .SetSize(10)
            .SetWeight(wxFONTWEIGHT_BOLD))
            .SetShadow(
            ShadowDefinition()
            .SetColor("#323232")
            .SetOffset(wxPoint(0, 1)));

        DefinitionBundle pressedBundle = defaultBundle;

        // Draw Instructions
        auto bottomHighlightInstruction = new DrawRectangleInstruction(
            DrawShapeInstruction::Params()
            .SetColor(bottomHighlight)
            .SetCornerRadius(radius)
            .SetRect(DimRect(0, 0, Dimension(0, 1.0), Dimension(0, 1.0))));

        auto borderInstruction = new DrawRectangleInstruction(
            DrawShapeInstruction::Params()
            .SetColor(borderColor)
            .SetCornerRadius(radius)
            .SetRect(DimRect(0, 0, Dimension(0, 1.0), Dimension(-1, 1.0))));

        auto topHighlightInstruction = new DrawRectangleInstruction(
            DrawShapeInstruction::Params()
            .SetColor(topHighlight)
            .SetCornerRadius(radius)
            .SetRect(DimRect(1, 1, Dimension(-2, 1.0), Dimension(-3, 1.0))));

        GradientDefinitionPtr gradient = std::make_shared<LinearGradientDefinition>(LinearGradientDefinition::Direction::VERTICAL);
        gradient->AddColorStop(0, "#505156");
        gradient->AddColorStop(1, "#404146");

        auto backgroundColorInstruction = new DrawRectangleInstruction(
            DrawShapeInstruction::Params()
            .SetGradientDefinition(gradient)
            .SetCornerRadius(radius)
            .SetRect(DimRect(1, 2, Dimension(-2, 1.0), Dimension(-4, 1.0))));

        auto pressedBackgroundInstruction = new DrawRectangleInstruction(
            DrawShapeInstruction::Params()
            .SetColor(pressedColor)
            .SetCornerRadius(radius)
            .SetRect(DimRect(1, 1, Dimension(-2, 1.0), Dimension(-3, 1.0))));


        std::vector<DrawInstruction*> defaultDrawInstructions;
        defaultDrawInstructions.push_back(bottomHighlightInstruction);
        defaultDrawInstructions.push_back(borderInstruction);
        defaultDrawInstructions.push_back(topHighlightInstruction);
        defaultDrawInstructions.push_back(backgroundColorInstruction);

        std::vector<DrawInstruction*> pressedDrawInstructions;
        pressedDrawInstructions.push_back(bottomHighlightInstruction);
        pressedDrawInstructions.push_back(borderInstruction);
        pressedDrawInstructions.push_back(pressedBackgroundInstruction);

        defaultBundle.SetDrawInstructions(defaultDrawInstructions);
        pressedBundle.SetDrawInstructions(pressedDrawInstructions);

        auto result = std::make_shared<Style>();
        result->AddBundle(Style::CAT_DEFAULT, defaultBundle);
        result->AddBundle(Style::CAT_PRESSED, pressedBundle);

        return result;
    }
}