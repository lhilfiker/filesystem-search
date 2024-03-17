#include <filesystem>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <vector>
#include <ctime>

namespace fs = std::filesystem;


std::vector<fs::path> get_paths(fs::path path, fs::file_time_type datetime) {
	std::vector<fs::path> paths;
	for (const auto& dir_entry : fs::recursive_directory_iterator(path)) {
			std::error_code ec;
			const auto ftime = fs::last_write_time(dir_entry, ec);
			if (!fs::is_directory(dir_entry, ec) && ftime > datetime) { // No read, is text file checks because that will the indexer do.
				paths.push_back(dir_entry.path());
			}
			if (ec) {
			// error logging
			}
	}
	return paths;
}

int main() 
{
	fs::path path = "/home/user/git/filesystem-search/";
	// This is just to get a file_time_type for the PoC. In the final implementation a file_time_type will be provided here.	
	fs::file_time_type datetime = fs::last_write_time("/home/user/git/filesystem-search/readme.md");
	
	std::error_code ec;
	if(!fs::is_directory(path,ec)) return 4;
	if(ec) return ec;

	std::vector<fs::path> paths = get_paths(path, datetime);

	for (fs::path path : paths) {
		std::cout << path << "\n";
	}	

	return 0;


}	

