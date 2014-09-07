#include "ClassInfo.h"

namespace wxstyle {
    const ClassInfo ClassInfo::BUTTON = ClassInfo("button");
    const ClassInfo ClassInfo::TEXTBOX = ClassInfo("textbox");
    const ClassInfo ClassInfo::CHECKBOX = ClassInfo("checkbox");
    const ClassInfo ClassInfo::LABEL = ClassInfo("label");
    const ClassInfo ClassInfo::UNKNOWN = ClassInfo("unknown");

    bool operator<(const ClassInfo& lhf, const ClassInfo& rhs) {
        return lhf.name < rhs.name;
    }
}