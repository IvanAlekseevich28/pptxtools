#include "streamutils.h"
#include <string.h>

using namespace std;
namespace StreamUtils
{

Stream::Stream(const string& filename) :
    st(nullptr), m_iter(0), m_len(0)
{
    ifstream file(filename);
    m_len = getFileSize(filename);

    st.reset(new char[m_len]);
    while (file)
        file.read(st.get(), m_len);

    file.close();
}

size_t Stream::searchNext(const char key[], size_t keyLen)
{
    std::unique_ptr<char[]> buf(new char[keyLen]);
    memset(buf.get(), keyLen, sizeof(char));
    size_t buf_i = 0;

    for (size_t i = m_iter; i < m_len; i++)
    {
        if (st[i] == key[buf_i])
        {
            buf[buf_i++] = st[i];
            if (buf_i == keyLen)
            {
                m_iter = (i - keyLen+1);
                return m_iter;
            }
        } else
        {
            buf_i = 0;
        }

    }

    return -1;
}

void Stream::skip(int count)
{
    if (m_iter + count < m_len)
        m_iter += count;
}

bool Stream::seek(size_t pos)
{
    if (pos < m_len)
    {
        m_iter = pos;
        return true;
    }
    return false;
}

string Stream::readString(size_t strLen)
{
    std::string str;
    for (; strLen > 0; strLen--)
        str += readData<char>();

    return str;
}

short Stream::read2()
{
    return readData<short>();
}

unsigned int Stream::read4()
{
    return readData<unsigned int>();
}

unsigned long Stream::readULong()
{
    return readData<unsigned long>();
}

size_t Stream::getFileSize(const std::string &filename)
{
    ifstream file(filename, ios::ate | ios::binary);
    size_t m_len = file.tellg();
    file.seekg(0);
    file.close();

    return m_len;
}

size_t Stream::len() const
{
    return m_len;
}

template<class T>
T Stream::readData()
{
    T data = 0;
    for (size_t dataLen = sizeof (T), i = 0;
         i < dataLen and m_iter < m_len;
         m_iter++, i++)
        data += (((T)st[m_iter] % 0x100) << (i * 8));

    return data;
}

bool writePositionsToFile(std::string file_path, Stream &st, size_t begin, size_t end)
{
    ofstream file(file_path, ios::binary | ios::out);
    if(!file.is_open())
        return false;

    const char*  data = st.getData() + begin;
    const size_t fLen = end - begin;
    file.write(data, fLen);

    file.close();
    return true;
}

std::unique_ptr<char[]> wcharToChar(const wstring &w)
{
    const auto dataLen = w.length() * 2;
    std::unique_ptr<char[]> pData(new char[dataLen]);
    for (size_t i = 0; i < dataLen; i++)
    {
        pData[i] = (char)((w[i/2] >> (8 * (i % 2)) % 0x100));
    }

    return pData;
}

}
