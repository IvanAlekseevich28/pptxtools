#include <iostream>
#include <iomanip>
#include "filemanager.h"
#include "zipheaders.h"


using namespace std;
using namespace StreamUtils;
using namespace ZipUtils;

char zipHead[] = {0x50, 0x4b, 0x03, 0x04};

char zipTail[] = {0x50, 0x4b, 0x05, 0x06};

inline bool exists_test (const std::string& name) {
    ifstream f(name.c_str());
    return f.good();
}

int main( int argc, char **argv )
{
    if (argc != 2)
    {
        cout << "Execute command with exists .ppt file";
        return 1;
    }

    char* filename = argv[1];
    if (exists_test(filename) == false)
    {
        cout << "File: " << filename << " not exists!\n";
        return 2;
    }


    Stream stream(filename);

//    cout << stream.searchNext(zipHead, 4) << " - " << stream.searchNext(zipTail, 4) << endl;
    size_t posHead(0), posTail(0);
    FileManager file(stream, filename);
     while(1)
     {
        SZipHead hzip;
        posHead = stream.searchNext(zipHead, 4);
        if ((int)posHead == -1)
            break;

        hzip.read(stream);
        SZipTail tzip;
        stream.searchNext(zipTail, 4);
        tzip.read(stream);
        posTail = stream.tell();
        file.write(posHead, posTail);
    }

    return 0;
}
