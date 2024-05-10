
#ifndef _UCBI_H_
#define _UCBI_H_

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <string.h>

    #include "utf8.h"
    #include "bf.h"


    extern char *get_file_extension(char *file_path);

    extern char *load_file_no_cr(char *file_path, size_t *out_file_size);

#endif
