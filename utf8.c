#include "utf8.h"


/* https://stackoverflow.com/questions/1031645/how-to-detect-utf-8-in-plain-c */
/* https://www.w3.org/International/questions/qa-forms-utf-8 */


int is_utf8_char(char *c)
{

    if (is_ascii_char(*c))
    {

        return 1;

    }
    

    unsigned char *b = (unsigned char *)c;

    if ( 
        (b[0] >= 0xC2 && b[0] <= 0xDF) &&
        (b[1] >= 0x80 && b[1] <= 0xBF)
       )
    {
    
        return 2;
    
    }


    if( (// excluding overlongs
            b[0] == 0xE0 &&
            (0xA0 <= b[1] && b[1] <= 0xBF) &&
            (0x80 <= b[2] && b[2] <= 0xBF)
        ) ||
        (// straight 3-byte
            ((0xE1 <= b[0] && b[0] <= 0xEC) ||
                b[0] == 0xEE ||
                b[0] == 0xEF) &&
            (0x80 <= b[1] && b[1] <= 0xBF) &&
            (0x80 <= b[2] && b[2] <= 0xBF)
        ) ||
        (// excluding surrogates
            b[0] == 0xED &&
            (0x80 <= b[1] && b[1] <= 0x9F) &&
            (0x80 <= b[2] && b[2] <= 0xBF)
        )
    )
    {
        return 3;
    }


    if( (// planes 1-3
            b[0] == 0xF0 &&
            (0x90 <= b[1] && b[1] <= 0xBF) &&
            (0x80 <= b[2] && b[2] <= 0xBF) &&
            (0x80 <= b[3] && b[3] <= 0xBF)
        ) ||
        (// planes 4-15
            (0xF1 <= b[0] && b[0] <= 0xF3) &&
            (0x80 <= b[1] && b[1] <= 0xBF) &&
            (0x80 <= b[2] && b[2] <= 0xBF) &&
            (0x80 <= b[3] && b[3] <= 0xBF)
        ) ||
        (// plane 16
            b[0] == 0xF4 &&
            (0x80 <= b[1] && b[1] <= 0x8F) &&
            (0x80 <= b[2] && b[2] <= 0xBF) &&
            (0x80 <= b[3] && b[3] <= 0xBF)
        )
    ) {
        return 4;
    }


    return 0;

}

bool is_utf8_string(char *s)
{

    if (!s)
    {

        return false;

    }

    char *s_char = s;

    while (*s_char)
    {

        int q = is_utf8_char(s_char);

        if (!q)
        {

            return false;

        }

        s_char += q;

    }

    return true;

}
