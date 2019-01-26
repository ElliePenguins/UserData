# UserData

This repository contains logic and elements that can help 
when needing to deal with user information in a C program.

Instead of producing a binary, it should be compiled into
position-independant code via. a ".so" file for use with
any number of programs via. dynamic linking.

After enough enough time has been dedicated to debug I will
include proper instructions for compile, possibly make/install.
Any help with efficency in this regard would be appreciated.

Things I would like to add to this program:

 // TODO:

	1.
	   Need functions to free all the pointers in
	   all the nodes that have memory allocated to
	   them internally in the linked lists.

	   Create function to find specific nodes and or
	   walk through the lists.

	2.
	   Disk I/O functions to save the data between program
	   runs. This should eventually implement atomicity.

	3.
	   Add memory alignment and other efficencies to malloc
	   wrapper function(s) in format.c source file.
	   
	4.
	   Add openssl library for creating hashes in the nodes
	   and for use in the validation functions.

	5.
	   Finish function definitions in userInteraction
	   module. Then define their proper usage in
	   docmentation. 

	6.
	   Important, create linked list modification wrappers.
		eg. swap prev, swap ahead.
	   --- There is a high level of code duplication.

	7.
	   Check that all source file are added correctly.

	8.
	   Build / Make scripts.

	9.
	  Testing.

As of now:
   This is a work in progress and is currently not ready for use.

