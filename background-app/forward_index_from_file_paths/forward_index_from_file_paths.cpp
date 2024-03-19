#include <vector>
#include <string>
#include <filesystem>
#include <system_error>
#include <unordered_set>
#include <fstream>
#include <iostream>
#include "../functions.h"
#include <iterator>

std::vector<std::string> forward_index_from_paths(std::vector<std::filesystem::path> paths) {
	static std::unordered_set<std::string> notallowed{".png", ".jpeg", ".mp4", ".mp3", ".wav", ".avi", ".mov", ".mkv", ".flv", ".wmv", ".m4a", ".flac", ".ogg", ".gif", ".bmp", ".tif", ".tiff", ".psd", ".eps", ".raw", ".cr2", ".nef", ".orf", ".sr2", ".webp", ".3gp", ".3g2", ".m4v", ".mpg", ".mpeg", ".m2v", ".svi", ".3gp", ".3g2", ".mxf", ".roq", ".nsv", ".flac", ".mid", ".midi", ".wma", ".aac", ".wav", ".ogg", ".oga", ".mka", ".ts", ".jpg", ".heic", ".arw", ".dng", ".dwg", ".dxf", ".ico", ".svg", ".webm", ".lrv", ".m2ts", ".mts", ".divx", ".dat", ".bin", ".iso", ".vob", ".mod", ".m2p", ".m2v", ".m4p", ".m4v", ".mp2", ".mpe", ".mpeg", ".mpg", ".mpv2", ".mts", ".nsv", ".ogm", ".ogv", ".qt", ".ram", ".rm", ".rmvb", ".tod", ".ts", ".vob", ".wm", ".yuv", ".doc", ".docx", ".pdf", ".xls", ".xlsx", ".ppt", ".pptx", ".odb", ".odg", ".odp", ".ods", ".odt", ".pages", ".key", ".numbers", ".ai", ".indd", ".pub", ".xps", ".3dm", ".max", ".obj", ".blend", ".c4d", ".ma", ".mb", ".dae", ".3ds", ".fbx", ".stl", ".skp", ".vrml", ".x3d", ".sldprt", ".sldasm", ".ipt", ".iam", ".dwf", ".dwt", ".idw", ".stl", ".ply", ".pct", ".pcx", ".pic", ".mrw", ".j2k", ".jpf", ".jpx", ".jpm", ".mj2", ".tga", ".dds", ".jxr", ".hdp", ".wdp", ".cur", ".ani"};
	std::vector<std::string> all;
	for (std::filesystem::path current_path : paths) {
		std::error_code ec;
		if (!std::filesystem::exists(current_path) || notallowed.find(current_path.extension()) != notallowed.end()) continue; // files with specific extension, do not even try to read it.
		auto filesize = std::filesystem::file_size(current_path);
		if (filesize > 20971520) continue; // skip if file is too large, in the future this can be customized.
		std::string content;
		content.reserve(filesize); //reserve space for faster read
		std::ifstream ifs(current_path);
		content.assign( (std::istreambuf_iterator<char>(ifs) ),
				(std::istreambuf_iterator<char>()    ) );
		std::stringstream ss(content);
		std::istream_iterator<std::string> begin(ss);
		std::istream_iterator<std::string> end;
		std::vector<std::string> vstrings(begin, end);
		std::vector<std::string> normalized_content = normalize(vstrings);
		all.insert(all.end(), normalized_content.begin(), normalized_content.end());
		if(ec) continue;
	}

	return all;
}

int main() {
	std::string d;
	std::vector<std::filesystem::path> paths;
	while(std::cin>>d) {
		paths.push_back(d);
	}

	std::vector<std::string> content = forward_index_from_paths(paths);
	
	for (std::string file : content) {
		std::cout << file;
	}
}
