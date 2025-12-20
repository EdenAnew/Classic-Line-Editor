#pragma once
#include <fstream>
#include <filesystem>

namespace FileHandler {
	std::filesystem::path find_directory(char* filename, char* pathway = nullptr);
	bool file_exists(std::filesystem::path pathway);
	std::ofstream return_file_stream(char* filename, char* pathway = nullptr);
}
