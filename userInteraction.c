/*
 * This source file contains functions that are used
 * to manipulate data contained within user functions.
 *
 * This file may also contain wrappers for ease of
 * use as a library, these functions may be moved
 * into their own helper source file eventually.
 * 
 * MIT License
 * Copyright (C) 2018 ElliePenguins
 *
 * The add and init functions may not be needed
 * but the mod, get, info and delete are.
 *
 */

#include "userInteraction.h"
#include "userQuery.h"
#include "userProfile.h"

// For compilation: delete after.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "format.h"

/*
 * Notes:
 * ------
 *
 * These functions can be used by ref or return.
 * they return NULL, if something didn't work.
 *
 * This is important, list modifiaction wrappers 
 * Consider making these insert in list functions.
 *
 * TODO: Define logic for sort methods.
 * TODO: Implement the ability to sort by date.
 */

/*
User * addUser(User * newUser, char *name)
{
   // TODO: createUser might not need prev user?
   newUser = createUser(NULL, name);
   return newUser;
}
*/

User* addUser(User* user, char *name)
{
   if ( user == NULL )
   {
      user = createUser(user, name);
   }
   else
   {
      // find end of list and add.
      while (user->next != NULL)
      {
         user = user->next;
      }
      // Once found, create.
      user->next = createUser(user->next, name);
      //user = user->next;
   }

   return user;
}

int updateStatusNumber(User * user)
{
	Status * sPtr = NULL; 
	int sCount = 0;

	if ( user != NULL )
		sPtr = user->status;

	// count:
	while ( sPtr->next != NULL)
	{
		sPtr = getNextStatus(sPtr);
		sCount++;
	}

	// Update data in user node.
	user->data->numberOfStatusNodes = sCount;
	
	return sCount;
}

// This is the number of instances a single status has,
// It is store in struct element numberOfDirectNodes.
int updateStatusInstanceNumber(Status * status)
{
	Instance* iPtr = NULL; 
	int iCount = 0;

	if ( status != NULL )
		iPtr = status->instance;

	// count:
	while ( iPtr->next != NULL)
	{
		iPtr = getNextInstance(iPtr);
		iCount++;
	}

	// Update data in user node.
	status->numberOfDirectNodes = iCount;
	
	return iCount;

}

// This is the overall number of nodes in
// the user struct.
int updateInstanceNumber(User * user)
{
	Status * sPtr = NULL; 
	int sCount = 0;

	if ( user != NULL )
		sPtr = user->status;

	// count:
	while ( sPtr->next != NULL)
	{
		sPtr = getNextStatus(sPtr);
		sCount += sPtr->numberOfDirectNodes;
	}

	// Update data in user node.
	user->data->numberOfInstanceNodes = sCount;
	
	return sCount;
}

// Give it the head node,
// Update you could use the get functions. instead.
int deleteUser(User * currentUser, int id)
{
   // Remember to reconnect links in list.
   int r_value = 0;
   if ( currentUser == NULL)
   {
      fprintf(stderr, "Attempted delete of non instantiaed user.\n");
   }
   else
   {
      if ( currentUser->id == id)
      {
   User * temp = NULL;
   temp = currentUser;
   // Reattach the next ptrs, and free.
   currentUser = currentUser->next;
   free(temp);
   temp = NULL;
   r_value = 1;
      }
   }
   return r_value;
}

// Pass it the head node.
// These should be modified to add status anywhere in list.
Status * addStatus(Status * status, char *name, char *notes)
{
   Status * s;
   if ( status == NULL )
   {
      status = createStatus(status, name, notes);
   }
   else
   {
      s = getLastStatus(status);
      printf("DEBUG: %s\n", s->name);
      // Once found, create.
      s->next = createStatus(s, name, notes);
   }

   // return new node.
   return s->next;
}

Instance* addInstance(Status * status, char *name, char *notes)
{
	Instance * iPtr = NULL;
	
   if ( status == NULL )
   {
		; // return null if issue with status.	
   }
   else
   {
		iPtr = status->instance;	
		//
      // find end of list and add.
      while (iPtr->next != NULL)
      {
		  iPtr = iPtr->next;
      }
		
      // Once found, create.
		// TODO: create Instance does not take notes.
      iPtr->next = createInstance(iPtr, name);
      iPtr = iPtr->next;
   }

   return iPtr;
}

// TODO: Add an option for no id, that will delete the passed node.
int deleteStatus(Status * status, int id)
{
   int r_value = 0;
   if (status == NULL)
   {
      
      fprintf(stderr, "Status list to add to has not been created.\n");
   }
   else
   {
      Status * statusPtr = NULL; 
      statusPtr = status; 
      //TODO : Change all this to use the libs own functions to find nodes.
      do {
    if ( statusPtr->id == id)
    {
      Status * temp = NULL;
      temp = statusPtr;
      // Reattach the next ptrs, and free.
      statusPtr = statusPtr->next;
      free(temp);
      break;
    }
    else
    {
       statusPtr= statusPtr->next;
    }
      } while ( statusPtr->next != NULL);

      if (statusPtr->id != id)
      {
    fprintf(stderr, "User Id to delete not found\n");
    r_value = -1;
      }
   }

   return r_value;
}

/*
Instance * addInstance(User * user, char * name, char * notes) 
{
   short int check = 0;

   // Find where to add the instance 
   User * userPtr = user;
   while ( userPtr->next != NULL )
   {
      userPtr = userPtr->next;
   }
   //
   // Once end of list found, look for status
   const char *name = status->name; 
   Status * statusPtr = NULL;
   
   // make the head node a little more manageable.
   statusPtr = userPtr->status;
   

   while (!strcmp(statusPtr->name, name))
   {
      if ( statusPtr->next != NULL)
    statusPtr = statusPtr->next;
      else
      {
    // If the name hasn't been found and you
    // and you hit the end of the list. set check. 
    fprintf(stderr, "Hit end of list, no status of type found");
      }
   }
   
   // Now find the last instance of the found status. 
   Instance * newInstance = NULL;

   if ( check < 0)
   {
      newInstance = createInstance(newInstance, "name");

      statusPtr->instance = newInstance;
      //TODO: Attach list.
   }
   // else

   // Returns NULL if there was an error.
   return newInstance;
}
*/

// Cannot delete from get functions because you need to acces the
// previous node to reattach the list. Consider a function.
// that returns the previous node of a list specificically for this.
int deleteInstance(Instance *instance, int id)
{
   // should any state be saved? or perm deletion.

   short int check = -1;
   Instance *previous = NULL;
   
   do
   {
      if ( instance->id == id)
      {
    free(instance->name);
    free(instance->notes);
    free(instance->meta);
    // Reconnect the list.
    if (instance->next != NULL )
    {
       previous->next = instance->next;
    }
    // Free node and set return value.
    free(instance);
    check = 0;
      }
      else
      {
    previous = instance; // Used to reconnect the list. 
    instance = instance->next;
      }

   } while ( instance->next != NULL);

   return check;
}

// Check hashes in meta
// have to wait until openssl/sha.h is implemented.
/*
User * validateUser(User *)
{

}
Status * validateStatus(User *, int statusId)
{

}
Instance * validateInstance(User *, int instanceId)
{

}
*/

// Can be used to return the head node of a list,
// which can be passed to other functions in this file.
User * getUser(User *user, int id)
{
   User *ptr = NULL; 
   
   if ( user != NULL )
   {
      do
      {
   if (user->id == id )
   {
      ptr = user;
      break;
   }
   else
   {
      user = getNextUser(user);
   }
      }  while ( user->next != NULL);
   }

   return ptr;
}


User * getUserByName(User *user, char *name) 
{
    User *userPtr = user; 

    while ( userPtr != NULL)
    {
        if( strcmp(name, getUserName(userPtr)) == 0) 
		break;
        else
	{
		userPtr = userPtr->next;

		/*
		if ( userPtr->next == NULL)
			userPtr = NULL; // return null
		*/
	}
    }


    return userPtr;
}

Status * getStatusByName(Status *status, char *name) 
{
    Status *statusPtr = status; 

    while ( statusPtr->next != NULL)
    {
		 printf("DEBUG StatusByName(): %s\n", statusPtr->name);
        if( strcmp(name, getStatusName(statusPtr)) == 0) 
		break;
        else
	{
		statusPtr = statusPtr->next;
		if ( statusPtr = NULL)
			break;
	}
    }

    return statusPtr;
}


// Should this run off the user list or Status list.
Status * getStatus(User *user, int id)
{
   Status *ptr = NULL;

   if ( user != NULL )
   {
      ptr = user->status; // head of status.
      while ( ptr->next != NULL )
      {
    printf("\nPointer: %p - id: %d\n", ptr->next, ptr->id);
    if ( ptr->id == id )
    {
       ptr = user->status;
       break;
    }
    else
       ptr = ptr->next;
      }
   }

   // Return NULL if any issue.
   return ptr;
}

Instance * getInstance(Status *status, int id)
{
   Instance *ptr = NULL;

   if ( status != NULL )
   {
      ptr = status->instance; // head of status.
      while ( ptr->next != NULL )
      {
        printf("\nPointer: %p - id: %d\n", ptr->next, ptr->name);
        if ( ptr->id == id )
        {
		// Doesn't this overwrite with head?
		//ptr = status->instance;
		break;
        }
        else
		if (ptr->next != NULL) // Redundant?
			ptr = ptr->next;
	}
   }

   // Return NULL if any issue.
   return ptr;
}

// Sort list functions, based on any way for any reason.
// TODO: Define sort logic.
User * sortUser( User * user, int numberOfNodes, int sortMethod)
{
   User *h_node = NULL;
   User *prev = NULL;
   
   // Assign the current head node as is.
   //int numberOfNodes = user->data->numberOfNodes;
   int i = 0;

   // Check variables.
   short int sorted = 0;
   short int complete = 0;

   if ( sortMethod == SORT_FORWARD)
   {
      do
      {
    sorted = 0;
    for(i = 0; i < numberOfNodes; i++)
    {
      if (strcmp(user->name, user->next->name) == 0)
      {
         if ( user->id == 1 || user->next->id == 1)
         {
       ; // Do not move the head node.
       sorted = 1;
         }
         else
         {
       // decalared in userProfile.h
       swapUserNodes(prev); // Could be easier to pass user and prev. 
       sorted = 1;
         }
      }
      else
      {
         // Advance the list by one node.
         prev = user;
         user = user->next;
      }
    } 
    if ( !sorted )
    {
       complete = 1;
    }

      } while (!complete);
   }
   else
      fprintf(stderr, "Sort method not available, no action taken");

   // The Return the head node. This must always be ID 1, and never sorted. 
   return h_node;
}


// Note: Requires that the number of nodes be passsed when called.
Status * sortStatus(Status * status, int numberOfNodes, int sortMethod) 
{
   Status *h_node = NULL;
   h_node = status;
   Status *prev = NULL;

   int i = 0;
   short int complete =0;
   short int sorted = 0;

   if ( sortMethod == SORT_FORWARD)
   {
      do {
    sorted  = 0;
    for ( i =0; i < numberOfNodes; i++)
    {
       if ( strcmp(status->name, status->next->name) == 0 )
       {
         if ( status->id == 1 || status->next->id == 1)
         {
       ; // Do not move the head node.
       sorted = 1;
         }
         else
         {
       swapStatusNode(prev); // Could be easier to pass user and prev. 
       sorted = 1;
         }
       }

       prev = status;
       status = status->next;
       
       if ( !sorted )
       {
          complete = 1;
       }
    } 
      } while ( !complete );

   }
   else
      fprintf(stderr, "Sort method not availabe, no action taken.\n");

   // Function returns the node that is head.
   return h_node;

}

// As of now I cant imagine why you would want to sort
// the instances from chron order as they were created.
/*
Instance * sortInstance(Status *, int sortMethod)
{

}
*/

/* The edit functions, work by being passed a node by
 * reference that is gotten via the getUser getStatus
 * etc. functions. */

// TODO: Allow function to change more then just 
//     the name, eg. notes etc.
User * editUser(User * user, char * name)
{
   if ( user->name != NULL )
   {
      free(user->name);
      user->name = mallocString(name);
      strcpy(user->name, name);
   }
   
   // else return NULL.
   return user;
}

// Should be able to edit notes as well.
Status * editStatus(Status * status, char * name)
{
   if ( status->name != NULL )
   {
      free(status->name);
      status->name = mallocString(name);
      strcpy(status->name, name);
   }
   
   // else return NULL.
   return status;  
}

// This one might have to be modified depending on how
// instances of a status are handled. (notes etc.)
Instance * editInstance(Status * status, char * name)
{
   Instance *instance = NULL;
   instance = status->instance;

   if ( instance->name != NULL )
   {
      free(instance->name);
      instance->name = mallocString(name);
      strcpy(instance->name, name);
   }
   
   // else return NULL.
   return instance;  
}

// Return a ptr to ptr with contiguous info.
/*
User * getUserInfo( User * )
{

}
*/

/* TODO: The below two functions reutnr the notes contained within
 *     the node. It is important to remember that these have no
 *     protections. consider casting to const or returning new ptr. */

// This function returns the notes contained withing the nodes.
char * getStatusInfo(User *user, int id)
{
   // If the node passed doesn't match, try and figure it out.
   Status * status = NULL;
   if (user->status->id != id)
   {
     status = getStatus(user, id);
   }

   // Remember this is not a const, and can be messed with.
   return status->notes;
}

char * getInstanceInfo(Status *status, int id)
{
   Instance * instance = NULL;
   instance = status->instance;

   if (instance->id != id)
   {
      instance = getInstance(status, id);
   }

   return instance->notes;
}

/*
int * deleteUser(User * currentUser, int id)
{
   // Remember to reconnect links in list.
   if ( currentUser == NULL)
   {
      fprintf(stderr, "Attempted delete of non instantiaed user.\n");
   }
   else
   {
      User * userPtr = currentUser;
      userPtr = currentUser; 
      do {
    if ( userPtr->id == id)
    {
      User * temp = NULL;
      temp = userPtr;
      // Reattach the next ptrs, and free.
      userPtr = userPtr->next;
      free(temp);
      break;
    }
    else
    {
       userPtr = userPtr->next;
    }
      } while(userPtr->next != NULL);
      
      // TODO: Clean this up.
      if (userPtr->next == NULL)
      {
    fprintf(stderr, "User Id to delete not found\n");
      }
   }
}
*/

/*
 * Temp.
int updateData(User * user)
{
	User * ptr;
	Status * sPtr;
	int sNodes = 0;
	int uNodes = 0;

	while ( ptr->next != NULL)
	{
		int i = 0;
		ptr = getNextUser(ptr);
		uNodes++;

		// Update to use GetStatus;
		sPtr = ptr->status; 

		if ( sPtr != NULL )
			while(sPtr->next != NULL) 
			{

				sPtr = getNextStatus(sPtr);
				sNodes++;

			}

		ptr->data->numberOfStatusNodes = sNodes;
		sNodes = 0;

	}

	// Only sets the number of Status nodes in each
	// user node atm.
	
	return sNodes;
}
*/
/*
 * Old version.
 * 
Instance * getInstance(Status *status, int id)
{
   Instance* ptr = NULL;
   Instance *current = NULL;

   current = status->instance;

   do
   {
      if ( current->id == id )
      {
	 //WTF IS THIS!
	 ptr = current;
	 break;
      }
      else
    current = current->next;

   } while ( current->next != NULL );

   return ptr;
}
*/
