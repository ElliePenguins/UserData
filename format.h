/*
 * This module contains usefull helper and
 * Wapper functions for things like opening
 * files and dynamic memory allocation.
 *
 * MIT License
 * Copyright (c) 2017 ElliePenguins 
 */

#ifndef LX_FORMAT_H_
#define LX_FORMAT_H_

// Handles the allocation of memory and any failures,
// dont forget to cast the void ptr it returns.
void * mallocWrap( int numberOfbytes);

// Same idea as above but for strings.
char * mallocString(const char * string);

// Handles opening files and any failures that may occure.
FILE * openFile( char * filename, char * options);

#endif
