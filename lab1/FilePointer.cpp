#include "FilePointer.h"

void file_pointer_main(const char *in_file_name, const char *out_file_name) {
    create_or_append_file(in_file_name);
    task(in_file_name, out_file_name);
}

//        fseek(file_ptr, 0, SEEK_SET);
void print_from_file(const char *file_name) {

    FILE *file_ptr = fopen(file_name, "r");
    while (true) {
        char chr = fgetc(file_ptr);
        if (chr == -1) {
            std::cout << '\n';
            break;
        }
        std::cout << chr;
//        std::cout << chr << " - " << ((int) chr) << '\n';
    }

    fclose(file_ptr);
}

void create_or_append_file(const char *file_name) {
    int mode = 0;
    FILE *file_ptr = fopen(file_name, "r");

    if (file_ptr != nullptr) {
        std::cout << "Found file, content:\n";
        fclose(file_ptr);
        print_from_file(file_name);

        std::cout << "To rewrite file enter 0, to append 1, to not change 2: ";
        std::cin >> mode;
    }

    switch (mode) {
        case 0: {
            file_ptr = fopen(file_name, "w");
            break;
        }
        case 1: {
            file_ptr = fopen(file_name, "a");
            break;
        }
        case 2: {
            return;
        }
        default: {
            throw;
        }
    }

    std::cout << "Writing to file.\nIf you want to end input, go to next line, press Ctrl+B and then Enter.\n";

    int chr = getchar();
    while ((chr = getchar()) != 2)  // 2 is code of Ctrl+B
        fputc(chr, file_ptr);


    fclose(file_ptr);
}

int to_number(FILE *file_ptr, int begin, int end) {
    fseek(file_ptr, begin, SEEK_SET);
    int num = 0;

    for (int i = begin; i < end - 1; ++i) {
        char chr = fgetc(file_ptr);
        if (!isdigit(chr)) {
            num = -1;
            break;
        }
        num = num * 10 + (chr - '0');
    }
    fseek(file_ptr, end, SEEK_SET);
    return num;
}

void write_task_line(FILE *in, FILE *out, int begin, int end, int min) {
    fprintf(out, "%d ", min);


    int word_end = end;
    for (int i = end - 1; i >= begin; --i) {
        fseek(in, i, SEEK_SET);
        int chr = fgetc(in);
        int num;

        if (chr == -1 || chr == 10 || chr == 32) {
            if (i < word_end - 1) {
                if ((num = to_number(in, i + 1, word_end + 1)) != -1) {
                    if (num != min)
                        fprintf(out, "%d ", num);
                }
            }
            word_end = i;
        }
    }


    fseek(in, begin, SEEK_SET);
    int word_begin = 0;
    for (int i = begin; i < end; ++i) {
        char chr = fgetc(in);
        if (chr == -1 || chr == 10 || chr == 32) {
            if (i > word_begin + 1) {
                if (to_number(in, word_begin, i) == -1){
                    fseek(in, word_begin - 1, SEEK_SET);
                    for (int j = word_begin; j < i; ++j) {
                        char ch =  fgetc(in);
                        fputc(ch, out);
                    }
                    fputc(' ', out);
                    fseek(in, i, SEEK_SET);
                }
            }
            word_begin = i + 1;
        }

    }


    fseek(out, -1, SEEK_CUR);
    fprintf(out, "\n");
}


void task(const char *in_file_name, const char *out_file_name) {
    FILE *in_file_ptr = fopen(in_file_name, "r");
    FILE *out_file_ptr = fopen(out_file_name, "w");

    int line_begin = 0, word_begin = 0, cur_pos = 0, min, num;
    bool min_found = false, cont = true;

    while (cont) {
        int chr = fgetc(in_file_ptr);
        cur_pos++;
        if (chr == -1 || chr == 10 || chr == 32) {
            if (cur_pos > word_begin + 1) {
                if ((num = to_number(in_file_ptr, word_begin, cur_pos)) != -1) {
                    if (min_found) {
                        if (min > num)
                            min = num;
                    } else {
                        min = num;
                        min_found = true;
                    }
                }
            }
            switch (chr) {
                case -1: {
                    cont = false;
                }
                case 10: {
                    if (min_found) {
                        std::cout << "writing line\n";
                        write_task_line(
                                in_file_ptr,
                                out_file_ptr,
                                line_begin,
                                cur_pos,
                                min
                        );
                    }
                    fseek(in_file_ptr, cur_pos, SEEK_SET);
                    min_found = false;
                    line_begin = cur_pos;
                }
                default: {
                    word_begin = cur_pos;
                }
            }
        }


    }

    fclose(in_file_ptr);
    fclose(out_file_ptr);

}
