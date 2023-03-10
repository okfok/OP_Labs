#include "FilePointer.h"

void file_pointer_main(const char *in_file_name, const char *out_file_name) {
    create_or_append_file(in_file_name);
    task(in_file_name, out_file_name);
    std::cout << "Output file:\n";
    print_from_file(out_file_name);
}

void print_from_file(const char *file_name) {

    FILE *file_ptr = fopen(file_name, "r");
    while (true) {
        wchar_t chr = fgetc(file_ptr);
        if (chr == -1) {
            std::wcout << '\n';
            break;
        }
        std::wcout << chr;
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

int to_number(const char *file_name, int begin, int end) {
    FILE *file_ptr = fopen(file_name, "r");
    fseek(file_ptr, begin, SEEK_SET);

    int num = 0;

    for (int i = begin; i < end - 1; ++i) {
        int chr = fgetc(file_ptr);
        if (!isdigit(chr)) {
            num = -1;
            break;
        }
        num = num * 10 + (chr - '0');
    }

    fclose(file_ptr);
    return num;
}

void write_task_line(const char *in_file_name, FILE* out_file_ptr, int begin, int end, int min) {
    FILE *in_file_ptr = fopen(in_file_name, "r");

    fprintf(out_file_ptr, "%d ", min);

    int word_end = end;
    for (int i = end - 1; i >= begin - 1; --i) {
        fseek(in_file_ptr, i, SEEK_SET);
        int chr = fgetc(in_file_ptr);
        int num;

        if (is_spacer(chr)) {
            if (i < word_end - 1) {
                if ((num = to_number(in_file_name, i + 1, word_end + 1)) != -1) {
                    if (num != min)
                        fprintf(out_file_ptr, "%d ", num);
                }
            }
            word_end = i;
        }

        if (i == 0 && i < word_end){
            if ((num = to_number(in_file_name, i, word_end + 1)) != -1) {
                if (num != min)
                    fprintf(out_file_ptr, "%d ", num);
            }
        }
    }


    fseek(in_file_ptr, begin, SEEK_SET);
    int word_begin = begin;
    for (int i = begin; i < end; ++i) {
        int chr = fgetc(in_file_ptr);
        if (is_spacer(chr)) {
            if (i > word_begin) {
                if (to_number(in_file_name, word_begin, i + 1) == -1) {
                    fseek(in_file_ptr, word_begin, SEEK_SET);
                    for (int j = word_begin; j < i; ++j) {
                        fputc(fgetc(in_file_ptr), out_file_ptr);
                    }
                    fputc(' ', out_file_ptr);
                    fseek(in_file_ptr, i + 1, SEEK_SET);
                }
            }
            word_begin = i + 1;
        }

    }


    fseek(out_file_ptr, -1, SEEK_CUR);
    fputc('\n', out_file_ptr);

    fclose(in_file_ptr);
}


void task(const char *in_file_name, const char *out_file_name) {
    FILE *in_file_ptr = fopen(in_file_name, "r");
    FILE *out_file_ptr = fopen(out_file_name, "w");

    int line_begin = 0, word_begin = 0, cur_pos = 0, min, num;
    bool min_found = false, cont = true;

    while (cont) {
        int chr = fgetc(in_file_ptr);
        cur_pos++;
        if (is_spacer(chr)) {
            if (cur_pos > word_begin + 1) {
                if ((num = to_number(in_file_name, word_begin, cur_pos)) != -1) {
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
                        write_task_line(
                                in_file_name,
                                out_file_ptr,
                                line_begin,
                                cur_pos,
                                min
                        );
                    }
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

bool is_spacer(int chr){
    return chr == -1 || chr == 10 || chr == 32;
}
