#include "../include/FileHandler.h"
#include <filesystem>
#include <fstream>
#include <stdexcept>

namespace FileHandler {
	std::filesystem::path find_directory(char* filename, char* pathway)
	{
		std::filesystem::path chosen_path{};
		if (pathway)
		{
			chosen_path = pathway;
			if (!std::filesystem::exists(chosen_path))
				throw std::invalid_argument("Path does not exist!\n");
		}
		else
		{
			chosen_path = "./LineEditorOutput";
			if (!std::filesystem::exists(chosen_path))
				std::filesystem::create_directory(chosen_path);
		}
		chosen_path += '/';
		chosen_path += filename;
		return chosen_path;
	}

	bool file_exists(std::filesystem::path pathway)
	{
		std::ifstream in{ pathway };
		if (!in)
			return false;
		in.close();
		return true;
	}
}