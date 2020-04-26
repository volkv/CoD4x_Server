﻿#pragma once
#include "cvar.hpp"

struct languageInfo_t
{
    const char* pszName;
    int bPresent;
};


extern "C"
{
    extern qboolean g_currentAsian;
    extern byte _ZZ23SEH_SafeTranslateStringPKcE13szErrorString[0x400];
    extern byte _ZZ23SEH_LocalizeTextMessagePKcS0_15msgLocErrType_tE9szStrings[0x2800];
    extern byte _ZZ23SEH_LocalizeTextMessagePKcS0_15msgLocErrType_tE11iCurrString[0x60];
    extern cvar_t* loc_language;
    extern cvar_t* loc_forceEnglish;
    extern cvar_t* loc_translate;

    extern languageInfo_t g_languages[15];
} // extern "C"
