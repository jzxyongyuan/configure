
#ifndef  __CC_TRANS_H_
#define  __CC_TRANS_H_

#include "cc_struct.h"

namespace cfgiml{
	class Trans{
		public:
			/**
			 * @brief �ж�һ���ַ����Ƿ���������ʽ
			 *
			 * @param [in] str   : const std::string&
			 * @return  bool 
			 * @retval   
			 * @see 
			**/
			static bool isInteger(const std::string & str);
			/**
			 * @brief �ж�һ���ַ����Ƿ��Ǹ�������ʽ������龫�ȷ�Χ��
			 *
			 * @param [in] str   : const std::string&
			 * @return  bool 
			 * @retval   
			 * @see 
			**/
			static bool isFloat(const std::string & str);
			/**
			 * @brief ��һ���ַ���ת����һ��int64
			 *
			 * @param [in] __str   : const std::string& bsl::string���͵��ַ���
			 * @param [out] buf   : int64*  ת�����
			 * @return  int 0�ɹ���ʧ�ܣ�OUTOFRANGE, NULLVALUE, FORMATERROR
			 * @retval   
			 * @see 
			**/
			static int str2int64(const std::string & __str, long long * buf);
			/**
			 * @brief ��һ���ַ���ת����һ��uint64
			 *
			 * @param [in] __str   : const std::string& bsl::string���͵��ַ���
			 * @param [out] buf   : uint64* ת�����
			 * @return  int 0�ɹ���ʧ�ܣ�OUTOFRANGE, NULLVALUE, FORMATERROR
			 * @retval   
			 * @see 
			**/
			static int str2uint64(const std::string & __str, unsigned long long * buf);
			/**
			 * @brief ��һ������ת���ַ����ַ������н�������\xFF, \022, \n֮����ı�ת����ʵ�ʵ��ַ���
			 *         �����������˫���ſ�ͷ��˫���Ž�β��
			 *
			 *         ��configure�ڲ�ʹ�ã��粻��Ϥ�ڲ���Ϊ�����Ƽ�ʹ�á�
			 *
			 * @param [in] __str   : const std::string& bsl::string���͵��ַ���
			 * @param [out] buf   : uint64* ת�����
			 * @return  int 0�ɹ���ʧ�ܣ�FORMATERROR
			 * @retval   
			 * @see 
			**/
			static int str2str(const std::string & str, std::string * buf);
			/**
			 * @brief ��һ���ַ���ת����һ��double
			 *
			 * @param [in] __str   : const std::string& bsl::string���͵��ַ���
			 * @param [out] buf   : double* ת�����
			 * @return  int 0�ɹ���ʧ�ܣ�OUTOFRANGE, NULLVALUE, FORMATERROR
			 * @retval   
			 * @see 
			**/
			static int str2double(const std::string & str, double * buf);

			//����configureʹ��
			static std::string cutComment(const std::string & str);
	};
}




#endif  //__CC_TRANS_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
