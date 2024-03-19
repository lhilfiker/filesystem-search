#include <filesystem>
#include <chrono>
#include <vector>
#include <iostream>

namespace fs = std::filesystem;


std::vector<fs::path> get_paths(fs::path path, fs::file_time_type datetime) {
	std::vector<fs::path> paths;
	for (const auto& dir_entry : fs::recursive_directory_iterator(path, fs::directory_options::skip_permission_denied)) {
			std::error_code ec;
			if (!fs::is_directory(dir_entry, ec) && fs::last_write_time(dir_entry, ec) > datetime) { // No read, is text file checks because that will the indexer do.
				paths.push_back(dir_entry.path());
			}
			if (ec) {
				//errors here are mostly permission errors so not really neccecary.
			}
	}
	return paths;
}
