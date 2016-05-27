
#ifndef  __CC_STRUCT_H_
#define  __CC_STRUCT_H_

#include <stdlib.h>

#include <string>
#include <list>
#include <map>

namespace cfgiml{


	
	typedef unsigned char cfgiml_type_uchar;		  /**< uchar       */
	typedef signed short cfgiml_type_int16;		  /**< int16       */
	typedef unsigned short cfgiml_type_uint16;		  /**< uint16       */
	typedef signed int cfgiml_type_int32;		  /**< int32       */
	typedef unsigned int cfgiml_type_uint32;		  /**< uint32       */
	typedef signed long long cfgiml_type_int64;		  /**< int64       */
	typedef unsigned long long cfgiml_type_uint64;		  /**< uing64       */

#define CC_CHAR "char"		  /**< char，出现在约束文件中的类型，下同       */
#define CC_UCHAR "uchar"		  /**< uchar       */
#define CC_INT16 "int16_t"		  /**< int16       */
#define CC_UINT16 "uint16_t"		  /**< uint16       */
#define CC_INT32 "int32_t"		  /**< int32       */
#define CC_UINT32 "uint32_t"		  /**< uint32       */
#define CC_INT64 "int64_t"		  /**< int64       */
#define CC_UINT64 "uint64_t"		  /**< uing64       */
#define CC_FLOAT "float"		  /**< float       */
#define CC_DOUBLE "double"		  /**< double       */
#define CC_STRING "string"		  /**< std::string  */
	typedef int ErrCode;		  /**< 错误号       */

}



#endif  //__CC_STRUCT_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
