/*
 * These are all the datatypes that will be used to build
 * the collections of functions used for a dynamic user
 * profile library.
 *
 * 	Mod:
 * 	   To be used for other data types in the future.
 * 	   
 * MIT License
 * Copyright (c) 2017 ElliePenguins 
 */

#include <time.h>
#ifndef USER_PROFILE_H_ 
#define USER_PROFILE_H_

typedef struct User {
   char * name;
   int id;
   int parentId; // Except head node.
   struct Data * data; 
   struct Meta * meta;
   struct Status * status; // Status head node.
   struct User * next;
} User;

typedef struct Data {
   time_t date;
   struct Meta * meta;
   int numberOfNodes;
   int numberOfStatusNodes;
   int numberOfInstanceNodes;
} Data;

typedef struct Meta {
   char * creationHash;
   char * lastModifiedHash;
   time_t creationTime;
   time_t lastModifiedTime;
} Meta;

// The next two are directly related to eachother.

typedef struct Status {
   char * name;
   char * notes; // users comments when instantiated.
   int id;
   int parentId;
   int numberOfDirectNodes;
   struct Instance *instance; // Instance head node.
   struct Status * next;
} Status;

typedef struct Instance {
  char * name;  // Shares the same name as the status.
  char * notes; // users comments when instantiated.
  int id;
  int parentId;
  struct Meta *meta;
  struct Instance *next;
} Instance; 

// Creation and initialization functions:
int countUserNodes(User *);
int countStatusNodes(Status*);
int countInstanceNodes(Instance*);

// User initialization.
User * createUser(User *prev, const char * name);
User * initUser( User * currentUser);

// Data initialization.
Data * createData(Data * currentData);
Data * initData( Data * currentData);

// Meta initialization.
Meta * createMeta(Meta * currentMeta);
Meta * initMeta(Meta *currentMeta); 

// Status initializtion.
Status * createStatus(Status *prev, const char * name, const char *notes);
Status * initStatus( Status * currentStatus );

// Instance initialization.
Instance * createInstance(Instance *prev, const char * name);
Instance * initInstance(Instance * currentInstancem, const Status *prevStatus,
      const char * notes);

// Meta manipulation functions.
void setUserTime( User * user );
void setUserCurrent_time( User * user, time_t *);
time_t lastModfiedTime(User *, time_t *);
void changeUserName(User *, const char *);

// These may be set in init, and maybe should not be manipulated?
// These can be used for any of the structs that require it.
int setUserId(int);
int setParentId(int);

// Data Manipulation.
time_t setDate ( Data * currentdata);
Data * setNumberOfNodes(User* currentUser);
int setNumberOfStatusNodes(User* currentUser); // ? commented out ?
// TODO: create setTotalNumberOfInstanceNodes(User *current);
int setNumberOfInstanceNodes(Instance* currentUser);
int countNumberOfNodes(User *currentUser, const short int type);

// Meta Manipulation.
char * setMetaHash(Meta*, const char* hash);
char * setLastModHash(Meta*, char* hash);
time_t creationTime(time_t *); // should be set when created.

// Status Manipulation.
char * setStatusName(Status *, char *name);
char * setStatusNotes(Status *, char *notes);
char * setStatusNumberOfinstanceNodes(Status *, int numberOfNodes);

// Instance Manipulation.
char * setInstanceName(Instance *, char * name);
char * setInstanceNotes(Instance *, char * notes);

int swapUserNodes( User * );
int swapStatusNode( Status *);

/*---------------*
 * end of header *
 *---------------*/

#endif
