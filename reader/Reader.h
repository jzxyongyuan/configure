
#ifndef  __READER_H_
#define  __READER_H_

#include "RawData.h"
#include "Configure.h"
#include <sys/uio.h>

namespace cfgiml{
#define REBUILD_CONF "REBUILD_CONF"
	class Reader{
			RawData _fd;
		public:
			int read(const char * file, Configure * cfg);
			Reader();
		private:
			int build(Configure * cfg);
			int push(Configure * cfg, const char * buf, size_t length);
			struct pair_t{
				std::string key;
				std::string value;
			};
			int sectionParser(const char * buf, size_t length, std::string * str);
			int keyParser(const char * buf, size_t length, pair_t * pair);
			int getWord(const char * from, const char * to, std::string * str);
			friend class ConfigUnit;
			friend class Configure;
			friend class ConfigGroup;
			std::string _cur_file;
			int _cur_line;
	};
}




#endif  //__READER_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
