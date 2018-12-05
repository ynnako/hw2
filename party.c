/*

  File: party.c

  Abstract:

    Party handling implementation

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "party.h"

#define MAX_PARTY_NAME      20
#define EXIST				1
#define NOT_EXIST			0
#define VALID_NAME			1
#define UNVALID_NAME	    0

/*
 * Types
 */
typedef struct _Party
{
    char Party[MAX_PARTY_NAME];
    unsigned long NumVoters;

    struct _Party* pNext;
} Party;


/*
 * Prototypes
 */
void PrintError(char* pPartyName);


/*
 * Statics
 */
static Party* PartyList = NULL;
static Party* PrevParty = NULL;

/*

  Function: CheckLegalName

  Abstract:

   check if the party name is valid

  Parameters:

    pPartyName - pointer to party name

  Returns: EXIST or NOT;

*/


int CheckLegalName(char* pPartyName)
{
	char _char='-';
	char* tmp=pPartyName;
	while(*tmp!='\0'){
		tmp=strchr(tmp,_char);
		if(tmp==NULL){
			return VALID_NAME;
		}
		if(*(tmp+1)<65 || *(tmp+1)>90 ||*(tmp+1)=='\0'){
			return UNVALID_NAME;
		}
		tmp++;
	}
    return VALID_NAME;
}
/*

  Function: PartyAlRdyExist

  Abstract:

  check if the party name is already exist ,if yes add 1 to number of voters  and return the party name pointer

  Parameters:

    pPartyName - pointer to party name
	partylist  - pointer to the partylist

  Returns: pointer to party name when already exist else NULL;

*/

char* PartyAlRdyExist	(char* pPartyName,Party* partylist){
	if (partylist ==NULL) return NULL;
	Party* tmp=partylist;
	while (tmp) {
		if (strcmp(pPartyName,tmp->Party)==0)
		{
		(tmp->NumVoters)++;
    return tmp->Party;
		}
		tmp=tmp->pNext;
	}
return NULL;
}

/*

  Function: AddtoHead

  Abstract:

  add the new party to the head list

  Parameters:

    new_party-pointer to the new party struct


  Returns:

*/



void AddtoHead(Party* new_party)
{
 //if (new_party->pNext==NULL) return;
 if (new_party==PartyList) return;
Party* tmp= PartyList;
 PartyList=new_party;
 PartyList->pNext=tmp;

 while(tmp->pNext != new_party){
	 tmp=tmp->pNext;
 }
tmp->pNext=NULL;
PrevParty=tmp;

}



/*

  Function: AddVote

  Abstract:

    Records the chosen party of a voter

  Parameters:

    pPartyName - The party that received the vote

  Returns: A pointer to the party name that is guaranteed to stay constant until 'FreeParties'
           is called. If the party name is illegal, we fail the operation and return NULL.

*/
char* AddVote(char* pPartyName)
{
	if (CheckLegalName(pPartyName)==UNVALID_NAME)
	{
		PrintError(pPartyName);
		return NULL;
	}
	char* PointerToPartyName=PartyAlRdyExist( pPartyName,PartyList);
	if (PointerToPartyName !=NULL)
	{
		return PointerToPartyName;
	}

	Party* new_party=(Party*)malloc(sizeof(Party));
	if(new_party==NULL) return NULL;
	if(PartyList==NULL)
	{
		PartyList=new_party;
		PrevParty=new_party;
	}
	else
	{
		PrevParty->pNext=new_party;
		PrevParty=new_party;
	}

	strcpy(new_party->Party,pPartyName);//check if :new_party->Party is the array pointer and valid if after the last letter '\0' appears
	new_party->NumVoters=1;
	new_party->pNext=NULL;

	AddtoHead(new_party);

	return new_party->Party;//pointer to the array start

}


/*

  Function: FreeParties

  Abstract:

    Frees all memory in the party database

*/
void FreeParties()
{
	Party* tmp;
	while(PartyList!=NULL){
		tmp=PartyList->pNext;
		free(PartyList);       //free the malloc for the party node
		PartyList=tmp;
	}


}


/*

  Function: PrintResult

  Abstract:

    Reports the election result so far

*/
void PrintResult()
{
    Party* pParty;

    printf("Election results\n");
    printf("----------------\n");

    /*
     * Iterate the party list and print the current number of voters for each party
     */
    for (pParty = PartyList; pParty; pParty = pParty->pNext)
        printf("Party:%s Number of voters:%ld\n", pParty->Party, pParty->NumVoters);
    printf("\n");
}


void PrintError(char* pPartyName)
{
    printf("ERROR: '%s' is a bad party name\n", pPartyName);
}
