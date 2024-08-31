#include "Environment.h"

Environment::Environment()
{
	_env_file = "../_interface.env";
	_env_fileName = "_interface.env";
	_env_path = "../";
}

Environment::~Environment()
{
	_env_file = "";
	_env_fileName = "";
	_env_path = "";
}

int Environment::envGetValue(const std::string key, std::string& output)
{
	std::ifstream envFile(_env_file);
	if(!envFile.is_open()) {
		std::cerr << "환경파일 읽어오기 실패[" << _env_file << "]" << std::endl;
		return -1;
	}

	std::string line;
	std::string lValue;

	size_t delimiterPos = 0;

	while(std::getline(envFile, line)) {
		if(line.empty() || line[0] == '#') {
			continue;
		}

		delimiterPos = line.find(DELIMITER_EQUAL);
		if(delimiterPos == std::string::npos) {
			continue;
		}

		lValue = line.substr(0, delimiterPos);
		if(lValue.compare(key) == 0) {
			output = line.substr(delimiterPos + 1);
			return 0;
		}
	}

	std::cerr << "값을 가져올 수 없습니다[" << key << "]" << std::endl;
	return -1;
}

