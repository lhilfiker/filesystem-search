// functions.h
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <string>
#include <filesystem>

//file change searcher
std::vector<std::filesystem::path> get_paths(std::filesystem::path path, std::filesystem::file_time_type datetime);

//normalize
std::vector<std::string> normalize(std::vector<std::string> input);

#endif
