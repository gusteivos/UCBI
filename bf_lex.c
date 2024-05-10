#include "bf_lex.h"


char  *bf_lex_source_code = NULL;

size_t bf_lex_source_code_length = 0;

static size_t bf_lex_source_code_index = 0;

static size_t bf_lex_source_code_line = 1;

static size_t bf_lex_source_code_column = 1;


static void bf_lex_advance_source_code_index()
{

    if (!bf_lex_source_code)
    {

        return;

    }

    if (bf_lex_source_code[bf_lex_source_code_index] == '\n')
    {

        bf_lex_source_code_line++;

        bf_lex_source_code_column = 0;

    }
    
    bf_lex_source_code_column++;

    if (bf_lex_source_code_index < bf_lex_source_code_length)
    {

        bf_lex_source_code_index++;

    }

}

bf_token_t bf_lex_next_token()
{

    bf_token_t token = (bf_token_t){ BF_T_T_INVALID, NULL, 0, 0};

    /*
    while (token.type == BF_T_T_INVALID)
    {
        
        char current_char = bf_lex_source_code[bf_lex_source_code_index];
        
        

        bf_lex_advance_source_code_index();

    }
    */

    return token;

}

void bf_lex_reset()
{

    bf_lex_source_code_index = 0;

    bf_lex_source_code_line = 1;

    bf_lex_source_code_column = 1;

}
