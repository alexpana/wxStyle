#pragma once

#include "Style.h"

namespace wxstyle {
    class StyledWindow;
    class Style;

    class StyleUtils {
    public:
        /**
         *  Merges two style by adding the definitions present in the second style
         *  over the ones in the first. This is done by merging every definition
         *  from both styles.
         */
        static Style MergeStyles(const Style& lhs, const Style& rhs) {
            Style computedStyle;

            computedStyle.shadowDefinition = MergeDefinitions(lhs.shadowDefinition, rhs.shadowDefinition);
            computedStyle.fontDefinition = MergeDefinitions(lhs.fontDefinition, rhs.fontDefinition);
            computedStyle.iconDefinition = MergeDefinitions(lhs.iconDefinition, rhs.iconDefinition);
            computedStyle.textAlignmentDefinition = MergeDefinitions(lhs.textAlignmentDefinition, rhs.textAlignmentDefinition);
            computedStyle.backgroundColorDefinition = MergeDefinitions(lhs.backgroundColorDefinition, rhs.backgroundColorDefinition);
            computedStyle.foregroundColorDefinition = MergeDefinitions(lhs.foregroundColorDefinition, rhs.foregroundColorDefinition);
            computedStyle.opacityDefinition = MergeDefinitions(lhs.opacityDefinition, rhs.opacityDefinition);
            computedStyle.drawInstructions = MergeDefinitions(lhs.drawInstructions, rhs.drawInstructions);

            return computedStyle;
        }

        /**
         *  Merges two optional definitions.
         */
        template<typename D>
        static boost::optional<D> MergeDefinitions(const boost::optional<D>& lhs, const boost::optional<D>& rhs) {
            if (lhs && rhs) {
                return MergeDefinitions(lhs.get(), rhs.get());
            } else if (lhs) {
                return lhs.get();
            } else if (rhs) {
                return rhs.get();
            }
            return boost::optional<D>();
        }

        /**
         *  Merge two StyleDefinitions.
         *  The merging is done via the Merge method that must be implemented by every
         *  style definition.
         */
        template<typename D>
        static D MergeDefinitions(const D& lhs, const D& rhs) {
            D result = lhs;
            return result.Merge(rhs);
        }
    };

} // namespace wxstyle