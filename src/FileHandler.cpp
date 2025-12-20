#include "FileHandler.h"
#include <filesystem>
#include <fstream>
#include <stdexcept>

namespace FileHandler {
	std::filesystem::path find_directory(char* filename, char* pathway = nullptr)
	{
		std::filesystem::path chosen_path{};
		if (pathway)
		{
			chosen_path = pathway;
			if (!std::filesystem::exists(chosen_path))
				throw std::invalid_argument("Path does not exist!");
		}
		else
		{
			chosen_path = ".\\Output Files";
			if (!std::filesystem::exists(chosen_path))
				std::filesystem::create_directory(chosen_path);
		}
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

	std::ofstream return_file_stream(char* filename, char* pathway = nullptr)
	{
		std::filesystem::path directory = find_directory(pathway);
		directory += filename;
		if (file_exists(directory))
		{
			std::ofstream file{ directory, std::ios::app };
			return file;
		}
		else
		{
			std::ofstream file{ directory, std::ios::out };
			return file;
		}
	}
}