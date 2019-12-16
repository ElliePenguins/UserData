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
	gcc ${CCOPTS} -c -fPIC format.c userProfile.c userInteraction.c userQuery.c 
	gcc -shared format.o userProfile.o userInteraction.o userQuery.o 			-o userdata.so

clean:
	rm format.o userProfile.o userInteraction.o userQuery.o
