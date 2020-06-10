#ifndef SETTINGS_H_06102020
#define SETTINGS_H_06102020

namespace CherryEngine {

#define SETTING(k, v) k,
enum SettingName
{
    #include "setting_names.h"
    S_NUM
};
#undef SETTING

#define SETTING(k, v) #k,
static const char* SettingNameStr[] = {
    #include "setting_names.h"
    "Invalid"
};
#undef SETTING

#define SETTING(k, v) v,
static const int DefaultSettingValue[] = {
    #include "setting_names.h"
    -1
};
#undef SETTING

}

#endif