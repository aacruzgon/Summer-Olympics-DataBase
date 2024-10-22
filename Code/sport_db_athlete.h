#ifndef SPORT_DB_ATHLETE_H
#define SPORT_DB_ATHLETE_H

#include <stdbool.h>
#define MAX_NAME_LENGTH 50 // Athlete name maximum acceptable length
#define MAX_NATIONALITY_LENGTH 3 // Nationality code length

// Forward declaration
struct nodeRelationship;

// Declaring structure that holds the athlete details
typedef struct {
    int athleteCode;  // Athlete code
    char name[MAX_NAME_LENGTH]; // Athlete name
    int age;  // Athlete age
    char nationality[MAX_NATIONALITY_LENGTH + 1]; // Nationality code (+1 for null termination)
} athlete;

// Node structure for athlete nodes
struct nodeAthlete {
    athlete newAthlete;
    struct nodeAthlete *next;
};

// Defining basic ATHLETE UI
#define ATHLETE_BASIC_UI() \
    do { \
        printf("------------------------------\n"); \
        printf("|    2211 Summer Olympics!   |\n"); \
        printf("|----------------------------|\n"); \
        printf("| New Athlete     |    i     |\n"); \
        printf("|-----------------|----------|\n"); \
        printf("| Search Athlete  |    s     |\n"); \
        printf("|-----------------|----------|\n"); \
        printf("| Update Athlete  |    u     |\n"); \
        printf("|-----------------|----------|\n"); \
        printf("| Print Athletes  |    p     |\n"); \
        printf("|-----------------|----------|\n"); \
        printf("| Erase Athlete   |    e     |\n"); \
        printf("|-----------------|----------|\n"); \
        printf("| Dump Athletes   |    d     |\n"); \
        printf("|-----------------|----------|\n"); \
        printf("| Restore Athletes|    r     |\n"); \
        printf("------------------------------\n"); \
    } while(0)


// Multiparameter macro definition for printing
#define PRINT_ATHLETE_HEADER(athleteCodeWidth, nameWidth, ageWidth, nationalityWidth) \
    printf("%*s     %-*s     %*s     %*s\n", athleteCodeWidth, "Athlete Code", nameWidth, "Athlete Name", ageWidth, "Athlete Age", nationalityWidth, "Nationality")
#define PRINT_ATHLETE_ROW(node, athleteCodeWidth, nameWidth, ageWidth) \
    printf("%*d          %-*s     %*d            %5s\n", athleteCodeWidth - 5, (node)->newAthlete.athleteCode, nameWidth, (node)->newAthlete.name, ageWidth - 5, (node)->newAthlete.age, (node)->newAthlete.nationality)

// Function prototypes
struct nodeAthlete* createAthleteNode(athlete newAthlete);
struct nodeAthlete* find_athlete_node(int code, struct nodeAthlete *head);
void insertAthlete(struct nodeAthlete **head);
void searchAthlete(struct nodeAthlete *head);
void updateAthlete(struct nodeAthlete *head);
void printAthletes(struct nodeAthlete *head);
void eraseAthlete(struct nodeAthlete **head, struct nodeRelationship *relationshipHead);
void restoreAthletes(struct nodeAthlete **athleteHead);
void dumpAthletes(struct nodeAthlete *athleteHead);
#endif // SPORT_DB_ATHLETE_H
