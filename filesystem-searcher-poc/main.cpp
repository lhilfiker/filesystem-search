#include <filesystem>
#include <chrono>
#include <vector>
#include <iostream>

namespace fs = std::filesystem;


std::vector<fs::path> get_paths(fs::path path, fs::file_time_type datetime) {
	std::vector<fs::path> paths;
	for (const auto& dir_entry : fs::recursive_directory_iterator(path)) {
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

int main() 
{
	
	std::error_code ec;

	fs::path path = "/";
	// This is just to get a file_time_type for the PoC. In the final implementation a file_time_type will be provided here.	
	fs::file_time_type datetime = fs::last_write_time("/");
	
	if(!fs::is_directory(path,ec)) return 4;
	if(ec) return ec.value();

	auto start = std::chrono::high_resolution_clock::now();
	std::vector<fs::path> paths = get_paths(path, datetime);
	
	auto end = std::chrono::high_resolution_clock::now();
	auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "\n" << paths.size() << " files found.\nTook " << time.count() << " miliseconds.";	

	return 0;


}	

