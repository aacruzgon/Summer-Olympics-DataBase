#include "sport_db_event.h"
#include "sport_db_relationship.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Function to create a new node
struct nodeEvent* createNode(event newEvent) {
    struct nodeEvent *newNode = (struct nodeEvent *)calloc(1, sizeof(struct nodeEvent));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->newEvent = newEvent;
    newNode->next = NULL;
    return newNode;
}


struct nodeEvent* find_event_node(int code, struct nodeEvent *head) {
    struct nodeEvent *current = head;
    while (current != NULL) {
        if (current->newEvent.eventCode == code) {
            return current;  // Return the pointer to the found node
        }
        current = current->next;
    }
    return NULL;  // Return NULL if the event code is not found
}

// insert a new event to the linked list of nodes
void insertEvent(struct nodeEvent **head) {

    //declaring structure variables
    int code, competitors;
    char name[MAX_LENGTH];
    char gender;

    printf("Enter the events code: ");
    scanf("%d", &code);

    // checks if the event is not in the data base
    if (find_event_node(code, *head) != NULL) {
        printf("Error: Event code must be unique.\n");
        return;
    }

    printf("Input the name of the event: ");
    scanf(" %[^\n]", name); //reads the whole line

    printf("Input the number of competitors in this event (Min: 10 Max: 99): ");
    scanf("%d", &competitors);
    // checks if competitors is within parameters
    if (competitors < 10 || competitors > 99) {
        printf("Error: Number of competitors must be between 10 and 99.\n");
        return;
    }

    printf("What is the gender of the event (M, W, or X): ");
    scanf(" %c", &gender);
    gender = toupper(gender);
    // checks if valid gender was inputed
    if (gender != 'M' && gender != 'W' && gender != 'X') {
        printf("Error: Gender must be M, W, or X.\n");
        return;
    }

    // if all parameters are valid then event structure is initialized
    event newEvent;
    newEvent.eventCode = code;
    strncpy(newEvent.name, name, MAX_LENGTH - 1);
    newEvent.name[MAX_LENGTH - 1] = '\0'; // Ensure null termination
    newEvent.count = competitors;
    newEvent.gender = gender;

    struct nodeEvent *newNode = createNode(newEvent);
    // checks if there is disposable memory for the event
    if (newNode == NULL) {
        printf("Error: Could not allocate memory for a new event.\n");
        return;
    }

    // if there's memory it will Insert the new node at the beginning of the list
    newNode->next = *head;
    *head = newNode;

    printf("Event inserted and created successfully.\n");
}


//Helper function that calculates maximum width
static int calculateMaxNameWidth(struct nodeEvent *head, char inputCommand){
    int maxWidth = strlen("Event Name");
    int nameLength;
    if (inputCommand == 'S'){
        nameLength = strlen(head->newEvent.name);
        if (maxWidth > nameLength){
            return maxWidth;
        }else{
            return nameLength;
        }
    }else{
        struct nodeEvent *current = head;
        while(current != NULL){
            nameLength = strlen(current ->newEvent.name);
            if (nameLength > maxWidth){
                maxWidth = nameLength;
            }
            current = current->next;
        }
    }
    return maxWidth;
}

// Function to search for an event by code
void searchEvent(struct nodeEvent *head) {
    int code;
    printf("Enter event code you would like to search: ");
    scanf("%d", &code);

    struct nodeEvent *current = head;
    while (current != NULL) {
        if (current->newEvent.eventCode == code) {
            int maxNameWidth = calculateMaxNameWidth(current, 'S');
            PRINT_HEADER((int) strlen("Event Code"), maxNameWidth, (int) strlen("Competitors"), (int) strlen("Gender"));
            PRINT_ROW(current, (int) strlen("Event Code"), maxNameWidth, (int) strlen("Competitors"), (int) strlen("Gender"));
        }
        current = current->next;
    }
    printf("Error: Event with code %d not found.\n", code);
}

// Function to update a desired event
void updateEvent(struct nodeEvent *head){
    int eventCode;
    printf("Enter the event code you would like to update: ");
    scanf("%d", &eventCode);

    struct nodeEvent *eventNode = find_event_node(eventCode,head);
    // if event is not in the data base return an error
    if (eventNode == NULL){
        printf("Event is not in the database.\n");
        return;
    }
    // update event struct events
    char name[MAX_LENGTH];
    int competitors;
    char gender;

    printf("Input the name of the event: ");
    scanf(" %[^\n]", name); //reads the whole line

    printf("Input the number of competitors in this event (Min: 10 Max: 99): ");
    scanf("%d", &competitors);
    // checks if competitors is within parameters
    if (competitors < 10 || competitors > 99) {
        printf("Error: Number of competitors must be between 10 and 99.\n");
        return;
    }

    printf("What is the gender of the event (M, W, or X): ");
    scanf(" %c", &gender);
    gender = toupper(gender);
    // checks if valid gender was inputed
    if (gender != 'M' && gender != 'W' && gender != 'X') {
        printf("Error: Gender must be M, W, or X.\n");
        return;
    }

    // if all parameters are valid then event structure is updated
    eventNode->newEvent.eventCode = eventCode;
    strncpy(eventNode->newEvent.name, name, MAX_LENGTH - 1);
    eventNode -> newEvent.name[MAX_LENGTH - 1] = '\0'; // Safeguard to add null termination
    eventNode -> newEvent.count = competitors;
    eventNode -> newEvent.gender = gender;

    printf("Event updated succesfully.\n");
}

void printEvents(struct nodeEvent *head){
    struct nodeEvent *current = head;
    int maxNameWidth = calculateMaxNameWidth(current, 'P');
    PRINT_HEADER((int) strlen("Event Code"), maxNameWidth, (int) strlen("Competitors"), (int) strlen("Gender"));
    while (current != NULL){
        PRINT_ROW(current, (int) strlen("Event Code"), maxNameWidth, (int) strlen("Competitors"), (int) strlen("Gender"));
        current = current ->next;
    }
}

void eraseEvent(struct nodeEvent **eventHead, struct nodeRelationship *relationshipHead) {
    int eventCode;

    printf("Enter the event code to remove: ");
    scanf("%d", &eventCode);

    // Check if there are relationships with this event code
    struct nodeRelationship *currentRelationship = relationshipHead;
    while (currentRelationship != NULL) {
        if (currentRelationship->relationship.eventCode == eventCode) {
            printf("Cannot remove event. There are existing relationships with this event code.\n");
            return;
        }
        currentRelationship = currentRelationship->next;
    }

    struct nodeEvent *current = *eventHead;
    struct nodeEvent *previous = NULL;

    while (current != NULL) {
        if (current->newEvent.eventCode == eventCode) {
            if (previous == NULL) {
                *eventHead = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            printf("Event removed successfully.\n");
            return;
        }
        previous = current;
        current = current->next;
    }
    printf("Event not found.\n");
}

// Function to dump events to a file
void dumpEvents(struct nodeEvent *eventHead) {
    char filename[100];
    printf("Enter the output file name: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }

    struct nodeEvent *current = eventHead;
    while (current != NULL) {
        fwrite(&current->newEvent, sizeof(event), 1, file);
        current = current->next;
    }

    fclose(file);
    printf("Events successfully dumped to %s\n", filename);
}

// Function to restore events from a file
void restoreEvents(struct nodeEvent **eventHead) {
    char filename[100];
    printf("Enter the input file name: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file for reading");
        return;
    }

    event newEvent;
    while (fread(&newEvent, sizeof(event), 1, file)) {
        struct nodeEvent *newNode = calloc(1, sizeof(struct nodeEvent));
        if (newNode == NULL) {
            perror("Error allocating memory");
            fclose(file);
            return;
        }
        newNode->newEvent = newEvent;
        newNode->next = *eventHead;
        *eventHead = newNode;
    }

    fclose(file);
    printf("Events successfully restored from %s\n", filename);
}
