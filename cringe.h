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

#ifndef _H_CRINGE
#define _H_CRINGE
#include <stddef.h>
/* Define Cringe types */
typedef char* crstring;
typedef crstring cr;

/* Statuses a Cringe string can report */
enum cr_status {
	cr_status_good, // Everything is OK
	cr_status_alloc_fail, // Failed allocation
	cr_status_free // String buffer is free
};

/* Cringe string header */
typedef struct cr_header {
	size_t length; // Length of the string
	enum cr_status status; // Status of the string (see "enum cr_status" above)
	int iscr; // Always 0; used to test if string is crstring
	char buffer[]; // Buffer - flexible char array
} cr_header;


cr_header* cr_getheader(crstring c);
/* cr_getheader -- Get header of Cringe string
 * 
 * Usage: cr_getheader(crstring)
 *
 * Returns: pointer to header of given crstring
 */

int cr_iscr(char* c);
/* 
 * cr_iscr -- Check if string is Cringe string
 *
 * Usage: cr_iscr(char*)
 *
 * Returns: 1 -- string is crstring
 *          0 -- string is char*
 */

size_t cr_length(crstring c);
/*
 * cr_length -- Get length of Cringe string
 *
 * Usage: cr_length(crstring)
 *
 * Returns: length of Cringe string
 */

enum cr_status cr_getstatus(crstring c);
/*
 * cr_status -- Get status of Cringe string
 *
 * Usage: cr_getstatus(crstring)
 *
 * Returns: enum cr_status holding the value of Cringe string status
 */

crstring cr_newbl(char* buff, size_t length);
/*
 * cr_newbl -- Create a new Cringe string with the specified buffer and length
 *
 * Usage: cr_newbl(char*, size_t)
 *
 * Returns: new Cringe string
 */

crstring cr_newb(char* buff);
/*
 * cr_newb -- Create a new Cringe string with the specified buffer
 *
 * Usage: cr_newb(char*)
 *
 * Returns: new Cringe string
 */

crstring cr_new(void);
/*
 * cr_new -- Create a new empty Cringe string
 *
 * Usage: cr_new()
 *
 * Returns: new Cringe string
 */

crstring cr_dup(crstring c);
/*
 * cr_dup -- Duplicate a Cringe string
 *
 * Usage: cr_dup(crstring)
 *
 * Returns: new Cringe string with buffer copied from the provided string
 */

int cr_isgood(crstring c);
/*
 * cr_isgood -- Check if Cringe string status is "good"
 *
 * Usage: cr_isgood(crstring)
 *
 * Returns: 2 -- string is not a Cringe string
 *          1 -- string's status is "good"
 *          0 -- string's status is not "good"
 */

void cr_free(crstring c);
/*
 * cr_free -- Free Cringe string
 *
 * Usage: cr_free(crstring)
 *
 * Returns: nothing
 */

void cr_update(crstring c);
/*
 * cr_update -- Update Cringe string length based on the null character
 *
 * Usage: cr_update(crstring)
 *
 * Returns: nothing
 */

crstring cr_resize(crstring c, size_t val);
/*
 * cr_resize -- Resize Cringe string
 *
 * Notes: string is cut if provided size is lower than the string size
 *
 * Usage: cr_resize(crstring, size_t)
 *
 * Returns: resized Cringe string
 */

crstring cr_catl(crstring dest, char* cat, size_t length);
/*
 * cr_catl -- Concatenate string of specified length to a Cringe string
 *
 * Notes: second parameter can also be a crstring
 *
 * Usage: cr_catl(crstring, char*, size_t)
 *
 * Returns: concatenated Cringe string
 */

crstring cr_cat(crstring dest, char* cat);
/*
 * cr_cat -- Concatenate string to a Cringe string
 *
 * Notes: second parameter can also be a crstring
 *
 * Usage: cr_cat(crstring, char*)
 *
 * Returns: concatenated Cringe string
 */
#endif //_H_CRINGE
