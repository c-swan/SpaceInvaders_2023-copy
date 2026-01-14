//#pragma once
//#include <fstream>
//#include <optional>
//#include "ErrorHandling.h"
//
//class FileHandle {
//public:
//	FileHandle(std::string filepath) {
//		file.open(filepath);
//		if(!file) {
//			throw file_error("Could not read file", filepath);
//		}
//		if(!is_open()) {
//			throw file_error("Could not open file", filepath);
//		}
//
//	}
//	~FileHandle() { file.close(); }
//
//	bool is_open() const noexcept { return file.is_open(); }
//	bool operator!() { return !file; }
//
//	std::fstream& getFile() { return file; }
//	bool fail() { return file.fail(); }
//private:
//	std::fstream file;
//};
