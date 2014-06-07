#pragma once

#include <boost/variant.hpp>
#include <boost/optional.hpp>

#include <string>
#include <unordered_map>

#include "Dimension.h"

namespace wxstyle {

class Style;

class StyleProperty {
public:
	StyleProperty() : m_value(0) {}
	StyleProperty(int val) : m_value(val) {}
	StyleProperty(const std::string& val) : m_value(val) {}
	StyleProperty(const Dimension& val) : m_value(val) {}
	StyleProperty(const char* val) : m_value(val) {}

	bool IsString() {
		return m_value.which() == 1;
	}

	bool IsInt() {
		return m_value.which() == 0;
	}

	bool IsDimension() {
		return m_value.which() == 2;
	}

	std::string ToString() {
		return boost::get<std::string>(m_value);
	}

	int ToInt() {
		return boost::get<int>(m_value);
	}

	Dimension ToDimension() {
		return boost::get<Dimension>(m_value);
	}

private:
	typedef boost::variant<int, std::string, Dimension> ImplType;

private:
	ImplType m_value;
};

class Stylesheet {
public:
    Stylesheet();

	boost::optional<StyleProperty> GetProperty(std::string name);

	void SetProperty(std::string name, StyleProperty val);

	bool HasProperty(std::string name);

	bool UnsetProperty(std::string name);

    void AddStyle(const std::string& name, const Style& style);

    Style GetStyle(const std::string& name) const;

    void SetClassDefaultStyle(const std::string& className, const std::string& styleName);

private:
    struct Implementation;
    std::shared_ptr<Implementation> pimpl;
};

} // namespace wxstyle