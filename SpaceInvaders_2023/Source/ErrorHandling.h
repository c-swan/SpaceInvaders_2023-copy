#pragma once
#include <iostream>
#include <string>
#include <format>
#include <print>

enum struct ErrorType {
	MISSING_TEXTURE,
	MISSING_FILE,
	FILE_COULD_NOT_OPEN,
	FILE_COULD_NOT_WRITE,
	NULLPTR_SCENE,
	NULLPTR_GAME,
	NULLPTR_TEXTURE_PACK,
	SAVE_HIGHSCORE_FAIL,
	UNKNOWN
};

struct ErrorMessage {
	ErrorType _type;
	std::string _msg;
};

inline void log_error(const std::string msg, std::string details = "") {
	std::cerr << msg << details << std::endl;
}
inline void log_error(std::string msg, const std::exception& e) {
	std::cerr << std::format("{}: {}\n", msg, e.what() );
}
inline void log_error(const std::exception& e) {
	std::cerr << std::format("Exception: {}\n", e.what() );
}

inline void HandleError(ErrorMessage error) {
	switch(error._type ) {
	case ErrorType::MISSING_TEXTURE:
		log_error("Missing texture: ", error._msg); break;
	case ErrorType::MISSING_FILE:
		log_error("Missing file: ", error._msg); break;
	case ErrorType::SAVE_HIGHSCORE_FAIL:
		log_error("Could not save highscore: ", error._msg); break;
	case ErrorType::NULLPTR_SCENE:
		log_error("No scene! _scene == nullptr"); break;
	case ErrorType::NULLPTR_TEXTURE_PACK:
		log_error("null texture", error._msg); break;
	case ErrorType::NULLPTR_GAME:
		log_error("_game == nullptr. ", error._msg); break;
	default:
		log_error("Unknown error"); break;
	}
}

inline void HandleError(ErrorType error) {
	HandleError(ErrorMessage{error, ""});
}
