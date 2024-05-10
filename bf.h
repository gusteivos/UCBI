
#ifndef BF_H_
#define BF_H_

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdint.h>
    #include <string.h>


    extern void interpret_bf_stack_dumb(char *source_code, size_t source_code_length, size_t source_code_index,
                                        uint8_t *memory, size_t memory_size, uint8_t *memory_pointer,
                                        size_t *stack, size_t stack_size, size_t stack_pointer);

#endif
