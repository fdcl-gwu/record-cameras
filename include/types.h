#ifndef TYPES_H
#define TYPES_H


struct System
{
    bool on = true;
    bool record = false;
    int argc;
    char **argv;
};


struct Params
{
    int argc;
    char **argv;
    int cam_num = 0;
};


#endif
