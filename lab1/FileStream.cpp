#include "FileStream.h"


void file_stream_main(const std::string &in_file_name, const std::string &out_file_name) {
    create_or_append_file(in_file_name); // Prev editing input file (or creating if not exists)
    std::cout << "Input file:\n";
    print_from_file(in_file_name); // printing input file
    task(in_file_name, out_file_name); // processing task
    std::cout << "Output file:\n";
    print_from_file(out_file_name); // printing output file
}

void print_from_file(const std::string &file_name) {
    std::ifstream file(file_name);
    std::string line;

    while (getline(file, line)) {
        std::cout << line << '\n';
    }

    file.close();
}

void create_or_append_file(const std::string &file_name) {
    std::ifstream in_file(file_name);
    int mode = 0;
    if (in_file.is_open()) { // if file found print content and ask what to do
        std::cout << "Found file, content:\n";
        in_file.close();

        print_from_file(file_name);

        std::cout << "To rewrite file enter 0, to mode 1, to not change 2: ";
        std::cin >> mode;
    }

    std::ofstream out_file;
    switch (mode) {
        case 0: {
            out_file.open(file_name); // rewrite mode
            break;
        }
        case 1: {
            out_file.open(file_name, std::ios::app); // append mode
            break;
        }
        case 2: {
            return; // not edit
        }
        default: {
            throw;
        }
    }

    std::cout << "Writing to file.\nIf you want to end input, go to next line, press Ctrl+B and then Enter.\n";

    std::string line;
    while (true) {
        std::getline(std::cin, line);
        if (line[0] == 2) // 2 is code of Ctrl+B
            break;
        if (!line.empty())
            out_file << line << '\n';
    }

    out_file.close();

}

bool is_number(const std::string &s) {
    if (s.empty())
        return false;

    for (char i : s) {
        if (!isdigit(i)) // if one of chars is not digit it is word
            return false;
    }

    return true;
}

void task(const std::string &in_file_name, const std::string &out_file_name) {
    std::ifstream in_file(in_file_name);
    std::ofstream out_file(out_file_name);
    std::string line;

    while (getline(in_file, line)) {
        bool min_found = false;
        int min;

        std::string str = line;
        while (true) { // finding min number
            int cur = str.find_first_of(' ');
            if (cur == -1) {
                if (is_number(str)) {
                    int num = std::stoi(str);
                    if (min_found) {
                        if (min > num)
                            min = num;
                    } else {
                        min = num;
                        min_found = true;
                    }
                }
                break;
            } else {

                std::string word = str.substr(0, cur);
                str.erase(0, cur + 1);

                if (is_number(word)) {
                    int num = std::stoi(word);
                    if (min_found) {
                        if (min > num)
                            min = num;
                    } else {
                        min = num;
                        min_found = true;
                    }
                }

            }
        }

        if (min_found) { // if min found write line to output file
            out_file << min << ' ';
            str = line;

            while (true) {
                int cur = str.find_last_of(' ');
                if (cur == -1) {

                    break;
                } else {
                    std::string word = str.substr(cur + 1, str.size());
                    str.erase(cur, str.size());

                    if (is_number(word)) {
                        int num = std::stoi(word);
                        if (min != num) {
                            out_file << num << ' ';
                        }
                    }
                }
            }
            str = line;
            while (true) {
                int cur = str.find_first_of(' ');
                if (cur == -1) {
                    if (!is_number(str)) {
                        out_file << str << ' ';
                    }
                    break;
                } else {
                    std::string word = str.substr(0, cur);
                    str.erase(0, cur + 1);
                    if (!is_number(word)) {
                        out_file << word << ' ';
                    }
                }
            }

            out_file << '\n';
        }

    }

    in_file.close();
    out_file.close();

}