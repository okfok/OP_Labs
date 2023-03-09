#include "FileStream.h"

std::string MODE = "-mode";
std::string FILE_POINTER_MODE = "FilePointer";
std::string FILE_STREAM_MODE = "FileStream";

std::string IN_FILE_NAME = "test.txt";
std::string OUT_FILE_NAME = "out.txt";

int main(int argc, char *argv[]) {

    std::cout << "Ctrl+B char: " << (char) 2 << '\n';

    if (argc >= 3 && argv[1] == MODE) {
        if (argv[2] == FILE_POINTER_MODE) {

        } else if (argv[2] == FILE_STREAM_MODE) {
            file_stream_main(IN_FILE_NAME, OUT_FILE_NAME);
        } else
            std::cout << "Incorrect mode!\n";
    } else {
        std::cout << "Missing arguments!\n";
    }

}