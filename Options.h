#pragma once

#include <map>
#include <string>
#include <sstream>

struct ConfigFile
{
    typedef std::map<std::string, std::string> ItemMap;
    typedef std::map<std::string, ItemMap> SectionMap;
    SectionMap map;

    void
    parseIniFile(const std::string& filename);

    std::ostream&
    dump(std::ostream& os) const;

    template <typename T>
    inline
    T
    get(const std::string& section,  const std::string& key, const T& value_default)
    {
        SectionMap::const_iterator smi = map.find(section);
        if (smi == map.end()) return value_default;

        ItemMap::const_iterator imi = smi->second.find(key);
        if (imi == smi->second.end()) return value_default;

        std::istringstream ss(imi->second);
        T value = value_default;
        ss >> value;
        if (ss.fail()) return value_default;

        return value;
    }

};

