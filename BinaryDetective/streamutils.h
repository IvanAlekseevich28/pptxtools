#pragma once
#include <memory>
#include <list>
#include <fstream>
namespace StreamUtils
{
class Stream
{
public:
    Stream(const std::string &filename);
    size_t searchNext(const char key[], size_t keyLen);
    void skip(int count);
    bool seek(size_t pos);
    inline size_t tell()const{return m_iter;}

    template<class T>
    T readData();
    std::string readString(size_t strLen);
    short read2();
    unsigned int read4();
    unsigned long readULong();

    char* getData()const{return st.get();}
    static size_t getFileSize(const std::string& filename);

    size_t len() const;

private:
private:
    std::unique_ptr<char[]> st;
    size_t m_iter;

    size_t m_len;
};

bool writePositionsToFile(std::string file_path, Stream &st, size_t begin, size_t end);
std::unique_ptr<char[]> wcharToChar(const std::wstring& w);
}
