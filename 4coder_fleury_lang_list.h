/* date = January 29th 2021 9:37 pm */

#ifndef FCODER_FLEURY_LANG_LIST_H
#define FCODER_FLEURY_LANG_LIST_H

// NOTE(rjf): Include language files here.
#include "generated/4coder_fleury_lexer_jai.h"
#include "generated/4coder_fleury_lexer_jai.cpp"
#include "4coder_fleury_lang_cpp.cpp"
#include "4coder_fleury_lang_jai.cpp"
#include "4coder_fleury_lang_metadesk.cpp"

// @note(maihd): Include mai language files here.
#include "generated/4coder_maihd_lexer_cs.h"
#include "generated/4coder_maihd_lexer_cs.cpp"
//#include "generated/4coder_maihd_lexer_lua.h"
//#include "generated/4coder_maihd_lexer_lua.cpp"
#include "generated/4coder_maihd_lexer_zig.h"
#include "generated/4coder_maihd_lexer_zig.cpp"
#include "4coder_maihd_lang_cs.cpp"
//#include "4coder_maihd_lang_lua.cpp"
#include "4coder_maihd_lang_zig.cpp"

// NOTE(rjf): @f4_register_languages Register languages.
function void
F4_RegisterLanguages(void)
{
    // NOTE(rjf): C/C++
    {
        String_Const_u8 extensions[] =
        {
            S8Lit("cpp"), S8Lit("cc"), S8Lit("c"), S8Lit("cxx"),
            S8Lit("C"), S8Lit("h"), S8Lit("hpp"),
        };
        for(int i = 0; i < ArrayCount(extensions); i += 1)
        {
            F4_RegisterLanguage(extensions[i],
                                F4_CPP_IndexFile,
                                lex_full_input_cpp_init,
                                lex_full_input_cpp_breaks,
                                F4_CPP_PosContext,
                                F4_CPP_Highlight,
                                Lex_State_Cpp);
        }
    }
    
    // NOTE(rjf): Jai
    {
        F4_RegisterLanguage(S8Lit("jai"),
                            F4_Jai_IndexFile,
                            lex_full_input_jai_init,
                            lex_full_input_jai_breaks,
                            F4_Jai_PosContext,
                            F4_Jai_Highlight,
                            Lex_State_Jai);
    }
    
    // NOTE(rjf): Metadesk
    {
        String_Const_u8 extensions[] =
        {
            // TODO(rjf): Maybe find a config-driven way to specify these? "mc" was sort of
            // introduced ad-hoc...
            S8Lit("md"), S8Lit("mc"), S8Lit("metacode"), S8Lit("meta"), S8Lit("metadesk"),
        };
        for(int i = 0; i < ArrayCount(extensions); i += 1)
        {
            F4_RegisterLanguage(extensions[i],
                                F4_MD_IndexFile,
                                lex_full_input_cpp_init,
                                lex_full_input_cpp_breaks,
                                F4_MD_PosContext,
                                F4_MD_Highlight,
                                Lex_State_Cpp);
        }
    }
    
    // @note(maihd): C#
    {
        F4_RegisterLanguage(S8Lit("cs"),
                            F4_CS_IndexFile,
                            lex_full_input_cs_init,
                            lex_full_input_cs_breaks,
                            F4_CS_PosContext,
                            F4_CS_Highlight,
                            Lex_State_CS);
    }
    
    // @note(maihd): Lua
    {
        //F4_RegisterLanguage(S8Lit("lua"),
        //F4_Lua_IndexFile,
        //lex_full_input_cpp_init,
        //lex_full_input_cpp_breaks,
        //F4_Lua_PosContext,
        //F4_Lua_Highlight,
        //Lex_State_Lua);
    }
    
    // @note(maihd): Zig
    {
        F4_RegisterLanguage(S8Lit("zig"),
                            F4_CPP_IndexFile,
                            lex_full_input_zig_init,
                            lex_full_input_zig_breaks,
                            F4_CPP_PosContext,
                            F4_CPP_Highlight,
                            Lex_State_Zig);
    }
}

#endif //FCODER_FLEURY_LANG_LIST_H
