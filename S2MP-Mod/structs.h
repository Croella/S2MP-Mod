//////////////////
//	   structs.h
//	Engine Structs
///////////////////
#pragma once
struct CmdText
{
    unsigned __int8* data;
    int maxsize;
    int cmdsize;
};

enum LocalClientNum_t : __int32
{
    LOCAL_CLIENT_INVALID = 0xFFFFFFFF,
    LOCAL_CLIENT_0 = 0x0,
    LOCAL_CLIENT_LAST = 0x0,
    LOCAL_CLIENT_COUNT = 0x1,
};

enum errorParm_t
{
    ERR_FATAL = 0x0,
    ERR_DROP = 0x1,
    ERR_SERVERDISCONNECT = 0x2,
    ERR_DISCONNECT = 0x3,
    ERR_SCRIPT = 0x4,
    ERR_SCRIPT_DROP = 0x5,
    ERR_LOCALIZATION = 0x6,
    ERR_MAPLOADERRORSUMMARY = 0x7,
};

struct DvarLimits_integer
{
    int min;
    int max;
};

struct DvarLimits_value
{
    float min;
    float max;
};

union DvarLimits
{
    DvarLimits_integer integer;
    DvarLimits_value floats;
};


enum dvarType_t : __int32
{
    DVAR_TYPE_BOOL = 0x0,
    DVAR_TYPE_FLOAT = 0x1,
    DVAR_TYPE_FLOAT_2 = 0x2,
    DVAR_TYPE_FLOAT_3 = 0x3,
    DVAR_TYPE_FLOAT_4 = 0x4,
    DVAR_TYPE_INT = 0x5,
    DVAR_TYPE_ENUM = 0x6,
    DVAR_TYPE_STRING = 0x7,
    DVAR_TYPE_COLOR = 0x8,
    DVAR_TYPE_INT64 = 0x9,
    DVAR_TYPE_LINEAR_COLOR_RGB = 0xA,
    DVAR_TYPE_COLOR_XYZ = 0xB,
    DVAR_TYPE_COUNT = 0xC,
};

union DvarValue
{
    bool enabled;
    int integer;
    unsigned int unsignedInt;
    float value;
    float vector[4];
    const char* string;
    unsigned __int8 color[4];
};

struct dvar_t {
    char* name;
    int flags;
    dvarType_t type;
    DvarValue current;
    //more stuff
};

//making this from scratch
struct playerState_s
{
    int commandTime;
    int pm_type;
    int pm_time;
    int pm_flags;
    int otherFlags;
    int linkFlags;
    int bobCycle;
    float origin[3];
    float velocity[3];
    //more...
};