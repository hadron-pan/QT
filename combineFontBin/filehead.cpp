#include "filehead.h"

fileHead::fileHead()
{

}

bool fileHead::getNameMsg(char *name,uint32_t nameSize)
{
    memcpy(fileHeadbuf,name,nameSize);
    return true;
}

bool fileHead::getVerMsg(char *ver,uint32_t verSize)
{
    memcpy(&fileHeadbuf[16],ver,verSize);
    return true;
}

bool fileHead::getResMsg(uint32_t base_add, uint32_t data_offset,uint32_t data_size,uint32_t font_num)
{  
    fileHeadbuf[48] = ((base_add) >> 24) & 0xFF;
    fileHeadbuf[49] = ((base_add) >> 16) & 0xFF;
    fileHeadbuf[50] = ((base_add) >> 8) & 0xFF;
    fileHeadbuf[51] = base_add & 0xFF;

    fileHeadbuf[52] = (data_offset >> 24) & 0xFF;
    fileHeadbuf[53] = (data_offset >> 16) & 0xFF;
    fileHeadbuf[54] = (data_offset >> 8) & 0xFF;
    fileHeadbuf[55] = data_offset & 0xFF;

    fileHeadbuf[56] = (data_size >> 24) & 0xFF;
    fileHeadbuf[57] = (data_size >> 16) & 0xFF;
    fileHeadbuf[58] = (data_size >> 8) & 0xFF;
    fileHeadbuf[59] = data_size & 0xFF;

    fileHeadbuf[60] = (font_num >> 24) & 0xFF;
    fileHeadbuf[61] = (font_num >> 16) & 0xFF;
    fileHeadbuf[62] = (font_num >> 8) & 0xFF;
    fileHeadbuf[63] = font_num & 0xFF;
    return true;
}

bool fileHead::getCheckMsg(uint32_t checkType, uint32_t check)
{
    fileHeadbuf[64] = (checkType >> 24) & 0xFF;
    fileHeadbuf[65] = (checkType >> 16) & 0xFF;
    fileHeadbuf[66] = (checkType >> 8) & 0xFF;
    fileHeadbuf[67] = checkType & 0xFF;

    fileHeadbuf[68] = (check >> 24) & 0xFF;
    fileHeadbuf[69] = (check >> 16) & 0xFF;
    fileHeadbuf[70] = (check >> 8) & 0xFF;
    fileHeadbuf[71] = check & 0xFF;
    return true;
}
