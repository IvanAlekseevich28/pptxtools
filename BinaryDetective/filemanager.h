#pragma once
#include "streamutils.h"

class FileManager
{
public:
    FileManager(StreamUtils::Stream& st, const std::string& path, const std::string& format = "zip");
    bool write(size_t begin, size_t end);
    bool mkdir(const std::string& path);

private:
    StreamUtils::Stream& m_stream;
    std::string m_dir;
    std::string m_format;
    unsigned m_number;
};
