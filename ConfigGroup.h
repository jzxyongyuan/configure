
#ifndef  __CONFIGGROUP_H_
#define  __CONFIGGROUP_H_

#include "ConfigUnit.h"
#include "ConfigError.h"
#include "vector"

namespace cfgiml{
	enum{
		GROUP_DUP_LEVEL0 = 0,   //允许重名，不检测
		GROUP_DUP_LEVEL1,       //检测第一级group，即 "GLOBAL"下的group是否重名 
		GROUP_DUP_LEVEL2,       //检测所有深度的重名group
		GROUP_DUP_LEVEL3,       //报告所有group名
	};

	class ConfigGroup : public ConfigError{
		public:
			ConfigGroup(){
				_name = "";
				_father = NULL;
				//fieldMap.create(256);
				_dupLevel = GROUP_DUP_LEVEL0;
			}
			ConfigGroup(const char * __name, ConfigGroup * __father = NULL){
				_dupLevel = GROUP_DUP_LEVEL0;
				create(__name, __father);
			}
			virtual const ConfigUnit & operator[] (const char *) const;
			virtual const ConfigUnit & operator[] (const std::string &) const;
			virtual const ConfigUnit & operator[] (int idx) const;

			virtual  ConfigUnit & operator[] (const char *) ;
			virtual  ConfigUnit & operator[] (const std::string &) ;
			virtual  ConfigUnit & operator[] (int idx) ;

			virtual  ConfigUnit & operator= (ConfigUnit & unit){
				return ConfigUnit::operator=(unit);
			}

			virtual void print(int indent = 0) const;
			virtual ~ConfigGroup();
			virtual size_t size()const{
				return fieldMap.size();
			}

			virtual char to_char(ErrCode * errCode = NULL)const;
			virtual unsigned char to_uchar(ErrCode * errCode = NULL)const;
			virtual int16_t to_int16(ErrCode * errCode = NULL)const;
			virtual u_int16_t to_uint16(ErrCode * errCode = NULL)const;
			virtual int to_int32(ErrCode * errCode = NULL)const;
			virtual u_int32_t to_uint32(ErrCode * errCode = NULL)const;
			virtual long long to_int64(ErrCode * errCode = NULL)const;
			virtual unsigned long long to_uint64(ErrCode * errCode = NULL)const;
			virtual float to_float(ErrCode * errCode = NULL)const;
			virtual double to_double(ErrCode * errCode = NULL)const;
			virtual std::string to_string(ErrCode * errCode = NULL)const;
			virtual std::string to_raw_string(ErrCode * errCode = NULL)const;
			virtual const char * to_cstr(ErrCode * errCode = NULL)const;

			/**
			 * @brief 带有默认值的to_XXX系列函数
			 *        返回值与to_xxx系列完全相同。
			 *        唯一的不同是：当errCode不为0（即发生错误）, 返回def默认值
			 *
			 * @param [out] errCode   : ErrCode* 出错信息
			 * @param [in] def   : const &  默认值
			 * @return  
			**/
			virtual char to_char(ErrCode * errCode, const char & def)const;
			virtual unsigned char to_uchar(ErrCode * errCode, const unsigned char & def)const;
			virtual int16_t to_int16(ErrCode * errCode, const int16_t & def)const;
			virtual u_int16_t to_uint16(ErrCode * errCode, const u_int16_t & def)const;
			virtual int to_int32(ErrCode * errCode, const int & def)const;
			virtual u_int32_t to_uint32(ErrCode * errCode, const u_int32_t & def)const;
			virtual long long to_int64(ErrCode * errCode, const long long & def)const;
			virtual unsigned long long to_uint64(ErrCode * errCode, const unsigned long long & def)const;
			virtual float to_float(ErrCode * errCode, const float & def)const;
			virtual double to_double(ErrCode * errCode, const double & def)const;
			virtual std::string to_string(ErrCode * errCode, const std::string & def)const;
			virtual std::string to_raw_string(ErrCode * errCode, const std::string & def)const;
			//获取C风格的字符串（常量）
			virtual const char * to_cstr(ErrCode * errCode, const char * def)const;

			virtual ErrCode get_char(char * valueBuf)const;
			virtual ErrCode get_uchar(unsigned char * valueBuf)const;
			virtual ErrCode get_int16(int16_t * valueBuf)const;
			virtual ErrCode get_uint16(u_int16_t * valueBuf)const;
			virtual ErrCode get_int32(int * valueBuf)const;
			virtual ErrCode get_uint32(u_int32_t * valueBuf)const;
			virtual ErrCode get_int64(long long * valueBuf)const;
			virtual ErrCode get_uint64(unsigned long long * valueBuf)const;
			virtual ErrCode get_float(float * valueBuf)const;
			virtual ErrCode get_double(double * valueBuf)const;
			virtual ErrCode get_string(std::string * valueBuf)const;
			virtual ErrCode get_raw_string(std::string * valueBuf) const;
			virtual ErrCode get_cstr(char * valueBuf, size_t len) const;

			/**
			 * @brief 带有默认值的ge_XXX系列函数
			 *        返回值与get_xxx系列完全相同。
			 *        唯一的不同是：当返回值不为0（即发生错误）valueBuf中使用def默认值
			 *
			 * @param [out] valueBuf   : char*  传出的值
			 * @param [in] def   : const char&  默认值
			 * @return  ErrCode 
			 * @retval   
			 * @see 
			**/
			virtual ErrCode get_char(char * valueBuf, const char & def)const;
			virtual ErrCode get_uchar(unsigned char * valueBuf, const unsigned char & def)const;
			virtual ErrCode get_int16(int16_t * valueBuf, const int16_t & def)const;
			virtual ErrCode get_uint16(u_int16_t * valueBuf, const u_int16_t & def)const;
			virtual ErrCode get_int32(int * valueBuf, const int & def)const;
			virtual ErrCode get_uint32(u_int32_t * valueBuf, const u_int32_t & def)const;
			virtual ErrCode get_int64(long long * valueBuf, const long long & def)const;
			virtual ErrCode get_uint64(unsigned long long * valueBuf, const unsigned long long & def)const;
			virtual ErrCode get_float(float * valueBuf, const float & def)const;
			virtual ErrCode get_double(double * valueBuf, const double & def)const;
			virtual ErrCode get_string(std::string * valueBuf, const std::string & def)const;
			virtual ErrCode get_raw_string(std::string * valueBuf, const std::string & def)const;
			virtual ErrCode get_cstr(char * valueBuf, size_t len, const char * def)const;

			virtual const ConfigUnit & get_sub_unit(int index) const;
			inline virtual const std::string & get_key_name() const{
				return this->_name;
			}

			/**
			 * @brief 比较是否相等
			 *
			 * @return  int 0表示相等 -1不相等
			**/
			virtual int equals(const ConfigUnit & conf) const;
			/**
			 * @brief 增加一个子unit
			 *
			 * @return  int 0 成功，其他是错误号
			**/
			virtual int add_unit(const std::string & key, const std::string& value,  
				const int objtype=CONFIG_UNIT_TYPE,int except=0, ConfigUnit ** ref=NULL);
			
			/**
			 * @brief 复制一个unit, 深拷贝
			 *
			 *  将unit的内容复制到本对象。
			 * 类型需要匹配，只能从group复制到group，array复制到array
			 * @return  int 0 成功，其他是错误号
			**/
			virtual int copy_unit(const ConfigUnit & unit, int except=0);
		protected:
			friend class Reader;
			friend class Configure;
			friend class ConfigUnit;
			void create(const char * __name, ConfigGroup * __father = NULL);
			ConfigUnit * relativeSection(ConfigUnit *globalSec, std::string str, int * depth);
			int push(const std::string& key, ConfigUnit* unit);
			const char * getName() const{
				return _name.c_str();
			}
			virtual int selfType() const{
				return CONFIG_GROUP_TYPE;
			}
			int getLevel() const{
				return _level;
			}

			int _level;

			//ConfigGroup * _father;
			std::string _name;
			std::vector <std::string > fieldList;
			typedef std::map <std::string, ConfigUnit*> :: iterator itr_t;
			typedef std::map <std::string, ConfigUnit*> :: const_iterator const_itr_t;
			typedef std::map <std::string, ConfigUnit*> :: iterator  ptr_t;
			std::map <std::string, ConfigUnit*> fieldMap;

			/**
			 * @brief 清除内容
			 *
			 * @return  void
			**/
			virtual void clear();
			
			/*
	 		 * @brief 根据_dupLevel允许的重名等级打印group名
			 *
			 * @return 0，正常；DUPLICATED_GROUP，存在重名的group
			 				在_dupLevel为GROUP_DUP_LEVEL0或GROUP_DUP_LEVEL3时，返回0
			 */
			int printGroup();
			struct dup_position{
				std::string file;
				int line;
			};
			typedef std::vector <struct dup_position> dup_vector;
			typedef std::map <ConfigUnit *, dup_vector> :: iterator dup_itr;
			typedef std::map <ConfigUnit *, dup_vector> :: iterator  dup_ptr;

			std::map <ConfigUnit *, dup_vector> _dupMap;
			int _dupLevel;
		public:
			/**
			 * @brief 复制一个group的子unit, 深拷贝
			 *
			 * @return  int 0 成功，其他是错误号
			**/
			virtual int _append_unit(const ConfigUnit & unit,int check=1, int except=0);

	};

}
















#endif  //__CONFIGGROUP_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
