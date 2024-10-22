#ifndef SPORT_DB_EVENT_H
#define SPORT_DB_EVENT_H

#include <stdbool.h>
// Forward declaration
struct nodeRelationship;

#define MAX_LENGTH 50 // events name maximum acceptable length

// Declaring structure that holds the sporting event details
typedef struct {
    int eventCode;  // event code
    char name[MAX_LENGTH]; // event name
    int count;  // number of competitors/athletes/teams
    char gender; // gender of the event
} event;

// Node structure for node events
struct nodeEvent {
    event newEvent;
    struct nodeEvent *next;
};

#define EVENT_BASIC_UI() \
    do { \
        printf("----------------------------\n"); \
        printf("|   2211 Summer Olympics!  |\n"); \
        printf("|--------------------------|\n"); \
        printf("| New Event     |    i     |\n"); \
        printf("|---------------|----------|\n"); \
        printf("| Search Event  |    s     |\n"); \
        printf("|---------------|----------|\n"); \
        printf("| Update Event  |    u     |\n"); \
        printf("|---------------|----------|\n"); \
        printf("| Print Events  |    p     |\n"); \
        printf("|---------------|----------|\n"); \
        printf("| Erase Event   |    e     |\n"); \
        printf("|---------------|----------|\n"); \
        printf("| Dump Events   |    d     |\n"); \
        printf("|---------------|----------|\n"); \
        printf("| Restore Events|    r     |\n"); \
        printf("----------------------------\n"); \
    } while(0)

// Multiparameter macro definition for printing
#define PRINT_HEADER(eventCodeWidth, maxNameWidth, countWidth, genderWidth) \
    printf("%*s     %-*s     %*s     %*s\n", eventCodeWidth, "Event Code", maxNameWidth, "Event Name", countWidth, "Competitors", genderWidth, "Gender")
#define PRINT_ROW(node, eventCodeWidth, eventNameWidth, countWidth, genderWidth) \
    printf("%*d          %-*s     %*d     %8c\n", eventCodeWidth - 5, (node)->newEvent.eventCode, eventNameWidth, (node)->newEvent.name, countWidth - 5, (node)->newEvent.count, (node)->newEvent.gender)

// Function prototypes
struct nodeEvent* createNode(event newEvent);
struct nodeEvent* find_event_node(int code, struct nodeEvent *head);
void insertEvent(struct nodeEvent **head);
void searchEvent(struct nodeEvent *head);
void updateEvent(struct nodeEvent *head);
void printEvents(struct nodeEvent *head);
void eraseEvent(struct nodeEvent **eventHead, struct nodeRelationship *relationshipHead);
void dumpEvents(struct nodeEvent *eventHead);
void restoreEvents(struct nodeEvent **eventHead);

#endif // SPORT_DB_EVENT_H
