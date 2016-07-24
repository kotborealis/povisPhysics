/*
 * Logger.cpp
 *
 *  Created on: 24 èþë. 2016 ã.
 *      Author: kotborealis
 */

#include "Logger.h"

namespace PovisEngine {

void Logger::log(const char* file, int line, const char* type, std::string text){
	std::cout<<"{"<<file<<" at "<<line<<"}"<<"["<<type<<"] "<<text<<std::endl;
}
} /* namespace PovisEngine */
