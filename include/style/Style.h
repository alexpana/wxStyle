#pragma once

#include "DrawInstruction.h"
#include "StyleDefinitions.h"

#include <vector>

namespace wxstyle {

    /**
     *  Style data structure.
     *
     *  The style class encapsulates information about the visual 
     *  properties of a component.
     */
    class Style {
    public:
        boost::optional<ShadowDefinition> shadowDefinition;
        boost::optional<IconDefinition> iconDefinition;
        boost::optional<FontDefinition> fontDefinition;
        boost::optional<TextAlignmentDefinition> textAlignmentDefinition;
        boost::optional<ValueDefinition<wxColor>> backgroundColorDefinition;
        boost::optional<ValueDefinition<wxColor>> foregroundColorDefinition;
        boost::optional<ValueDefinition<bool>> opacityDefinition;
        boost::optional<ValueDefinition<std::vector<DrawInstruction*>>> drawInstructions;
    };

} // namespace wxstyle