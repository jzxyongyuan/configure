
#ifndef  __CC_TRANS_H_
#define  __CC_TRANS_H_

#include "cc_struct.h"

namespace cfgiml{
	class Trans{
		public:
			/**
			 * @brief 判断一个字符串是否是整数格式
			 *
			 * @param [in] str   : const std::string&
			 * @return  bool 
			 * @retval   
			 * @see 
			**/
			static bool isInteger(const std::string & str);
			/**
			 * @brief 判断一个字符串是否是浮点数格式（不检查精度范围）
			 *
			 * @param [in] str   : const std::string&
			 * @return  bool 
			 * @retval   
			 * @see 
			**/
			static bool isFloat(const std::string & str);
			/**
			 * @brief 把一个字符串转换成一个int64
			 *
			 * @param [in] __str   : const std::string& bsl::string类型的字符串
			 * @param [out] buf   : int64*  转换结果
			 * @return  int 0成功，失败：OUTOFRANGE, NULLVALUE, FORMATERROR
			 * @retval   
			 * @see 
			**/
			static int str2int64(const std::string & __str, long long * buf);
			/**
			 * @brief 把一个字符串转换成一个uint64
			 *
			 * @param [in] __str   : const std::string& bsl::string类型的字符串
			 * @param [out] buf   : uint64* 转换结果
			 * @return  int 0成功，失败：OUTOFRANGE, NULLVALUE, FORMATERROR
			 * @retval   
			 * @see 
			**/
			static int str2uint64(const std::string & __str, unsigned long long * buf);
			/**
			 * @brief 把一个带有转义字符的字符串进行解析（把\xFF, \022, \n之类的文本转换成实际的字符）
			 *         这个串必须是双引号开头、双引号结尾。
			 *
			 *         【configure内部使用，如不熟悉内部行为，不推荐使用】
			 *
			 * @param [in] __str   : const std::string& bsl::string类型的字符串
			 * @param [out] buf   : uint64* 转换结果
			 * @return  int 0成功，失败：FORMATERROR
			 * @retval   
			 * @see 
			**/
			static int str2str(const std::string & str, std::string * buf);
			/**
			 * @brief 把一个字符串转换成一个double
			 *
			 * @param [in] __str   : const std::string& bsl::string类型的字符串
			 * @param [out] buf   : double* 转换结果
			 * @return  int 0成功，失败：OUTOFRANGE, NULLVALUE, FORMATERROR
			 * @retval   
			 * @see 
			**/
			static int str2double(const std::string & str, double * buf);

			//仅限configure使用
			static std::string cutComment(const std::string & str);
	};
}




#endif  //__CC_TRANS_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
