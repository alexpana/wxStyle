#include "LookAndFeel.h"

#include "ClassInfo.h"

#include "style/DefaultStylesheet.h"
#include "style/Style.h"
#include "style/Stylesheet.h"

#include <memory>

using namespace std;

namespace wxstyle
{
    std::shared_ptr<Stylesheet> LookAndFeel::m_stylesheet = CreateDefaultStylesheet();

    std::map<ClassInfo, std::shared_ptr<Style>> LookAndFeel::m_styleMap;

    std::map<ClassInfo, std::shared_ptr<IRenderer>> LookAndFeel::m_rendererMap;

    void LookAndFeel::SetStylesheet(Stylesheet stylesheet) {
        static ClassInfo widgetTypes[] = {
            ClassInfo::BUTTON, 
            ClassInfo::CHECKBOX, 
            ClassInfo::LABEL, 
            ClassInfo::TEXTBOX};

        for (int i = 0; i < 4; ++i) {
            auto style = stylesheet.GetClassDefaultStyle(widgetTypes[i].name);
            if (style != nullptr) {
                SetDefaultStyle(widgetTypes[i], style);
            }
        }
    }

    void LookAndFeel::SetDefaultStyle(ClassInfo widgetType, std::shared_ptr<Style> style) {
        m_styleMap[widgetType] = style;
    }

    void LookAndFeel::SetDefaultRenderer(ClassInfo widgetType, 
                                         shared_ptr<IRenderer> renderer) {
        m_rendererMap[widgetType] = renderer;
    }

    shared_ptr<Style> LookAndFeel::GetStyle(ClassInfo widgetType) {
        if (m_styleMap.find(widgetType) != m_styleMap.end()) {
            return m_styleMap[widgetType];
        }
        auto stylesheetStyle = m_stylesheet->GetClassDefaultStyle(widgetType.name);
        if (stylesheetStyle != nullptr) {
            return stylesheetStyle;
        }
        return nullptr;
    }

    shared_ptr<IRenderer> LookAndFeel::GetRenderer(ClassInfo widgetType) {
        return m_rendererMap[widgetType];
    }
}