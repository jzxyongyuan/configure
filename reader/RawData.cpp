
#include "RawData.h"
#include <fcntl.h>
#include "glog/logging.h"

namespace cfgiml{
	size_t RawData :: lineNum(){
		return _lnum;
	}

	size_t RawData :: size(){
		return _fsize;
	}

	const char * RawData :: getLine(int idx){
		if(idx < 0 || (size_t)idx >= lineNum()){
			return NULL;
		}
		return (const char *)(_file + _line[idx]);
	}

	RawData :: RawData(){
		_file = NULL;
		_lnum = 0;
		_fsize = 0;
		_bufsize = 0;
	}
	RawData :: ~RawData(){
		if(_file){
			free(_file);
		}
	}

	int RawData :: load(const char * filename){
        LOG(INFO) << "Config : RawData read file ["<<filename<<"]";
		struct stat st;
		if( stat(filename, &st) != 0 ){
            LOG(WARNING) << "I can't stat ["<<filename<<"]";
			return -1;
		}

		int fd = open(filename, O_RDONLY);
		if(-1 == fd){
            LOG(WARNING) << "I can't open ["<<filename<<"]";
			return -1;
		}
		if(_file){
			free(_file);
			_file = NULL;
		}
		_fsize = (size_t)st.st_size;
		_bufsize = ((_fsize >> 12) + 1) << 12;//以4K为单位上取整

		_file = (char *)malloc(_bufsize);
		if(NULL == _file){
            LOG(WARNING) << "malloc failed.";
			close(fd);
			return -1;
		}

		if( read(fd, _file, _fsize) != (ssize_t)_fsize ){
            LOG(WARNING) << "Read file %s error...";
			free(_file);
			_file = NULL;
			close(fd);
			return -1;
		}

		close(fd);
		return rebuild();
	}

	char * RawData :: getRebuildBuffer(size_t __size){
		if(_file){
			free(_file);
			_file = NULL;
		}
		_line.clear();
		_lnum = 0;
		_fsize = __size;
		_bufsize = ((_fsize >> 12) + 1) << 12;//以4K为单位上取整
		_file = (char *)malloc(_bufsize);
		return _file;
	}

	int RawData :: rebuild(){
		if(_fsize == 0){
            LOG(WARNING) <<"The rebuild buffer is empty." ;
			return -1;
		}
		_line.clear();
		_line.push_back(0);
		for(size_t i = 0; i < _fsize; ++i){
			if(_file[i] == '\n' || _file[i] == '\r' || _file[i] == '\0'){
				_file[i] = '\0';
				_line.push_back(i+1);
			}
		}
		_file[_fsize] = '\0';
		_lnum = _line.size();
		_line.push_back(_fsize);//多余的一行的位置，便于计算最后一行的长度
		return 0;
	}

}

/* vim: set ts=4 sw=4 sts=4 tw=100 */
