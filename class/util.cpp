#include "util.h"


int utilLogging(const char* fileName, const char* funcName, const int line, int level, const char* format, ...)
{
    va_list arg_ptr;

    char buffer[65536] = {0,};
    int  length  = 0;
    int  nowDate = utilGetNowDate(NULL);
    int  nowTime = utilGetNowTime(NULL);

    std::string fileName_s = fileName;
                fileName_s = fileName_s.substr(0, fileName_s.find_last_of('.'));

    length += sprintf(&buffer[length], "%d|%d|%-16s|%-20s|%-4d|"
        , nowDate
        , nowTime
        , fileName_s.c_str()
        , funcName
        , line);

    switch(level) {
        case LOGLV_NOR:
            length += sprintf(&buffer[length], "NOR");
        break;
        case LOGLV_DBG:
            length += sprintf(&buffer[length], "DBG");
        break;
        case LOGLV_ERR:
            length += sprintf(&buffer[length], "ERR");
        break;
    }
    length += sprintf(&buffer[length], "|");

    va_start(arg_ptr, format);
    length += vsprintf(&buffer[length], format, arg_ptr);
    va_end(arg_ptr);

    char file[1024] = {0,};
    int  fLength = 0;

    fLength += sprintf(&file[fLength], "%s/%s.%d.log", DIR_PATH_LOG, fileName_s.c_str(), nowDate);
    file[fLength] = '\0';

    std::ofstream logFile;
    logFile.open(file, std::ios::app);
    if(!logFile) {
        return 0;
    }

    logFile << buffer << '\n';
    logFile.close();

    if(level == LOGLV_ERR) {
        char errFile[1024] = {0,};
        int  errFLength = 0;                                                                                                        

        errFLength += sprintf(&errFile[errFLength], "%s/error.%d.log", DIR_PATH_LOG, nowDate);
        errFile[errFLength] = '\0';

        std::ofstream errLogFile;
        errLogFile.open(errFile, std::ios::app);
        if(!errLogFile) {
            return 0;
        }

        errLogFile << buffer << '\n';
        errLogFile.close();
    }

    return length;
}

int utilGetEnvValue(std::string file, std::string key, std::string& output)
{
    std::ifstream envFile(file);
    if(!envFile.is_open()) {                                                                                                                                                                                                                                 
        UTILLOG(LOGLV_ERR, "환경파일 읽어오기 실패[%s]", file.c_str());                                                       
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
            UTILLOG(LOGLV_DBG, "[%s]: [%s]", lValue.c_str(), output.c_str());
            return 0;
        }
    }

    UTILLOG(LOGLV_ERR, "값을 가져올 수 없습니다[%s]", key.c_str());
    return -1;
}

int utilGetNowDate(std::string* output)
{
    char nowDate[16] = {0,};
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm* now_tm = std::localtime(&now_time);                                                                                    

    std::strftime(&nowDate[0], 16, "%Y%m%d", now_tm);
    if(output != NULL) {
        *output = nowDate;
    }

    return std::atoi(nowDate);
}

int utilGetNowTime(std::string* output)
{
    char nowTime[16] = {0,};
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm* now_tm = std::localtime(&now_time);

    std::strftime(&nowTime[0], 16, "%H%M%S", now_tm);
    if(output != NULL) {
        *output = nowTime;
    }

    return std::atoi(nowTime);
}

int utilClearScreen(int os_type)
{
    switch(os_type) {
        case OS_WINDOWS:
            return std::system("cls");
        break;
        case OS_LINUX:
            return std::system("clear");
        break;
        case OS_MAC:
        default:
            return -1;
    }

    return 0;
}

int utilPrintDescription(const std::string desc)
{
	/*
    std::string description = "echo " + desc;
    system(description.c_str());
	*/

	std::cout << desc << std::endl;

    return 0;
}

int utilInputStringHidden(std::string& output)
{
	struct termios oldt;
	struct termios newt;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    std::getline(std::cin, output);

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

	return output.length();
}

int utilInputString(int cflag, std::string& output)
{
	if(cflag == 1) {
		std::cout << "command : ";
	}

    std::getline(std::cin, output);

    return output.length();
}

int utilInputChar(int cflag, char& output)
{
	if(cflag == 1) {
		std::cout << "command : ";
	}

	std::string input;
	std::getline(std::cin, input);
	output = input[0];

	return static_cast<int>(output);
}

int utilInputNumber(int cflag, int output)
{
	if(cflag == 1) {
		std::cout << "command : ";
	}

	std::string input;
	std::getline(std::cin, input);
    try {
        int rtn = std::stoi(input.substr(0, input.find(' ')));
        output = static_cast<int>(rtn);
		if(output < 0) {
			output = 0;
		}
    } catch(const std::invalid_argument& e) {
        UTILLOG(LOGLV_ERR, "0이상의 수를 입력하세요.");
		return -1;
    }
    
    return output;
}

int utilItos(int num, std::string& output)
{
	std::stringstream ss;
	ss << num;

	output = ss.str();

	return output.size();
}
