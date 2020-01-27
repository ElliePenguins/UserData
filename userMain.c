
/*
 * UserData project.
 *
 * Source file userMain
 * 
 * As name suggests this source file contains the main function 
 * for the userProfile project, It is the main interface for
 * testing the functions while they are being written.
 *
 * Because this project is ment to be position independant
 * shared object for the purpose of being a library
 * intended to be used by other developers, this sourcefile
 * will not be compiled into the final project.
 *
 * Again this source file is for testing and debugging
 * purposes.
 *
 * This could be a test program, that could check and
 * allow new users to play with createing and deleting
 * elements and nodes in a visual way?
 *
 * Use this as a reference tool to determine weather we need
 * more higher level functions to wrap the lower.
 *
 * Think about the ease of use for devs who would
 * use this lib.
 *
 * MIT License
 * Copyright (c) 2018 ElliePenguins 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h> // exit();

#include "userProfile.h"
#include "userInteraction.h"
#include "userQuery.h"
#include "format.h"

#define BANNER "Main Menu, Try it now."

int menu( void );
void printLine ( int numberOfStars, char character);
void printSpace ( int numberOfSpaces );
void waitKey(void);

// TODO: Maybe save some of these? or consider
//     turning them into a kind of wrapper?
void display(User *);
void detailDisplay(User *);
User* makeNewUser( User *);
Status* makeNewStatus( Status *);
void makeNewInstance( Status *);
User * selectUser(User *);
Status * selectStatus(User *);
Status * selectStatusName(User *user);
int prompt ( char * str );

// Detailed outputs.
void outputUser(User *);
void outputStatus(User *,Status *);
void outputInstance(Status * status);
void outputMeta(User *);

int main ( void ) 
{ 

   /* Create Head node user and a loop with a menu
    * for the user to create, edit and display
    * nodes as they wish, this should provide the
    * developer some idea what is going on.
    */

   User * user = NULL;
   
   // Create head node.
   user = createUser(NULL, "Head");

   // Don't wannt mess around and lose the head. 
   User *userPtr = user;

   // Formatting.
   printf("\n\n\n");

   while (1) {

     int selection =  menu(); // Allow the user to play with the datas and functions. 
     int end = 0;

     // For this testing program, print how many nodes exist. good for debugging. 
     // Note here that select user can set the userPtr prior to call to get functions.
     // TODO: create getdataNode();
     int numberOfNodes = getNumberNodes(user->data);
     int numberOfStatusNodes = getNumberStatusNodes(user->data);
     int numberOfInstanceNodes = getNumberInstanceNodes(user->data);

     /* The options that are selected call functions that are written
      * in this practice and are not part of the library.
      */

     // Display if there is a node selected and which one.

     // Note that user ( headnode ) is not moved it is left alone
     // and userPtr is manipulated, when needs to be reset
     // then it can be reset to user ( headnode.)
     
     switch (selection)
     {
   case 0:
      end = !end;
      break;
   case 1:
      makeNewUser(user);  // Always Pass head node.
      userPtr = getNextUser(userPtr); 
      break;
   case 2: 
      makeNewStatus(getLastStatus(userPtr->status));
      // update data has to be done manually for now.
      updateStatusNumber(userPtr);
      break;
   case 3:
      // TODO: continue from here.
      //	get status might have an issue.
      makeNewInstance(getStatus(userPtr, 1));   
            // todo: Modify to use getStatus instead. 
         // Or maybe create a set to last node for this one.
      break;
   case 4:
      userPtr = selectUser(user);
      deleteUser(user, getUserId(user));
      puts("\nNot Available.");
      break;
   case 5:
      display(userPtr); //TODO: expand on this. 
      waitKey();
      break;
   case 6:
      detailDisplay(userPtr); // show options to output internals.
      break;
   case 7:
      // TODO: modify selectUser to return somthing useful.
      userPtr = selectUser(user);
      // If NULL is returned, Reset to head pointer.
      if ( userPtr == NULL )
         userPtr = user;   
      break;
   default:
      break;

     }

     //userPtr = getLastUser(user);
     if (userPtr != NULL)
     {
   printSpace(2);
   printLine(25, '*');
   printf("User node with id: %d, selected.\n", userPtr->id);
   printLine(25, '*');
     }
     else
     {
   printSpace(2);
   puts("No Node is Currently Selected.");
     }

     // If end flag is set, 
     // stop the loop & end the program.
     if ( end == 1 )
   break;
   }

   // Delete all allocated memory for all elements.
   while ( user != NULL )
   {
      deleteUser(user, 0);
      user = user->next;
   }

   puts("GoodBye.");
   printSpace(1);

   return 0;

}

// ------------------------------------------------------------
// These functions help create a men in the main function above,
// They allow the user to play with the functions in a predictable
// manner to allow the user to get a feel for how to use the
// library, as well as an easy testing env for the libs development.

#define PROMPT ">>>"

// Functions decalred here are mostly just for menu() and
// dont need to be seen by main();

void waitKey ( void )
{
     puts("\n\nPress ENTER to continue.");
     char junk = getchar();
     junk = getchar(); 
}

void detailDisplay(User * user)
{
   puts("1\t-\tUser Details");
   puts("2\t-\tStatus Details");
   puts("3\t-\tMetaData Details");
   int select = prompt(PROMPT);
   Status * status = NULL;

   switch(select)
   {
      case 1:
	outputUser(user);
	break;
      case 2:
    // Remeber that status is a linked list too.
    puts("1 - id\n2 - name");
    int select2 = (int) prompt(PROMPT);
    
    if (select2 == 1)
    {
       status = selectStatus(user);
    }
    else if(select2 = 2)
    {
       status = selectStatusName(user);
    }

    outputStatus(user, status);
    break;
      case 3:
       outputMeta(user);
    break;
      default:
    break;
   }
}
void outputInstance( Status * status)
{
      Instance *instance = NULL;
      instance = status->instance;
   
      printf("Instance node name: %s\n",  instance->name);
      puts("***************");
      printf("Instance node address: %p\n", instance);
      printf("Instance ID: %d\nInstance pid: %d",
       // TODO: Status node output functions.
       instance->id,
       instance->parentId);
      printf("\nIncluded Notes: %s", instance->notes);
      waitKey();
}

void outputStatus( User * user, Status * status)
{
   
      printf("\nUser: %s -> Status\n", getUserName(user));
      puts("***************");
      printf("Status node address: %p\n", status);
      printf("Status Name: %s \nStatus ID: %d\nStatus Pid: %d",
       // TODO: Status node output functions.
       status->name,
       status->id,
       status->parentId);
      printf("\nIncluded Notes: %s", status->notes);
      waitKey();
}

void outputUser( User * user )
{
      printf("\nUser: ");
      puts(getUserName(user));
      printf("User Node Address: %p\n", user);
      printf("id: %d - pid: %d\n", 
       getUserId(user),
       getUserParentId(user));

      printf("\nUser: %s -> Data\n", user->name);
      puts("***************");
      printf("Data node address: %p\n", user->data);

      printf("NumberOfNodes: %d\n"\
       "NumberOfStatusNodes: %d\n"\
       "NumberOfInstanceNodes: %d\n",
       user->data->numberOfNodes, 
       user->data->numberOfStatusNodes, 
       user->data->numberOfInstanceNodes);
      puts("***************");
      waitKey();
}

void outputMeta (User * user )
{
      printf("\nUser: %s -> Meta\n", user->name);
      puts("***************");
      printf("Meta node address: %p\n", user->meta);
      
      printf("Creation Hash: %s\n"\
       "Last Modified Hash: %s\n",
       getCreationHash(user->meta), // example: getMeta(user);
       getLastModifiedHash(user->meta));
         // TODO: modify above to user getMeta
      printf("Creation Time: %lld\n"\
       "Last Modified Time: %lld\n",
       getCreationTime(user->meta),
       getModificationTime(user->meta));
      puts("***************");
      waitKey();
}

int menu( void )
{
   printSpace(1);
   printLine( strlen(BANNER), '*');
   puts(BANNER);
   printLine( strlen(BANNER) , '*');
   puts(" Options: ");
   printLine(9,'-');
   puts(" 0\t-\tEnd");
   puts(" 1\t-\tNew User");
   puts(" 2\t-\tNew Status in User");
   puts(" 3\t-\tNew Instance of Status");
   puts(" 4\t-\tDelete User"); // Need delete status / instance too.
   puts(" 5\t-\tDisplay");
   puts(" 6\t-\tDetailed Display");
   puts(" 7\t-\tSelect User");
   puts(" 8\t-\tSelect Status");
   
   // Need Delete User
   // Need display all. 

   printSpace(2);
   
   printf("Enter Selection: ");
   int selection = prompt(PROMPT);

   return selection; 
}

int prompt ( char * str )
{
   printf("%s ", str);
   int selection = 0;
   scanf("%d", &selection); 
   return selection; 
}

void printSpace ( int numberOfSpaces )
{
   int i = 0;
   // demo module, but still alot of syscalls.
   for ( i = 0; i < numberOfSpaces; i++)
      printf("\n");
}

void printLine ( int numberOfStars, char character)
{
   int i = 0;
   for (i = 0 ; i < numberOfStars; i++)
   {
      printf("%c", character);
   }
   printf("%c", '\n');
}

// This is apart of the menu function, so it can interact with the user.
User * makeNewUser( User * user)
{
   char buffer[128];
   User *uPtr = NULL;
    
   // this clear acts up on some platforms. (debian)
//   scanf("%c", buffer[0]); // Clear stdin. 
   printf("Please Enter the User's name: ");
   prompt(PROMPT);
   fgets(buffer, 127, stdin);
   newlineStrip(buffer);

   // TODO:
   // Create input validation, however this is a simple test sourcefile. it
   // might be a better idea to make these their own module at that point.

   if (user != NULL)
      addUser(getLastUser(user), buffer);

   return uPtr;
}

Status * makeNewStatus( Status * status)
{
      char buffer[128];
      char notes_buffer[128]; // Testing only, notes can be much larger.

      printf("Please Enter status Name.");
      prompt(PROMPT);
      fgets (buffer, 127, stdin);
      printf("Please Enter status Info.");
      prompt(PROMPT);
      fgets (notes_buffer, 127, stdin);

      addStatus(status, buffer, notes_buffer);

      return getLastStatus(status);
}

void makeNewInstance( Status * status)
{
   // Continue debugging from here.
   // omitting getLastInstance for now.

	char buffer[128];
	char notes_buffer[128]; // Testing only, notes can be much larger.
	printf("Please Enter Instance Name.");
	prompt(PROMPT);
	fgets (buffer, 127, stdin);
	printf("Please Enter Instance Info.");
	prompt(PROMPT);
	fgets (notes_buffer, 127, stdin);

	Instance * instance = getLastInstance(status->instance);
	instance->next = createInstance(instance, buffer);
}

void display(User *user)
{
   // Seems to still segfault if user is deleted.
   if ( user != NULL )
   {
      puts("\n");
      printLine(11, '-');
      printf("User: ");
      puts(getUserName(user));
      printf("User Node Address: %p\n", user);
      printf("id: %d - pid: %d\n", 
       getUserId(user),
       getUserParentId(user));
      printLine(11, '-');
   }
}

Status * selectStatus(User *user)
{
   Status *status = NULL;

   if ( user != NULL )
   {
      puts("Please Enter Status Id.");      
      int selection = (int) prompt(PROMPT);
      status = getStatus(user, selection);      
   } 

   return status;
}

Status * selectStatusName(User *user)
{
   Status *status = NULL;

   if ( user != NULL )
   {
      puts("Please Enter Status name.");      
      prompt(PROMPT);
      char buffer[128];
      fgets(buffer,127,stdin);

      status = getStatusByName(user->status, buffer);      
      printf("Debug: %s", user->status->name);
   } 

   return status;
}

User * selectUser( User * user) {

   User * userPtr = NULL;
      
   if (user != NULL)
   { 
      puts("\n");
      printLine(21, '*');
      puts("Node Selection Menu");
      printLine(21, '*');
      puts("1\t-\tSelect Node By Id");
      puts("2\t-\tSelect Node By Name");

      short int selection = prompt(PROMPT);
      
      if ( selection == 1)
      {
    puts("Please Enter Node Id");
    int nodeId = prompt(PROMPT);

    userPtr = getUser(user, nodeId);
    if ( userPtr == NULL )
    {
       printSpace(2); 
       printLine( strlen(BANNER), '*');
       printf("Node with id: %d, not found\n", nodeId);
       printLine( strlen(BANNER), '*');
    }
      }
      else if ( selection == 2)
      {
    char buffer[128];
    printf("\nEnter The Name: ");
    prompt(PROMPT);
    fgets(buffer, 127, stdin);

    newlineStrip(buffer);
    userPtr = getUserByName(user, buffer);

    if (userPtr == NULL)
       // TODO: This needs to be built into the library.
       fprintf(stderr, "Node with userName %s, not found\n", buffer);
      }
      else
    puts("Invalid");
   }

   return userPtr; // Return found node.
}


/**************************************************************************
 *
 * TODO:
 *
 * I am creating a small block of comments on what needs to be done to the
 * menu system to make it work well.
 *
 * So far it creates a user, we need to add a function that searches
 * for a specific user in the linked list and sets it as being modified.
 *
 * This will then be the user that is being worked on. 
 * 
 * From this point we can add, subtract and modify elements of that specific
 * user. For example we can add status nodes, we can add instances of that
 * status and menu should also provide a method for deleteing elements
 * as well.  
 *
 * For now try and create the functions required to display all the users
 * internal datas.
 *
 **************************************************************************/

/*
 * TODO:
 *     getStatus functions inside of userQuery need to be
 *     modified to work from a user pointer not from  
 *     userPtr -> status. This complicates things unnecesarily.


   // Bug avoidance.
/*
   userPtr = NULL;
   if (deleteUser(user ,0) < 0)
   {
      exit(1);
   }
   */

   /*
   Data * dataPtr = getUserDataNode(userPtr);
   Meta * metaPtr = getUserMetaNode(userPtr);
   Status * statusPtr = getUserStatusNode(userPtr);
   */
/*
 * unused Code from main menu:
 *
   case 6:
      // Select user in the menu?
      if ( user == NULL )
         userPtr = selectUser(user);
      if (userPtr != NULL)
      {
         detailDisplay(userPtr); // show options to output internals.
      }
      break;
*/
