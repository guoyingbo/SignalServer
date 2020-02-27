/*
 *  Copyright 2011 The WebRTC Project Authors. All rights reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include "utils.h"

#include <stdio.h>

std::string int2str(int i) {
	char str[128];
	sprintf_s(str, "%d", i);
	return str;
}

std::string size_t2str(size_t i) {
	char str[128];
	sprintf_s(str, "%d", (int)i);
	return str;
}


#define STACK_ARRAY(TYPE, LEN) static_cast<TYPE*>(::alloca((LEN)*sizeof(TYPE)))

bool hex_decode(char ch, unsigned char* val) {
	if ((ch >= '0') && (ch <= '9')) {
		*val = ch - '0';
	}
	else if ((ch >= 'A') && (ch <= 'Z')) {
		*val = (ch - 'A') + 10;
	}
	else if ((ch >= 'a') && (ch <= 'z')) {
		*val = (ch - 'a') + 10;
	}
	else {
		return false;
	}
	return true;
}

size_t url_decode(char * buffer, size_t buflen,
	const char * source, size_t srclen) {
	if (NULL == buffer)
		return srclen + 1;
	if (buflen <= 0)
		return 0;

	unsigned char h1, h2;
	size_t srcpos = 0, bufpos = 0;
	while ((srcpos < srclen) && (bufpos + 1 < buflen)) {
		unsigned char ch = source[srcpos++];
		if (ch == '+') {
			buffer[bufpos++] = ' ';
		}
		else if ((ch == '%')
			&& (srcpos + 1 < srclen)
			&& hex_decode(source[srcpos], &h1)
			&& hex_decode(source[srcpos + 1], &h2))
		{
			buffer[bufpos++] = (h1 << 4) | h2;
			srcpos += 2;
		}
		else {
			buffer[bufpos++] = ch;
		}
	}
	buffer[bufpos] = '\0';
	return bufpos;
}

std::string s_url_decode(const std::string& source) {
	// Ask transformation function to approximate the destination size (returns upper bound)
	size_t maxlen = url_decode(NULL, 0, source.data(), source.length());
	char * buffer = STACK_ARRAY(char, maxlen);
	size_t len = url_decode(buffer, maxlen, source.data(), source.length());
	std::string result(buffer, len);
	return result;
}