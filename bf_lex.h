
#ifndef BF_LEX_H_
#define BF_LEX_H_

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>
    #include <stdbool.h>

    #define BF_LEX_CHARS "+-><[].,"

    typedef enum bf_token_type_e
    {

        BF_T_T_INVALID = 0,

        BF_T_T_COMMENT,

        BF_T_T_DATA_INCREMENT,
        BF_T_T_DATA_DECREMENT,

        BF_T_T_DATA_POINTER_INCREMENT,
        BF_T_T_DATA_POINTER_DECREMENT,

        BF_T_T_WRITE_DATA,
        BF_T_T_READ_DATA,

        BF_T_T_JUMP_IF_DATA_ZERO    ,
        BF_T_T_JUMP_IF_DATA_NOT_ZERO,

        BF_T_T_EOS = EOF

    } bf_token_type_t;

    typedef struct bf_token_s
    {

        bf_token_type_t type;

        char *value;

        size_t line;

        size_t column;

    } bf_token_t;
    
    extern char  *bf_lex_source_code;

    extern size_t bf_lex_source_code_length;

    bf_token_t bf_lex_next_token(void);

    void bf_lex_reset(void);

#endif
