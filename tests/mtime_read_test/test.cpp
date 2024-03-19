#include <iostream>
#include <filesystem>
#include <chrono>

namespace fs = std::filesystem;

int main() {
	    fs::path file_path = "/home/user/test.txt";

	        auto start = std::chrono::high_resolution_clock::now();

		    try {
			            auto ftime = fs::last_write_time(file_path);
				    auto isdir = fs::is_directory(file_path);
				            auto end = std::chrono::high_resolution_clock::now();

					            std::chrono::duration<double, std::milli> duration = end - start;

						            std::cout << "Reading mtime took " << duration.count() << " milliseconds.\n";
							        } catch (const fs::filesystem_error& e) {
									        std::cerr << "Error reading file mtime: " << e.what() << '\n';
										        return 1;
											    }

		        return 0;
}

