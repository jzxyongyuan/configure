#include "cc_utils.h"

#include "glog/logging.h"

namespace cfgiml{

	bool Trans :: isInteger(const std::string & str){
		for(int i = 0; i < (int)str.size(); ++i){
			if(isdigit(str[i]) || (str[i] == '-' && i == 0) ||
					(str[i] == '+' && i == 0)){
				continue;
			}
			else{
				return false;
			}
		}
		return true;
	}

	//Float状态机，检查某个字符串是否为float
	//float的组成如下，第二行为状态号: 
	//   [+-][digit][.][digit][Ee][+-][digit] '\0'  ->  true false
	// 0  1     2    3    4    5   6     7               -1    -2
	enum{digit = 0, sig=1, dot=2, E=3, end=4};
	static int g_float_table[8][5] = {
		//digit sig dot E end
		{2, 1, 3, -2, -2}, // 0
		{2, -2, 3, -2, -2},// 1
		{2, -2, 3, 5, -1},//2
		{4, -2, -2, -2, -2},//3
		{4, -2, -2, 5, -1}, //4
		{7, 6, -2, -2, -2},//5
		{7, -2, -2, -2, -2},//6
		{7, -2, -2, -2, -1} //7
	};
	//举例：以g_float_table[2]为例：
	//当前处于状态2 (digit)，如果读到数字，仍然处于状态2.如果读到正负号，出错(-2)
	//如果读到点，变为状态3，如果读到字母E，变为状态5，如果读到结尾，此时已经满足isFloat为true(-1)
	bool floatAutoMachine(int status, const std::string & str, int nextpos){
		if(status == -1){
			return true;
		}else if(status == -2){
			return false;
		}
		char nextchar = (int)str.size() > nextpos ? str[nextpos] : '\0';
		int next;
		if(isdigit(nextchar)){
			next = digit;
		}else if(nextchar == '+' || nextchar == '-'){
			next = sig;
		}else if(nextchar == '.'){
			next = dot;
		}else if(nextchar == 'E' || nextchar == 'e'){
			next = E;
		}else if(nextchar == '\0'){
			next = end;
		}else{
			return false;
		}
		return floatAutoMachine(g_float_table[status][next], str, nextpos+1);
	}

	bool Trans :: isFloat(const std::string & str){
		return floatAutoMachine(0, str, 0);
	}

	static std::string getFirstPart(const std::string & str){
		for(int i = 0; i < (int)str.size(); ++i){
			if(isspace(str[i]) || str[i] == '#'){
				return str.substr(0, i);
			}
		}
		return str;
	}

	int Trans :: str2double(const std::string & __str, double * buf){
		if(! __str.size()){
            LOG(WARNING) << "Config : Null value";
			return NULLVALUE;
		}
		std::string str = getFirstPart(__str);
		char *endptr = NULL;
		errno = 0;
		*buf = strtod(str.c_str(), &endptr);
		if(errno == ERANGE){
            LOG(WARNING) << "Config : str2double : out of rangue";
			return OUTOFRANGE;
		}
		if(*endptr != '\0'){
            LOG(WARNING) << "Config : str2double : Format error char=["  << *endptr << "]";
			return FORMATERROR;
		}
		return 0;
	}

	int Trans :: str2uint64(const std::string & __str, unsigned long long * buf){
		if(! __str.size()){
            LOG(WARNING) << "Config : Null value";
			return NULLVALUE;
		}
		std::string str = getFirstPart(__str);
		char *endptr = NULL;
		if(str[0] == '-'){
			//strtoull有一个问题，会将-1转化成0xFFFFFFFF
			return FORMATERROR;
		}
		errno = 0;
		*buf = strtoull(str.c_str(), &endptr, 0);
		if(errno == ERANGE){
            LOG(WARNING) << "Config : str2uint64 : Out of range";
			return OUTOFRANGE;
		}
		if(*endptr != '\0'){
            LOG(WARNING) << "Config : str2uint64 : Format error char=["  << *endptr << "]";
			return FORMATERROR;
		}
		return 0;
	}

	int Trans :: str2int64(const std::string & __str, long long * buf){
		if(! __str.size()){
            LOG(WARNING) << "Config : Null value";
			return NULLVALUE;
		}
		std::string str = getFirstPart(__str);
		char *endptr = NULL;
		errno = 0;
		*buf = strtoll(str.c_str(), &endptr, 0);
		if(errno == ERANGE){
            LOG(WARNING) << "Config : str2uint64 : Out of range";
			return OUTOFRANGE;
		}
		if(*endptr != '\0'){
            LOG(WARNING) << "Config : str2uint64 : " << __str << "Format error char=["  << *endptr << "]";
			return FORMATERROR;
		}
		return 0;
	}
	/**
	 * \0	空字符(NULL)	00H/0
	 * \n	换行符(LF)	0AH/10
	 * \r	回车符(CR)	0DH/13
	 * \t	水平制表符(HT)	09H/9
	 * \v	垂直制表(VT)	0B/11
	 * \a	响铃(BEL) 	07/7
	 * \b	退格符(BS)	08H/8
	 * \f	换页符(FF)	0CH/12
	 * \’	单引号	27H/39
	 * \"	双引号	22H/34
	 * \\	反斜杠	5CH/92
	 * \ddd 	任意字符 	三位八进制
	 * \xhh 	任意字符 	二位十六进制
	 */
	static int hex2int(char c){
		if(c >= 'A' && c <= 'F'){
			return int(c - 'A' + 10);
		}
		if(c >= 'a' && c <= 'f'){
			return int(c - 'a' + 10);
		}
		if(c >= '0' && c <= '9'){
			return int(c - '0');
		}
		return -255;
	}
	int Trans :: str2str(const std::string & str, std::string * buf){
		if(str.size() == 0 || str[0] != '\"'){
			*buf = str;
			return 0;
		}
		else{
			*buf = "";
			for(int i = 1; i < (int)str.size(); ++i){
				if( str[i] == '\"'){
					return 0;
				}
				else if(str[i] == '\\'){
					++i;
					if(i >= (int)str.size()){
						return FORMATERROR;
					}
					switch(str[i]){
						case '0':
							buf->push_back('\0');break;
						case 'n':
							buf->push_back('\n');break;
						case 'r':
							buf->push_back('\r');break;
						case 't':
							buf->push_back('\t');break;
						case 'v':
							buf->push_back('\v');break;
						case 'a':
							buf->push_back('\a');break;
						case 'b':
							buf->push_back('\b');break;
						case 'f':
							buf->push_back('\f');break;
						case '\'':
							buf->push_back('\'');break;
							case '\"':
								buf->push_back('\"');break;
						case '\\':
							buf->push_back('\\');break;
						case 'x':
						default:
							if(i+2 >= (int)str.size()){
								return FORMATERROR;
							}
							if(str[i] == 'x'){
								int c = hex2int(str[i+1]) * 16 + hex2int(str[i+2]);
								if(c < 0){
									return FORMATERROR;
								}
								else{
									buf->push_back(char(c));
								}
							}
							else if(str[i] >= '0' && str[i] < '8'){
								int c = int(str[i] - '0') * 64 + int(str[i+1] - '0') * 8 + int(str[i+2] - '0');
								if(c > 255){
									return FORMATERROR;
								}
								else{
									buf->push_back(char(c));
								}
							}
							else{
								return FORMATERROR;
							}
							i += 2;
					}
				}
				else{
					buf->push_back(str[i]);
				}
			}
		}
		return FORMATERROR;
	}

	std::string Trans :: cutComment(const std::string & str){
		for(int i = 0; i < (int)str.size(); ++i){
			if(str[i] == '#'){
				return str.substr(0, i);
			}
		}
		return str;
	}

}




/* vim: set ts=4 sw=4 sts=4 tw=100 */
