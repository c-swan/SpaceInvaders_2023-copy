#pragma once
#include <iostream>
#include <string>
#include <format>
#include <print>

enum struct ErrorType {
	MISSING_TEXTURE,
	MISSING_FILE,
	NULLPTR_SCENE,
	UNKNOWN
};

inline void log_error(const std::string msg) {
	std::cerr << msg << std::endl;
}
inline void log_error(const std::string msg, const std::exception& e) {
	std::cerr << std::format("Runtime error: {}\n", e.what() );
}

inline std::runtime_error file_error(std::string msg, std::string filepath) {
	return std::runtime_error("Could not open file: " + filepath);
}

inline void debug_log(const std::string &msg) {
#ifdef DEBUG
	std::println("{}", msg);
#endif
}
