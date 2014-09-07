#include <string>

namespace wxstyle {

    /* Minimal support for RTTI */
    class ClassInfo {
    public:
        ClassInfo(const std::string& name) : name(name) {};

    public:
        const std::string name;

        const ClassInfo GetClassByName(const std::string& name) {
            if (name == BUTTON.name) return BUTTON;
            if (name == TEXTBOX.name) return TEXTBOX;
            if (name == CHECKBOX.name) return CHECKBOX;
            if (name == LABEL.name) return LABEL;
            return UNKNOWN;
        }

    public:
        static const ClassInfo BUTTON;
        static const ClassInfo TEXTBOX;
        static const ClassInfo CHECKBOX;
        static const ClassInfo LABEL;
        static const ClassInfo UNKNOWN;
    };

    bool operator<(const ClassInfo& lhf, const ClassInfo& rhs);
}