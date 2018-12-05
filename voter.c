/*

  File: voter.c

  Abstract:

    Voter handling implementation

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "voter.h"


/*
 * Types
 */
typedef struct _Voter
{
    char* pName;
    char* pParty;
    int ID;

    struct _Voter* pNext;
} Voter;


/*
 * Statics
 */
static Voter* VoterList = NULL;
static Voter* PrevVoter  =NULL;
static int malloc_fail=0;

/*

  Function: FixLetters

  Abstract:

    fix any word,first letter be a Capital and the others low
  Parameters:

    word-pointer to the word

  Returns: --

*/

void FixLetters(char* word)
{
	int i=0;
	while (*(word+i)!='\0')
	{
		if (i==0){
			  if ((*(word+i) >= 97) && (*(word+i) <= 122)){
					*(word+i) = *(word+i) - 32;
			  }
		}
		else{
			if ((*(word+i) >= 65) && (*(word+i) <= 90)){
					*(word+i) = *(word+i) + 32;
			  }
		}
		i++;
	}
}

/*

  Function: Make_Voter

  Abstract:

    allocate memory fot the new voter name and copy the full name
  Parameters:

    word-pointer to the word

  Returns: pointer for the new voter name

*/
char* Make_Voter(char* pName, char* pSurname)
{
    //int malloc_fail=0;
	char space_=' ';
	int surname_size=0,name_size=0,length=0;//ask yonatan about the sizes
	surname_size = strlen(pSurname);
	name_size	 = strlen(pName);
	length=surname_size+name_size+2;//2= 1 for space and 1 for \0
	FixLetters(pName);
	FixLetters(pSurname);
	//malloc for new name voter
	char* Name_Voter=(char*)malloc(sizeof(char)*(length));//not forget free this at the function//
	if(Name_Voter==NULL){
		malloc_fail=1;
		return NULL;
	}
	//copy the name to the place
	strcpy(Name_Voter,pName);
	strcpy(Name_Voter+name_size,&space_);
	strcpy(Name_Voter+name_size+1,pSurname);

	return Name_Voter;

}
/*

  Function: sort

  Abstract:

    sort the list according the ID from high to low
  Parameters:

    refrence- pointer to the head of the list
	Cur		- pointer for the new voter

  Returns: --

*/

void sort(Voter* refrence,Voter* Cur){//accualy refrence is the head/start of the list
	if (refrence->pNext==NULL) return;

	Voter* tmp;
	Voter* OldCmpr;
	Voter* CurToCmp=refrence;

	int Head=1;//indicate if the new ID bigger then the head -- 1 yes, 0 no
	while(CurToCmp->ID < Cur->ID ){
		OldCmpr=CurToCmp;
		CurToCmp=CurToCmp->pNext;
		Head=0;
	}

	 if (CurToCmp->ID == Cur->ID){

		 return;
	 }
	 tmp=CurToCmp;
	 if(Head==0){
	 OldCmpr->pNext=Cur;
	 Cur->pNext=CurToCmp;
	 }
	 else{
		VoterList=Cur;
		VoterList->pNext=tmp;
	 }

	while(tmp->pNext!= Cur){
			tmp=tmp->pNext;
			}

		tmp->pNext=NULL;
		PrevVoter=tmp;

	 return;
}





/*

  Function: AddVoter

  Abstract:

    Adds a new voter to the database

  Parameters:

    pName    - The voter's name
    pSurname - The voter's surname
    ID		 - The voter's ID (assumed to be unique)
    pParty   - The voter's vote (assumed NOT to be changed)

  Returns: --

*/
void AddVoter(char* pName, char* pSurname, int ID, char* pParty)
{

	Voter* new_voter=(Voter*)malloc(sizeof(Voter));
	if(new_voter==NULL) return;

	if (VoterList==NULL)
	{
		VoterList= new_voter;
		PrevVoter = new_voter;
	}
	else
	{
		PrevVoter->pNext=new_voter;
		PrevVoter=new_voter;
	}

	new_voter->pName=Make_Voter( pName,  pSurname);
	if (malloc_fail==1){
		free(new_voter);
		malloc_fail=0;
		return;
	}
	new_voter->ID=ID;
	new_voter->pParty=pParty;
	new_voter->pNext=NULL;
	sort(VoterList,new_voter);

}


/*

  Function: FreeVoters

  Abstract:

    Frees all memory in the voter data-base

*/
void FreeVoters()
{
	Voter* tmp;
	while(VoterList){
		tmp=VoterList->pNext;
		free(VoterList->pName);//free the malloc for name
		free(VoterList);       //free the malloc for the node
		VoterList=tmp;
	}

}


/*

  Function: PrintVoters

  Abstract:

    Prints all registered voters

*/
void PrintVoters()
{
    Voter* pVoter;

    printf("Registered voters\n");
    printf("-----------------\n");

    /*
     * Iterate the voter list and print the details of each voter
     */
    for (pVoter = VoterList; pVoter; pVoter = pVoter->pNext)
    {
        printf("ID:%d Name:%s Vote:%s\n", pVoter->ID, pVoter->pName, pVoter->pParty);
    }
    printf("\n");
}


/*void sort_after_debug(Voter* refrence,Voter* Cur){//accualy refrence is the head/start of the list
	if (refrence->pNext==NULL){
        printf("first voter");//debug mode
        printf("Head voter ID is :%d\n",refrence->ID );
        PrintVoters();
        return;
	}
	else
    {
     printf("not first voter\n");//debug mode
    }
	Voter* tmp;
	Voter* OldCmpr;
	Voter* CurToCmp=refrence;
    printf("new voter ID is :%d\n",Cur->ID);
    printf("Head voter ID is :%d\n",CurToCmp->ID );
	int Head=1;//indicate if the new ID bigger then the head -- 1 yes, 0 no
	while(CurToCmp->ID < Cur->ID ){
		OldCmpr=CurToCmp;
		CurToCmp=CurToCmp->pNext;
		printf("OldCmpr is :%d\n",OldCmpr);
		printf("CurToCmp is :%d\n",CurToCmp);
		Head=0;
	}
	printf("Head is :%d\n",Head);
	 if (CurToCmp->ID == Cur->ID){
        PrintVoters();
		 return;
	 }
	 tmp=CurToCmp;
	 if(Head==0){
     printf("OldCmpr->pNext is:%d\n",OldCmpr->pNext) ;
	 OldCmpr->pNext=Cur;
	 Cur->pNext=CurToCmp;
	 printf(" Cur->pNext is:%d\n",Cur->pNext) ;

	 }
	 else{
        printf("tmp suppose to be if Head=1 the Voter list'tmp is :%d\n",tmp);
        printf("the cur voter address is:%d\n",Cur);
        printf("refrence is headlist befor hasama is :%d\n",VoterList);
		VoterList=Cur;
		printf("refrence in our case is the head :%d\n",VoterList);
		VoterList->pNext=tmp;
		printf("After sort the head list is:%d\n",VoterList);
	   printf("the head list point to :%d\n",VoterList->pNext);
	 }
    printf("tmp->pNext is:%d\n",tmp->pNext);
	while(tmp->pNext!= Cur){

            printf("tmp->pNext is:%d\n",tmp->pNext);
			tmp=tmp->pNext;
			printf("tmp is:%d\n",tmp);
			}

		tmp->pNext=NULL;
		PrevVoter=tmp;
		printf("tmp->pNext is:%d\n",tmp->pNext);
        PrintVoters();
	 return;
}

*/




