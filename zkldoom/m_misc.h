//
// Copyright(C) 1993-1996 Id Software, Inc.
// Copyright(C) 2005-2014 Simon Howard
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// DESCRIPTION:
//      Miscellaneous.
//    


#ifndef __M_MISC__
#define __M_MISC__

#include "doomtype.h"

unsigned int abss(int v);
boolean M_WriteFile(char *name, void *source, int length);
int M_ReadFile(char *name, byte **buffer);
void M_MakeDirectory(char *dir);
char *M_TempFile(char *s);
boolean M_FileExists(char *file);
boolean M_StrToInt(const char *str, int *result);
void M_ExtractFileBase(char *path, char *dest);
void M_ForceUppercase(char *text);
char *M_StrCaseStr(char *haystack, char *needle);
char *M_StringDuplicate(const char *orig);
char *M_StringReplace(const char *haystack, const char *needle,
                      const char *replacement);
boolean M_StringStartsWith(const char *s, const char *prefix);
boolean M_StringEndsWith(const char *s, const char *suffix);
char *M_OEMToUTF8(const char *ansi);

#endif

