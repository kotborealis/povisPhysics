/*
 * Logger.h
 *
 *  Created on: 24 èþë. 2016 ã.
 *      Author: kotborealis
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <iostream>

#define info(str) log(__FILE__,__LINE__,"info",str);
#define warn(str) log(__FILE__,__LINE__,"warn",str);
#define error(str) log(__FILE__,__LINE__,"error",str);

namespace PovisEngine {

class Logger {
public:
	static void log(const char* file, int line, const char* type, std::string text){
		std::cout<<"{"<<file<<" at "<<line<<"}"<<"["<<type<<"] "<<text<<std::endl;
	}
};

} /* namespace PovisEngine */

#endif /* LOGGER_H_ */
