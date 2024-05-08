#include "ascii.h"


bool is_ascii_char(char c)
{

    return
    (

    /*  c == '\a' || */
    /*  c == '\b' || */
        c == '\t' ||
        c == '\n' ||
    /*  c == '\v' || */
    /*  c == '\f' || */
        c == '\r' ||

        (c >= ' ' && c <= '~') /* '~' or (char)0x7F */

    );

}

bool is_ascii_string(char *s)
{

    if (!s)
    {

        return false;

    }

    char *s_char = s;

    while (*s_char)
    {

        if (!is_ascii_char(*s_char))
        {

            return false;

        }

        s_char++;

    }

    return true;

}
