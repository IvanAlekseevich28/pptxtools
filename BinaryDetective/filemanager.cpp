#include "filemanager.h"
#include <cstdlib>
#include <fstream>

using namespace std;

FileManager::FileManager(StreamUtils::Stream& st, const string& path, const string& format)
    : m_stream(st), m_format('.' + format), m_number(1)
{
    auto dotIter = path.find(".");
    if ((int)dotIter != -1)
    {
        m_dir = string(path.cbegin(), path.cbegin() + dotIter);
        mkdir(m_dir);
    }
}

bool FileManager::write(size_t begin, size_t end)
{
    if (end >= m_stream.len())
        return false;

    string filename = m_dir + "/" + to_string(begin) + "_" + to_string(m_number++) + m_format;
    ofstream file(filename, ios::out | ios::binary);
    if (!file.is_open())
        return false;

    const size_t fLen = end - begin;
    file.write(m_stream.getData() + begin, fLen);
    file.close();

    return true;
}

bool FileManager::mkdir(const string &path)
{
    string command = "mkdir -p " + path;
    const int dir_err = system(command.c_str());

    return -1 != dir_err;
}
