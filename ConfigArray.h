
#ifndef  __CONFIGARRAY_H_
#define  __CONFIGARRAY_H_

#include "ConfigGroup.h"
#include "glog/logging.h"

namespace cfgiml{
	class ConfigArray : public ConfigGroup{
		public:
			virtual int push(std::string key, ConfigUnit* unit){
                DLOG(INFO) <<"["<<long(getFather())<<"]ConfigArray["<<long(this)<<"] ["<<key<<"].push" ;
				vec.push_back(unit);
				return 0;
			}

			ConfigArray(const char * __name, ConfigGroup * __father=NULL){
				if(*__name == '@'){
					++__name;
				}
				create(__name, __father);
			}
			virtual int selfType() const{
				return CONFIG_ARRAY_TYPE;
			}

			void print(int indent = 0) const{
				pindent(indent);
				printf("Array--------[%s] : {\n", getName());
				for(int i = 0; i < (int)vec.size(); ++i){
					vec[i]->print(indent+1);
				}
				pindent(indent);
				printf("}\n");
			}

			const ConfigUnit & operator[] (int idx) const{
				if(idx < (int)vec.size()){
					return *vec[idx];
				}
                LOG(INFO) << "Configure: visit element not exist ConfigArray[int] : "<<_name<<"["<<idx<<"]";
				std::string tmp=this->_name;
				char tmpid[64];
				snprintf(tmpid,64, "%d",idx);
				tmp.append("[").append(tmpid).append("]");
				setErrorKeyPath(tmp);
				return *get_err_unit();
			}
			const ConfigUnit & operator[] (const char *str) const {
                LOG(INFO) << "Configure: visit ConfigArray[char *] : "<<_name<<"["<<str<<"]\n";
				std::string tmp=this->_name;
				tmp.append(".").append(str);
				setErrorKeyPath(tmp);
				return *get_err_unit();
			}
			const ConfigUnit & operator[] (const std::string &str) const{
                LOG(INFO) << "Configure: visit ConfigArray[std::string] : "<<_name<<"["<<str<<"]\n";
				std::string tmp=this->_name;
				tmp.append(".").append(str);
				setErrorKeyPath(tmp);
				return *get_err_unit();
			}
			ConfigUnit & operator[] (int idx) {
				if(idx < (int)vec.size()){
					return *vec[idx];
				}
                LOG(INFO) << "Configure: visit element not exist ConfigArray[int] : "<<_name<<"["<<idx<<"]";
				std::string tmp=this->_name;
				char tmpid[64];
				snprintf(tmpid,64, "%d",idx);
				tmp.append("[").append(tmpid).append("]");
				setErrorKeyPath(tmp);
				return *get_err_unit();
			}
			ConfigUnit & operator[] (const char *str)  {
                LOG(INFO) << "Configure: visit ConfigArray[char *] : "<<_name<<"["<<str<<"]\n";
				std::string tmp=this->_name;
				tmp.append(".").append(str);
				setErrorKeyPath(tmp);
				return *get_err_unit();
			}
			ConfigUnit & operator[] (const std::string &str) {
                LOG(INFO) << "Configure: visit ConfigArray[std::string] : "<<_name<<"["<<str<<"]\n";
				std::string tmp=this->_name;
				tmp.append(".").append(str);
				setErrorKeyPath(tmp);
				return *get_err_unit();
			}
			virtual  ConfigUnit & operator= (ConfigUnit & unit) {
				return ConfigUnit::operator=(unit);
			}
			virtual ~ConfigArray(){
				for(int i = 0; i < (int)vec.size(); ++i){
					delete vec[i];
				}
			}

			virtual size_t size()const{
				return vec.size();
			}

			const ConfigUnit & get_sub_unit(int index) const {
				if ((0<=index) && (index < (int)vec.size())){
					return *vec[index];
				}
				return *get_err_unit();
			}
			/**
			 * @brief 比较是否相等
			 *
			 * @return  int 0表示相等 -1不相等
			 * @author zhang_rui
			**/
			virtual int equals(const ConfigUnit & conf) const {
				try {
					for(int i = 0; i < (int)vec.size(); ++i){
						if (0 != vec[i]->equals(conf[i])) {
							return -1;
						}
					}
					return 0;
				} catch (std::exception) {
					return -1;
				}
				return -1;
			}
			/**
			 * @brief 增加一个unit
			 *
			 * @return  int 0 成功，其他是错误号
			**/
			virtual int add_unit(const std::string & key, const std::string& value,
				const int objtype, int except, ConfigUnit ** ref){
				ConfigUnit * tmp=NULL;
				if (0 < vec.size() && objtype != vec[0]->selfType()) {
					goto adderr;
				}
				tmp = create_unit(key, value, objtype, this->getFather());
				if (NULL == tmp){
					goto adderr;
				} 
				this->push(key,tmp);
				if (NULL != ref) {
					*ref = tmp;
				}
				return 0;
				adderr:
				if (except) {
					popError(NULL, CONFIG_ERROR);
				}
				return CONFIG_ERROR;
			}
		protected:
			std::vector <ConfigUnit *> vec;

			/**
			 * @brief 清除内容
			 *
			 * @return  void
			 * @author zhang_rui
			**/
			virtual void clear() {
				for(int i = 0; i < (int)vec.size(); ++i){
					delete vec[i];
				}
				vec.clear();
			}
	};
}








#endif  //__CONFIGARRAY_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
