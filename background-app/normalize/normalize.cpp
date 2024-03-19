#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <utility>
#include <chrono> // just for time measure.
#include <unordered_set>
// https://github.com/Blake-Madden/OleanderStemmingLibrary
#include "english_stem.h"


std::vector<std::string> normalize(std::vector<std::string> input) {
	static const std::unordered_set<char> allowed = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	static std::unordered_set<std::string> stopwords = {"a", "about", "above", "after", "again", "against", "all", "am", "an", "and", "any", "are", "arent", "as", "at", "be", "because", "been", "before", "being", "below", "between", "both", "but", "by", "cant", "cannot", "could", "couldnt", "did", "didnt", "do", "does", "doesnt", "doing", "dont", "down", "during", "each", "few", "for", "from", "further", "had", "hadnt", "has", "hasnt", "have", "havent", "having", "he", "hed", "hell", "hes", "her", "here", "heres", "hers", "herself", "him", "himself", "his", "how", "hows", "i", "id", "ill", "im", "ive", "if", "in", "into", "is", "isnt", "it", "its", "its", "itself", "lets", "me", "more", "most", "mustnt", "my", "myself", "no", "nor", "not", "of", "off", "on", "once", "only", "or", "other", "ought", "our", "ours", "ourselves", "out", "over", "own", "same", "shant", "she", "shed", "shell", "shes", "should", "shouldnt", "so", "some", "such", "than", "that", "thats", "the", "their", "theirs", "them", "themselves", "then", "there", "theres", "these", "they", "theyd", "theyll", "theyre", "theyve", "this", "those", "through", "to", "too", "under", "until", "up", "very", "was", "wasnt", "we", "wed", "well", "were", "weve", "were", "werent", "what", "whats", "when", "whens", "where", "wheres", "which", "while", "who", "whos", "whom", "why", "whys", "with", "wont", "would", "wouldnt", "you", "youd", "youll", "youre", "youve", "your", "yours", "yourself", "yourselves"};
	static stemming::english_stem<> StemEnglish;
	std::vector<std::string> output;
	output.reserve(input.size());
	int i = 0;
	for (std::string word : input) {
		std::string updated = "";
		updated.reserve(word.size());
		for (const char c : word) { // remove invalid 
			if (allowed.find(c) != (allowed.end())) {
				updated += std::tolower(c);
			}
		}
		// stemm
		try {
			std::wstring wordstem(updated.begin(), updated.end());
			StemEnglish(wordstem);
			std::string sw(wordstem.begin(), wordstem.end());
			updated = sw;
		}
		catch(...) {}
		if (!updated.empty() && stopwords.find(updated) == stopwords.end()) {
			output.push_back(updated); 
		}
		++i;
		
	}
	// remove duplicates
	std::sort(output.begin(), output.end());
	auto it = std::unique(output.begin(), output.end());
	output.erase(it, output.end());
	return output;

}
