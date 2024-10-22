#include <stdio.h>
#include <stdlib.h>
#include "sport_db_relationship.h"

void insertRelationship(struct nodeEvent *eventHead, struct nodeAthlete *athleteHead, struct nodeRelationship **relationshipHead) {
    int eventCode, athleteCode, relationshipCode;

    printf("Enter the relationship code: ");
    scanf("%d", &relationshipCode);

    // Check if the relationship code is unique
    struct nodeRelationship *current = *relationshipHead;
    while (current != NULL) {
        if (current->relationship.relationshipCode == relationshipCode) {
            printf("Relationship code already exists. Please use a unique code.\n");
            return;
        }
        current = current->next;
    }

    printf("Enter the event code: ");
    scanf("%d", &eventCode);
    printf("Enter the athlete code: ");
    scanf("%d", &athleteCode);

    // Check if the event exists
    if (find_event_node(eventCode, eventHead) == NULL) {
        printf("Event with code %d does not exist.\n", eventCode);
        return;
    }

    // Check if the athlete exists
    if (find_athlete_node(athleteCode, athleteHead) == NULL) {
        printf("Athlete with code %d does not exist.\n", athleteCode);
        return;
    }

    if (checkRelationship(eventCode, athleteCode, *relationshipHead)) {
        printf("This relationship already exists.\n");
        return;
    }

    struct nodeRelationship *newNode = calloc(1, sizeof(struct nodeRelationship));
    if (newNode == NULL) {
        perror("Error allocating memory");
        return;
    }

    newNode->relationship.eventCode = eventCode;
    newNode->relationship.athleteCode = athleteCode;
    newNode->relationship.relationshipCode = relationshipCode; // Assign user-provided relationship code

    newNode->next = *relationshipHead;
    *relationshipHead = newNode;

    printf("Relationship added successfully.\n");
}


// Function to print all event-athlete relationships
void printRelationships(struct nodeRelationship *relationshipHead) {
    struct nodeRelationship *current = relationshipHead;

    printf("Relationship Code | Event Code | Athlete Code\n");
    printf("---------------------------------------------\n");
    while (current != NULL) {
        printf("%17d | %10d | %12d\n", current->relationship.relationshipCode, current->relationship.eventCode, current->relationship.athleteCode);
        current = current->next;
    }
}


// Function to search for a specific event-athlete relationship by relationship code
int searchRelationship(struct nodeRelationship *relationshipHead) {
    int relationshipCode;

    printf("Enter the relationship code: ");
    scanf("%d", &relationshipCode);

    struct nodeRelationship *current = relationshipHead;
    while (current != NULL) {
        if (current->relationship.relationshipCode == relationshipCode) {
            printf("Relationship found\nRelationship Code: %d\nEvent Code: %d\nAthlete Code: %d\n",
                   relationshipCode, current->relationship.eventCode, current->relationship.athleteCode);
            return 1;
        }
        current = current->next;
    }
    printf("Relationship not found.\n");
    return 0;
}

// Function to print all events for a specific athlete
void printEventsForAthlete(struct nodeEvent *eventHead, struct nodeRelationship *relationshipHead) {
    int athleteCode;

    printf("Enter the athlete code: ");
    scanf("%d", &athleteCode);

    struct nodeRelationship *current = relationshipHead;
    printf("Events for Athlete Code %d:\n", athleteCode);
    while (current != NULL) {
        if (current->relationship.athleteCode == athleteCode) {
            struct nodeEvent *event = find_event_node(current->relationship.eventCode, eventHead);
            if (event != NULL) {
                printf("Event Code: %d | Event Name: %s | Competitors: %d | Gender: %c\n",
                    event->newEvent.eventCode,
                    event->newEvent.name,
                    event->newEvent.count,
                    event->newEvent.gender);
            }
        }
        current = current->next;
    }
}


// Function to print all athletes for a specific event
void printAthletesForEvent(struct nodeAthlete *athleteHead, struct nodeRelationship *relationshipHead) {
    int eventCode;

    printf("Enter the event code: ");
    scanf("%d", &eventCode);

    struct nodeRelationship *current = relationshipHead;
    printf("Athletes for Event Code %d:\n", eventCode);
    while (current != NULL) {
        if (current->relationship.eventCode == eventCode) {
            struct nodeAthlete *athlete = find_athlete_node(current->relationship.athleteCode, athleteHead);
            if (athlete != NULL) {
                printf("Athlete Code: %d | Athlete Name: %s | Age: %d | Nationality: %s\n",
                    athlete->newAthlete.athleteCode,
                    athlete->newAthlete.name,
                    athlete->newAthlete.age,
                    athlete->newAthlete.nationality);
            }
        }
        current = current->next;
    }
}

// Function to remove a specific event-athlete relationship by relationship code
void removeRelationship(struct nodeRelationship **relationshipHead) {
    int relationshipCode;

    printf("Enter the relationship code: ");
    scanf("%d", &relationshipCode);

    struct nodeRelationship *current = *relationshipHead;
    struct nodeRelationship *previous = NULL;

    while (current != NULL) {
        if (current->relationship.relationshipCode == relationshipCode) {
            if (previous == NULL) {
                *relationshipHead = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            printf("Relationship removed successfully.\n");
            return;
        }
        previous = current;
        current = current->next;
    }
    printf("Relationship not found.\n");
}


// Function to check if a relationship exists
int checkRelationship(int eventCode, int athleteCode, struct nodeRelationship *relationshipHead) {
    struct nodeRelationship *current = relationshipHead;

    while (current != NULL) {
        if (current->relationship.eventCode == eventCode && current->relationship.athleteCode == athleteCode) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// Function to dump relationships to a file
void dumpRelationships(struct nodeRelationship *relationshipHead) {
    char filename[100];
    printf("Enter the output file name: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }

    struct nodeRelationship *current = relationshipHead;
    while (current != NULL) {
        fwrite(&current->relationship, sizeof(event_athlete_code), 1, file);
        current = current->next;
    }

    fclose(file);
    printf("Relationships successfully dumped to %s\n", filename);
}

// Function to restore relationships from a file
void restoreRelationships(struct nodeRelationship **relationshipHead) {
    char filename[100];
    printf("Enter the input file name: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file for reading");
        return;
    }

    event_athlete_code newRelationship;
    while (fread(&newRelationship, sizeof(event_athlete_code), 1, file)) {
        struct nodeRelationship *newNode = calloc(1, sizeof(struct nodeRelationship));
        if (newNode == NULL) {
            perror("Error allocating memory");
            fclose(file);
            return;
        }
        newNode->relationship = newRelationship;
        newNode->next = *relationshipHead;
        *relationshipHead = newNode;
    }

    fclose(file);
    printf("Relationships successfully restored from %s\n", filename);
}
