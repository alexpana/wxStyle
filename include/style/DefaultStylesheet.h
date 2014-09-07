#include <memory>

namespace wxstyle {
    class Stylesheet;
    std::shared_ptr<Stylesheet> CreateDefaultStylesheet();
}