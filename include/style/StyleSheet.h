#pragma once

#include <boost/variant.hpp>
#include <boost/optional.hpp>

#include <string>
#include <unordered_map>

#include "Dimension.h"

namespace wxstyle {

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
	boost::optional<StyleProperty> GetProperty(std::string name) {
		auto mapValue = m_properties.find(name);
		if (mapValue != m_properties.end()) {
			return boost::optional<StyleProperty>(mapValue->second);
		} else {
			return boost::optional<StyleProperty>();
		}
	}

	void SetProperty(std::string name, StyleProperty val) {
		m_properties[name] = val;
	}

	bool HasProperty(std::string name) {
		return m_properties.find(name) != m_properties.end();
	}

	bool UnsetProperty(std::string name) {
		return m_properties.erase(name) > 0;
	}

private:
	typedef std::unordered_map<std::string, StyleProperty> PropertValueMap;

private:
	PropertValueMap m_properties;
};

} // namespace wxstyle