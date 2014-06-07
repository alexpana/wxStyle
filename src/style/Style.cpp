#include "style/Style.h"

#include <map>

namespace wxstyle {

    struct Style::Implementation {
        std::map<Category, DefinitionBundle> definitionBundleMap;
    };

    Style Style::Merge(const Style& lhs, const Style& rhs) {
        Style result;
        
        result.AddBundle(CAT_DEFAULT, DefinitionBundle::Merge(lhs.GetBundle(CAT_DEFAULT), rhs.GetBundle(CAT_DEFAULT)));
        result.AddBundle(CAT_DISABLED, DefinitionBundle::Merge(lhs.GetBundle(CAT_DISABLED), rhs.GetBundle(CAT_DISABLED)));
        result.AddBundle(CAT_FOCUSED, DefinitionBundle::Merge(lhs.GetBundle(CAT_FOCUSED), rhs.GetBundle(CAT_FOCUSED)));
        result.AddBundle(CAT_HOVERED, DefinitionBundle::Merge(lhs.GetBundle(CAT_HOVERED), rhs.GetBundle(CAT_HOVERED)));
        result.AddBundle(CAT_PRESSED, DefinitionBundle::Merge(lhs.GetBundle(CAT_PRESSED), rhs.GetBundle(CAT_PRESSED)));

        return result;
    }

    Style::Style() {
        pimpl = std::make_shared<Style::Implementation>();
    }

    DefinitionBundle Style::GetBundle(Category category) const {
        // TODO: What happens when there is no default bundle ?
        if (pimpl->definitionBundleMap.find(category) != pimpl->definitionBundleMap.end()) {
            return pimpl->definitionBundleMap[category];
        } else {
            return pimpl->definitionBundleMap[CAT_DEFAULT];
        }
    }

    Style& Style::AddBundle(Category category, DefinitionBundle bundle) {
        pimpl->definitionBundleMap[category] = bundle;
        return *this;
    }

} // namespace wxstyle