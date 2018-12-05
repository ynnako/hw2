/*

  File: election.c

  Abstract:

    Election application entry point

*/

//nothing else matters
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "voter.h"
#include "party.h"

#define MAX_LINE_LENGTH     256


int main() {

    char buffer[MAX_LINE_LENGTH];
	char* delimiters = " \t\n";
    char* next_token_p;
    int user_quit = 0;
	int ID ;
	char *pName,*pSurname,*pPartyName,*pPartyName_tmp;
	int i = 0;
    do {
        i = 0;
    	// Primt prompt
    	printf("> ");

    	// In case EOF is reached
        if (!fgets(buffer, MAX_LINE_LENGTH, stdin)) {
            break;
        }

        // Parse next command
        next_token_p = strtok(buffer, delimiters);

        switch (*next_token_p) {
		// ADD <name> <surname> <ID> <party>
        case 'A':

			while (next_token_p !=NULL){
				next_token_p = strtok(NULL, delimiters);

				if ( i == 0 ) pName=next_token_p;
				else if ( i == 1 ) pSurname=next_token_p;
				else if ( i == 2 )
                {
                     ID = atoi(next_token_p);
                }
				else if ( i == 3 ) pPartyName= next_token_p;
				i++;
			}
			pPartyName_tmp=AddVote( pPartyName);
			if (pPartyName_tmp!=NULL)
			{
				AddVoter( pName,  pSurname , ID , pPartyName_tmp);

			}
            break;

        // Print (Voters or Results)
        case 'P':

            next_token_p = strtok(NULL, delimiters);

            if (*next_token_p == 'V') {
	            PrintVoters();
            } else {
	            PrintResult();
            }

            break;

        // Handle quit
        case 'Q':
        	user_quit = 1;
        	break;
        }

    } while(!user_quit);

    // Free allocated data
    FreeVoters();
    FreeParties();

    return 0;
}
