#include "style/Style.h"

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

    ShadowDefinition Style::GetTextShadow() const {
        return shadowDefinition.get();
    }

    IconDefinition Style::GetIcon() const {
        return iconDefinition.get();
    }

    FontDefinition Style::GetFont() const {
        return fontDefinition.get();
    }

    wxAlignment Style::GetTextAlignment() const {
        return textAlignmentDefinition.get().value.get();
    }

    wxColor Style::GetBackgroundColor() const {
        return backgroundColorDefinition.get().value.get();
    }

    wxColor Style::GetForegroundColor() const {
        return foregroundColorDefinition.get().value.get();
    }

    bool Style::IsOpaque() const {
        return opacityDefinition.get().value.get();
    }

    std::vector<DrawInstruction*> Style::GetDrawInstructions() const {
        return drawInstructions.get().value.get();
    }

    bool Style::HasTextShadowDefinition() const {
        return shadowDefinition;
    }

    bool Style::HasIconDefinition() const {
        return iconDefinition;
    }

    bool Style::HasFontDefinition() const {
        return fontDefinition;
    }

    bool Style::HasTextAlignmentDefinition() const {
        return  textAlignmentDefinition;
    }

    bool Style::HasBackgroundColorDefinition() const {
        return backgroundColorDefinition;
    }

    bool Style::HasForegroundColorDefinition() const {
        return foregroundColorDefinition;
    }

    bool Style::HasOpacityDefinition() const {
        return opacityDefinition;
    }

    bool Style::HasDrawInstructions() const {
        return drawInstructions;
    }

    Style& Style::SetShadow(const ShadowDefinition& shadowDefinition) {
        this->shadowDefinition = shadowDefinition;
        return *this;
    }

    Style& Style::SetIcon(const IconDefinition& iconDefinition) {
        this->iconDefinition = iconDefinition;
        return *this;
    }

    Style& Style::SetFont(const FontDefinition& fontDefinition) {
        this->fontDefinition = fontDefinition;
        return *this;
    }

    Style& Style::SetTextAlignment(const wxAlignment& textAlignmentDefinition) {
        this->textAlignmentDefinition = textAlignmentDefinition;
        return *this;
    }

    Style& Style::SetBackgroundColor(const wxColor& backgroundColorDefinition) {
        this->backgroundColorDefinition = backgroundColorDefinition;
        return *this;
    }

    Style& Style::SetForegroundColor(const wxColor& foregroundColorDefinition) {
        this->foregroundColorDefinition = foregroundColorDefinition;
        return *this;
    }

    Style& Style::SetOpacity(bool opacityDefinition) {
        this->opacityDefinition = opacityDefinition;
        return *this;
    }

    Style& Style::SetDrawInstructions(std::vector<DrawInstruction*> drawInstructions) {
        this->drawInstructions = drawInstructions;
        return *this;
    }

    Style Style::Merge(const Style& lhs, const Style& rhs) {
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

} // namespace wxstyle