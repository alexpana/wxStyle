#include "style/Stylesheet.h"

#include "pugxml/pugixml.hpp"

#include <string>
#include <map>

#include "style/Style.h"

namespace wxstyle
{
    struct Stylesheet::Implementation
    {
        typedef std::unordered_map<std::string, StyleProperty> PropertValueMap;

        PropertValueMap properties;
        std::string name;
        std::map<std::string, std::shared_ptr<Style>> styles;
        std::map<std::string, std::string> classDefaultStyles;
    };

    Stylesheet::Stylesheet() {
        pimpl = std::make_shared<Stylesheet::Implementation>();
    }

    void Stylesheet::AddStyle(const std::string& name, const std::shared_ptr<Style> style) {
        pimpl->styles[name] = style;
    }

    std::shared_ptr<Style> Stylesheet::GetStyle(const std::string& name) const {
        return pimpl->styles[name];
    }

    void Stylesheet::SetClassDefaultStyle(const std::string& className, const std::string& styleName) {
        pimpl->classDefaultStyles[className] = styleName;
    }

    std::shared_ptr<Style> Stylesheet::GetClassDefaultStyle(const std::string& className) {
        return GetStyle(pimpl->classDefaultStyles[className]);
    }

    boost::optional<StyleProperty> Stylesheet::GetProperty(std::string name) {
        auto mapValue = pimpl->properties.find(name);
        if (mapValue != pimpl->properties.end()) {
            return boost::optional<StyleProperty>(mapValue->second);
        } else {
            return boost::optional<StyleProperty>();
        }
    }

    void Stylesheet::SetProperty(std::string name, StyleProperty val) {
        pimpl->properties[name] = val;
    }

    bool Stylesheet::HasProperty(std::string name) {
        return pimpl->properties.find(name) != pimpl->properties.end();
    }

    bool Stylesheet::UnsetProperty(std::string name) {
        return pimpl->properties.erase(name) > 0;
    }
} // namespace wxstyle