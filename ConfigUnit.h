 
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
			 * @brief   ���������أ�������������֧���Է����Ż�ȡ��Ӧ�ֶ�
			 * 			֧���ַ�����std::string��int�±ꡣint�±�Arrayר�á�
			 * 			�����������һ��ConfigError���͵ĳ���
			 * 			������ conf[""].selfType() != CONFIG_ERROR_TYPE���ж�
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
			 * @brief ��һ��ErrCodeת��Ϊһ����Ӧ���ַ�����Ϣ
			 * 			ErrCode�ڲ�����һ��int, 0ΪOK����0Ϊ������Ϣ
			 *
			 * @return  const char* 
			**/
			virtual const char * seeError(const ErrCode &) const;
			virtual ~ConfigUnit();

			/**
			 * @brief ��һ���ֶ��л�ȡ�ض����͵�����
			 * 			XXX to_XXX() ��ʾ��XXX���ͻ�ȡ��������
			 *
			 * @param [out] errCode   : ErrCode* ������Ϣ
			 * 				errCode��ΪNULLʱ������Ž���д��*errCode
			 * 				���˴�errCodeΪĬ��ֵNULLʱ�����������쳣����ʽ�׳�
			 * 				�׳����쳣Ϊ��ConfigException��������
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
			//to_raw_string : δ����ת�崦����ַ���
			virtual std::string to_raw_string(ErrCode * errCode = NULL)const;
			//��ȡC�����ַ�����������
			virtual const char * to_cstr(ErrCode * errCode = NULL)const;

			/**
			 * @brief ����Ĭ��ֵ��to_XXXϵ�к���
			 *        ����ֵ��to_xxxϵ����ȫ��ͬ��
			 *        Ψһ�Ĳ�ͬ�ǣ���errCode��Ϊ0������������, ����defĬ��ֵ
			 *
			 * @param [out] errCode   : ErrCode* ������Ϣ
			 * @param [in] def   : const &  Ĭ��ֵ
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



			/**
			 * @brief ��to_XXX������ͬ�ĺ���������get_XXXϵ��ΪC���
			 * 			����Ϊ���ڷ�ֵ��buffer������ֵ�Ǵ����
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
			//��ȡC�����ַ��������ַ�������valueBuf��len��valueBuf���ȣ��Զ���0��������len-1���ַ�
			virtual ErrCode get_cstr(char * valueBuf, size_t len) const;


			/**
			 * @brief ����Ĭ��ֵ��ge_XXXϵ�к���
			 *        ����ֵ��get_xxxϵ����ȫ��ͬ��
			 *        Ψһ�Ĳ�ͬ�ǣ�������ֵ��Ϊ0������������valueBuf��ʹ��defĬ��ֵ
			 *
			 * @param [out] valueBuf   : char*  ������ֵ
			 * @param [in] def   : const char&  Ĭ��ֵ
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
			 * @brief ��ȡ�Լ�������
			 *
			 * @return  int 
			 * @retval   
			**/
			virtual int selfType()const{
				return CONFIG_UNIT_TYPE;
			}
			
			/**
			 * @brief ��ȡԪ�ظ���
			 *
			 * @return  size_t ����
			**/
			virtual size_t size()const{
				return 1;
			}


			/**
			 * @brief ���ʲ����ڵ�key�󣬸��������ڵ�key�ľ���·�������� group.sub.nokey
			 *
			 * @return  const char*  �����ڵ�key��·��
			 * @author zhang_rui
			**/
			const char * getErrKeyPath() const;

			/**
			 * @brief ��ȡ��unit��ConfigUnitֱ�ӷ���error unit
			 *
			 * @return  ConfigUnit &
			**/
			virtual const ConfigUnit & get_sub_unit(int index) const;
			/**
			 * @brief �Ƚ��Ƿ����
			 *
			 * @return  int 0��ʾ��� -1�����
			**/
			virtual int equals(const ConfigUnit & conf) const;

			//���º����Ĳ����У�exceptΪ0���ô���ű�ʾ����
			//exceptΪ1�����쳣��ʾ����
			/**
			 * @brief ����һ��unit, ���ӵ���unit���������
			 *
			 * @param [in] key   : ����unit��key
			 * @param [in] value : ����unit��value
			 * @param [in] objtype : unit���͡�
			 *    CONFIG_UNIT_TYPE��ʾunit;
			 *    CONFIG_GROUP_TYPE��ʾgroup;
			 *    CONFIG_ARRAY_TYPE��ʾarray;
			 * @return  int 0 �ɹ��������Ǵ����
			**/
			virtual int add_unit(const std::string & key, const std::string& value, 
				const int objtype=CONFIG_UNIT_TYPE, int except=0, ConfigUnit ** ref=NULL);

			/**
			 * @brief ����һ��unit, ���
			 *
			 *  ��unit������׷�ӵ����������档
			 * ������Ҫƥ�䣬ֻ�ܴ�group���Ƶ�group��array���Ƶ�array
			 * groupҪ���key�Ƿ��ظ������ظ���׷��
			 * arrayֱ��׷��
			 * @return  int 0 �ɹ��������Ǵ����
			**/
			virtual int append_unit(const ConfigUnit & unit, int except=0);

			/**
			 * @brief ����һ��unit, ���
			 *
			 *  ��unit�����ݸ��Ƶ�������
			 * ������Ҫƥ�䣬ֻ�ܴ�group���Ƶ�group��array���Ƶ�array
			 * @return  int 0 �ɹ��������Ǵ����
			**/
			virtual int copy_unit(const ConfigUnit & unit, int except=0);
			
			/**
			 * @brief �޸�unit��value��ֵ
			 *
			 * @return  int 0 �ɹ��������Ǵ����
			**/
			virtual int set_value(const std::string & value, int except=0);

			//-----------------���������µĶ����û�����Ҫ����-----------------

			//���캯����
			ConfigUnit();
			ConfigUnit(const std::string& __key, const std::string& __value, const Reader * __cur_reader = NULL, ConfigGroup * father = NULL);

			//���Դ�ӡʱ�ã�����
			void pindent(int ind)const{
				while(ind--){
					printf("    ");
				}
			}
			//��ӡ
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
			std::string _cstr; //ר�ŵ�һ�����������string��ֻ�е�value��"Ϊ��ͷʱ��������
			int _cstr_err;
			const char * _at_file;
			int _at_line;
			ConfigGroup * _father;
			ConfigUnit * create_unit(const std::string & key, const std::string& value, 
				int objtype, ConfigGroup * father);

			/**
			 * @brief �������
			 *
			 * @return  void
			**/
			virtual void clear();
			
		public:
			/**
			 * @brief ����һ��unit, ���
			 *
			 *  ��unit�����ݸ��Ƶ����������档
			 * ������Ҫƥ�䣬ֻ�ܴ�group���Ƶ�group��array���Ƶ�array
			 * groupҪ���key�Ƿ��ظ������ظ���׷��
			 * arrayֱ��׷��
			 * @return  int 0 �ɹ��������Ǵ����
			**/
			virtual int _append_unit(const ConfigUnit & unit,int check=1, int except=0);
		private:
			int init_unit(const std::string& __key, const std::string& __value);
	};

}


#endif  //__CONFIGUNIT_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
