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

char * getStatusName(Status* status)
{
   if (status->name != NULL)
      return status->name;
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
Data * getUserData(User* user)
{
   return user->data;
}

Meta * getUserMeta(User* user)
{
   return user->meta;
}

Status * getUserStatus(User* user)
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

/*
 * causes segfault?
User * getLastStatus(User * user)
{
   User *userPtr = user;

   while ( userPtr->next != NULL)
   {
      userPtr = userPtr->next; 
   }

   return userPtr;
}
*/

Status * getLastStatus(Status * status)
{
   Status *ptr = status;
   Status *r_ptr = status;
   
   while ( ptr->next != NULL) 
   {
      ptr = getNextStatus(ptr);
      if ( ptr->next == NULL )
      {
	r_ptr = ptr;
	break;
      }
      else
      {
	 ptr = ptr->next;
      }
   }

   return r_ptr;
}

Instance * getLastInstance(Instance* instance)
{
	printf("getLast-> %s",instance->name);
   Instance *ptr = instance;
   Instance *r_ptr = instance;
   
   while ( ptr->next != NULL) 
   {
      ptr = getNextInstance(ptr);
      if ( ptr->next == NULL )
      {
	r_ptr = ptr;
	break;
      }
      else
      {
         // TODO: fix issue with next ptr in instance.
	 ptr = ptr->next;
      }
   }

   return r_ptr;
}

/*
Instance * getLastInstance( Instance * instance)
{
   while ( instance->next != NULL) 
      instance = getNextInstance(instance);
      
   return instance;
}
*/


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
