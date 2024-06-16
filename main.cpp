#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

void list_files(const std::string& directory);
void file_size(const std::string& file);

int main(int argc, char* argv[])
{
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <command> <path>" << std::endl;
        std::cerr << "Commands:" << std::endl;
        std::cerr << " list <directory>     List files in the directory" << std::endl;
        std::cerr << " size <file>          Show size of the file" << std::endl;
        return 1;
    }

    std::string command = argv[1];
    std::string path = argv[2];

    if (command == "list") {
        list_files(path);
    } else if (command == "size") {
        file_size(path);
    } else {
        std::cerr << "Unknown command: " << command << std::endl;
        return 1;
    }
    return 0;
}

void list_files(const std::string& directory)
{
    try {
        for (const auto& entry: fs::directory_iterator(directory)) {
            std::cout << entry.path().filename().string() << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void file_size(const std::string& file) 
{
    try {
        auto size = fs::file_size(file);
        std::cout << "Size of " << file << " is " << size << " bytes." << std::endl;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}