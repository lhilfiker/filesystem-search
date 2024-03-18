#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>

std::vector<std::string> normalize(std::vector<std::string> input) {
	static const char allowed[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	static std::string stopwords[] = {"a", "about", "above", "after", "again", "against", "all", "am", "an", "and", "any", "are", "arent", "as", "at", "be", "because", "been", "before", "being", "below", "between", "both", "but", "by", "cant", "cannot", "could", "couldnt", "did", "didnt", "do", "does", "doesnt", "doing", "dont", "down", "during", "each", "few", "for", "from", "further", "had", "hadnt", "has", "hasnt", "have", "havent", "having", "he", "hed", "hell", "hes", "her", "here", "heres", "hers", "herself", "him", "himself", "his", "how", "hows", "i", "id", "ill", "im", "ive", "if", "in", "into", "is", "isnt", "it", "its", "its", "itself", "lets", "me", "more", "most", "mustnt", "my", "myself", "no", "nor", "not", "of", "off", "on", "once", "only", "or", "other", "ought", "our", "ours", "ourselves", "out", "over", "own", "same", "shant", "she", "shed", "shell", "shes", "should", "shouldnt", "so", "some", "such", "than", "that", "thats", "the", "their", "theirs", "them", "themselves", "then", "there", "theres", "these", "they", "theyd", "theyll", "theyre", "theyve", "this", "those", "through", "to", "too", "under", "until", "up", "very", "was", "wasnt", "we", "wed", "well", "were", "weve", "were", "werent", "what", "whats", "when", "whens", "where", "wheres", "which", "while", "who", "whos", "whom", "why", "whys", "with", "wont", "would", "wouldnt", "you", "youd", "youll", "youre", "youve", "your", "yours", "yourself", "yourselves"};
	int i = 0;
	for (std::string word : input) {
		std::string updated = "";
		for (const char c : word) { // remove invalid 
			if (std::count(std::begin(allowed), std::end(allowed), c)) {
				updated += std::tolower(c);
			}
		}
		if (updated != "" && !std::count(std::begin(stopwords), std::end(stopwords), updated)) {
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
	int enteredwords = 0;

	std::string in;
	std::vector<std::string> inv;
	while(std::cin >> in) {
		if (in == "end") break;
		inv.push_back(in);
		++enteredwords;
	}
	std::vector<std::string> cleaned = normalize(inv);

	for (auto const word : cleaned) std::cout << "\n" << word;
	
	std::cout << "\n\n\nWords entered at beginning: " << enteredwords << "\nWords after: " << cleaned.size();
}


