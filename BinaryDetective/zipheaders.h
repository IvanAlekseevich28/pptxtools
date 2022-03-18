#pragma once

#include "streamutils.h"

namespace ZipUtils
{
typedef unsigned int uLong;
typedef unsigned short uInt;
typedef char Bytef;

struct SZipHead
{
    int     text;       /* true if compressed data believed to be text */
    uLong   time;       /* modification time */
    int     xflags;     /* extra flags (not used when writing a gzip file) */
    int     os;         /* operating system */
    std::string extra;     /* pointer to extra field or Z_NULL if none */
    uInt    extra_len;  /* extra field length (valid if extra != Z_NULL) */
    uInt    extra_max;  /* space at extra (only when reading header) */
    std::string name;      /* pointer to zero-terminated file name or Z_NULL */
    uInt    name_max;   /* space at name (only when reading header) */
    std::string comment;   /* pointer to zero-terminated comment or Z_NULL */
    uInt    comm_max;   /* space at comment (only when reading header) */
    int     hcrc;       /* true if there was or will be a header crc */
    int     done;       /* true when done reading gzip header (not used
                           when writing a gzip file) */
    uLong   comp_size;
    uLong   uncomp_size;


    SZipHead();
    bool read(StreamUtils::Stream& st);
};

struct SZipTail
{
    uInt number_disk;
    uInt central_dir_starts;
    uInt number_central_dir;
    uInt tolal_number_central_dir;
    uLong size_central_dir;
    uLong offset_start_central;
    uInt comm_len;
    std::string comment;

    SZipTail();
    bool read(StreamUtils::Stream& st);
};
}
