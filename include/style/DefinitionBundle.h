#pragma once

#include <vector>

#include "Insets.h"
#include "style/draw/DrawInstruction.h"
#include "style/StyleDefinitions.h"

namespace wxstyle {

    class Insets;

    /**
     *  DefinitionBundle data structure.
     *
     *  The bundle class encapsulates information about the visual 
     *  properties of a component.
     */
    class DefinitionBundle {
    public:

        static DefinitionBundle Merge(const DefinitionBundle& lhs, const DefinitionBundle& rhs);

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

        bool HasInsetsDefinition() const;

        Insets GetInsets() const;

        bool HasDrawInstructions() const;

        std::vector<DrawInstruction*> GetDrawInstructions() const;

        // Mutation methods

        DefinitionBundle& SetShadow(const ShadowDefinition& shadowDefinition);

        DefinitionBundle& SetIcon(const IconDefinition& iconDefinition);

        DefinitionBundle& SetFont(const FontDefinition& fontDefinition);

        DefinitionBundle& SetTextAlignment(const wxAlignment& textAlignmentDefinition);

        DefinitionBundle& SetBackgroundColor(const wxColor& backgroundColorDefinition);

        DefinitionBundle& SetForegroundColor(const wxColor& foregroundColorDefinition);

        DefinitionBundle& SetOpacity(bool opacityDefinition);

        DefinitionBundle& SetInsets(const Insets& insets);

        DefinitionBundle& SetDrawInstructions(std::vector<DrawInstruction*> drawInstructions);

    private:
        boost::optional<ShadowDefinition> shadowDefinition;
        boost::optional<IconDefinition> iconDefinition;
        boost::optional<FontDefinition> fontDefinition;
        boost::optional<ValueDefinition<wxAlignment>> textAlignmentDefinition;
        boost::optional<ValueDefinition<wxColor>> backgroundColorDefinition;
        boost::optional<ValueDefinition<wxColor>> foregroundColorDefinition;
        boost::optional<ValueDefinition<bool>> opacityDefinition;
        boost::optional<ValueDefinition<Insets>> insetsDefinition;
        boost::optional<ValueDefinition<std::vector<DrawInstruction*>>> drawInstructions;
    };

} // namespace wxstyle