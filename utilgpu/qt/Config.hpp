#pragma once
#include <utilgpu/qt/Config.h>

#include <cassert>

#include <QString>

namespace util
{
template <typename T>
T Config::value(const std::string& key)
{
    assert(m_defaults.find(key) != m_defaults.end());
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
