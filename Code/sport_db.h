#ifndef SPORT_DB_H
#define SPORT_DB_H

#include "sport_db_event.h"
#include "sport_db_athlete.h"
#include "sport_db_relationship.h"



//defining basic MAIN UI
#define MAIN_BASIC_UI() \
    do { \
        printf("-----------------------------------\n"); \
        printf("|              Commands           |\n"); \
        printf("|---------------------------------|\n"); \
        printf("| Help                 |    h     |\n"); \
        printf("|----------------------|----------|\n"); \
        printf("| Quit                 |    q     |\n"); \
        printf("|----------------------|----------|\n"); \
        printf("| Control Events       |    e     |\n"); \
        printf("|----------------------|----------|\n"); \
        printf("| Control Athletes     |    a     |\n"); \
        printf("|----------------------|----------|\n"); \
        printf("| Manage Relationships |    r     |\n ");\
        printf("-----------------------------------\n"); \
    } while(0)

#define HELP() \
    do { \
        printf("Input the appropriate commands to nagivate the program.\n"); \
        printf("Control Event lets you manage the summer olympic events database.\n"); \
        printf("Control Athletes lets you manage the summer olympics athletes database.\n"); \
    }while(0)

// Function prototypes for main navigation
void manageEvents(struct nodeEvent **eventHead, struct nodeRelationship *relationshipHead);
void manageAthletes(struct nodeAthlete **athleteHead, struct nodeRelationship *relationshipHead);
void manageRelationships(struct nodeEvent *eventHead, struct nodeAthlete *athleteHead, struct nodeRelationship **relationshipHead);

#endif // MAIN SPORTS
