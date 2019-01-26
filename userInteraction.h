/*
 * This source file contains functions that are used
 * to manipulate data contained within user functions.
 *
 * This Source file also contains wrappers for ease
 * of use as a library.
 *
 * Alot of these functions allow you to set new
 * elements by using a reference call, but they
 * also return a reference to these elements for
 * direct dev manipulation, or can be passed into
 * other functions:
 * 	eg.
 * 	   addStatus(getStatus(userPtr, idnum));
 *
 *
 * MIT License
 * Copyright (C) 2018 ElliePenguins 
 *
 */

#include "userProfile.h"
#include <time.h>
#ifndef USER_INTERACTION_H_
#define USER_INTERACTION_H_


/* Define constants for sort methods */
#define SORT_FORWARD 1
#define SORT_BACKWARD 2
#define SORT_ID 3
#define SORT_DATE 4

// These functions can be used by ref or return.
// they return NULL, if something didn't work.
User * addUser(User *, char *name);
User * initNewUser(User *);
int deleteUser(User *, int id);

Status * addStatus(Status *);
Status * initNewStatus(Status *);
int deleteStatus(Status *, int id);

Instance * addInstace(User *, Status *); 
Instance * initNewInstance(User *, Status *);
//int deleteInstance(User *, Status *); Why would someone need this?

// Check hashes in meta.
User * validateUser(User *);
Status * validateStatus(User *, int statusId);
Instance * validateInstance(User *, int instanceId);

// Can be used to return the head node of a list,
// which can be passed to other functions in this file.
User * getUser(User *, int id);
// TODO: check these to make sure they return what is requrested.
Status * getStatus(User*, int id);
Instance * getInstance(Status *, int id);

// Sort list functions, based on any way for any reason.
User * sortUser(User *, int numberOfNodes, int sortMethod);
Status * sortStatus(Status *, int numberOfNodes, int sortMethod); 
//Instance * sortInstance(Status *, int numberOfNodes, int sortMethod);

User * editUser(User *, char * name);
Status * editStatus(Status *, char * name);
Instance * editInstance(Status *, char * name);

// Return a ptr to ptr with contiguous info.
User * getUserInfo( User *, int id); // Maybe doesn't need id, can use get functions.
char * getStatusInfo(User*, int id);
Instance * getInstanceInfo1(Instance *);

#endif
