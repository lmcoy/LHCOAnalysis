/*
 * Utils.cpp
 *
 *  Created on: 12.09.2012
 *      Author: lo
 */

#include "Utils.h"

strings FieldsFunc(std::string & s, int (*f)(int)) {
	size_t n = 0;
	bool inField = false;

	for (size_t i = 0; i < s.size(); i++) {
		bool wasInField = inField;
		inField = !f(s[i]);
		if (inField && !wasInField) {
			n += 1;
		}
	}

	std::vector<std::string> a(n);
	size_t na = 0;
	int fieldStart = -1;
	for (size_t i = 0; i < s.size(); i++) {
		if (f(s[i])) {
			if (fieldStart >= 0) {
				a[na] = s.substr(fieldStart, i - (size_t) fieldStart);
				na += 1;
				fieldStart = -1;
			}
		} else {
			if (fieldStart == -1) {
				fieldStart = i;
			}
		}
	}
	if (fieldStart >= 0) {
		a[na] = s.substr(fieldStart);
	}
	return a;
}

strings Fields(std::string & s) {
	return FieldsFunc(s, isspace);
}

double ParseDouble(std::string& s, bool * ok) {
	if (ok) {
		*ok = true;
	}
	char *endptr = 0;
	const char *cstring = s.c_str();
	errno = 0;
	double d = strtod(cstring, &endptr);
	if (errno == ERANGE) {
		fprintf(stderr, "range error\n");
		if (ok) {
			*ok = false;
		}
	}
	if (endptr == cstring) {
		fprintf(stderr, "no digits were found\n");
		if (ok) {
			*ok = false;
		}
	}

	if (*endptr != '\0') {
		fprintf(stderr, "unable to parse characters: \"%s\"\n", endptr);
		if (ok) {
			*ok = false;
		}
	}
	return d;
}

long ParseLong(std::string& s, bool * ok) {
	if (ok) {
		*ok = true;
	}
	char *endptr = 0;
	const char *cstring = s.c_str();
	errno = 0;
	long l = strtol(cstring, &endptr, 10);
	if (errno == ERANGE) {
		fprintf(stderr, "range error\n");
		if (ok) {
			*ok = false;
		}
	}
	if (endptr == cstring) {
		fprintf(stderr, "no digits were found\n");
		if (ok) {
			*ok = false;
		}
	}

	if (*endptr != '\0') {
		fprintf(stderr, "unable to parse characters: \"%s\"\n", endptr);
		if (ok) {
			*ok = false;
		}
	}
	return l;
}
