/*
 * Utils.h
 *
 *  Created on: 12.09.2012
 *      Author: lo
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include <cerrno>
#include <cstdlib>
#include <vector>
#include <cstdio>

typedef std::vector<std::string> strings;

/// FieldsFunc splits the string s at each occurrence of one or more character for which f(c) returns true.
strings FieldsFunc( std::string & s, int (*f)(int) );

/// Fields splits the string s at each occurrence of one or more white space.
strings Fields( std::string & s );

/// ParseDouble converts the string s to an double.
///
/// If it's not possible to convert the string and ok is not 0 ParseDouble will set *ok to false.
double ParseDouble( std::string s, bool * ok );

/// ParseDouble converts the string s to an double.
///
/// If it's not possible to convert the string and ok is not 0 ParseDouble will set *ok to false.
double ParseDouble( const char * s, bool * ok );

/// ParseLong converts the string s to an integer.
/// 
/// If it's not possible to convert the string and ok is not 0 ParseLong will set *ok to false.
long ParseLong( std::string s, bool * ok );

/// ParseLong converts the string s to an integer.
/// 
/// If it's not possible to convert the string and ok is not 0 ParseLong will set *ok to false.
long ParseLong( const char * s, bool * ok );


#endif /* UTILS_H_ */
