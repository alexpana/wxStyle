#include "style/DefinitionBundle.h"

namespace wxstyle {

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

    ShadowDefinition DefinitionBundle::GetTextShadow() const {
        return shadowDefinition.get();
    }

    IconDefinition DefinitionBundle::GetIcon() const {
        return iconDefinition.get();
    }

    FontDefinition DefinitionBundle::GetFont() const {
        return fontDefinition.get();
    }

    AlignmentDefinition DefinitionBundle::GetTextAlignment() const {
        return textAlignmentDefinition.get();
    }

    wxColor DefinitionBundle::GetBackgroundColor() const {
        return backgroundColorDefinition.get().value.get();
    }

    wxColor DefinitionBundle::GetForegroundColor() const {
        return foregroundColorDefinition.get().value.get();
    }

    bool DefinitionBundle::IsOpaque() const {
        return opacityDefinition.get().value.get();
    }

    Insets DefinitionBundle::GetInsets() const {
        return insetsDefinition.get().value.get();
    }

    std::vector<DrawInstruction*> DefinitionBundle::GetDrawInstructions() const {
        return drawInstructions.get().value.get();
    }

    bool DefinitionBundle::HasTextShadowDefinition() const {
        return shadowDefinition;
    }

    bool DefinitionBundle::HasIconDefinition() const {
        return iconDefinition;
    }

    bool DefinitionBundle::HasFontDefinition() const {
        return fontDefinition;
    }

    bool DefinitionBundle::HasTextAlignmentDefinition() const {
        return  textAlignmentDefinition;
    }

    bool DefinitionBundle::HasBackgroundColorDefinition() const {
        return backgroundColorDefinition;
    }

    bool DefinitionBundle::HasForegroundColorDefinition() const {
        return foregroundColorDefinition;
    }

    bool DefinitionBundle::HasOpacityDefinition() const {
        return opacityDefinition;
    }

    bool DefinitionBundle::HasInsetsDefinition() const {
        return insetsDefinition;
    }

    bool DefinitionBundle::HasDrawInstructions() const {
        return drawInstructions;
    }

    DefinitionBundle& DefinitionBundle::SetShadow(const ShadowDefinition& shadowDefinition) {
        this->shadowDefinition = shadowDefinition;
        return *this;
    }

    DefinitionBundle& DefinitionBundle::SetIcon(const IconDefinition& iconDefinition) {
        this->iconDefinition = iconDefinition;
        return *this;
    }

    DefinitionBundle& DefinitionBundle::SetFont(const FontDefinition& fontDefinition) {
        this->fontDefinition = fontDefinition;
        return *this;
    }

    DefinitionBundle& DefinitionBundle::SetTextAlignment(const AlignmentDefinition& textAlignmentDefinition) {
        this->textAlignmentDefinition = textAlignmentDefinition;
        return *this;
    }

    DefinitionBundle& DefinitionBundle::SetBackgroundColor(const wxColor& backgroundColorDefinition) {
        this->backgroundColorDefinition = backgroundColorDefinition;
        return *this;
    }

    DefinitionBundle& DefinitionBundle::SetForegroundColor(const wxColor& foregroundColorDefinition) {
        this->foregroundColorDefinition = foregroundColorDefinition;
        return *this;
    }

    DefinitionBundle& DefinitionBundle::SetOpacity(bool opacityDefinition) {
        this->opacityDefinition = opacityDefinition;
        return *this;
    }

    DefinitionBundle& DefinitionBundle::SetInsets(const Insets& insets) {
        insetsDefinition = insets;
        return *this;
    }

    DefinitionBundle& DefinitionBundle::SetDrawInstructions(std::vector<DrawInstruction*> drawInstructions) {
        this->drawInstructions = drawInstructions;
        return *this;
    }

    DefinitionBundle DefinitionBundle::Merge(const DefinitionBundle& lhs, const DefinitionBundle& rhs) {
        DefinitionBundle computedStyle;
        computedStyle.shadowDefinition = MergeDefinitions(lhs.shadowDefinition, rhs.shadowDefinition);
        computedStyle.fontDefinition = MergeDefinitions(lhs.fontDefinition, rhs.fontDefinition);
        computedStyle.iconDefinition = MergeDefinitions(lhs.iconDefinition, rhs.iconDefinition);
        computedStyle.textAlignmentDefinition = MergeDefinitions(lhs.textAlignmentDefinition, rhs.textAlignmentDefinition);
        computedStyle.backgroundColorDefinition = MergeDefinitions(lhs.backgroundColorDefinition, rhs.backgroundColorDefinition);
        computedStyle.foregroundColorDefinition = MergeDefinitions(lhs.foregroundColorDefinition, rhs.foregroundColorDefinition);
        computedStyle.opacityDefinition = MergeDefinitions(lhs.opacityDefinition, rhs.opacityDefinition);
        computedStyle.insetsDefinition = MergeDefinitions(lhs.insetsDefinition, rhs.insetsDefinition);
        computedStyle.drawInstructions = MergeDefinitions(lhs.drawInstructions, rhs.drawInstructions);
        return computedStyle;
    }

} // namespace wxstyle