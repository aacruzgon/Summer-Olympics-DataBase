#include "sport_db_athlete.h"
#include "sport_db_relationship.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// Helper function to create a new node for an athlete
struct nodeAthlete* createAthleteNode(athlete newAthlete) {
    // Allocate memory for the new node
    struct nodeAthlete *newNode = (struct nodeAthlete *)calloc(1, sizeof(struct nodeAthlete));
    if (newNode == NULL) {
        return NULL; // Return NULL if memory allocation fails
    }
    newNode->newAthlete = newAthlete; // Initialize the new node with athlete data
    newNode->next = NULL; // Set the next pointer to NULL
    return newNode; // Return the newly created node
}

// Helper function to find a node with the specified athlete code
struct nodeAthlete* find_athlete_node(int code, struct nodeAthlete *head) {
    struct nodeAthlete *current = head; // Start from the head of the list
    // Traverse the list to find the node with the specified athlete code
    while (current != NULL) {
        if (current->newAthlete.athleteCode == code) {
            return current; // Return the pointer to the found node
        }
        current = current->next; // Move to the next node
    }
    return NULL; // Return NULL if the athlete code is not found
}

//Helper function that calculates maximum width
static int calculateMaxNameWidth(struct nodeAthlete *head, char inputCommand){
    int maxWidth = strlen("Athlete Name");
    int nameLength;
    if (inputCommand == 'S'){
        nameLength = strlen(head->newAthlete.name);
        if (maxWidth > nameLength){
            return maxWidth;
        }else{
            return nameLength;
        }
    }else{
        struct nodeAthlete *current = head;
        while(current != NULL){
            nameLength = strlen(current ->newAthlete.name);
            if (nameLength > maxWidth){
                maxWidth = nameLength;
            }
            current = current->next;
        }
    }
    return maxWidth;
}

void insertAthlete(struct nodeAthlete **head) {
    // Declaring structure variables
    int code, age;
    char name[MAX_NAME_LENGTH];
    char nationality[MAX_NATIONALITY_LENGTH + 1];

    printf("Enter the athlete code: ");
    scanf("%d", &code);

    // Check if the athlete code is unique
    if (find_athlete_node(code, *head) != NULL) {
        printf("Error: Athlete code must be unique.\n");
        return;
    }

    printf("Input the name of the athlete: ");
    scanf(" %[^\n]", name); // Reads the whole line

    printf("Input the age of the athlete (Min: 14 Max: 120): ");
    scanf("%d", &age);
    // Checks if age is within parameters
    if (age < 14 || age > 120) {
        printf("Error: Age must be between 14 and 120.\n");
        return;
    }

    printf("Input the nationality code of the athlete: ");
    scanf("%s", nationality);
    // Truncate nationality code if it's longer than 3 characters
    nationality[MAX_NATIONALITY_LENGTH] = '\0';

    // If all parameters are valid then athlete structure is initialized
    athlete newAthlete;
    newAthlete.athleteCode = code;
    strncpy(newAthlete.name, name, MAX_NAME_LENGTH - 1);
    newAthlete.name[MAX_NAME_LENGTH - 1] = '\0'; // Ensure null termination
    newAthlete.age = age;
    strncpy(newAthlete.nationality, nationality, MAX_NATIONALITY_LENGTH);
    newAthlete.nationality[MAX_NATIONALITY_LENGTH] = '\0'; // Ensure null termination

    struct nodeAthlete *newNode = createAthleteNode(newAthlete);
    // Check if there is disposable memory for the athlete
    if (newNode == NULL) {
        printf("Error: Could not allocate memory for a new athlete.\n");
        return;
    }

    // If there's memory, insert the new node at the beginning of the list
    newNode->next = *head;
    *head = newNode;

    printf("Athlete inserted and created successfully.\n");
}

void updateAthlete(struct nodeAthlete *head) {
    int athleteCode;
    printf("Enter the athlete code you would like to update: ");
    scanf("%d", &athleteCode);

    struct nodeAthlete *athleteNode = find_athlete_node(athleteCode, head);
    // If athlete is not in the database, return an error
    if (athleteNode == NULL) {
        printf("Athlete is not in the database.\n");
        return;
    }

    // Update athlete struct fields
    char name[MAX_NAME_LENGTH];
    int age;
    char nationality[MAX_NATIONALITY_LENGTH + 1];

    printf("Input the name of the athlete: ");
    scanf(" %[^\n]", name); // Reads the whole line

    printf("Input the age of the athlete (Min: 14 Max: 120): ");
    scanf("%d", &age);
    // Checks if age is within parameters
    if (age < 14 || age > 120) {
        printf("Error: Age must be between 14 and 120.\n");
        return;
    }

    printf("Input the nationality code of the athlete: ");
    scanf("%s", nationality);
    // Truncate nationality code if it's longer than 3 characters
    nationality[MAX_NATIONALITY_LENGTH] = '\0';

    // If all parameters are valid then athlete structure is updated
    athleteNode->newAthlete.athleteCode = athleteCode;
    strncpy(athleteNode->newAthlete.name, name, MAX_NAME_LENGTH - 1);
    athleteNode->newAthlete.name[MAX_NAME_LENGTH - 1] = '\0'; // Safeguard to add null termination
    athleteNode->newAthlete.age = age;
    strncpy(athleteNode->newAthlete.nationality, nationality, MAX_NATIONALITY_LENGTH);
    athleteNode->newAthlete.nationality[MAX_NATIONALITY_LENGTH] = '\0'; // Ensure null termination

    printf("Athlete updated successfully.\n");
}

void searchAthlete(struct nodeAthlete *head) {
    int athleteCode;
    printf("Enter the athlete code you would like to search: ");
    scanf("%d", &athleteCode);

    struct nodeAthlete *current = head;
    while (current != NULL) {
        if (current->newAthlete.athleteCode == athleteCode) {
            int maxNameWidth = calculateMaxNameWidth(head, 'S');
            int natWidth = strlen("Nationality");

            // Print the header and the athlete information
            PRINT_ATHLETE_HEADER((int)strlen("Athlete Code"), maxNameWidth, (int)strlen("Athlete Age"), natWidth);
            PRINT_ATHLETE_ROW(current, (int)strlen("Athlete Code"), maxNameWidth, (int)strlen("Athlete Age"));
            return;
        }
        current = current->next;
    }
    printf("Error: Athlete with code %d not found.\n", athleteCode);
}

void printAthletes(struct nodeAthlete *head) {
    struct nodeAthlete *current = head;
    int maxNameWidth = calculateMaxNameWidth(current, 'P');
    int nationalityWidth = (int)strlen("Nationality");

    // Print the header
    PRINT_ATHLETE_HEADER((int)strlen("Athlete Code"), maxNameWidth, (int)strlen("Athlete Age"), nationalityWidth);

    // Print each athlete
    while (current != NULL) {
        PRINT_ATHLETE_ROW(current, (int)strlen("Athlete Code"), maxNameWidth, (int)strlen("Athlete Age"));
        current = current->next;
    }
}

void eraseAthlete(struct nodeAthlete **athleteHead, struct nodeRelationship *relationshipHead) {
    int athleteCode;

    printf("Enter the athlete code to remove: ");
    scanf("%d", &athleteCode);

    // Check if there are relationships with this athlete code
    struct nodeRelationship *currentRelationship = relationshipHead;
    while (currentRelationship != NULL) {
        if (currentRelationship->relationship.athleteCode == athleteCode) {
            printf("Cannot remove athlete. There are existing relationships with this athlete code.\n");
            return;
        }
        currentRelationship = currentRelationship->next;
    }

    struct nodeAthlete *current = *athleteHead;
    struct nodeAthlete *previous = NULL;

    while (current != NULL) {
        if (current->newAthlete.athleteCode == athleteCode) {
            if (previous == NULL) {
                *athleteHead = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            printf("Athlete removed successfully.\n");
            return;
        }
        previous = current;
        current = current->next;
    }
    printf("Athlete not found.\n");
}

// Function to dump athletes to a file
void dumpAthletes(struct nodeAthlete *athleteHead) {
    char filename[100];
    printf("Enter the output file name: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }

    struct nodeAthlete *current = athleteHead;
    while (current != NULL) {
        fwrite(&current->newAthlete, sizeof(athlete), 1, file);
        current = current->next;
    }

    fclose(file);
    printf("Athletes successfully dumped to %s\n", filename);
}

// Function to restore athletes from a file
void restoreAthletes(struct nodeAthlete **athleteHead) {
    char filename[100];
    printf("Enter the input file name: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file for reading");
        return;
    }

    athlete newAthlete;
    while (fread(&newAthlete, sizeof(athlete), 1, file)) {
        struct nodeAthlete *newNode = calloc(1, sizeof(struct nodeAthlete));
        if (newNode == NULL) {
            perror("Error allocating memory");
            fclose(file);
            return;
        }
        newNode->newAthlete = newAthlete;
        newNode->next = *athleteHead;
        *athleteHead = newNode;
    }

    fclose(file);
    printf("Athletes successfully restored from %s\n", filename);
}
