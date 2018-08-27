#ifndef TYPES_H
#define TYPES_H


struct System
{
    bool on = true;
    bool record = false;
    int camera_num = 0;
    int argc;
    char **argv;
};


struct Args
{
    int argc;
    char **argv;
};


#endif
