#pragma once

#include "Style.h"
#include "StyleDefinitions.h"

namespace wxstyle {

    class StyleBuilder {
    public:
        static StyleBuilder NewBuilder();

        StyleBuilder* SetShadowDefinition(const ShadowDefinition& shadowDefinition) {
            return this;
        }

        StyleBuilder* SetIconDefinition(const IconDefinition& iconDefinition) {
            return this;
        }

        StyleBuilder* SetFontDefinition(const FontDefinition& fontDefinition) {
            return this;
        }

        StyleBuilder* SetTextAlignmentDefinition(const TextAlignmentDefinition& textAlignmentDefinition) {
            return this;
        }

        StyleBuilder* SetBackgroundColor(const wxColor& backgroundColor) {
            return this;
        }

        StyleBuilder* SetForegroundColor(const wxColor& foregroundColor) {
            return this;
        }

        StyleBuilder* SetOpacity(const bool opacity) {
            return this;
        }

        StyleBuilder* SetDrawInstructions(const wxColor& backgroundColor) {
            return this;
        }

        Style Build();
    private:
        StyleBuilder();
    };

}