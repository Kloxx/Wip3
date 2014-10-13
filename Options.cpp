#include "Options.h"

#include <fstream>
#include <iostream>
#include <sstream>

void
strip_string(std::string& str, const char foo = ' ')
{
    while (!str.empty() && *str.begin() == foo) str.erase(str.begin());
    while (!str.empty() && *str.rbegin() == foo) str.erase(--str.end());
}

void
ConfigFile::parseIniFile(const std::string& filename)
{
    std::ifstream handle(filename.c_str());

    if (!handle) return;

    std::cout << "Loading " << filename << std::endl;

    std::string current_section_string = "";
    while (handle.good())
    {
        char line_buffer[512];
        handle.getline(line_buffer, 512);
        std::string line_string(line_buffer);

        if (line_string.empty()) continue;

        if (*line_string.begin() == '[' && *line_string.rbegin() == ']')
        {
            current_section_string = line_string;
            current_section_string.erase(--current_section_string.end());
            current_section_string.erase(current_section_string.begin());
            continue;
        }

        std::size_t equal_position = line_string.find("=");
        if (equal_position == std::string::npos) continue;

        std::string key_string = line_string.substr(0, equal_position);
        std::string value_string = line_string.substr(equal_position+1, std::string::npos);
        strip_string(key_string);
        strip_string(value_string);

        map[current_section_string][key_string] = value_string;
    }
}

std::ostream&
ConfigFile::dump(std::ostream& os) const
{
    for (SectionMap::const_iterator smi=map.begin(), sme=map.end(); smi!=sme; smi++)
    {
        if (!smi->first.empty()) os << "[" << smi->first << "]" << std::endl;
        for (ItemMap::const_iterator imi=smi->second.begin(), ime=smi->second.end(); imi!=ime; imi++)
        {
            os << imi->first << "=" << imi->second << std::endl;
        }
        os << std::endl;
    }
    return os;
}

Options::Options(const int argc, char* argv[])
{
    ConfigFile config;
    config.parseIniFile("config.ini");
    config.parseIniFile("../config.ini");
    config.parseIniFile("../config_sample.ini");
    if (argc > 1) config.parseIniFile(argv[1]);

    //std::cout << "********************" << std::endl;
    //config.dump(std::cout);
    //std::cout << "********************" << std::endl;

    fullscreen = config.get("display", "fullscreen", false);
    width = config.get("display", "width", 1024);
    height = config.get("display", "height", 768);
}

std::ostream&
operator<<(std::ostream& os, const Options& options)
{
    return os << "[Options fs=" << options.fullscreen << " res=" << options.width << "x" << options.height << "]";
}

