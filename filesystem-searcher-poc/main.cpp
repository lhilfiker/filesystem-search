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
			if (!fs::is_directory(dir_entry, ec) && ftime > datetime) {
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
	fs::path path = "/";
	std::cin >> path;
	// This is just to get a file_time_type for the PoC. In the final implementation a file_time_type will be provided here.	
	fs::file_time_type datetime = fs::last_write_time("/");

	std::vector<fs::path> paths = get_paths(path, datetime);

	for (fs::path path : paths) {
		std::cout << path << "\n";
	}	


}	

