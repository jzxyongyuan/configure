
#ifndef  __RAWDATA_H_
#define  __RAWDATA_H_

#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <vector>
#include "utils/cc_exception.h"

namespace cfgiml{
	class RawData{
		public:

			int load(const char * filename);
			char * getRebuildBuffer(size_t size);
			int rebuild();
			size_t lineNum();
			size_t size();
			const char * getLine(int idx);
			RawData();
			~RawData();
		protected:
			std::vector <size_t> _line;
			size_t _lnum;
			char * _file;
			size_t _fsize;
			size_t _bufsize;
	};
}
















#endif  //__RAWDATA_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
