#ifndef  __CC_EXCEPTION_H_
#define  __CC_EXCEPTION_H_

#include "cc_struct.h"
//#include "bsl/exception/bsl_exception.h"
#include <exception>
#include "glog/logging.h"


namespace cfgiml{
	enum {
		OK = 0,
		ERROR,// other error
		CONSTRAINT_ERROR,
		CONFIG_ERROR,
		UNKNOWN,
		NOSUCHKEY,
		FORMATERROR,
		OUTOFRANGE,//������Χ
		NULLVALUE, //��ֵ��get_stringʱ���᷵�ش˴���
		NULLBUFFER, //�����bufΪ��
		GROUPTOUNIT, //����group��to_xxx��get_xxx����
		DUPLICATED_KEY, /**<  �޸�configureʱ������ظ�key      */
		DUPLICATED_GROUP,
	};
	/*
	 * @brief configure�׳��������쳣����ConfigException������
	 */
	//class ConfigException : public bsl::BasicException<ConfigException, bsl::Exception>{
	class ConfigException : public std::exception{
		public:
			ConfigException(){};
			ConfigException(const char * s){
				msg = s;
			}
			ConfigException(const std::string& s){
				msg = s;
			}
			virtual ~ConfigException() throw(){};
			const char *seeError() throw() {

				return msg.c_str();
			}
			void pushMsg(const std::string & s) throw(){
				msg.append(std::string(" | ")).append(s);
			}
		protected:
			std::string msg;
	};
    /*
	class NoSuchKeyException : public bsl::BasicException<NoSuchKeyException, ConfigException>{};
    */
	class NoSuchKeyException : public ConfigException{};
	class FormatErrorException : public ConfigException{};
	class UnknownException : public ConfigException{};
	class OutOfRangeException : public ConfigException{};
	class NullValueException : public ConfigException{};
	class NullBufferException : public ConfigException{};
	class GroupToUnitException : public ConfigException{};
	class ConfigThrower {
		public:
			static void throwException(const ErrCode & err){
				switch(err){
					case OK:
						break;
					case NOSUCHKEY:
                        
						throw NoSuchKeyException();
						break;
					case OUTOFRANGE:
                        throw OutOfRangeException();
						break;
					case FORMATERROR:
                        throw FormatErrorException();
						break;
					case NULLVALUE:
						throw NullValueException();
                        break;
					case NULLBUFFER:
						throw NullBufferException();
                        break;
					case GROUPTOUNIT:
						throw GroupToUnitException();
                        break;
					case UNKNOWN:
					default:
						//throw UnknownException().push("ConfigException.Unknown");
                        throw UnknownException();
				}
			}
	};

}







#endif  //__CC_EXCEPTION_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
