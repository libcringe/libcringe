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

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "cringe.h"
#include <string.h>

cr_header* cr_getheader(crstring c) {
	return (void*)(c - sizeof(cr_header));
}

int cr_iscr(char* c) {
	if (cr_getheader(c)->iscr == 0) {
		return 1;
	}
	return 0;
}

size_t cr_length(crstring c) {
	if (!cr_iscr(c)) {
		return 0;
	}
	return cr_getheader(c)->length;
}

enum cr_status cr_getstatus(crstring c) {
	return cr_getheader(c)->status;
}

crstring cr_newbl(char* buff, size_t length) {
	cr_header* head;
	if (buff) {
		head = malloc(sizeof *head + length + 1);
	} else {
		head = calloc(sizeof *head + length + 1, 1);
	}

	if (head == NULL) {
		static cr_header errhead;
		errhead.status = cr_status_alloc_fail;
		return errhead.buffer;
	}

	head->length = length;
	head->status = cr_status_good;
	head->iscr = 0;
	if (length && buff) {
		memcpy(head->buffer, buff, length);
	}
	head->buffer[length] = '\0';
	return head->buffer;
}

crstring cr_newb(char* buff) {
	size_t bufflength = buff ? strlen(buff) : 0;
	return cr_newbl(buff, bufflength);
}

crstring cr_new(void) {
	return cr_newbl("", 0);
}

crstring cr_dup(crstring c) {
	return cr_newb(c);
}

int cr_isgood(crstring c) {
	if (!cr_iscr(c)) {
		return 2;
	}
	if (cr_getstatus(c) != cr_status_good) {
		return 0;
	}
	return 1;
}

void cr_free(crstring c) {
	if (!cr_isgood(c)) {
		return;
	}
	free(cr_getheader(c));
	cr_getheader(c)->status = cr_status_free;
}

void cr_update(crstring c) {
	if (!cr_isgood(c)) {
		return;
	}
	size_t reallength = strlen(c);
	cr_getheader(c)->length = reallength;
}

crstring cr_resize(crstring c, size_t val) {
	if (!cr_isgood(c)) {
		return c;
	}
	return cr_newbl(c, val);
}

crstring cr_catl(crstring dest, char* cat, size_t length) {
	if (!cr_isgood(dest)) {
		return dest;
	}
	size_t curlen = cr_length(dest);
	dest = cr_resize(dest, cr_length(dest) + length);
	if (!cr_isgood(dest)) {
		return dest;
	}
	memcpy(dest+curlen, cat, length);
	cr_getheader(dest)->length = curlen + length;
	dest[curlen + length] = '\0';
	return dest;
}

crstring cr_cat(crstring dest, char* cat) {
	return cr_catl(dest, cat, strlen(cat));
}
