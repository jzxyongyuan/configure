#include "ConfigUnit.h"
#include "ConfigError.h"
#include "ConfigArray.h"

#include "utils/cc_utils.h"
#include "reader/Reader.h"
#include "glog/logging.h"

namespace cfgiml{

	ConfigUnit * ConfigUnit :: get_err_unit() {
		static ConfigUnit* g_err_unit = NULL;
		if (NULL == g_err_unit) {
			g_err_unit = new ConfigError();
		}
		return g_err_unit;
	}

	class ErrorUnitControl {
	private:
		static int _needfree;
	public:
		ErrorUnitControl() {
			ConfigUnit :: get_err_unit();
		}
		~ErrorUnitControl() {
			if (_needfree) {
				_needfree =0;
				ConfigUnit *eu = ConfigUnit :: get_err_unit();
				delete eu;
			}
		}
	};
 
	int ErrorUnitControl::_needfree = 1;

	static ErrorUnitControl err_unit_control;

	const ConfigUnit & ConfigUnit :: operator[] (const char * str) const {
		if (selfType() == CONFIG_UNIT_TYPE) {
            LOG(INFO) << "Configure: visit ConfigUnit[char *] : " << _key << "[" << str << "]\n";
			std::string tmp=this->_key;
			tmp.append(".").append(str);
			setErrorKeyPath(tmp);
		}
		return *get_err_unit();
	}
	const ConfigUnit & ConfigUnit :: operator[] (const std::string & str) const{
		if (selfType() == CONFIG_UNIT_TYPE) {
            LOG(INFO) << "Configure: visit ConfigUnit[std::string *] : " << _key << "[" << str << "]\n";
			std::string tmp=this->_key;
			tmp.append(".").append(str);
			setErrorKeyPath(tmp);
		}
		return *get_err_unit();
	}
	const ConfigUnit & ConfigUnit :: operator[] (int idx) const{
		if (selfType() == CONFIG_UNIT_TYPE) {
            LOG(INFO) << "Configure: visit ConfigUnit[cint *] : " << _key << "[" << idx << "]\n";
			std::string tmp=this->_key;
			char tmpid[64];
			snprintf(tmpid,64, "%d",idx);
			tmp.append("[").append(tmpid).append("]");;
			setErrorKeyPath(tmp);
		}
		return *get_err_unit();
	}
	ConfigUnit & ConfigUnit :: operator[] (const char * str) {
		if (selfType() == CONFIG_UNIT_TYPE) {
            LOG(INFO) << "Configure: visit ConfigUnit[char *] : " << _key << "[" << str << "]\n";
			std::string tmp=this->_key;
			tmp.append(".").append(str);
			setErrorKeyPath(tmp);
		}
		return *get_err_unit();
	}
	ConfigUnit & ConfigUnit :: operator[] (const std::string & str) {
		if (selfType() == CONFIG_UNIT_TYPE) {
            LOG(INFO) << "Configure: visit ConfigUnit[std::string] : " << _key << "[" << str << "]\n";
			std::string tmp=this->_key;
			tmp.append(".").append(str);
			setErrorKeyPath(tmp);
		}
		return *get_err_unit();
	}
	ConfigUnit & ConfigUnit :: operator[] (int idx) {
		if (selfType() == CONFIG_UNIT_TYPE) {
            LOG(INFO) << "Configure: visit ConfigUnit[int : " << _key << "[" << idx << "]\n";
			std::string tmp=this->_key;
			char tmpid[64];
			snprintf(tmpid,64, "%d",idx);
			tmp.append("[").append(tmpid).append("]");;
			setErrorKeyPath(tmp);
		}
		return *get_err_unit();
	}

	ConfigUnit & ConfigUnit :: operator= (ConfigUnit & unit) {
		copy_unit(unit, 1);
		return *this;
	}
	ConfigUnit :: ConfigUnit():  _key(""), _at_file ("NULL"), _at_line(-1), _father(NULL) {
	}
	ConfigUnit :: ConfigUnit(const std::string& __key, const std::string& __value, const Reader * __cur_reader, ConfigGroup * father)
				: _at_file("NULL"), _at_line(-1){
		for(int i = 0; i < (int)__key.size(); ++i){
			if(i == 0 && __key[i] == '@'){
				continue;
			}
			if((!isalpha(__key[i])) && (!isdigit(__key[i])) && __key[i] != '_'){
				LOG(WARNING) << "Unsupport _key format [" << __key<<"]";
				throw ConfigException();
			}
		}
		_key = __key;
		_value = __value;
		_cstr = _value;
		_cstr_err = 0;
		_father = father;
		if(__cur_reader != NULL){
			//如果这个reader被释放了，_at_file就会指向非法内存片
			setFilePosition(__cur_reader->_cur_file.c_str(),  __cur_reader->_cur_line);
		}
		if(_value.size() > 0 && _value[0] == '"'){
			_cstr_err = Trans :: str2str(_value, &_cstr);
			if(_cstr_err){
                LOG(WARNING) << "Config : Error format : _key["<< _key <<"] _value["<< _value <<"]";
			}
		}
	}

	const char * ConfigUnit :: seeError(const ErrCode & err)const{
		switch(err){
			case ERROR :
				return "Something error";
			case OK :
				return "OK";
			case FORMATERROR :
				return "Format error";
			case OUTOFRANGE :
				return "Out of range";
			case NULLVALUE :
				return "Value is null";
			case NULLBUFFER :
				return "Given buffer is null";
			case NOSUCHKEY :
				return "No such _key";
			case CONSTRAINT_ERROR :
				return "Constraint error";
			case CONFIG_ERROR :
				return "config error";
			case GROUPTOUNIT :
				return "use group as key";
			case DUPLICATED_KEY :
				return "duplicated key";
			case UNKNOWN :
			default:
				return "Unknown error";
		}
		return "Unknown error";
	}
	void ConfigUnit :: popError(ErrCode * err, ErrCode code)const{
		if(err) {
			*err  = code;
		} else{
			ConfigThrower::throwException(code);
		}
	}

	void ConfigUnit :: setErrorKeyPath(std::string str)const{
		std::string errkeypath = str; //this->_key;
		const ConfigGroup * top = this->_father;
		for (;NULL !=  top; top = top->_father){
			if (top->_name == CONFIG_GLOBAL){
				break;
			} else {
				errkeypath = std::string(top->_name).append(".").append(errkeypath);
			}
		}
		//}
	}

	ConfigUnit :: ~ConfigUnit(){} 
	char ConfigUnit :: to_char(ErrCode * errCode)const{
		char tmp;
		popError(errCode, get_char(&tmp));
		return tmp;
	}

	unsigned char ConfigUnit :: to_uchar(ErrCode * errCode)const{
		unsigned char tmp;
		popError(errCode, get_uchar(&tmp));
		return tmp;
	}

	int16_t ConfigUnit :: to_int16(ErrCode * errCode)const{
		int16_t tmp;
		popError(errCode, get_int16(&tmp));
		return tmp;
	}

	u_int16_t ConfigUnit :: to_uint16(ErrCode * errCode)const{
		u_int16_t tmp;
		popError(errCode, get_uint16(&tmp));
		return tmp;
	}

	int ConfigUnit :: to_int32(ErrCode * errCode)const{
		int tmp;
		popError(errCode, this->get_int32(&tmp));
		return tmp;
	}

	u_int32_t ConfigUnit :: to_uint32(ErrCode * errCode)const{
		u_int32_t tmp;
		popError(errCode, get_uint32(&tmp));
		return tmp;
	}

	long long ConfigUnit :: to_int64(ErrCode * errCode)const{
		long long tmp;
		popError(errCode, get_int64(&tmp));
		return tmp;
	}

	unsigned long long ConfigUnit :: to_uint64(ErrCode * errCode)const{
		unsigned long long tmp;
		popError(errCode, get_uint64(&tmp));
		return tmp;
	}

	float ConfigUnit :: to_float(ErrCode * errCode)const{
		float tmp;
		popError(errCode, get_float(&tmp));
		return tmp;
	}

	double ConfigUnit :: to_double(ErrCode * errCode)const{
		double tmp;
		popError(errCode, get_double(&tmp));
		return tmp;
	}
	std::string ConfigUnit :: to_string(ErrCode * errCode)const{
		std::string tmp;
		popError(errCode, get_string(&tmp));
		return tmp;
	}
	std::string ConfigUnit :: to_raw_string(ErrCode * errCode)const{
		std::string tmp;
		popError(errCode, get_raw_string(&tmp));
		return tmp;
	}
	const char * ConfigUnit :: to_cstr(ErrCode * errCode)const{
		if (_cstr_err) {
            LOG(INFO) << "Configure: visit ConfigUnit.to_cstr() failed";
			setErrorKeyPath(this->_key);
		}
		popError(errCode, _cstr_err);
		return _cstr.c_str();
	}

	//----------------to_xxx with default value
	char ConfigUnit :: to_char(ErrCode * errCode, const char & def)const {
		char ret;
		*errCode = get_char(&ret, def);
		return ret;
	}
	unsigned char ConfigUnit :: to_uchar(ErrCode * errCode, const unsigned char & def)const{
		unsigned char ret;
		*errCode = get_uchar(&ret, def);
		return ret;
	}
	int16_t ConfigUnit :: to_int16(ErrCode * errCode, const int16_t & def)const{
		int16_t ret;
		*errCode = get_int16(&ret, def);
		return ret;
	}
	u_int16_t ConfigUnit :: to_uint16(ErrCode * errCode, const u_int16_t & def)const{
		u_int16_t ret;
		*errCode = get_uint16(&ret, def);
		return ret;
	}
	int ConfigUnit :: to_int32(ErrCode * errCode, const int & def)const{
		int ret;
		*errCode = get_int32(&ret, def);
		return ret;
	}
	u_int32_t ConfigUnit :: to_uint32(ErrCode * errCode, const u_int32_t & def)const{
		u_int32_t ret;
		*errCode = get_uint32(&ret, def);
		return ret;
	}
	long long ConfigUnit :: to_int64(ErrCode * errCode, const long long & def)const{
		long long ret;
		*errCode = get_int64(&ret, def);
		return ret;
	}
	unsigned long long ConfigUnit :: to_uint64(ErrCode * errCode, const unsigned long long & def)const{
		unsigned long long ret;
		*errCode = get_uint64(&ret, def);
		return ret;
	}
	float ConfigUnit :: to_float(ErrCode * errCode, const float & def)const{
		float ret;
		*errCode = get_float(&ret, def);
		return ret;
	}
	double ConfigUnit :: to_double(ErrCode * errCode, const double & def)const{
		double ret;
		*errCode = get_double(&ret, def);
		return ret;
	}
	std::string ConfigUnit :: to_string(ErrCode * errCode, const std::string & def)const{
		std::string ret;
		*errCode = get_string(&ret, def);
		return ret;
	}
	std::string ConfigUnit :: to_raw_string(ErrCode * errCode, const std::string & def)const{
		std::string ret;
		*errCode = get_raw_string(&ret, def);
		return ret;
	}
	//获取C风格的字符串（常量）
	const char * ConfigUnit :: to_cstr(ErrCode * errCode, const char * def)const{
		std::string str;
		*errCode = get_string(&str);
		if (0 != *errCode){
			return def;
		}
		return _cstr.c_str();
	}


	ErrCode ConfigUnit :: get_char(char * valueBuf)const{
        LOG(INFO) << "Config : Get char from _key [" << _key <<"]";
		if(valueBuf == NULL){
            LOG(INFO) << "Configure: visit ConfigUnit.get_char() failed : NULLBUFFER";
			setErrorKeyPath(this->_key);
			return NULLBUFFER;
		}
		std::string buf;
		int ret = Trans :: str2str(_value, &buf);
		if(ret){
            LOG(INFO) << "Configure: visit ConfigUnit.get_char() failed";
			setErrorKeyPath(this->_key);
			return ret;
		}
		if(buf.size()){
			*valueBuf = char(buf[0]);
		}
		else{
            LOG(INFO) << "Configure: visit ConfigUnit.get_char() failed: NULLVALUE";
			setErrorKeyPath(this->_key);
			return NULLVALUE;
		}
		return 0;
	}   

	ErrCode ConfigUnit :: get_uchar(unsigned char * valueBuf)const{
        LOG(INFO) << "Config : Get uchar from _key [" << _key <<"]";
		if(valueBuf == NULL){
            LOG(INFO) << "Configure: visit ConfigUnit.get_uchar() failed : NULLBUFFER";
			setErrorKeyPath(this->_key);
			return NULLBUFFER;
		}
		std::string buf;
		int ret = Trans :: str2str(_value, &buf);
		if(ret){
            LOG(INFO) << "Configure: visit ConfigUnit.get_uchar() failed";
			setErrorKeyPath(this->_key);
			return ret;
		}
		if(buf.size()){
			*valueBuf = (unsigned char)(buf[0]);
		}
		else{
            LOG(INFO) << "Configure: visit ConfigUnit.get_uchar() failed: NULLVALUE";
			setErrorKeyPath(this->_key);
			return NULLVALUE;
		}
		return 0;
	}   

	ErrCode ConfigUnit :: get_int16(int16_t * valueBuf)const{
        LOG(INFO) << "Config : Get int16 from _key [" << _key <<"]";
		if(valueBuf == NULL){
            LOG(INFO) << "Configure: visit ConfigUnit.get_int16() failed : NULLBUFFER";
			setErrorKeyPath(this->_key);
			return NULLBUFFER;
		}
		long long val;
		int ret = Trans :: str2int64(_value, &val);
		if(ret) {
            LOG(INFO) << "Configure: visit ConfigUnit.get_int16() failed";
			setErrorKeyPath(this->_key);
			return ret;
		}
		if( val > (long long)0x7fff || val < -(long long)0x8000 ) {
            LOG(WARNING) << "Config : Get ["<<_key<<"] : out of range.";
			setErrorKeyPath(this->_key);
			return OUTOFRANGE;
		}
		*valueBuf = (int16_t)val;
		return 0;
	}   

	ErrCode ConfigUnit :: get_uint16(u_int16_t * valueBuf)const{
        LOG(INFO) << "Config : Get uint16 from _key [" << _key <<"]";
		if(valueBuf == NULL){
            LOG(INFO) << "Configure: visit ConfigUnit.get_uint16() failed : NULLBUFFER";
			setErrorKeyPath(this->_key);
			return NULLBUFFER;
		}
		unsigned long long val;
		int ret = Trans :: str2uint64(_value, &val);
		if(ret) {
            LOG(INFO) << "Configure: visit ConfigUnit.get_uint16() failed";
			setErrorKeyPath(this->_key);
			return ret;
		}
		if( val > (unsigned long long)0xffff ) {
            LOG(WARNING) << "Config : Get ["<<_key<<"] : out of range.";
			setErrorKeyPath(this->_key);
			return OUTOFRANGE;
		}
		*valueBuf = (u_int16_t)val;
		return 0;
	}   

	ErrCode ConfigUnit :: get_int32(int * valueBuf)const{
        LOG(INFO) << "Config : Get int32 from _key [" << _key <<"]";
		if(valueBuf == NULL){
            LOG(INFO) << "Configure: visit ConfigUnit.get_int32) failed : NULLBUFFER";
			setErrorKeyPath(this->_key);
			return NULLBUFFER;
		}
		long long val;
		int ret = Trans :: str2int64(_value, &val);
		if(ret) {
            LOG(INFO) << "Configure: visit ConfigUnit.get_int32) failed";
			setErrorKeyPath(this->_key);
			return ret;
		}
		if( val > (long long)0x7fffffff || val < -(long long)0x80000000 ) {
            LOG(WARNING) << "Config : Get ["<<_key<<"] : out of range.";
			setErrorKeyPath(this->_key);
			return OUTOFRANGE;
		}
		*valueBuf = (int)val;
		return 0;
	}   

	ErrCode ConfigUnit :: get_uint32(u_int32_t * valueBuf)const{
        LOG(INFO) << "Config : Get uint32 from _key [" << _key <<"]";
		if(valueBuf == NULL){
            LOG(INFO) << "Configure: visit ConfigUnit.get_uint32) failed : NULLBUFFER";
			setErrorKeyPath(this->_key);
			return NULLBUFFER;
		}
		unsigned long long val;
		int ret = Trans :: str2uint64(_value, &val);
		if(ret) {
            LOG(INFO) << "Configure: visit ConfigUnit.get_uint32) failed";
			setErrorKeyPath(this->_key);
			return ret;
		}
		if( val > (unsigned long long)0xffffffff ) {
            LOG(WARNING) << "Config : Get ["<<_key<<"] : out of range.";
			setErrorKeyPath(this->_key);
			return OUTOFRANGE;
		}
		*valueBuf = (u_int32_t)val;
		return 0;
	}   

	ErrCode ConfigUnit :: get_int64(long long * valueBuf)const{
        LOG(INFO) << "Config : Get int64 from _key [" << _key <<"]";
		if(valueBuf == NULL){
            LOG(INFO) << "Configure: visit ConfigUnit.get_int64) failed : NULLBUFFER";
			setErrorKeyPath(this->_key);
			return NULLBUFFER;
		}
		long long val;
		int ret = Trans :: str2int64(_value, &val);
		if(ret) {
            LOG(INFO) << "Configure: visit ConfigUnit.get_int64) failed";
			setErrorKeyPath(this->_key);
			return ret;
		}
		*valueBuf = val;
		return 0;
	}   

	ErrCode ConfigUnit :: get_uint64(unsigned long long * valueBuf)const{
        LOG(INFO) << "Config : Get uint64 from _key [" << _key <<"]";
		if(valueBuf == NULL){
            LOG(INFO) << "Configure: visit ConfigUnit.get_uint64) failed : NULLBUFFER";
			setErrorKeyPath(this->_key);
			return NULLBUFFER;
		}
		unsigned long long val;
		int ret = Trans :: str2uint64(_value, &val);
		if(ret) {
            LOG(INFO) << "Configure: visit ConfigUnit.get_int64) failed";
			setErrorKeyPath(this->_key);
			return ret;
		}
		*valueBuf = val;
		return 0;
	}   


	ErrCode ConfigUnit :: get_float(float * valueBuf)const{  
        LOG(INFO) << "Config : Get float from _key [" << _key <<"]";
		if(valueBuf == NULL){
            LOG(INFO) << "Configure: visit ConfigUnit.get_float) failed : NULLBUFFER";
			setErrorKeyPath(this->_key);
			return NULLBUFFER;
		}
		double buf = 0.0;
		int ret = Trans :: str2double(_value, &buf);
		if(ret) {
            LOG(INFO) << "Configure: visit ConfigUnit.get_float) failed";
			setErrorKeyPath(this->_key);
		}
		*valueBuf = float(buf);
		return ret;
	}   
	ErrCode ConfigUnit :: get_double(double * valueBuf)const{
        LOG(INFO) << "Config : Get double from _key [" << _key <<"]";
		if(valueBuf == NULL){
            LOG(INFO) << "Configure: visit ConfigUnit.get_double) failed : NULLBUFFER";
			setErrorKeyPath(this->_key);
			return NULLBUFFER;
		}
		int ret = Trans :: str2double(_value, valueBuf);
		if(ret) {
            LOG(INFO) << "Configure: visit ConfigUnit.get_double) failed";
			setErrorKeyPath(this->_key);
		}
		return ret;
	}   

	ErrCode ConfigUnit :: get_string(std::string * valueBuf) const{
        LOG(INFO) << "Config : Get std::string from _key [" << _key <<"]";
		if(valueBuf == NULL){
            LOG(INFO) << "Configure: visit ConfigUnit.get_string) failed : NULLBUFFER";
			setErrorKeyPath(this->_key);
			return NULLBUFFER;
		}
		int ret = Trans :: str2str(_value, valueBuf);
		if(ret) {
            LOG(INFO) << "Configure: visit ConfigUnit.get_string) failed";
			setErrorKeyPath(this->_key);
		}
		return ret;
	}   
	ErrCode ConfigUnit :: get_raw_string(std::string * valueBuf) const{
        LOG(INFO) << "Config : Get raw string from _key [" << _key <<"]";
		if(valueBuf == NULL){
            LOG(INFO) << "Configure: visit ConfigUnit.get_raw_string) failed : NULLBUFFER";
			setErrorKeyPath(this->_key);
			return NULLBUFFER;
		}
		*valueBuf = _value;
		return 0;
	}   
	ErrCode ConfigUnit :: get_cstr(char * valueBuf, size_t len) const{
        LOG(INFO) << "Config : Get c style string from _key [" << _key <<"]";
		if(valueBuf == NULL){
            LOG(INFO) << "Configure: visit ConfigUnit.get_cstring) failed : NULLBUFFER";
			setErrorKeyPath(this->_key);
			return NULLBUFFER;
		}
		std::string str;
		int ret = get_string(&str);
		if(ret == 0){
			snprintf(valueBuf, len, "%s", str.c_str());
		} else {
            LOG(INFO) << "Configure: visit ConfigUnit.get_cstr() failed";
			setErrorKeyPath(this->_key);
		}
		return ret;
	}
	//--------------get_xx with default-----------

	ErrCode ConfigUnit :: get_char(char * valueBuf, const char & def)const{
		ErrCode ret = get_char(valueBuf);
		if(ret != 0){
			*valueBuf = def;
		}
		return ret;
	}

	ErrCode ConfigUnit :: get_uchar(unsigned char * valueBuf, const unsigned char & def)const{
		ErrCode ret = get_uchar(valueBuf);
		if(ret != 0){
			*valueBuf = def;
		}
		return ret;
	}

	ErrCode ConfigUnit :: get_int16(int16_t * valueBuf, const int16_t & def)const{
		ErrCode ret = get_int16(valueBuf);
		if(ret != 0){
			*valueBuf = def;
		}
		return ret;
	}

	ErrCode ConfigUnit :: get_uint16(u_int16_t * valueBuf, const u_int16_t & def)const{
		ErrCode ret = get_uint16(valueBuf);
		if(ret != 0){
			*valueBuf = def;
		}
		return ret;
	}

	ErrCode ConfigUnit :: get_int32(int * valueBuf, const int & def)const{
		ErrCode ret = get_int32(valueBuf);
		if(ret != 0){
			*valueBuf = def;
		}
		return ret;
	}

	ErrCode ConfigUnit :: get_uint32(u_int32_t * valueBuf, const u_int32_t & def)const{
		ErrCode ret = get_uint32(valueBuf);
		if(ret != 0){
			*valueBuf = def;
		}
		return ret;
	}

	ErrCode ConfigUnit :: get_int64(long long * valueBuf, const long long & def)const{
		ErrCode ret = get_int64(valueBuf);
		if(ret != 0){
			*valueBuf = def;
		}
		return ret;
	}

	ErrCode ConfigUnit :: get_uint64(unsigned long long * valueBuf, const unsigned long long & def)const{
		ErrCode ret = get_uint64(valueBuf);
		if(ret != 0){
			*valueBuf = def;
		}
		return ret;
	}

	ErrCode ConfigUnit :: get_float(float * valueBuf, const float & def)const{
		ErrCode ret = get_float(valueBuf);
		if(ret != 0){
			*valueBuf = def;
		}
		return ret;
	}

	ErrCode ConfigUnit :: get_double(double * valueBuf, const double & def)const{
		ErrCode ret = get_double(valueBuf);
		if(ret != 0){
			*valueBuf = def;
		}
		return ret;
	}

	ErrCode ConfigUnit :: get_string(std::string * valueBuf, const std::string & def)const{
		ErrCode ret = get_string(valueBuf);
		if(ret != 0){
			*valueBuf = def;
		}
		return ret;
	}

	ErrCode ConfigUnit :: get_raw_string(std::string * valueBuf, const std::string & def)const{
		ErrCode ret = get_raw_string(valueBuf);
		if(ret != 0){
			*valueBuf = def;
		}
		return ret;
	}

	ErrCode ConfigUnit :: get_cstr(char * valueBuf, size_t len, const char * def)const{
		ErrCode ret = get_cstr(valueBuf, len);
		if(ret != 0){
			snprintf(valueBuf, len, "%s", def);
		}
		return ret;
	}


	const char * ConfigUnit :: getErrKeyPath() const{
        return NULL;
	}

	const ConfigUnit & ConfigUnit :: get_sub_unit(int /*index*/) const {
		return *get_err_unit();
	}

	void ConfigUnit :: get_full_path(std::string &path, const int get_global)const {
		path = get_key_name();
		ConfigGroup * tmp = getFather();
		if(get_global){
			while(tmp != NULL){
				const char * group_name = tmp->get_key_name().c_str();
				std::string app = path;
                std::string new_path = group_name;
                new_path.append(".");
                new_path.append(app);
                path = new_path;
				//path.setf("%s.%s", group_name, app.c_str());
				tmp = tmp->getFather();
			}
		}
		else{
			while(tmp != NULL){
				const char * group_name = tmp->get_key_name().c_str();
				if(strcmp(group_name, CONFIG_GLOBAL)){	//ignore CONFIG_GLOBAL
					std::string app = path;
                    std::string new_path = group_name;
                    new_path.append(".");
                    new_path.append(app);
                    path = new_path;
					//path.setf("%s.%s", group_name, app.c_str());
				}
				tmp = tmp->getFather();
			}
		}
	}

	int ConfigUnit :: equals(const ConfigUnit & conf) const {
		try {
			if (conf.to_string() == to_string()) {
				return 0;
			}
			return -1;
		} catch (std::exception) {
			return -1;
		}
		return -1;
	}

	int ConfigUnit :: add_unit(const std::string & /*key*/, const std::string& /*value*/,
			const int /*objtype*/, int except, ConfigUnit ** /*ref*/) {
		if (except) {
			//}
			popError(NULL, ERROR);
		}
		return ERROR;
	}

	int ConfigUnit :: _append_unit(const ConfigUnit & /*unit*/,int /*check*/, int except) {
		if (except) {
			//}
			popError(NULL, ERROR);
		}
		return ERROR;
	}

	int ConfigUnit :: append_unit(const ConfigUnit & unit, int except) {
		return _append_unit(unit, 1, except);
	}

	int ConfigUnit :: copy_unit(const ConfigUnit & unit, int except) {
		int ret = 0;
		if (this->selfType()!= unit.selfType()) {
			ret = ERROR;
			goto cpend;
		}
		ret = init_unit(unit._key, unit._value);
		return ret;
	cpend:
		if (except && (0 != ret)) {
			//}
			popError(NULL, ERROR);
		}
		return ret;
	}

	int ConfigUnit :: set_value(const std::string & value, int /*except*/){
		_value = value;
		_cstr = _value;
		if(_value.size() > 0 && _value[0] == '"'){
			_cstr_err = Trans :: str2str(_value, &_cstr);
			if(_cstr_err){
                LOG(WARNING) << "Config : Error format : _key[" <<_key<<"] _value["<<_value<<"]";
			}
		}
		return 0;
	}
	ConfigUnit * ConfigUnit :: create_unit(const std::string & key, const std::string& value, 
			int objtype, ConfigGroup * father) {
		ConfigUnit * tmp=NULL;
		try {
			switch (objtype) {
			case CONFIG_UNIT_TYPE :
				tmp = new ConfigUnit(key, value, NULL, father);
				return tmp;
				break;
			case CONFIG_GROUP_TYPE :
				tmp = new ConfigGroup(key.c_str(), father);
				return tmp;
				break;
			case CONFIG_ARRAY_TYPE :
				tmp = new ConfigArray(key.c_str(), father);
				return tmp;
				break;
			default :
				break;
			}
		} catch (...) {
			if (tmp) {
				delete tmp;
			}
			return NULL;
		}
		return NULL;
	}

	void ConfigUnit :: clear() {
		return;
	}

	int ConfigUnit :: init_unit(const std::string& /*__key*/, const std::string& __value) {
		_value = __value;
		_cstr = _value;
		_cstr_err = 0;
		if(_value.size() > 0 && _value[0] == '"'){
			_cstr_err = Trans :: str2str(_value, &_cstr);
			if(_cstr_err){
                LOG(WARNING) << "Config : Error format : _key["<<_key<<"] _value["<<_value<<"]";
			}
		}
		return 0;
	}

	
};




/* vim: set ts=4 sw=4 sts=4 tw=100 */
