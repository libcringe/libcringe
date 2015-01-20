/*
 * This file is part of LibCringe.
 * LibCringe is double-licensed under GPLv2 and GPLv3 licenses.
 *
 * Copyright (C) 2015 Dominik "Zatherz" Banaszak
 *
 * LibCringe is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or version 3 of the License.
 *
 * LibCringe is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License v2 and/or v3 for more details.
 *
 * You should have received a copy of the GNU General Public License v2 and v3
 * along with LibCringe; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef _H_CRSTRING_STRING_HIJACK
#define _H_CRSTRING_STRING_HIJACK
#include <string.h>
#include <cringe.h>
extern char* _cringe_strcpy(char *__restrict __dest, const char *__restrict __src) __THROW __nonnull ((1, 2));

extern char* _cringe_strcpy(char *__restrict __dest, const char *__restrict __src) {
	if (cr_iscr(__dest) == 0) {
		__dest = cr_newb((char*)__src);
		return __dest;
	}
	return strcpy(__dest, __src);
}

#define strcpy _cringe_strcpy
#endif //_H_CSTRING_STRING_HIJACK
