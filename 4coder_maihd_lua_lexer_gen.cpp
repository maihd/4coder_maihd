/*
4coder_maihd_lua_lexer_gen.cpp - Model definition for a Lua lexer.
*/

// TOP

#define LANG_NAME_LOWER lua
#define LANG_NAME_CAMEL Lua

#include "lexer_generator/4coder_lex_gen_main.cpp"

internal void
build_language_model(void)
{
    u8 utf8[129];
    smh_utf8_fill(utf8);
    
    smh_set_base_character_names();
    smh_typical_tokens();
    
    // Lua Names
    //sm_char_name('!', "Not");
    //sm_char_name('&', "And");
    //sm_char_name('|', "Or");
    //sm_char_name('^', "Xor");
    //sm_char_name('?', "Ternary");
    //sm_char_name('%', "Mod");
    //sm_char_name('/', "Div");
    sm_char_name('.', "Dot");
    sm_char_name('-', "Minus");
    
    // Lua Direct Toke Kinds
    sm_select_base_kind(TokenBaseKind_Comment);
    sm_direct_token_kind("BlockComment");
    sm_direct_token_kind("LineComment");
    
    sm_select_base_kind(TokenBaseKind_Whitespace);
    sm_direct_token_kind("Backslash");
    
    sm_select_base_kind(TokenBaseKind_LiteralFloat);
    sm_direct_token_kind("LiteralNumber");
    
    sm_select_base_kind(TokenBaseKind_LiteralString);
    sm_direct_token_kind("LiteralString");
    
    // Lua Operators
    Operator_Set *main_ops = sm_begin_op_set();
    
    sm_select_base_kind(TokenBaseKind_ScopeOpen);
    sm_op("do");
    sm_op("then");
    sm_op("repeat");
    sm_op("function");
    sm_select_base_kind(TokenBaseKind_ScopeClose);
    sm_op("end");
    sm_op("until");
    
    sm_select_base_kind(TokenBaseKind_ParentheticalOpen);
    sm_op("{");
    sm_op("(");
    sm_op("[");
    sm_select_base_kind(TokenBaseKind_ParentheticalClose);
    sm_op("}");
    sm_op(")");
    sm_op("]");
    
    sm_select_base_kind(TokenBaseKind_StatementClose);
    sm_op(";");
    
    sm_select_base_kind(TokenBaseKind_Operator);
    sm_op("...");
    sm_op(":");
    //sm_op("::");
    sm_op("=");
    sm_op(".");
    sm_op("+");
    sm_op("-");
    //sm_op("!");
    //sm_op("~");
    sm_op("*");
    //sm_op("&");
    //sm_op(".*");
    sm_op("/");
    sm_op("%");
    //sm_op("->");
    //sm_op("=>");
    sm_op("..");
    
    //sm_char_name('<', "Left");
    //sm_char_name('>', "Right");
    //sm_op("<<");
    //sm_op(">>");
    
    sm_char_name('<', "Less");
    sm_char_name('>', "Grtr");
    sm_op("<");
    sm_op("<=");
    sm_op(">");
    sm_op(">=");
    sm_op("==");
    sm_op("~=");
    
    sm_op("^");
    sm_op("|");
    //sm_op("?");
    sm_op("=");
    //sm_op("+=");
    //sm_op("-=");
    //sm_op("*=");
    //sm_op("/=");
    //sm_op("%=");
    
    sm_char_name('<', "Left");
    sm_char_name('>', "Right");
    //sm_op("<<=");
    //sm_op(">>=");
    
    sm_select_base_kind(TokenBaseKind_StatementClose);
    sm_op(",");
    
    // Lua Keywords
    Keyword_Set *main_keys = sm_begin_key_set("main_keys");
    
    sm_select_base_kind(TokenBaseKind_Keyword);
    sm_key("Local");
    sm_key("Function");
    sm_key("Do");
    sm_key("If");
    sm_key("Else");
    sm_key("Elseif");
    sm_key("End");
    sm_key("While");
    sm_key("Repeat");
    sm_key("Until");
    sm_key("For");
    sm_key("Then");
    sm_key("Goto");
    sm_key("Or");
    sm_key("And");
    sm_key("Not");
    
    sm_select_base_kind(TokenBaseKind_LiteralInteger);
    sm_key("LiteralNil", "nil");
    sm_key("LiteralTrue", "true");
    sm_key("LiteralFalse", "false");
    
    sm_select_base_kind(TokenBaseKind_Identifier);
    sm_key_fallback("Identifier");
    
    // State Machine
    State *root = sm_begin_state_machine();
    
    Flag *is_hex = sm_add_flag(FlagResetRule_AutoZero);
    Flag *is_oct = sm_add_flag(FlagResetRule_AutoZero);
    
    Flag *is_char = sm_add_flag(FlagResetRule_AutoZero);
    
#define AddState(N) State *N = sm_add_state(#N)
    
    AddState(identifier);
    AddState(whitespace);
    AddState(whitespace_end_pp);
    AddState(backslash);
    
    AddState(operator_or_fnumber_dot);
    AddState(operator_or_comment_minus);
    
    AddState(number);
    AddState(znumber);
    
    AddState(fnumber_decimal);
    AddState(fnumber_exponent);
    AddState(fnumber_exponent_sign);
    AddState(fnumber_exponent_digits);
    
    AddState(number_hex_first);
    AddState(number_hex);
    AddState(number_oct);
    
    AddState(string);
    AddState(string_esc);
    AddState(string_esc_oct2);
    AddState(string_esc_oct1);
    AddState(string_esc_hex);
    AddState(string_esc_universal_8);
    AddState(string_esc_universal_7);
    AddState(string_esc_universal_6);
    AddState(string_esc_universal_5);
    AddState(string_esc_universal_4);
    AddState(string_esc_universal_3);
    AddState(string_esc_universal_2);
    AddState(string_esc_universal_1);
    
    AddState(raw_string);
    AddState(raw_string_get_delim);
    AddState(raw_string_finish_delim);
    AddState(raw_string_find_close);
    AddState(raw_string_try_delim);
    AddState(raw_string_try_quote);
    
    //AddState(comment_block);
    //AddState(comment_block_try_close);
    //AddState(comment_block_newline);
    AddState(comment_line);
    //AddState(comment_line_backslashing);
    
    Operator_Set *main_ops_without_dot_or_minus = smo_copy_op_set(main_ops);
    smo_remove_ops_with_prefix(main_ops_without_dot_or_minus, ".");
    smo_remove_ops_with_prefix(main_ops_without_dot_or_minus, "-");
    
    Operator_Set *main_ops_with_dot = smo_copy_op_set(main_ops);
    smo_remove_ops_without_prefix(main_ops_with_dot, ".");
    smo_ops_string_skip(main_ops_with_dot, 1);
    
    ////
    
    sm_select_state(root);
    
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("EOF");
        sm_case_eof(emit);
    }
    
    sm_case("abcdefghijklmnopqrstvwxyz"
            "ABCDEFGHIJKMNOPQSTVWXYZ"
            "_$",
            identifier);
    sm_case(utf8, identifier);
    
    sm_case(" \r\t\f\v", whitespace);
    sm_case("\n", whitespace_end_pp);
    //sm_case("\\", backslash);
    
    sm_case(".", operator_or_fnumber_dot);
    sm_case("-", operator_or_comment_minus);
    {
        Character_Set *char_set = smo_new_char_set();
        smo_char_set_union_ops_firsts(char_set, main_ops_without_dot_or_minus);
        smo_char_set_remove(char_set, ".-");
        char *char_set_array = smo_char_set_get_array(char_set);
        State *operator_state = smo_op_set_lexer_root(main_ops_without_dot_or_minus, root, "LexError");
        sm_case_peek(char_set_array, operator_state);
    }
    
    sm_case("123456789", number);
    sm_case("0", znumber);
    
    sm_case("\'", string);
    
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LexError");
        sm_fallback(emit);
    }
    
    ////
    
    sm_select_state(identifier);
    sm_case("abcdefghijklmnopqrstuvwxyz"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "_$"
            "0123456789",
            identifier);
    sm_case(utf8, identifier);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_keys(main_keys);
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(whitespace);
    sm_case(" \t\r\f\v", whitespace);
    sm_case("\n", whitespace_end_pp);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("Whitespace");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(whitespace_end_pp);
    sm_fallback_peek(whitespace);
    
    ////
    
    sm_select_state(backslash);
    sm_case("\r", backslash);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("Backslash");
        sm_case("\n", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("Backslash");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(operator_or_comment_minus);
    sm_case("-", comment_line);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("Minus");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(operator_or_fnumber_dot);
    sm_case("0123456789", fnumber_decimal);
    {
        Character_Set *char_set = smo_new_char_set();
        smo_char_set_union_ops_firsts(char_set, main_ops_with_dot);
        char *char_set_array = smo_char_set_get_array(char_set);
        State *operator_state = smo_op_set_lexer_root(main_ops_with_dot, root, "LexError");
        sm_case_peek(char_set_array, operator_state);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("Dot");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(number);
    sm_case("0123456789", number);
    sm_case(".", fnumber_decimal);
    sm_case("Ee", fnumber_exponent);
    //sm_case("Uu", U_number);
    //sm_case("L", L_number);
    //sm_case("l", l_number);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralInteger");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(znumber);
    sm_case(".", fnumber_decimal);
    sm_case("Ee", fnumber_exponent);
    //sm_case("Uu", U_number);
    //sm_case("L", L_number);
    //sm_case("l", l_number);
    sm_case("Xx", number_hex_first);
    sm_case("01234567", number_oct);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralInteger");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(fnumber_decimal);
    sm_case("0123456789", fnumber_decimal);
    sm_case("Ee", fnumber_exponent);
    {
        //Emit_Rule *emit = sm_emit_rule();
        //sm_emit_handler_direct("LiteralFloat32");
        //sm_case("Ff", emit);
    }
    {
        //Emit_Rule *emit = sm_emit_rule();
        //sm_emit_handler_direct("LiteralFloat64");
        //sm_case("Ll", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralFloat64");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(fnumber_exponent);
    sm_case("+-", fnumber_exponent_sign);
    sm_case("0123456789", fnumber_exponent_digits);
    {
        //Emit_Rule *emit = sm_emit_rule();
        //sm_emit_handler_direct("LiteralFloat32");
        //sm_case("Ff", emit);
    }
    {
        //Emit_Rule *emit = sm_emit_rule();
        //sm_emit_handler_direct("LiteralFloat64");
        //sm_case("Ll", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralFloat64");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(fnumber_exponent_sign);
    sm_case("0123456789", fnumber_exponent_digits);
    {
        //Emit_Rule *emit = sm_emit_rule();
        //sm_emit_handler_direct("LiteralFloat32");
        //sm_case("Ff", emit);
    }
    {
        //Emit_Rule *emit = sm_emit_rule();
        //sm_emit_handler_direct("LiteralFloat64");
        //sm_case("Ll", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralFloat64");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(fnumber_exponent_digits);
    sm_case("0123456789", fnumber_exponent_digits);
    {
        //Emit_Rule *emit = sm_emit_rule();
        //sm_emit_handler_direct("LiteralFloat32");
        //sm_case("Ff", emit);
    }
    {
        //Emit_Rule *emit = sm_emit_rule();
        //sm_emit_handler_direct("LiteralFloat64");
        //sm_case("Ll", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralFloat64");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(number_hex_first);
    sm_set_flag(is_hex, true);
    sm_case("0123456789abcdefABCDEF", number_hex);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LexError");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(number_hex);
    sm_case("0123456789abcdefABCDEF", number_hex);
    //sm_case("Uu", U_number);
    //sm_case("L", L_number);
    //sm_case("l", l_number);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralIntegerHex");
        sm_fallback_peek(emit);
    }
    
    ////
    
    sm_select_state(number_oct);
    sm_set_flag(is_oct, true);
    sm_case("01234567", number_oct);
    //sm_case("Uu", U_number);
    //sm_case("L", L_number);
    //sm_case("l", l_number);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LiteralIntegerOct");
        sm_fallback_peek(emit);
    }
    
    ////
    
    //sm_select_state(U_number);
    //sm_case("L", UL_number);
    //sm_case("l", Ul_number);
    {
        //Emit_Rule *emit = sm_emit_rule();
        //sm_emit_handler_direct(is_hex, "LiteralIntegerHexU");
        //sm_emit_handler_direct(is_oct, "LiteralIntegerOctU");
        //sm_emit_handler_direct("LiteralIntegerU");
        //sm_fallback_peek(emit);
    }
    
    ////
    
    //sm_select_state(L_number);
    //sm_case("L", LL_number);
    //sm_case("Uu", LU_number);
    {
        //Emit_Rule *emit = sm_emit_rule();
        //sm_emit_handler_direct(is_hex, "LiteralIntegerHexL");
        //sm_emit_handler_direct(is_oct, "LiteralIntegerOctL");
        //sm_emit_handler_direct("LiteralIntegerL");
        //sm_fallback_peek(emit);
    }
    
    ////
    
    //sm_select_state(l_number);
    //sm_case("l", LL_number);
    //sm_case("Uu", lU_number);
    {
        //Emit_Rule *emit = sm_emit_rule();
        //sm_emit_handler_direct(is_hex, "LiteralIntegerHexL");
        //sm_emit_handler_direct(is_oct, "LiteralIntegerOctL");
        //sm_emit_handler_direct("LiteralIntegerL");
        //sm_fallback_peek(emit);
    }
    
    ////
    
    //sm_select_state(LL_number);
    //sm_case("Uu", ULL_number);
    {
        //Emit_Rule *emit = sm_emit_rule();
        //sm_emit_handler_direct(is_hex, "LiteralIntegerHexLL");
        //sm_emit_handler_direct(is_oct, "LiteralIntegerOctLL");
        //sm_emit_handler_direct("LiteralIntegerLL");
        //sm_fallback_peek(emit);
    }
    
    ////
    
    //sm_select_state(UL_number);
    //sm_case("L", ULL_number);
    {
        //Emit_Rule *emit = sm_emit_rule();
        //sm_emit_handler_direct(is_hex, "LiteralIntegerHexUL");
        //sm_emit_handler_direct(is_oct, "LiteralIntegerOctUL");
        //sm_emit_handler_direct("LiteralIntegerUL");
        //sm_fallback_peek(emit);
    }
    
    ////
    
    //sm_select_state(Ul_number);
    //sm_case("l", ULL_number);
    {
        //Emit_Rule *emit = sm_emit_rule();
        //sm_emit_handler_direct(is_hex, "LiteralIntegerHexUL");
        //sm_emit_handler_direct(is_oct, "LiteralIntegerOctUL");
        //sm_emit_handler_direct("LiteralIntegerUL");
        //sm_fallback_peek(emit);
    }
    
    ////
    
    //sm_select_state(LU_number);
    {
        //Emit_Rule *emit = sm_emit_rule();
        //sm_emit_handler_direct(is_hex, "LiteralIntegerHexUL");
        //sm_emit_handler_direct(is_oct, "LiteralIntegerOctUL");
        //sm_emit_handler_direct("LiteralIntegerUL");
        //sm_fallback_peek(emit);
    }
    
    ////
    
    //sm_select_state(lU_number);
    {
        //Emit_Rule *emit = sm_emit_rule();
        //sm_emit_handler_direct(is_hex, "LiteralIntegerHexUL");
        //sm_emit_handler_direct(is_oct, "LiteralIntegerOctUL");
        //sm_emit_handler_direct("LiteralIntegerUL");
        //sm_fallback_peek(emit);
    }
    
    ////
    
    //sm_select_state(ULL_number);
    {
        //Emit_Rule *emit = sm_emit_rule();
        //sm_emit_handler_direct(is_hex, "LiteralIntegerHexULL");
        //sm_emit_handler_direct(is_oct, "LiteralIntegerOctULL");
        //sm_emit_handler_direct("LiteralIntegerULL");
        //sm_fallback_peek(emit);
    }
    
    ////
    
    //sm_select_state(pp_directive_whitespace);
    //sm_case(" \t\f\v", pp_directive_whitespace);
    //sm_case_peek("abcdefghijklmnopqrstuvwxyz"
    //"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    //"_"
    //"0123456789",
    //pp_directive_first);
    {
        //Emit_Rule *emit = sm_emit_rule();
        //sm_emit_handler_direct("LexError");
        //sm_fallback_peek(emit);
    }
    
    ////
    
    //sm_select_state(pp_directive_first);
    //sm_delim_mark_first();
    //sm_set_flag(is_pp_body, true);
    //sm_fallback_peek(pp_directive);
    
    ////
    
    //sm_select_state(pp_directive);
    //sm_case("abcdefghijklmnopqrstuvwxyz"
    //"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    //"_"
    //"0123456789",
    //pp_directive);
    //sm_fallback_peek(pp_directive_emit);
    
    ////
    
    //sm_select_state(pp_directive_emit);
    //sm_delim_mark_one_past_last();
    //{
    //Emit_Rule *emit = sm_emit_rule();
    //sm_emit_check_set_flag("PPInclude", is_include_body, true);
    //sm_emit_check_set_flag("PPError", is_error_body, true);
    //sm_emit_handler_keys_delim(pp_directive_set);
    //sm_fallback_peek(emit);
    //}
    
    ////
    
    //sm_select_state(include_pointy);
    //sm_case("abcdefghijklmnopqrstuvwxyz"
    //"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    //"_. /\\"
    //"0123456789",
    //include_pointy);
    //{
    //Emit_Rule *emit = sm_emit_rule();
    //sm_emit_handler_direct("PPIncludeFile");
    //sm_case(">", emit);
    //}
    //{
    //Emit_Rule *emit = sm_emit_rule();
    //sm_emit_handler_direct("LexError");
    //sm_fallback_peek(emit);
    //}
    
    ////
    
    //sm_select_state(include_quotes);
    //sm_case("abcdefghijklmnopqrstuvwxyz"
    //"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    //"_. /\\"
    //"0123456789",
    //include_quotes);
    //{
    //Emit_Rule *emit = sm_emit_rule();
    //sm_emit_handler_direct("PPIncludeFile");
    //sm_case("\"", emit);
    //}
    //{
    //Emit_Rule *emit = sm_emit_rule();
    //sm_emit_handler_direct("LexError");
    //sm_fallback_peek(emit);
    //}
    
    ////
    
    //sm_select_state(pre_L);
    //sm_set_flag(is_wide, true);
    sm_case("\"", string);
    //sm_case("R", pre_R);
    //sm_fallback_peek(identifier);
    
    ////
    
    //sm_select_state(pre_u);
    //sm_set_flag(is_utf16, true);
    //sm_case("\"", string);
    //sm_case("8", pre_u8);
    //sm_case("R", pre_R);
    //sm_fallback_peek(identifier);
    
    ////
    
    //sm_select_state(pre_U);
    //sm_set_flag(is_utf32, true);
    //sm_case("\"", string);
    //sm_case("R", pre_R);
    //sm_fallback_peek(identifier);
    
    ////
    
    //sm_select_state(pre_u8);
    //sm_set_flag(is_utf8, true);
    //sm_case("\"", string);
    //sm_case("R", pre_R);
    //sm_fallback_peek(identifier);
    
    ////
    
    //sm_select_state(pre_R);
    //sm_case("\"", raw_string);
    //sm_fallback_peek(identifier);
    
    ////
    
    //sm_select_state(character);
    //sm_set_flag(is_char, true);
    //sm_fallback_peek(string);
    
    ////
    
    sm_select_state(string);
    {
        Emit_Rule *emit = sm_emit_rule();
        //sm_emit_handler_direct(is_wide, "LiteralStringWide");
        //sm_emit_handler_direct(is_utf8 , "LiteralStringUTF8");
        //sm_emit_handler_direct(is_utf16, "LiteralStringUTF16");
        //sm_emit_handler_direct(is_utf32, "LiteralStringUTF32");
        sm_emit_handler_direct("LiteralString");
        sm_case_eof_peek(emit);
        sm_case_flagged(is_char, false, "\"", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        //sm_emit_handler_direct(is_wide, "LiteralCharacterWide");
        //sm_emit_handler_direct(is_utf8 , "LiteralCharacterUTF8");
        //sm_emit_handler_direct(is_utf16, "LiteralCharacterUTF16");
        //sm_emit_handler_direct(is_utf32, "LiteralCharacterUTF32");
        sm_emit_handler_direct("LiteralString");
        sm_case_eof_peek(emit);
        sm_case_flagged(is_char, true, "\'", emit);
    }
    //sm_case("\\", string_esc);
    //{
    //Emit_Rule *emit = sm_emit_rule();
    //sm_emit_handler_direct("LexError");
    //sm_case_peek("\n", emit);
    //}
    //{
    //Emit_Rule *emit = sm_emit_rule();
    //sm_emit_handler_direct("LexError");
    //sm_case_eof_peek(emit);
    //}
    //sm_case_flagged(is_char, true, "\"", string);
    //sm_case_flagged(is_char, false, "\'", string);
    //sm_fallback(string);
    
    ////
    
    sm_select_state(string_esc);
    sm_case("\n'\"?\\abfnrtv", string);
    sm_case("01234567", string_esc_oct2);
    sm_case("x", string_esc_hex);
    sm_case("u", string_esc_universal_4);
    sm_case("U", string_esc_universal_8);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LexError");
        sm_case_peek("\n", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LexError");
        sm_case_eof_peek(emit);
    }
    sm_fallback(string);
    
    ////
    
    sm_select_state(string_esc_oct2);
    sm_case("01234567", string_esc_oct1);
    sm_fallback_peek(string);
    
    ////
    
    sm_select_state(string_esc_oct1);
    sm_case("01234567", string);
    sm_fallback_peek(string);
    
    ////
    
    sm_select_state(string_esc_hex);
    sm_case("0123456789abcdefABCDEF", string_esc_hex);
    sm_fallback_peek(string);
    
    ////
    
    sm_select_state(string_esc_universal_8);
    sm_case("0123456789abcdefABCDEF", string_esc_universal_7);
    sm_fallback_peek(string);
    
    ////
    
    sm_select_state(string_esc_universal_7);
    sm_case("0123456789abcdefABCDEF", string_esc_universal_6);
    sm_fallback_peek(string);
    
    ////
    
    sm_select_state(string_esc_universal_6);
    sm_case("0123456789abcdefABCDEF", string_esc_universal_5);
    sm_fallback_peek(string);
    
    ////
    
    sm_select_state(string_esc_universal_5);
    sm_case("0123456789abcdefABCDEF", string_esc_universal_4);
    sm_fallback_peek(string);
    
    ////
    
    sm_select_state(string_esc_universal_4);
    sm_case("0123456789abcdefABCDEF", string_esc_universal_3);
    sm_fallback_peek(string);
    
    ////
    
    sm_select_state(string_esc_universal_3);
    sm_case("0123456789abcdefABCDEF", string_esc_universal_2);
    sm_fallback_peek(string);
    
    ////
    
    sm_select_state(string_esc_universal_2);
    sm_case("0123456789abcdefABCDEF", string_esc_universal_1);
    sm_fallback_peek(string);
    
    ////
    
    sm_select_state(string_esc_universal_1);
    sm_case("0123456789abcdefABCDEF", string);
    sm_fallback_peek(string);
    
    ////
    
    sm_select_state(raw_string);
    sm_delim_mark_first();
    sm_fallback_peek(raw_string_get_delim);
    
    ////
    
    sm_select_state(raw_string_get_delim);
    sm_case_peek("(", raw_string_finish_delim);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LexError");
        sm_case(" \\)", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LexError");
        sm_case_eof_peek(emit);
    }
    sm_fallback(raw_string_get_delim);
    
    ////
    
    sm_select_state(raw_string_finish_delim);
    sm_delim_mark_one_past_last();
    sm_fallback_peek(raw_string_find_close);
    
    ////
    
    sm_select_state(raw_string_find_close);
    sm_case(")", raw_string_try_delim);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LexError");
        sm_case_eof_peek(emit);
    }
    sm_fallback(raw_string_find_close);
    
    ////
    
    sm_select_state(raw_string_try_delim);
    sm_match_delim(raw_string_try_quote, raw_string_find_close);
    
    ////
    
    sm_select_state(raw_string_try_quote);
    {
        Emit_Rule *emit = sm_emit_rule();
        //sm_emit_handler_direct(is_wide, "LiteralStringWideRaw");
        //sm_emit_handler_direct(is_utf8 , "LiteralStringUTF8Raw");
        //sm_emit_handler_direct(is_utf16, "LiteralStringUTF16Raw");
        //sm_emit_handler_direct(is_utf32, "LiteralStringUTF32Raw");
        sm_emit_handler_direct("LiteralString");
        sm_case("\"", emit);
    }
    sm_fallback_peek(raw_string_find_close);
    
    ////
    
    //sm_select_state(comment_block);
    //sm_case("*", comment_block_try_close);
    //sm_case("\n", comment_block_newline);
    //{
    //Emit_Rule *emit = sm_emit_rule();
    //sm_emit_handler_direct("BlockComment");
    //sm_case_eof_peek(emit);
    //}
    //sm_fallback(comment_block);
    
    ////
    
    //sm_select_state(comment_block_try_close);
    //{
    //Emit_Rule *emit = sm_emit_rule();
    //sm_emit_handler_direct("BlockComment");
    //sm_case("/", emit);
    //}
    //{
    //Emit_Rule *emit = sm_emit_rule();
    //sm_emit_handler_direct("BlockComment");
    //sm_case_eof_peek(emit);
    //}
    //sm_case("*", comment_block_try_close);
    //sm_fallback(comment_block);
    
    ////
    
    //sm_select_state(comment_block_newline);
    //sm_set_flag(is_pp_body, false);
    //sm_set_flag(is_include_body, false);
    //sm_fallback_peek(comment_block);
    
    ////
    
    sm_select_state(comment_line);
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LineComment");
        sm_case_peek("\n", emit);
    }
    {
        Emit_Rule *emit = sm_emit_rule();
        sm_emit_handler_direct("LineComment");
        sm_case_eof_peek(emit);
    }
    //sm_case("\\", comment_line_backslashing);
    //sm_fallback(comment_line);
    
    //sm_select_state(comment_line_backslashing);
    //sm_case("\r", comment_line_backslashing);
    //sm_fallback(comment_line);
}

//! EOF

