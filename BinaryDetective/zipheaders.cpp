#include "zipheaders.h"

//using namespace StreamUtils;

ZipUtils::SZipHead::SZipHead()
{
    text = 0;
    time = 0;
    xflags = 0;
    os = 0;
    extra_len = 0;
    extra_max = 0;
    name_max = 0;
    comm_max = 0;
    hcrc = 0;
    done = 0;
    comp_size = 0;
    uncomp_size = 0;
}

bool ZipUtils::SZipHead::read(StreamUtils::Stream& st)
{
    long head = st.readData<uLong>();
    if (head != 0x04034b50)
        return false;

    st.skip(14);
    comp_size = st.readData<uLong>();
    uncomp_size = st.readData<uLong>();
    name_max = st.read2();
    extra_max = st.read2();
    name = st.readString(name_max);
    extra = st.readString(name_max);

    return true;
}

ZipUtils::SZipTail::SZipTail()
{
    number_disk = 0;
    central_dir_starts = 0;
    number_central_dir = 0;
    tolal_number_central_dir = 0;
    size_central_dir = 0;
    offset_start_central = 0;
    comm_len = 0;
}

bool ZipUtils::SZipTail::read(StreamUtils::Stream& st)
{
    long head = st.readData<uLong>();
    if (head != 0x06054b50)
        return false;

    number_disk = st.read2();
    central_dir_starts = st.read2();
    number_central_dir = st.read2();
    tolal_number_central_dir = st.read2();
    size_central_dir = st.read4();
    offset_start_central = st.read4();
    comm_len = st.read2();
    comment = st.readString(comm_len);

    return true;
}
