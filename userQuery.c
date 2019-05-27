/*
 * 	Functions that makle it easier to extract data's from
 * 	the linked lists. 
 * 	These can be a bit more specific in the datas each
 * 	of these functions return.
 *
 * 	This is the sorce file that contains the implementation/
 * 	and definitions of the declared functions in this module.
 *
 * 	MIT License
 * 	Copyright (c) 2018 ElliePenguins 
 */

/********************************
 * 	Start Definitions	*
 ********************************/

#include <stdio.h>

#include "userProfile.h"

/* 	User node queries	*
 ********************************/

char * getUserName(User* user)
{
   if (user->name != NULL)
      return user->name;
}

int getUserId(User* user)
{
   return user->id;
}

int getUserParentId(User* user)
{
   return user->parentId;
}

// Return the head node contained within each user.
Data * getUserDataNode(User* user)
{
   return user->data;
}

Meta * getUserMetaNode(User* user)
{
   return user->meta;
}

Status * getUserStatusNode(User* user)
{
   return user->status;
}

// Note: easier way to get the next node?
// NOTE THIS DOES NOT WORK
User * getNextUser(User* user)
{
   User * ptr = NULL;
   if ( user != NULL )
      ptr = user->next;
   
   return ptr;
}

Status * getNextStatus(Status * status)
{
   Status * ptr = NULL;
   if (status != NULL)
      ptr = status->next;
   
   return ptr;
}

Instance * getNextInstance(Instance * instance)
{
   return instance->next; 
}

// Find last.

User * getLastUser(User * user)
{
   User *userPtr = user;

   while ( userPtr->next != NULL)
   {
      userPtr = userPtr->next; 
   }

   return userPtr;
}

Status * getLastStatus(Status * status)
{
   Status *ptr = NULL;
   Status *r_ptr = NULL;
   ptr = getNextStatus(status);


   while ( ptr != NULL) 
   {
      puts("fail here");
      ptr = getNextStatus(ptr);
      if ( ptr == NULL )
	break;
      else
	 r_ptr = ptr;
   }

   return r_ptr;
}

Instance * getLastInstance( Instance * instance)
{
   while ( instance->next != NULL) 
      instance = getNextInstance(instance);
      
   return instance;
}


/*	Data Node Queries	*
 ********************************/

// Use the above functions to get Data nodes.
time_t getDataTime(Data * data)
{
   return data->date; 
}

Meta * getDataMetaNode(Data *data)
{
   return data->meta;
}

int getNumberNodes(Data *data)
{ 
   return data->numberOfNodes;
}

int getNumberStatusNodes(Data * data)
{
   return data->numberOfStatusNodes;
}

int getNumberInstanceNodes(Data * data)
{
   return data->numberOfInstanceNodes;
}

/*	Meta Node Queries	*
 ********************************/

char * getCreationHash(Meta *meta)
{
   return meta->creationHash;
}

char * getLastModifiedHash(Meta *meta)
{
   return meta->lastModifiedHash;
}

time_t getCreationTime(Meta *meta)
{
   return meta->creationTime;
}

time_t getModificationTime(Meta *meta)
{
   return meta->lastModifiedTime;
}

/*	Status Node Queries	*
 ********************************/
/*
*/
