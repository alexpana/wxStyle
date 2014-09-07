#pragma once

#include <map>
#include <memory>

namespace wxstyle
{
    class IRenderer;
    class Stylesheet;
    class Style;
    class ClassInfo;

    class LookAndFeel
    {
    public:

        static void SetStylesheet(Stylesheet stylesheet);

        static void SetDefaultStyle(ClassInfo widgetType, std::shared_ptr<Style> style);

        static void SetDefaultRenderer(ClassInfo widgetType, std::shared_ptr<IRenderer> renderer);

        static std::shared_ptr<Style> GetStyle(ClassInfo widgetType);

        static std::shared_ptr<IRenderer> GetRenderer(ClassInfo widgetType);

    private:
        // Ensure no instances of this class can be created
        LookAndFeel();
        ~LookAndFeel();

        static std::shared_ptr<Stylesheet> m_stylesheet;

        static std::map<ClassInfo, std::shared_ptr<Style>> m_styleMap;

        static std::map<ClassInfo, std::shared_ptr<IRenderer>> m_rendererMap;
    };
}