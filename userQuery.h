/*
 * 	Functions that makle it easier to extract data's from
 * 	the linked lists. 
 * 	These can be a bit more specific in the datas each
 * 	of these functions return.
 *
 * 	Think of all the possible elements of interest
 * 	within the linked lists that would be interesting
 * 	to have access to. maybe even change this module
 * 	to include possible modifiers.
 *
 * 	Note the block style comments that denote each section.
 * 	Great way to make each section totally clear. However
 * 	can be difficult to maintain,
 * 		- Need comment policy
 *
 * 	MIT License
 * 	Copyright (c) 2018 ElliePenguins 
 */

#ifndef USER_QUERIES_H_
#define USER_QUERIES_H_


/* 	User node queries	*
 ********************************/

char * getUserName(User*);
int getUserId(User*);
int getUserParentId(User*);

char * getStatusName(Status*);

Data * getUserData(User*);
Meta * getUserMeta(User*);
Status * getUserStatus(User*);

// Easy way to get the next node?
User * getNextUser(User*);
Status * getNextStatus(Status*);
Instance * getNextInstance(Instance*); // this one will be interesting.

User* getLastUser(User*);
Status * getLastStatus(Status*);
Instance * getLastInstance(Instance*);

// * Count Actual Nodes *
// **********************
int countUser(User * user);
int countStatus(Status * status);
int countInstance(User * status);


/*	Data Node Queries	*
 ********************************/

// Use the above functions to get Data nodes.
time_t getDataTime(Data *);
Meta * getDataMetaNode(Data *);
int getNumberNodes(Data *);
int getNumberStatusNodes(Data *);
int getNumberInstanceNodes(Data *);

/*	Meta Node Queries	*
 ********************************/

char * getCreationHash(Meta *);
char * getLastModifiedHash(Meta *);
time_t getCreationTime(Meta *);
time_t getModificationTime(Meta *);


#endif
