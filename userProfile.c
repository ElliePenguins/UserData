/*
 *
 * This file contains the definitions for the
 * protypes in the userProfile.h header file.
 *
 * TODO: Create functions for searching UID/PID
 *     of nodes and assigning them to other
 *     and deciding how to assign them to other
 *     nodes.
 *     
 * Warning:
 *       dangling ptrs can be this programs
 *       kryptonite.
 *
 * Note:
 *       See main() for a simple usage case,
 *       and look at the other structs and
 *       functions to get an idea for the
 *       the internals, I suppose try to be
 *       opened minded about usage possiblities?
 *
 * TODO:
 *       Functions to free memory properly.
 *
 * TODO:
 *       functions that wrap create functions to
 *       append new nodes to the respective
 *       linked list by reference instead of
 *       by returns, expecting the library
 *       user to handle adding.
 *       (although that should still be an
 *       option if they wish via the original
 *       routines.)
 *
 * MIT License
 * Copyright (c) 2017 ElliePenguins 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// TODO:
// #include <openssl/sha.h>
// Maybe build a seperate module for that.

#include "userProfile.h"
#include "format.h"

/*
 *    FUNCTIONS START:
 */

// Generic functions.

int setUserId(int preferedId)
{
   // Does .bss initialize to 0 at startup?
   static int id = 0;

   if (preferedId > id )
   {
      if ( preferedId > 0)
    id = preferedId;
      else
    id++;
   }
   else
      id++;

   return id; 
   
}

// TODO: Need a function that searches the list for used/unused ID's

// Also: Should each node have a uuid, something that no-matter
//     of what type a node is, it is always unique.

int setStatusId(int preferedId)
{
   static int id = 0;

   if (preferedId > id )
   {
      if ( preferedId > 0)
    id = preferedId;
      else
    id++;
   }
   else
      id++;

   return id; 
   
}

int setInstanceId(int preferedId)
{
   static int id = 0;

   if (preferedId > id )
   {
      if ( preferedId > 0)
    id = preferedId;
      else
    id++;
   }
   else
      id++;

   return id; 

}

int setParentId(int preferedId)
{
   static int id;

   if (preferedId > id )
   {
      if ( preferedId > 0)
    id = preferedId;
      else
    id++;
   }
   else
      id++;

   return id; 
}

// User creation/initialization, pass it prevNode->next.
User * createUser(User *user, const char * name)
{
   User * currentUser;

   if ( user == NULL)
   {
     // Create Single Instance. 
     currentUser = mallocWrap(sizeof(User));
     currentUser->name = mallocString(name);
     strcpy(currentUser->name, name);

     // These have their initialize functions called internally.
     currentUser->data = createData(currentUser->data);
     currentUser->meta = createMeta(currentUser->meta);
     currentUser->status = createStatus(currentUser->status, name, "Head");

     currentUser = initUser(currentUser);
     
     currentUser->next = NULL;
   }
   else
   {
      fprintf(stderr, "User not free!");
      currentUser == user;
   }

   return currentUser;
}

// This is a better method, incase we want to
// overwrite a users current status.

User * initUser( User * currentUser)
{
  // TODO: if user == NULL, call function to create here?
   currentUser->data = initData(currentUser->data);
      //TODO !debug segfault here: CONTINUE.
   currentUser->meta = initMeta(currentUser->meta);
   currentUser->status = initStatus(currentUser->status);
   
   // Assuming entry at end of list.
   // TODO: logic for in list entry.
   currentUser->next = NULL; 

   
  currentUser->data = initData(currentUser->data);
  //currentUser->data = setNumberOfNodes(currentUser);
  // TODO: Functnions for decidig on uid/pid
  // Why is the id and pid set to zero at run time?
  currentUser->id = setUserId(0);
  currentUser->parentId = setParentId(0); 
}

// Data initialization.
Data * createData( Data * currentData )
{
   currentData = (Data*) mallocWrap(sizeof(Data));
   currentData->date = time(0); // !check this
   createMeta(currentData->meta);

   currentData->numberOfNodes = 0;
   currentData->numberOfStatusNodes = 0;
   currentData->numberOfInstanceNodes = 0;  
   // TODO: find a way to use init function.
   initData(currentData);

   return currentData;
}

Data * initData ( Data * currentData )
{
   if (currentData == NULL)
   { 
      fprintf(stderr, "\nUserData pointer is not null\n");
      currentData = NULL; // return null to indicate error.
   }
   else
   {
      currentData = mallocWrap(sizeof(Data));
      currentData->date = time(NULL);
      currentData->meta = createMeta(NULL);
      currentData->meta = initMeta(currentData->meta);

      // TODO: Init these by calling the proper functions.
      currentData->numberOfNodes = 0;
      currentData->numberOfStatusNodes = 0;
      currentData->numberOfInstanceNodes = 0;  
   }

   return currentData;
}

// Meta initialization.
Meta * createMeta(Meta * ptr)
{
   if (ptr == NULL)
   {
      ptr = (Meta*) mallocWrap(sizeof(Meta));
   }

   // TODO: decide on a hash algorithm and implement.
   ptr->creationHash = NULL;
   ptr->lastModifiedHash = NULL;

   initMeta(ptr);

   ptr->creationTime = time(0);
   ptr->lastModifiedTime = time(0); // hasn't been mod yet.

}

Meta * initMeta(Meta *currentMeta) 
{
   currentMeta->creationHash = setMetaHash(currentMeta, "aa55"); 
   currentMeta->lastModifiedHash = setMetaHash(currentMeta, "ef02");

   currentMeta->creationTime = time(NULL);
   currentMeta->lastModifiedTime = time(NULL);
   
   return currentMeta;
}

// Status initializtion.
// Note that this function, although accepts the previous node in
// the list, technically does not add the new node to the list. 
// Instead this function only returns the new node.
Status * createStatus(Status *prev, const char * name, const char *notes)
{
   Status * ptr = NULL;
   ptr = mallocWrap(sizeof(Status));

   // Creating status reqires name, not notes.
   ptr->name = mallocString(name);
   strcpy(ptr->name, name);

   if (notes != NULL)
   {
      ptr->notes = mallocString(notes);
      strcpy(ptr->notes, notes);
   }
   else
      ptr->notes = NULL;

   // Let a serperate function handle init defaults.
   ptr = initStatus(ptr);

   return ptr;
}

Status * initStatus( Status * currentStatus )
{
   Status * ptr = NULL;
   ptr = currentStatus;

   //TODO: check and mod passed values to create id. 
   ptr->id = setStatusId(0);
   ptr->parentId = setParentId(0);
   ptr->numberOfDirectNodes = 0;
   ptr->instance = createInstance(NULL, currentStatus->name);
   //ptr->instance = NULL; 


   ptr->next = NULL; // change the check if(prev == NULL) here.. 

   return currentStatus;
}

// This may require ptr protections or, save origin addr and reset.
int countUserNodes(User * currentUser)
{
   int numberOfNodes = 0;
   User * temp = currentUser;

   while ( currentUser->next != NULL )
   {
      temp = temp->next;
      numberOfNodes++;
   }

   return numberOfNodes;
}

int countStatusNodes( Status * currentStatus )
{
   int numberOfNodes = 0;
   Status * temp = currentStatus;

   while ( currentStatus->next != NULL )
   {
      temp = temp->next;
      numberOfNodes++;
   }

   return numberOfNodes;
}

int countInstanceNodes(Instance * currentInstance)
{
   int numberOfNodes = 0;
   Instance * temp = currentInstance;

   while (temp->next != NULL)
   {
      temp = temp->next;
      numberOfNodes++;
   }

   return numberOfNodes;
}

// Instance initialization.
Instance * createInstance(Instance *prev, const char * name)
{
   Instance * currentInstance = NULL;
   
   if ( strlen(name) < 0 )
   {
      ; // error, Instances require the name or type of their parrent.
   }
   else
   {
      // TODO delegate this to initInstance();
      puts("Instance Created"); // debug
      currentInstance = (Instance*) mallocWrap(sizeof(Instance));
      // TODO:  Change this to point to the same string as statusPtr?
      // or should they be able to change within context?
      currentInstance->name = mallocString(name);
      strcpy(currentInstance->name, name);
   
      currentInstance->id = setInstanceId(0);
      currentInstance->parentId = setParentId(0);
      createMeta(currentInstance->meta);
      currentInstance->next = NULL;

      // TODO:
//      currentInstance = initInstance(currentInstance, NULL, NULL);
      

      // This if/else needs some work.
      if (prev == NULL)
        ; // code to handle linked list entries.
      else
        currentInstance->next = NULL; // fixed 
   }
   
   return currentInstance; // NULL if name not set.
}

// Requires the name of its status.
Instance * initInstance(Instance * currentInstance, const Status *prevStatus,
      const char *notes)
{
   if (currentInstance == NULL)
   {
      fprintf(stderr, "\nInitialize instance pointer is NULL\n");
      currentInstance = NULL;
   }
   else
   {
      // TODO: Requires memory allocation on new ptrs.
      strcpy(currentInstance->name, prevStatus->name);
      strcpy(currentInstance->notes, notes);

      currentInstance->id = setInstanceId(0);
      currentInstance->parentId = prevStatus->id; 
      
      currentInstance->meta = createMeta(NULL);
      currentInstance->meta = initMeta(currentInstance->meta);
      currentInstance->next = NULL; // New node only;
   }

   return currentInstance;
}

// Meta manipulation functions.
time_t setUserCreateTime( User * user, time_t timeToSet )
{
   if(timeToSet < 0)
   {
      timeToSet = time(0);
   }     
   user->meta->creationTime = timeToSet;

   return timeToSet; //Return the time set for errors or whatev.
}

time_t setUsertime( User * currentUser, time_t *timeToSet)
{
   currentUser->meta->lastModifiedTime = creationTime(timeToSet);
   
   return currentUser->meta->lastModifiedTime;
}

// Note: This SubR may not be need as the prev could be passed NULL.
time_t setUserCurrentTime( User * currentUser, time_t * timeToSet)
{
   if(timeToSet < 0)
   {
      *timeToSet = time(NULL);
   }     

   currentUser->meta->creationTime = creationTime(timeToSet);

   return currentUser->meta->creationTime;
}

// This also allows you to set the timestamp. Why? not sure yet.
time_t setUserModTime(User *user, time_t timeToSet )
{
   // If timeToSet is NULL set to curren time.
   if(timeToSet < 0)
   {
      timeToSet = time(0);
   }     

   user->meta->lastModifiedTime = timeToSet;

   return timeToSet;
}


// User Manipulation.
void changeUserName(User *user, const char *newName)
{
   if ( user->name)
      free(user->name);

   user->name = mallocString(newName);
   strcpy(user->name, newName);
}

// Data Manipulation.
time_t setDate ( Data * currentData)
{
   // TODO: this function is probobly not needed, as we are useing epoch time.
   currentData->date = time(0);
}

Data * setNumberOfNodes(User* currentUser)
{

   // TODO: The count nodes function is too heavy for this.
   currentUser->data->numberOfNodes =
      countNumberOfNodes(currentUser, 1);
   currentUser->data->numberOfStatusNodes =
      countNumberOfNodes(currentUser, 2);
   currentUser->data->numberOfInstanceNodes =
      countNumberOfNodes(currentUser, 3);

   // Set it interally or just return it.
   return currentUser->data;
}

int countNumberOfNodes(User* currentUser, const short int type)
{
   Instance * currentInstance = NULL;
   Status * currentStatus = NULL;

   currentStatus = currentUser->status;
   currentInstance = currentUser->status->instance;

   int instanceCount = 0; 
   int statusCount = 0;
   
   // Iterate through the nodes and count them.
   // This val can be stored to save cpu time.
   while ( currentStatus->next != NULL)
   {
      while ( currentInstance->next != NULL) 
      {
    currentInstance = currentInstance->next;
         instanceCount++;
      }
      currentStatus = currentStatus->next;
      statusCount++;
   }

   int ret_val = 0;
   // Depending on type, return the number of nodes.
   switch (type)
   {
      case 1:
    ret_val = (instanceCount + statusCount);
    break;
      case 2:
    ret_val = statusCount;
    break;
      case 3:
    ret_val = instanceCount;
    break;
      default:
    fprintf(stderr, "Unknown error in setNumberOfNodes();");
   }
   
   return ret_val;
}
   
   // Depending on type, return the number 
// Meta Manipulation.
// TODO: Why are we passing this a meta node?
char * setMetaHash(Meta* currentMeta, const char * hash)
{
   char * r_hashPtr = NULL;

   r_hashPtr = (char*) mallocString(hash);
   strcpy(r_hashPtr, hash);

//   free(currentMeta->creationHash);
//   currentMeta->creationHash= (char*) mallocString(hash);
//   strcpy(currentMeta->creationHash, hash);

//return currentMeta->creationHash;
   return r_hashPtr;
}

// Don't forget about this one? can set last without return.
char * setLastModHash(Meta* meta, char* hash)
{
   // TODO: find a way to work with already set.
   if (meta->lastModifiedHash == NULL)
   {
        // Optionally set internally?
//      meta->lastModifiedHash= (char*) mallocString(hash);
//      strcpy(meta->lastModifiedHash, hash);
   } 
   else
   {
      free(meta->lastModifiedHash);
      meta->lastModifiedHash = (char*) mallocString(hash);
      strcpy(meta->lastModifiedHash, hash);
   }

   return hash;
}

int setNumberOfStatusNodes(User* currentUser)
{
   int numberOfNodes = 0;
   User * tempUser = NULL;

   while ( currentUser->next != NULL )
   {
      currentUser = currentUser->next;
      numberOfNodes++;
   }

   return numberOfNodes;
}

int setNumberOfInstanceNodes ( Instance * currentInstance )
{
   int numberOfNodes = 0;
   Instance * temp= currentInstance;

   while ( temp->next != NULL )
   {
      temp = temp->next;
      numberOfNodes++;
   }
   
   return numberOfNodes; 
}

// Pass this NULL, for current time.
time_t creationTime(time_t * timePtr) 
{
   time_t timeReturn = time(timePtr);
   return timeReturn;
}

// Again pass this NULL, for current time.
time_t LastModTime ( time_t *timePtr)
{
   time_t timeReturn = time(timePtr); 
   return timeReturn;
}

/* Moving nodes */

// For now, use reference and return acknoledgement.
int swapUserNodes( User * user )
{
   User * tempUser = NULL;

   tempUser = user->next;

     // Pass this the prev node?
   user->next = tempUser->next;
   tempUser->next = user->next;
   tempUser->next = user->next;

} 

int swapStatusNode( Status * status )
{
   Status * tempStatus = NULL;

   tempStatus = status->next;

     // Pass this the prev node?
   status->next = tempStatus->next;
   tempStatus->next = status->next;
   tempStatus->next = status->next;

} 

/* unused code */

/*

int setNumberOfStatusNodes(user* currentUser)
{
   Status *currentStatus = NULL;
   currentStatus = currentUser->status;

   int count = 0;

   while(currentStatus->next != NULL)
   {
      currentStatus = currentStatus->next;
      count++;
   } 

   return count;
}
 
*/
/* Only sets one hash, set return value.
char * setMetaHash(Meta* currentMeta, const char * hash)
{
      // TODO: find a way to work with already set.
   if (currentMeta->creationHash == NULL)
   {
      currentMeta->creationHash = (char*) mallocString(hash);
      strcpy(currentMeta->creationHash, hash);
   } 
   else
   {
      free(currentMeta->creationHash);
      currentMeta->creationHash= (char*) mallocString(hash);
      strcpy(currentMeta->creationHash, hash);
   }

   return currentMeta->creationHash;
}
*/

// This block below, can be used for a function that
// works directly on a a status/user/etc node to
// set the id/pid, This can be used in the future for
// pid maybe.

/*
   static int id; // TODO: init. 
   if ( status != NULL )
   {
      if (preferedId > 0)
    status->id = id++;
      else
    status->id = preferedId;
   }

   return status->id;
   */
