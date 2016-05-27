
#include "glog/logging.h"
#include "Configure.h"
#include "reader/Reader.h"
#include "utils/cc_utils.h"

namespace cfgiml{


    int Configure :: split_path(char* full_file, std::string& dir, std::string& file) {
        char* pos = strrchr(full_file, '/');

        if (NULL == pos) {
            dir  = ".";
            file = std::string(full_file);
        } else {
            dir  = "";
            int front_size = pos - full_file;
            dir.append(full_file, front_size);
            int end_size = strlen(full_file) - front_size - 1;
            file = "";
            file.append(pos+1, end_size);
        }

        return 0;
    }

	//extern Reader * g_cur_reader;
	int Configure :: load(char * config_file) {
		int ret = 0;
		if(config_file == NULL){
            LOG(WARNING) << "Configure.load : path or filename error...";
			return ERROR;
		}

        std::string file;
        split_path(config_file, _path, file);

		if(_readers.size() != 0){
            LOG(WARNING) << "Configure.load : Configure can't be reused, create a new object for load.";
			return ERROR;
		}

		size_t idx = 0;
		pushSubReader(file.c_str(), 0);//config文件进入队列，因为可能有$include，按广度优先处理
		while(idx < _readers.size()){
			ReaderNode & r = (*_readers[idx]);
			_cur_reader = r.reader;
			_cur_level  = r.level;
			_section    = this;//切换到GLOBAL
			_depth      = 0;
			_at_file    = r.filename.c_str();
			ret = r.reader->read(_at_file, this);
			if(ret != 0){
                LOG(WARNING) << "Reader configure file ["<<r.filename<<"] error. Stop.";
				return CONFIG_ERROR;
			}
			++idx;
		}

		return 0;
	}
	void Configure :: pushSubReader(const char * conf, int level){
		if(conf == NULL){
			return;
		}
		if(level < 0){
			level = _cur_level + 1;
		}
		//		conf, MAX_INCLUDE_DEPTH, level);
        DLOG(INFO) << "Config $include : "<<conf<<", MAX_DEPTH="<<MAX_INCLUDE_DEPTH<<", level="<<level<<"";
		if(level > MAX_INCLUDE_DEPTH){
			//		MAX_INCLUDE_DEPTH, _cur_reader->_cur_file.c_str(), _cur_reader->_cur_line);
            LOG(WARNING) << "Config error: Max $include level is "<<MAX_INCLUDE_DEPTH<<" ["<<_cur_reader->_cur_file<<":"<<_cur_reader->_cur_line<<"]";
			return;
		}
		ReaderNode * newNode = new ReaderNode();
		_readers.push_back(newNode);
		ReaderNode & r = *(_readers[_readers.size() - 1]);
		r.reader = new Reader();
		r.filename.append(_path).append("/").append(conf);
		r.level = level;
        LOG(INFO) << "Config : $include : "<<r.filename<<", level=" << r.level;
	}
	
	void Configure :: changeSection(std::string str){
		//		this->getName(), _section->getName(), _depth, _section->getFather()?_section->getFather()->getName():"NULL");
		if(str[0] != '.'){
			_section = this;
			_depth = 0;
		} else {
			int i;
			for(i = 0; i < (int)str.size(); ++i){
				if(str[i] != '.'){
					break;
				}
			}

			if((int)i > _depth){
                LOG(WARNING) <<"Configure : Section Error [%s] Ignored." ;
				throw ConfigException();
			}
			str = str.substr(i);
			//--i;
			i = _depth - i;
			while(i > 0){
				_section = (ConfigGroup *)_section->getFather();
				_depth--;
				i--;
			}
		}

		ConfigGroup * _bak_section = _section;
        LOG(INFO) <<"Config : set Section: New["<<str<<"] -> Father["<<_section->getName()<<"]" ;
		_section = (ConfigGroup *)_section->relativeSection(this, str, &_depth);
		if(_section == NULL){
			_section = _bak_section;
		}
		if(_section && _cur_reader){
			_section->setFilePosition(_cur_reader->_cur_file.c_str(), _cur_reader->_cur_line);
		}
        //LOG(INFO) << "Config : Now _section in : ["<<<<"]";
	}

	void Configure :: pushPair(const std::string& key, const std::string& value){
		ConfigUnit * tmp = new ConfigUnit(key, value, _cur_reader, _section);
		if(_section && (_section->push(key, tmp) != 0)){
			delete tmp;
			free(tmp);
			throw ConfigException();
		}
	}


	Configure :: Configure(){
		create(CONFIG_GLOBAL);
		_section = this;
		_depth = 0;
		_cur_reader = NULL;
		_cur_level = -1;
	}

	Configure :: ~Configure(){
		for(size_t i = 0; i < _readers.size(); ++i){
			delete _readers[i]->reader;
			delete _readers[i];
		}
	}
	

}





