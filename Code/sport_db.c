
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "sport_db.h"


int main(void) {
    struct nodeEvent *eventHead = NULL; // Event head
    struct nodeAthlete *athleteHead = NULL; // Athlete head
    struct nodeRelationship *relationshipHead = NULL; // Relationship head

    char inputCommand;

    while (1) {
        MAIN_BASIC_UI();
        printf("Input the desired command: ");
        scanf(" %c", &inputCommand);
        inputCommand = toupper(inputCommand);

        if (inputCommand == 'Q') {
            break;
        }

        switch (inputCommand) {
            case 'H':
                HELP();
                break;
            case 'E':
                manageEvents(&eventHead, relationshipHead);
                break;
            case 'A':
                manageAthletes(&athleteHead, relationshipHead);
                break;
            case 'R':
                manageRelationships(eventHead, athleteHead, &relationshipHead);
                break;
            default:
                printf("Invalid command. Please try again.\n");
        }
    }

    return 0;
}

void manageEvents(struct nodeEvent **eventHead, struct nodeRelationship *relationshipHead) {
    char inputCommand;

    while (1) {
        EVENT_BASIC_UI();
        printf("Input the desired command: ");
        scanf(" %c", &inputCommand);
        inputCommand = toupper(inputCommand);

        if (inputCommand == 'Q') {
            break;
        }

        switch (inputCommand) {
            case 'I':
                insertEvent(eventHead);
                break;
            case 'S':
                searchEvent(*eventHead);
                break;
            case 'U':
                updateEvent(*eventHead);
                break;
            case 'P':
                printEvents(*eventHead);
                break;
            case 'E':
                eraseEvent(eventHead, relationshipHead);
                break;
            case 'D':
                dumpEvents(*eventHead);
                break;
            case 'R':
                restoreEvents(eventHead);
                break;
            default:
                printf("Invalid command. Please try again.\n");
        }
        break;
    }
}

void manageAthletes(struct nodeAthlete **athleteHead, struct nodeRelationship *relationshipHead) {
    char inputCommand;

    while (1) {
        ATHLETE_BASIC_UI();
        printf("Input the desired command: ");
        scanf(" %c", &inputCommand);
        inputCommand = toupper(inputCommand);

        if (inputCommand == 'Q') {
            break;
        }

        switch (inputCommand) {
            case 'I':
                insertAthlete(athleteHead);
                break;
            case 'S':
                searchAthlete(*athleteHead);
                break;
            case 'U':
                updateAthlete(*athleteHead);
                break;
            case 'P':
                printAthletes(*athleteHead);
                break;
            case 'E':
                eraseAthlete(athleteHead, relationshipHead);
                break;
            case 'D':
                dumpAthletes(*athleteHead);
                break;
            case 'R':
                restoreAthletes(athleteHead);
                break;
            default:
                printf("Invalid command. Please try again.\n");
        }
        break;
    }
}

void manageRelationships(struct nodeEvent *eventHead, struct nodeAthlete *athleteHead, struct nodeRelationship **relationshipHead) {
    char inputCommand[3];

    while (1) {
        RELATIONSHIP_BASIC_UI();
        printf("Input the desired command: ");
        scanf("%2s", inputCommand);
        inputCommand[0] = toupper(inputCommand[0]);
        inputCommand[1] = toupper(inputCommand[1]);

        if (strcmp(inputCommand, "Q") == 0) {
            break;
        }

        if (strcmp(inputCommand, "I") == 0) {
            insertRelationship(eventHead, athleteHead, relationshipHead);
        } else if (strcmp(inputCommand, "S") == 0) {
            searchRelationship(*relationshipHead);
        } else if (strcmp(inputCommand, "P") == 0) {
            printRelationships(*relationshipHead);
        } else if (strcmp(inputCommand, "EA") == 0) {
            printEventsForAthlete(eventHead, *relationshipHead);
        } else if (strcmp(inputCommand, "AE") == 0) {
            printAthletesForEvent(athleteHead, *relationshipHead);
        } else if (strcmp(inputCommand, "E") == 0) {
            removeRelationship(relationshipHead);
        } else if (strcmp(inputCommand, "D") == 0) {
            dumpRelationships(*relationshipHead);
        } else if (strcmp(inputCommand, "R") == 0) {
            restoreRelationships(relationshipHead);
        } else {
            printf("Invalid command. Please try again.\n");
        }
        break;
    }
}
