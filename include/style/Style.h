#pragma once

#include <vector>

#include "style/draw/DrawInstruction.h"
#include "style/StyleDefinitions.h"

namespace wxstyle {

    /**
     *  Style data structure.
     *
     *  The style class encapsulates information about the visual 
     *  properties of a component.
     */
    class Style {
    public:

        bool HasTextShadowDefinition() const;

        ShadowDefinition GetTextShadow() const;

        bool HasIconDefinition() const;

        IconDefinition GetIcon() const;

        bool HasFontDefinition() const;

        FontDefinition GetFont() const;

        bool HasTextAlignmentDefinition() const;

        wxAlignment GetTextAlignment() const;

        bool HasBackgroundColorDefinition() const;

        wxColor GetBackgroundColor() const;

        bool HasForegroundColorDefinition() const;

        wxColor GetForegroundColor() const;

        bool HasOpacityDefinition() const;

        bool IsOpaque() const;

        bool HasDrawInstructions() const;

        std::vector<DrawInstruction*> GetDrawInstructions() const;

        static Style Merge(const Style& lhs, const Style& rhs);

        // Mutation methods

        Style& SetShadow(const ShadowDefinition& shadowDefinition);

        Style& SetIcon(const IconDefinition& iconDefinition);

        Style& SetFont(const FontDefinition& fontDefinition);

        Style& SetTextAlignment(const wxAlignment& textAlignmentDefinition);

        Style& SetBackgroundColor(const wxColor& backgroundColorDefinition);

        Style& SetForegroundColor(const wxColor& foregroundColorDefinition);

        Style& SetOpacity(bool opacityDefinition);

        Style& SetDrawInstructions(std::vector<DrawInstruction*> drawInstructions);

    private:
        boost::optional<ShadowDefinition> shadowDefinition;
        boost::optional<IconDefinition> iconDefinition;
        boost::optional<FontDefinition> fontDefinition;
        boost::optional<ValueDefinition<wxAlignment>> textAlignmentDefinition;
        boost::optional<ValueDefinition<wxColor>> backgroundColorDefinition;
        boost::optional<ValueDefinition<wxColor>> foregroundColorDefinition;
        boost::optional<ValueDefinition<bool>> opacityDefinition;
        boost::optional<ValueDefinition<std::vector<DrawInstruction*>>> drawInstructions;
    };

} // namespace wxstyle