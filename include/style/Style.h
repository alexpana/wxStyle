#pragma once

#include <memory>
#include <vector>

#include "style/DefinitionBundle.h"

namespace wxstyle {

    class Style {
    public:
        enum Category {
            CAT_DEFAULT,
            CAT_DISABLED,
            CAT_FOCUSED,
            CAT_HOVERED,
            CAT_PRESSED
        };

    public:
        Style();

        DefinitionBundle GetBundle(Category category) const;
        Style& AddBundle(Category category, DefinitionBundle bundle);

        static Style Merge(const Style& lhs, const Style& rhs);

    private:
        struct Implementation;
        std::shared_ptr<Implementation> pimpl;
    };

} // namespace wxstyle