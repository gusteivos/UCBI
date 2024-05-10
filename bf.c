#include "bf.h"


void interpret_bf_stack_dumb(char *source_code, size_t source_code_length, size_t source_code_index,
                             uint8_t *memory, size_t memory_size, uint8_t *memory_pointer,
                             size_t *stack, size_t stack_size, size_t stack_pointer)
{

    if (!source_code)
    {

        fprintf(stderr, ".\n");

        return;

    }

    if (!source_code_length)
    {

        source_code_length = strlen(source_code);

    }

    if (source_code_index > source_code_length)
    {

        fprintf(stderr, ".\n");

        return;

    }

    /*TODO: check things related to memory and stack.*/

        memory_pointer = (memory_pointer == NULL) ? memory : memory_pointer;

    char source_code_current_char = '\0';

    while (source_code_index < source_code_length && (source_code_current_char = source_code[source_code_index]))
    {

        source_code_index++;

        switch (source_code_current_char)
        {

        case '+':
            ++*memory_pointer;
            break;
        case '-':
            --*memory_pointer;
            break;

        case '>':
            ++ memory_pointer;
            break;
        case '<':
            -- memory_pointer;
            break;

        case '.':
            fwrite(memory_pointer, 1, 1, stdout);
            break;
        case ',':
            fread (memory_pointer, 1, 1, stdin );
            break;

        case '[':
            {

                if (stack_pointer == stack_size)
                {

                    fprintf(stderr, ".\n");

                    return;

                }
            
                if (*memory_pointer != 0)
                {

                    stack[stack_pointer++] = source_code_index - 1;

                }
                else 
                {

                    /*TODO: make it better later.*/

                    int open_close_brackets = 0;

                    for (size_t i = source_code_index - 1; i < source_code_length; i++)
                    {

                        char source_code_char = source_code[i];

                        if (source_code_char == '[')
                        {
                            open_close_brackets++;
                        }
                        else if (source_code_char == ']')
                        {
                            open_close_brackets--;
                        }

                        if (open_close_brackets == 0)
                        {
                            source_code_index = i + 1;
                            break;
                        }
                        else if (open_close_brackets == -1)
                        {
                            fprintf(stderr, ".\n");
                            return;
                        }

                    }

                }

            }
            break;
        case ']':
            {

                if (stack_pointer == 0)
                {

                    fprintf(stderr, "b.\n");

                    return;

                }

                size_t source_code_index_from_stack = stack[--stack_pointer];

                if (*memory_pointer != 0)
                {

                    source_code_index = source_code_index_from_stack;

                }

            }
            break;

        }

    }

}
