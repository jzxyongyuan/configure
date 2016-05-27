 
#ifndef  __CONFIGUNIT_H_
#define  __CONFIGUNIT_H_

#include "utils/cc_utils.h"
#include <stdio.h>
#include <map>
#include <vector>

namespace cfgiml{
	enum{
		CONFIG_UNIT_TYPE = 0,
		CONFIG_GROUP_TYPE,
		CONFIG_ARRAY_TYPE,
		CONFIG_ERROR_TYPE
	};
	class Reader;
	class ConfigGroup;
	class ConfigUnit{
		public:
			/**
			 * @brief   方括号重载（三个函数），支持以方括号获取相应字段
			 * 			支持字符串、std::string和int下标。int下标Array专用。
			 * 			如果出错，返回一个ConfigError类型的常量
			 * 			可以用 conf[""].selfType() != CONFIG_ERROR_TYPE来判断
			 *
			 * @return  const ConfigUnit& [] 
			**/
			virtual const ConfigUnit & operator[] (const char *) const;
			virtual const ConfigUnit & operator[] (const std::string &) const;
			virtual const ConfigUnit & operator[] (int) const;

			virtual  ConfigUnit & operator[] (const char *) ;
			virtual  ConfigUnit & operator[] (const std::string &) ;
			virtual  ConfigUnit & operator[] (int) ;
			virtual  ConfigUnit & operator= (ConfigUnit & unit) ;
			
			/**
			 * @brief 将一个ErrCode转化为一个对应的字符串信息
			 * 			ErrCode内部就是一个int, 0为OK，非0为出错信息
			 *
			 * @return  const char* 
			**/
			virtual const char * seeError(const ErrCode &) const;
			virtual ~ConfigUnit();

			/**
			 * @brief 从一个字段中获取特定类型的数据
			 * 			XXX to_XXX() 表示以XXX类型获取该配置项
			 *
			 * @param [out] errCode   : ErrCode* 出错信息
			 * 				errCode不为NULL时，错误号将会写入*errCode
			 * 				当此处errCode为默认值NULL时，出错将会以异常的形式抛出
			 * 				抛出的异常为：ConfigException或其子类
			 * @return  char 
			**/
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
			//to_raw_string : 未经过转义处理的字符串
			virtual std::string to_raw_string(ErrCode * errCode = NULL)const;
			//获取C风格的字符串（常量）
			virtual const char * to_cstr(ErrCode * errCode = NULL)const;

			/**
			 * @brief 带有默认值的to_XXX系列函数
			 *        返回值与to_xxx系列完全相同。
			 *        唯一的不同是：当errCode不为0（即发生错误）, 返回def默认值
			 *
			 * @param [out] errCode   : ErrCode* 出错信息
			 * @param [in] def   : const &  默认值
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



			/**
			 * @brief 与to_XXX功能相同的函数。不过get_XXX系列为C风格
			 * 			传入为用于放值的buffer，返回值是错误号
			 *
			 * @param [out] valueBuf   : char*
			 * @return  ErrCode 
			**/
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
			//获取C风格的字符串，将字符串填入valueBuf，len是valueBuf长度，自动补0，最多填充len-1个字符
			virtual ErrCode get_cstr(char * valueBuf, size_t len) const;


			/**
			 * @brief 带有默认值的ge_XXX系列函数
			 *        返回值与get_xxx系列完全相同。
			 *        唯一的不同是：当返回值不为0（即发生错误）valueBuf中使用def默认值
			 *
			 * @param [out] valueBuf   : char*  传出的值
			 * @param [in] def   : const char&  默认值
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

			/**
			 * @brief 获取自己的类型
			 *
			 * @return  int 
			 * @retval   
			**/
			virtual int selfType()const{
				return CONFIG_UNIT_TYPE;
			}
			
			/**
			 * @brief 获取元素个数
			 *
			 * @return  size_t 个数
			**/
			virtual size_t size()const{
				return 1;
			}


			/**
			 * @brief 访问不存在的key后，给出不存在的key的具体路径。比如 group.sub.nokey
			 *
			 * @return  const char*  不存在的key的路径
			 * @author zhang_rui
			**/
			const char * getErrKeyPath() const;

			/**
			 * @brief 获取子unit。ConfigUnit直接返回error unit
			 *
			 * @return  ConfigUnit &
			**/
			virtual const ConfigUnit & get_sub_unit(int index) const;
			/**
			 * @brief 比较是否相等
			 *
			 * @return  int 0表示相等 -1不相等
			**/
			virtual int equals(const ConfigUnit & conf) const;

			//以下函数的参数中，except为0则用错误号表示错误，
			//except为1则用异常表示错误
			/**
			 * @brief 增加一个unit, 连接到子unit，不做深拷贝
			 *
			 * @param [in] key   : 新增unit的key
			 * @param [in] value : 新增unit的value
			 * @param [in] objtype : unit类型。
			 *    CONFIG_UNIT_TYPE表示unit;
			 *    CONFIG_GROUP_TYPE表示group;
			 *    CONFIG_ARRAY_TYPE表示array;
			 * @return  int 0 成功，其他是错误号
			**/
			virtual int add_unit(const std::string & key, const std::string& value, 
				const int objtype=CONFIG_UNIT_TYPE, int except=0, ConfigUnit ** ref=NULL);

			/**
			 * @brief 复制一个unit, 深拷贝
			 *
			 *  将unit的内容追加到本对象下面。
			 * 类型需要匹配，只能从group复制到group，array复制到array
			 * group要检查key是否重复，不重复则追加
			 * array直接追加
			 * @return  int 0 成功，其他是错误号
			**/
			virtual int append_unit(const ConfigUnit & unit, int except=0);

			/**
			 * @brief 复制一个unit, 深拷贝
			 *
			 *  将unit的内容复制到本对象。
			 * 类型需要匹配，只能从group复制到group，array复制到array
			 * @return  int 0 成功，其他是错误号
			**/
			virtual int copy_unit(const ConfigUnit & unit, int except=0);
			
			/**
			 * @brief 修改unit中value的值
			 *
			 * @return  int 0 成功，其他是错误号
			**/
			virtual int set_value(const std::string & value, int except=0);

			//-----------------从这里往下的东西用户不需要关心-----------------

			//构造函数，
			ConfigUnit();
			ConfigUnit(const std::string& __key, const std::string& __value, const Reader * __cur_reader = NULL, ConfigGroup * father = NULL);

			//调试打印时用，缩进
			void pindent(int ind)const{
				while(ind--){
					printf("    ");
				}
			}
			//打印
			virtual void print(int indent = 0)const{
				pindent(indent);
				printf("=[%s], _value=[%s]\n", _key.c_str(), _value.c_str());
			}


			//for debug or writelog
			virtual std::string info() const{
				std::string buf;
                char char_buf[2048];
                sprintf(char_buf, "[File:%s Line:%d Key:%s Value:%s]",
						_at_file ? _at_file : "NULL", _at_line, _key.c_str(), _value.c_str());
				//buf.appendf("[File:%s Line:%d Key:%s Value:%s]", 
				//		_at_file ? _at_file : "NULL", _at_line, _key.c_str(), _value.c_str());
                buf.append(char_buf);

				return buf;
			}
			//for child class
			virtual ConfigUnit * relativeSection(ConfigUnit *, std::string, int* ){
				return NULL;
			}
			inline const char * getFileName(){
				return _at_file;
			}
			inline int getFileLine(){
				return _at_line;
			}
			static ConfigUnit* get_err_unit();
			virtual void get_full_path(std::string &path, const int get_global = 0) const;
			inline virtual const std::string & get_key_name() const{
				return _key;
			}
			inline ConfigGroup * getFather()const{
				return _father;
			}
		protected:
			inline void setFilePosition(const char *cur_file = "NULL", const int cur_line = -1){
				_at_file = cur_file;
				_at_line = cur_line;
			}
			inline void setFileLine(const int cur_line = -1){
				_at_line = cur_line;
			}
			virtual void popError(ErrCode *, ErrCode) const;
			void setErrorKeyPath(std::string str)const;
			
			std::string _key;
			std::string _value;
			std::string _cstr; //专门的一个被解析后的string，只有当value以"为开头时才起作用
			int _cstr_err;
			const char * _at_file;
			int _at_line;
			ConfigGroup * _father;
			ConfigUnit * create_unit(const std::string & key, const std::string& value, 
				int objtype, ConfigGroup * father);

			/**
			 * @brief 清除内容
			 *
			 * @return  void
			**/
			virtual void clear();
			
		public:
			/**
			 * @brief 复制一个unit, 深拷贝
			 *
			 *  将unit的内容复制到本对象下面。
			 * 类型需要匹配，只能从group复制到group，array复制到array
			 * group要检查key是否重复，不重复则追加
			 * array直接追加
			 * @return  int 0 成功，其他是错误号
			**/
			virtual int _append_unit(const ConfigUnit & unit,int check=1, int except=0);
		private:
			int init_unit(const std::string& __key, const std::string& __value);
	};

}


#endif  //__CONFIGUNIT_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
