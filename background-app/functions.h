// functions.h
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <string>
#include <filesystem>

struct DocumentIndex {
	std::filesystem::path document_path;
	std::vector<std::string> terms;

	DocumentIndex(const std::filesystem::path& path, const std::vector<std::string>& terms)
		: document_path(path), terms(terms) {}
};

//file change searcher
std::vector<std::filesystem::path> get_paths(std::filesystem::path path, std::filesystem::file_time_type datetime);

//normalize
std::vector<std::string> normalize(std::vector<std::string> input);

// string to vector
std::vector<std::string> string_to_vector(std::string input);

#endif
