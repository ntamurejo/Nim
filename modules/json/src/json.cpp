


#include "jsonFile.h"

namespace json {

	json::JSON json::JSON::LoadJsonFile(const string &str) {
		size_t offset = 0;
		return std::move(parse_next(str, offset));
	}

}
