#pragma once

#include <QString>
#include <QStringList>

#include <nlohmann/json.hpp>

///////////////////////////////////////////////////////////////////////////////
// QString
///////////////////////////////////////////////////////////////////////////////
inline void to_json(nlohmann::json &j, const QString &str)
{
    j = nlohmann::json(str.toStdString());
}

inline void from_json(const nlohmann::json &j, QString &str)
{
    if (j.is_string())
        str = QString::fromStdString(j.get<std::string>());
    else
        throw nlohmann::detail::type_error::create(302, "type must be a string, but is not");
}

///////////////////////////////////////////////////////////////////////////////
// QStringList
///////////////////////////////////////////////////////////////////////////////
inline void to_json(nlohmann::json &j, const QStringList &strList)
{
    std::vector<QString> list(strList.cbegin(), strList.cend());
    j = list;
}

inline void from_json(const nlohmann::json &j, QStringList &strList)
{
    if (j.is_array()) {
        auto list = j.get<std::vector<QString>>();
        strList = QStringList(list.cbegin(), list.cend());
    } else {
        throw nlohmann::detail::type_error::create(302, "type must be an array, but is not");
    }
}