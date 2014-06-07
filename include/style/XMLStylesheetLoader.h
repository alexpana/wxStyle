#pragma once

#include <string>

namespace wxstyle {
    class Stylesheet;

    class XMLStylesheetLoader {
    public:
        Stylesheet Load(const std::string& filename);
    };

} // namespace wxstyle