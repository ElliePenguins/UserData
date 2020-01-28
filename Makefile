#
# Script to build either the debug version of the library with
# a menu that can be used to test various features of the library
# for debug purposes. this is the default.
#
# The other option is library, which creates a shared object 
# file that provides the functionatlity to other programs  
# for handling user data. This is the purposes of this library
# and will be the new default once we get further with this lib.
#
# TODO: We need an install option to add the library and
# 	header files to the include directory.
#
# MIT License
# Copyright (c) 2019 ElliePenguins 
#
#

CCOPTS = -g -O0
CC = gcc
#/.DEFAULT_GOAL =: debug 


debug:	
	gcc ${CCOPTS} format.c userProfile.c userInteraction.c userQuery.c 			userMain.c -o userdata 

library:	
	gcc -c -fPIC format.c userProfile.c userInteraction.c userQuery.c 
	gcc -shared format.o userProfile.o userInteraction.o userQuery.o 			-o userdata.so
	make clean

install:
	mkdir -p /usr/lib/UserData
	cp userdata.so /usr/lib/UserData/
	mkdir -p /usr/include
	cp UserData.h /usr/include
	mkdir /usr/include/UserData
	cp userProfile.h /usr/include/UserData
	cp userInteraction.h /usr/include/UserData
	cp userQuery.h /usr/include/UserData
	cp format.h /usr/include/UserData

local:
	mkdir -p usr/lib/UserData
	cp userdata.so usr/lib/UserData/
	mkdir -p usr/include
	cp UserData.h usr/include

clean:
	rm format.o userProfile.o userInteraction.o userQuery.o

localDelete:
	rm -r usr/lib/UserData
	rm usr/include/UserData.h

delete:
	rm -r /usr/lib/UserData
	rm /usr/include/UserData.h

