#include "bf_lex.h"


char  *bf_lex_source_code = NULL;

size_t bf_lex_source_code_length = 0;


static size_t bf_lex_source_code_index = 0;

static size_t bf_lex_source_code_line = 1;

static size_t bf_lex_source_code_column = 1;


bool bf_lex_is_end_of_source_code()
{

    return bf_lex_source_code_index >= bf_lex_source_code_length ||
           bf_lex_source_code[bf_lex_source_code_index] == '\0';

}

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

    if (!bf_lex_is_end_of_source_code())
    {

        bf_lex_source_code_index++;

    }

}

static char *bf_lex_parse_char_sequence()
{

    char current_char = bf_lex_source_code[bf_lex_source_code_index];

    size_t str_len = 0;

    char *str = NULL;

    while
    (
        !bf_lex_is_end_of_source_code() &&
        (
            (isprint(current_char) && !strchr(BF_LEX_CHARS, (int)current_char)) ||
            isspace(current_char)
        )
    )
    {

        if (!str)
        {

            str = (char *)malloc((str_len + 1) * sizeof(char));

        }
        else
        {

            str = (char *)realloc(str, (str_len + 1) * sizeof(char));

        }


        str[str_len++] = current_char;

        bf_lex_advance_source_code_index();

        current_char = bf_lex_source_code[bf_lex_source_code_index];

    }

    if (str_len != 0)
    {

        str[str_len] = '\0';

    }

    return str;

}


bf_token_t bf_lex_next_token()
{

    bf_token_t token = (bf_token_t){ BF_T_T_INVALID, NULL, 0, 0};

    do
    {

        token.line = bf_lex_source_code_line;

        token.column = bf_lex_source_code_column;

        char current_char = bf_lex_source_code[bf_lex_source_code_index];

        switch (current_char)
        {

        case '+':
            token.type = BF_T_T_DATA_INCREMENT;
            break;
        case '-':
            token.type = BF_T_T_DATA_DECREMENT;
            break;

        case '>':
            token.type = BF_T_T_DATA_POINTER_INCREMENT;
            break;
        case '<':
            token.type = BF_T_T_DATA_POINTER_DECREMENT;
            break;

        case '.':
            token.type = BF_T_T_WRITE_DATA;
            break;
        case ',':
            token.type = BF_T_T_READ_DATA;
            break;

        case '[':
            token.type = BF_T_T_JUMP_IF_DATA_ZERO;
            break;
        case ']':
            token.type = BF_T_T_JUMP_IF_DATA_NOT_ZERO;
            break;

        case '\0':
            token.type = BF_T_T_EOS;
            return token;

        default:
            {

                char *token_value = NULL;

                if ((token_value = bf_lex_parse_char_sequence()))
                {

                    int i;

                    for (i = 0; token_value[i] != '\0'; i++)
                    {
                    
                        if (!isspace((int)token_value[i]))
                        {

                            token.type = BF_T_T_COMMENT;

                            token.value = token_value;

                            return token;
                        
                        }
                    
                    }

                    free(token_value);

                }
                else
                {

                    return token;

                }

            }
            break;

        }

        bf_lex_advance_source_code_index();

    }
    while
    (
        !bf_lex_is_end_of_source_code() &&
        token.type == BF_T_T_INVALID
    );

    return token;

}

void bf_lex_reset()
{

    bf_lex_source_code_index = 0;

    bf_lex_source_code_line = 1;

    bf_lex_source_code_column = 1;

}
