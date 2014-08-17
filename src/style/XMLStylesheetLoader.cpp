#include "style/XMLStylesheetLoader.h"

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>

#include "pugxml/pugixml.hpp"

#include "DimRect.h"
#include "DimPoint.h"
#include "Insets.h"

#include "style/Stylesheet.h"
#include "style/Style.h"

#include "style/draw/DrawRectangleInstruction.h"
#include "style/draw/DrawEllipseInstruction.h"
#include "style/draw/DrawTextInstruction.h"
#include "style/draw/DrawImageInstruction.h"

using namespace pugi;

namespace wxstyle {

    template<typename T>
    inline bool Name(const T& node, const char* name) {
        return strcmp(node.name(), name) == 0;
    }

    template <typename T>
    T Convert(const char *stringValue);

    template <typename T>
    T Convert(const xml_attribute& xmlAttribute) {
        return Convert<T>(xmlAttribute.as_string());
    }

    template <>
    int Convert(const xml_attribute& xmlAttribute) {
        return xmlAttribute.as_int();
    }

    template <>
    std::string Convert(const char *stringValue) {
        return std::string(stringValue);
    }

    template <>
    wxFontWeight Convert(const char *stringValue) {
        if (strcmp(stringValue, "normal") == 0) return wxFONTWEIGHT_NORMAL;
        if (strcmp(stringValue, "bold") == 0) return wxFONTWEIGHT_BOLD;
        if (strcmp(stringValue, "light") == 0) return wxFONTWEIGHT_LIGHT;
        return wxFONTWEIGHT_NORMAL;
    }

    template <>
    wxFontStyle Convert(const char *stringValue) {
        if (strcmp(stringValue, "normal") == 0) return wxFONTSTYLE_NORMAL;
        if (strcmp(stringValue, "italic") == 0) return wxFONTSTYLE_ITALIC;
        return wxFONTSTYLE_NORMAL;
    }

    template <>
    Insets Convert(const char *stringValue) {
        return Insets::ValueOf(stringValue);
    }

    template <>
    DimRect Convert(const char *stringValue) {
        return DimRect::ValueOf(stringValue);
    }

    template <>
    Dimension Convert(const char *stringValue) {
        return Dimension::ValueOf(stringValue).get();
    }

    template <>
    wxPoint Convert(const char *stringValue) {
        std::vector<std::string> points;
        boost::split(points, std::string(stringValue), boost::is_any_of(", "), boost::token_compress_on);

        return wxPoint(
            boost::lexical_cast<int>(points[0]),
            boost::lexical_cast<int>(points[1]));
    }

    template <>
    Style::Category Convert(const char *stringValue) {
        if (strcmp(stringValue, "default") == 0) return Style::CAT_DEFAULT;
        if (strcmp(stringValue, "disabled") == 0) return Style::CAT_DISABLED;
        if (strcmp(stringValue, "focused") == 0) return Style::CAT_FOCUSED;
        if (strcmp(stringValue, "hovered") == 0) return Style::CAT_HOVERED;
        if (strcmp(stringValue, "pressed") == 0) return Style::CAT_PRESSED;
        return Style::CAT_DEFAULT;
    }

    template <>
    wxPenStyle Convert(const char *stringValue) {
        if (strcmp(stringValue, "solid") == 0) return wxPenStyle::wxPENSTYLE_SOLID;
        if (strcmp(stringValue, "dot") == 0) return wxPenStyle::wxPENSTYLE_DOT;
        return wxPenStyle::wxPENSTYLE_SOLID;
    }

    template <>
    HorizontalAlignment Convert(const char *stringValue) {
        if (strcmp(stringValue, "left") == 0) return HorizontalAlignment::HA_LEFT;
        if (strcmp(stringValue, "center") == 0) return HorizontalAlignment::HA_CENTER;
        if (strcmp(stringValue, "right") == 0) return HorizontalAlignment::HA_RIGHT;
        return HorizontalAlignment::HA_CENTER;
    }

    template <>
    VerticalAlignment Convert(const char *stringValue) {
        if (strcmp(stringValue, "top") == 0) return VerticalAlignment::VA_TOP;
        if (strcmp(stringValue, "center") == 0) return VerticalAlignment::VA_CENTER;
        if (strcmp(stringValue, "bottom") == 0) return VerticalAlignment::VA_BOTTOM;
        return VerticalAlignment::VA_CENTER;
    }

    template <>
    wxColor Convert(const char *stringValue) {
        return wxColor(stringValue);
    }

    template <>
    DimPoint Convert(const char *stringValue) {
        return DimPoint::ValueOf(stringValue);
    }

    template <typename T>
    T ParseDefinition(const xml_node& node);

    template <>
    FontDefinition ParseDefinition(const xml_node& node) {
        FontDefinition fontDefinition;

        for (auto param : node.attributes()) {

            if (Name(param, "face")) {
                fontDefinition.SetFace(Convert<std::string>(param));
            } 
            else if (Name(param, "size")) {
                fontDefinition.SetSize(Convert<int>(param));
            } 
            else if (Name(param, "weight")) {
                fontDefinition.SetWeight(Convert<wxFontWeight>(param));
            } 
            else if (Name(param, "style")) {
                fontDefinition.SetStyle(Convert<wxFontStyle>(param));
            }
        }

        return fontDefinition;
    }

    template <>
    ShadowDefinition ParseDefinition(const xml_node& node) {
        ShadowDefinition shadowDefinition;

        for (auto param : node.attributes()) {

            if (Name(param, "offset")) {
                shadowDefinition.SetOffset(Convert<wxPoint>(param));
            } 
            else if (Name(param, "color")) {
                shadowDefinition.SetColor(param.as_string());
            }
        }

        return shadowDefinition;
    }

    template <>
    wxColor ParseDefinition(const xml_node& node) {
        return wxColor(node.attribute("color").as_string());
    }

    template <>
    bool ParseDefinition(const xml_node& node) {
        return node.attribute("value").as_bool();
    }

    template <>
    Insets ParseDefinition(const xml_node& node) {
        return Convert<Insets>(node.attribute("rect").as_string());
    }

    template <>
    AlignmentDefinition ParseDefinition(const xml_node& node) {
        AlignmentDefinition;

        AlignmentDefinition result;

        std::string vertical = node.attribute("vertical").as_string("center");
        std::string horizontal = node.attribute("horizontal").as_string("center");

        if (vertical == "top") result.verticalAlignment = VerticalAlignment::VA_TOP;
        if (vertical == "center") result.verticalAlignment = VerticalAlignment::VA_CENTER;
        if (vertical == "bottom") result.verticalAlignment = VerticalAlignment::VA_BOTTOM;

        if (horizontal == "left") result.horizontalAlignment = HorizontalAlignment::HA_LEFT;
        if (horizontal == "center") result.horizontalAlignment = HorizontalAlignment::HA_CENTER;
        if (horizontal == "right") result.horizontalAlignment = HorizontalAlignment::HA_RIGHT;

        return result;
    }

    template <>
    IconDefinition ParseDefinition(const xml_node& node) {
        return IconDefinition().SetIconName(node.attribute("name").as_string());
    }

    template <>
    DrawRectangleInstruction* ParseDefinition(const xml_node& node) {
        DrawShapeInstruction::Params params;

        for (auto param : node.attributes()) {
            if (Name(param, "rect")) params.SetRect(Convert<DimRect>(param));
            if (Name(param, "corner-radius")) params.SetCornerRadius(Convert<int>(param));
            if (Name(param, "insets")) params.SetInsets(Convert<Insets>(param));
            if (Name(param, "color")) params.SetColor(Convert<wxColor>(param));
            //if (Name(param, "gradient")) params.SetGradientDefinition(Convert<GradientDefinitionPtr>(param));
            if (Name(param, "pen-size")) params.SetPenSize(Convert<int>(param));
            if (Name(param, "pen-color")) params.SetPenColor(Convert<wxColor>(param));
            if (Name(param, "pen-style")) params.SetPenStyle(Convert<wxPenStyle>(param));
            if (Name(param, "h-anchor")) params.SetHorizontalAnchor(Convert<HorizontalAlignment>(param));
            if (Name(param, "v-anchor")) params.SetVerticalAnchor(Convert<VerticalAlignment>(param));
        }

        return new DrawRectangleInstruction(params);
    }

    template <>
    DrawEllipseInstruction* ParseDefinition(const xml_node& node) {
        DrawShapeInstruction::Params params;

        for (auto param : node.attributes()) {
            if (Name(param, "rect")) params.SetRect(Convert<DimRect>(param));
            if (Name(param, "corner-radius")) params.SetCornerRadius(Convert<int>(param));
            if (Name(param, "insets")) params.SetInsets(Convert<Insets>(param));
            if (Name(param, "color")) params.SetColor(Convert<wxColor>(param));
            //if (Name(param, "gradient")) params.SetGradientDefinition(Convert<GradientDefinitionPtr>(param));
            if (Name(param, "pen-size")) params.SetPenSize(Convert<int>(param));
            if (Name(param, "pen-color")) params.SetPenColor(Convert<wxColor>(param));
            if (Name(param, "pen-style")) params.SetPenStyle(Convert<wxPenStyle>(param));
            if (Name(param, "h-anchor")) params.SetHorizontalAnchor(Convert<HorizontalAlignment>(param));
            if (Name(param, "v-anchor")) params.SetVerticalAnchor(Convert<VerticalAlignment>(param));
        }

        return new DrawEllipseInstruction(params);
    }

    template <>
    DrawImageInstruction* ParseDefinition(const xml_node& node) {
        DrawImageInstruction::Params params;

        for (auto param : node.attributes()) {
            if (Name(param, "image-path")) params.SetImagePath(Convert<std::string>(param));
            if (Name(param, "position")) params.SetPosition(Convert<DimPoint>(param));
            if (Name(param, "size")) params.SetImageSize(Convert<DimPoint>(param));
            if (Name(param, "h-anchor")) params.SetHorizontalAnchor(Convert<HorizontalAlignment>(param));
            if (Name(param, "v-anchor")) params.SetVerticalAnchor(Convert<VerticalAlignment>(param));
        }

        return new DrawImageInstruction(params);
    }

    template <>
    DrawTextInstruction* ParseDefinition(const xml_node& node) {
        DrawTextInstruction::Params params;
        ShadowDefinition shadow;
        FontDefinition font;
        
        for (auto param : node.attributes()) {
            if (Name(param, "message")) params.SetText(Convert<std::string>(param));
            if (Name(param, "shadow-offset")) shadow.SetOffset(Convert<wxPoint>(param));
            if (Name(param, "shadow-color")) shadow.SetColor(Convert<wxColor>(param));
            if (Name(param, "font-face")) font.SetFace(Convert<std::string>(param));
            if (Name(param, "font-size")) font.SetSize(Convert<int>(param));
            if (Name(param, "font-weight")) font.SetWeight(Convert<wxFontWeight>(param));
            if (Name(param, "font-style")) font.SetStyle(Convert<wxFontStyle>(param));
            if (Name(param, "color")) params.SetTextColor(Convert<wxColor>(param));
            if (Name(param, "h-anchor")) params.SetHorizontalAnchor(Convert<HorizontalAlignment>(param));
            if (Name(param, "v-anchor")) params.SetVerticalAnchor(Convert<VerticalAlignment>(param));
            if (Name(param, "position")) params.SetTextPosition(Convert<DimPoint>(param));
        }

        return new DrawTextInstruction(params);
    }

    template <>
    std::vector<DrawInstruction*> ParseDefinition(const xml_node& node) {
        std::vector<DrawInstruction*> drawInstructions;

        for (auto instruction : node.children()) {
            if (Name(node, "rect")) {
                drawInstructions.push_back(ParseDefinition<DrawRectangleInstruction*>(node));
            }
            if (Name(node, "ellipse")) {
                drawInstructions.push_back(ParseDefinition<DrawEllipseInstruction*>(node));
            }
            if (Name(node, "image")) {
                drawInstructions.push_back(ParseDefinition<DrawImageInstruction*>(node));
            }
            if (Name(node, "text")) {
                drawInstructions.push_back(ParseDefinition<DrawTextInstruction*>(node));
            }
        }

        return drawInstructions;
    }

    Style ParseStyleNode(const xml_node& node) {
        // TODO: Handle property links
        Style style;

        for (auto category : node.children()) {
            DefinitionBundle bundle;

            for (auto definition : category.children()) {

                if (Name(definition, "font")) {
                    bundle.SetFont(ParseDefinition<FontDefinition>(definition));
                }
                else if (Name(definition, "shadow")) {
                    bundle.SetShadow(ParseDefinition<ShadowDefinition>(definition));
                }
                else if (Name(definition, "icon")) {
                    bundle.SetIcon(ParseDefinition<IconDefinition>(definition));
                }
                else if (Name(definition, "alignment")) {
                    bundle.SetTextAlignment(ParseDefinition<AlignmentDefinition>(definition));
                }
                else if (Name(definition, "background")) {
                    bundle.SetBackgroundColor(ParseDefinition<wxColor>(definition));
                }
                else if (Name(definition, "foreground")) {
                    bundle.SetForegroundColor(ParseDefinition<wxColor>(definition));
                }
                else if (Name(definition, "opacity")) {
                    bundle.SetOpacity(ParseDefinition<bool>(definition));
                }
                else if (Name(definition, "insets")) {
                    bundle.SetInsets(ParseDefinition<Insets>(definition));
                }
                else if (Name(definition, "paint")) {
                    bundle.SetDrawInstructions(ParseDefinition<std::vector<DrawInstruction*>>(definition));
                }
            }

            style.AddBundle(Convert<Style::Category>(category.name()), bundle);
        }

        return style;
    }

    Stylesheet XMLStylesheetLoader::Load(const std::string& filename) {
        Stylesheet stylesheet;

        xml_document document;
        xml_parse_result result = document.load_file(filename.c_str());

        // TODO: Handle failure

        // parse styles
        auto styles = document.first_child().child("styles");
        for (auto node : styles.children("style")) {
            std::string name = node.attribute("name").as_string();
            Style style = ParseStyleNode(node);

            xml_attribute parent = node.attribute("parent");
            if (!parent.empty()) {
                style = Style::Merge(stylesheet.GetStyle(Convert<std::string>(parent)), style);
            }

            stylesheet.AddStyle(name, style);
        }

        // parse map
        auto classStyleMap = document.first_child().child("map");
        for (auto node : classStyleMap.children("item")) {
            std::string style_name = node.attribute("style").as_string();
            std::string class_name = node.attribute("class").as_string();
            stylesheet.SetClassDefaultStyle(class_name, style_name);
        }

        return stylesheet;
    }

} // namespace wxstyle