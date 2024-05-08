#include "main.h"


extern void interpret(char* input);


int main(int argc, char *argv[])
{

    char  *bf_source_code      = "++++[++++>---<]>-.---[----->+<]>-.+++[->+++<]>++.++++++++.+++++.-[->+++<]>-.[----->+++<]>.-[--->+<]>.++++++++.>++++++++++.";

    size_t bf_source_code_size = strlen(bf_source_code);

    if (argc > 1)
    {

        char *file_path = argv[1];

        char *file_extension = get_file_extension(file_path);

        if (strcmp((const char *)file_extension, ".bf") != 0)
        {

            fprintf(stderr, ".\n");

            return EXIT_FAILURE;

        }

        bf_source_code = load_file_no_cr(file_path, &bf_source_code_size);

        if (!bf_source_code)
        {

            fprintf(stderr, ".\n");

            return EXIT_FAILURE;

        }

        if (!is_utf8_string(bf_source_code))
        {

            fprintf(stderr, ".\n");

            return EXIT_FAILURE;

        }

    }

    interpret(bf_source_code);

    return EXIT_SUCCESS;

}

char *get_file_extension(char *file_path)
{

    if (!file_path)
    {

        return NULL;

    }

    char *last_dot = strrchr(file_path, '.');

    if (!last_dot)
    {

        return NULL;

    }

    size_t extension_length = strlen(last_dot);

    char *file_extension_buffer = (char *)malloc(extension_length + 1);

    if (!file_extension_buffer)
    {
    
        return NULL;

    }

    strcpy(file_extension_buffer, (const char *)last_dot);

    return file_extension_buffer;

}

char *load_file_no_cr(char *file_path, size_t *out_file_size)
{

    if (!file_path)
    {

        return NULL;

    }

    FILE *file_stream = fopen(file_path, "rb");

    if (file_stream == NULL)
    {

        return NULL;

    }


    if (fseek(file_stream, 0, SEEK_END) != 0)
    {

        fclose(file_stream);


        return NULL;

    }

    long file_size = ftell(file_stream);

    if (file_size == -1)
    {

        fclose(file_stream);


        return NULL;

    }

    if (fseek(file_stream, 0, SEEK_SET) != 0)
    {

        fclose(file_stream);


        return NULL;

    }

    char *file_data_buffer = (char *)malloc(file_size + 1);

    size_t char_count = 0;

    int fgetc_output;

    while ((fgetc_output = fgetc(file_stream)) != EOF)
    {

        char c = (char)fgetc_output; 

        if (c == '\r')
        {

            continue;

        }

        file_data_buffer[char_count] = c;

        char_count++;

    }

    size_t file_data_size = strlen((const char *)file_data_buffer);

    char  *file_data = (char *)malloc(file_data_size + 1);

    if (!file_data)
    {

        free(file_data_buffer);

        return NULL;

    }

    strcpy(file_data, (const char *)file_data_buffer);

    if (out_file_size)
    {

        *out_file_size = file_data_size;

    }

    return file_data;

}
