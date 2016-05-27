
#ifndef  __CONFIGURE_H_
#define  __CONFIGURE_H_

#include "ConfigGroup.h"
#include "sys/uio.h"
#include <vector>

#define CONFIG_GLOBAL "GLOBAL"
#define CONFIG_INCLUDE "$include"

namespace cfgiml{
	const int MAX_INCLUDE_DEPTH = 1;
	class Reader;
	/**
	 * @brief configure class
	 *
	 */
	class Configure : public ConfigGroup{
		public:
			/**
			 * @brief load config
			 *
			 * @param config_file   : const char* file path of config file
			 * @return 0 success
			 * 				CONFIG_ERROR 配置文件解析错误
			 * 				ERROR 其它错误
			 * @retval   
			 * @see 
			 **/
			int load(char * config_file);


			virtual  ConfigUnit & operator= (ConfigUnit & unit) {
				return ConfigUnit::operator=(unit);
			}

			Configure();
			~Configure();
		protected:
            int split_path(char* full_file, std::string& dir, std::string& file);

			void pushSubReader(const char * conf, int level = -1);
			friend class Reader;
			friend class ConfigGroup;
			friend class ConfigUnit;

			struct ReaderNode{//每一个conf文件
				std::string filename;
				Reader * reader;
				int level;
			};
			std::vector <ReaderNode *> _readers;
			std::string _path;
			Reader * _cur_reader;//当前在处理的文件
			int _cur_level;//当前文件的深度($include的层次)
			void changeSection(std::string str);
			void pushPair(const std::string& key, const std::string& value);
			
			ConfigGroup* _section;
			//depth是一个调试变量
			int _depth;
	};
}



#endif  //__CONFIGURE_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
