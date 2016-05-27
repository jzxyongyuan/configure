
#ifndef  __CONFIGGROUP_H_
#define  __CONFIGGROUP_H_

#include "ConfigUnit.h"
#include "ConfigError.h"
#include "vector"

namespace cfgiml{
	enum{
		GROUP_DUP_LEVEL0 = 0,   //���������������
		GROUP_DUP_LEVEL1,       //����һ��group���� "GLOBAL"�µ�group�Ƿ����� 
		GROUP_DUP_LEVEL2,       //���������ȵ�����group
		GROUP_DUP_LEVEL3,       //��������group��
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
			 * @brief ����Ĭ��ֵ��to_XXXϵ�к���
			 *        ����ֵ��to_xxxϵ����ȫ��ͬ��
			 *        Ψһ�Ĳ�ͬ�ǣ���errCode��Ϊ0������������, ����defĬ��ֵ
			 *
			 * @param [out] errCode   : ErrCode* ������Ϣ
			 * @param [in] def   : const &  Ĭ��ֵ
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
			//��ȡC�����ַ�����������
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
			 * @brief ����Ĭ��ֵ��ge_XXXϵ�к���
			 *        ����ֵ��get_xxxϵ����ȫ��ͬ��
			 *        Ψһ�Ĳ�ͬ�ǣ�������ֵ��Ϊ0������������valueBuf��ʹ��defĬ��ֵ
			 *
			 * @param [out] valueBuf   : char*  ������ֵ
			 * @param [in] def   : const char&  Ĭ��ֵ
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
			 * @brief �Ƚ��Ƿ����
			 *
			 * @return  int 0��ʾ��� -1�����
			**/
			virtual int equals(const ConfigUnit & conf) const;
			/**
			 * @brief ����һ����unit
			 *
			 * @return  int 0 �ɹ��������Ǵ����
			**/
			virtual int add_unit(const std::string & key, const std::string& value,  
				const int objtype=CONFIG_UNIT_TYPE,int except=0, ConfigUnit ** ref=NULL);
			
			/**
			 * @brief ����һ��unit, ���
			 *
			 *  ��unit�����ݸ��Ƶ�������
			 * ������Ҫƥ�䣬ֻ�ܴ�group���Ƶ�group��array���Ƶ�array
			 * @return  int 0 �ɹ��������Ǵ����
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
			 * @brief �������
			 *
			 * @return  void
			**/
			virtual void clear();
			
			/*
	 		 * @brief ����_dupLevel����������ȼ���ӡgroup��
			 *
			 * @return 0��������DUPLICATED_GROUP������������group
			 				��_dupLevelΪGROUP_DUP_LEVEL0��GROUP_DUP_LEVEL3ʱ������0
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
			 * @brief ����һ��group����unit, ���
			 *
			 * @return  int 0 �ɹ��������Ǵ����
			**/
			virtual int _append_unit(const ConfigUnit & unit,int check=1, int except=0);

	};

}
















#endif  //__CONFIGGROUP_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
