#include <filesystem>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <vector>
#include <ctime>

namespace fs = std::filesystem;

std::vector<fs::path> get_paths(fs::path path, time_t datetime) {
	std::vector<fs::path> paths;
	for (const auto& dir_entry : fs::recursive_directory_iterator(path)) {
			std::error_code ec;
			if (!fs::is_directory(dir_entry, ec) && to_time_t(fs::last_write_time(dir_entry, ec)) > datetime) {
				paths.push_back(dir_entry.path());
				std::cout << dir_entry << " got added.";
			}
			if (ec) {
			// error logging
			}
	}
	return paths;
}

time_t to_time_T(fs::file_time_type filetime) {
   const auto systemTime = std::chrono::clock_cast<std::chrono::system_clock>(filetime);
   return std::chrono::system_clock::to_time_t(systemTime);
}

int main() 
{
	fs::path path = "/home/user"; 
	time_t datetime = 946684800;

	std::vector<fs::path> paths = get_paths(path, datetime);

	for (fs::path path : paths) {
		std::cout << path << "\n";
	}	


}	

