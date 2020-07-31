#pragma once
#include <utilgpu/qt/Config.h>

#ifndef NDEBUG
#include <cassert>
#include <iostream>
#endif

#include <QString>

namespace util
{
template <typename T>
T Config::value(const std::string& key)
{
#ifndef NDEBUG
    if (m_defaults.find(key) == m_defaults.end())
    {
        std::cerr << "Key '" << key << "' not in defaults" << std::endl;
        assert(false);
    }
#endif
    const auto setting =
        m_settings.value(QString::fromStdString(key),
                         QString::fromStdString(m_defaults.at(key)));
    return setting.value<T>();
}

template <typename T>
void Config::setValue(const std::string& key, const T& value)
{
    m_settings.setValue(QString::fromStdString(key), value);
    m_settings.sync();
}
}  // namespace util
