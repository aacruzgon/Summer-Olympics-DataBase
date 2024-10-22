#ifndef SPORT_DB_RELATIONSHIP_H
#define SPORT_DB_RELATIONSHIP_H

#include "sport_db_event.h"
#include "sport_db_athlete.h"

// Structure to represent the relationship between events and athletes
typedef struct {
    int relationshipCode; // Add unique relationship code
    int eventCode;
    int athleteCode;
} event_athlete_code;

struct nodeRelationship {
    event_athlete_code relationship;
    struct nodeRelationship *next;
};

// RELATIONSHIP UI
#define RELATIONSHIP_BASIC_UI() \
    do { \
        printf("-------------------------------\n"); \
        printf("|    2211 Summer Olympics!    |\n"); \
        printf("|-----------------------------|\n"); \
        printf("| New Relationship |    i     |\n"); \
        printf("|------------------|----------|\n"); \
        printf("| Search Relation  |    s     |\n"); \
        printf("|------------------|----------|\n"); \
        printf("| Print Relations  |    p     |\n"); \
        printf("|------------------|----------|\n"); \
        printf("| Events for Athl  |    ea    |\n"); \
        printf("|------------------|----------|\n"); \
        printf("| Athls for Event  |    ae    |\n"); \
        printf("|------------------|----------|\n"); \
        printf("| Erase Relation   |    e     |\n"); \
        printf("|------------------|----------|\n"); \
        printf("| Dump Relations   |    d     |\n"); \
        printf("|------------------|----------|\n"); \
        printf("| Restore Relations|    r     |\n"); \
        printf("-------------------------------\n"); \
    } while(0)


// Function prototypes
void insertRelationship(struct nodeEvent *eventHead, struct nodeAthlete *athleteHead, struct nodeRelationship **relationshipHead);
void printRelationships(struct nodeRelationship *relationshipHead);
int searchRelationship(struct nodeRelationship *relationshipHead);
void printEventsForAthlete(struct nodeEvent *eventHead, struct nodeRelationship *relationshipHead);
void printAthletesForEvent(struct nodeAthlete *athleteHead, struct nodeRelationship *relationshipHead);
void removeRelationship(struct nodeRelationship **relationshipHead);
int checkRelationship(int eventCode, int athleteCode, struct nodeRelationship *relationshipHead);
void restoreRelationships(struct nodeRelationship **relationshipHead);
void dumpRelationships(struct nodeRelationship *relationshipHead);

#endif // SPORT_DB_RELATIONSHIP_H
