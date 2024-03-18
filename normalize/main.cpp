#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

std::vector<std::string> normalize(std::vector<std::string> input) {
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


