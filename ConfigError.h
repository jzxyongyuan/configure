
#ifndef  __CONFIGERROR_H_
#define  __CONFIGERROR_H_

#include "utils/cc_utils.h"
#include "ConfigUnit.h"
namespace cfgiml{

	class ConfigError : public ConfigUnit{
		public:

			virtual ~ConfigError(){};

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


			virtual int selfType() const{
				return CONFIG_ERROR_TYPE;
			}
			virtual size_t size()const{
				return 0;
			}
 
			virtual std::string info() const{
				return std::string("[Error: No such key.]");
			}
			/**
			 * @brief �Ƚ��Ƿ����
			 *
			 * @return  int 0��ʾ��� -1�����
			 * @author zhang_rui
			**/
			virtual int equals(const ConfigUnit & conf) const;
			/**
			 * @brief ɾ��һ��unit
			 *
			 * @return  int 0 �ɹ��������Ǵ����
			 * @author zhang_rui
			**/
			virtual int set_value(const std::string & value, int except=0);
			/**
			 * @brief ����һ��unit, ���
			 *
			 *  ��unit�����ݸ��Ƶ�������
			 * ������Ҫƥ�䣬ֻ�ܴ�group���Ƶ�group��array���Ƶ�array
			 * @return  int 0 �ɹ��������Ǵ����
			 * @author zhang_rui
			**/
			virtual int copy_unit(const ConfigUnit & unit, int except=0);
			virtual  ConfigUnit & operator= (ConfigUnit & unit){
				return ConfigUnit::operator=(unit);
			}
	};

}




#endif  //__CONFIGERROR_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */