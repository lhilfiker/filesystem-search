#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>
std::vector<std::string> normalize(std::vector<std::string> input) {
	const char invalid[] = {'.', ',', '!', '?'};
	int i = 0;
	for (std::string word : input) {
		std::string updated = "";
		for (const char c : word) { // remove invalid 
			if (!std::count(std::begin(invalid), std::end(invalid), c)) {
				updated += std::tolower(c);
			}
		}
		if (updated != "") {
			input[i] = updated;
			++i;
		}
		else {
			input.erase(input.begin() + i); // if updated string is empty, delete it.
		}
	}
	// remove duplicates
	std::sort(input.begin(), input.end());
	auto it = std::unique(input.begin(), input.end());
	input.erase(it, input.end());
	return input;

}

int main() {
	std::string in;
	std::vector<std::string> inv;
	while(std::cin >> in) {
		if (in == "end") break;
		inv.push_back(in);
	}
	std::vector<std::string> cleaned = normalize(inv);

	for (auto const word : cleaned) std::cout << "\n" << word;

}


