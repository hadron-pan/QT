#ifndef FILEHEAD_H
#define FILEHEAD_H

#include <iostream>

class fileHead
{
public:
    fileHead();
    bool getVerMsg(char *ver,uint32_t verSize);
    bool getNameMsg(char *name,uint32_t nameSize);
    bool getResMsg(uint32_t base_add, uint32_t data_offset,uint32_t data_size,uint32_t font_nums);
    bool getCheckMsg(uint32_t checkType,uint32_t check);

public:
    char fileHeadbuf[256];   /* 资源头大小 */
};

#endif // FILEHEAD_H
