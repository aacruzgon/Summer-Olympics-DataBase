# Define the compiler to use
CC = gcc

# Define the compilation flags
CFLAGS = -Wall -Werror -Wextra -pedantic

# The default target to build the executable
all: sport_db

# Link the object files to create the final executable
sport_db: sport_db.o sport_db_event.o sport_db_athlete.o sport_db_relationship.o
	$(CC) $(CFLAGS) -o sport_db sport_db.o sport_db_event.o sport_db_athlete.o sport_db_relationship.o

# Compile the main program source file into an object file
sport_db.o: sport_db.c sport_db.h
	$(CC) $(CFLAGS) -c sport_db.c

# Compile the event-related source file into an object file
sport_db_event.o: sport_db_event.c sport_db_event.h
	$(CC) $(CFLAGS) -c sport_db_event.c

# Compile the athlete-related source file into an object file
sport_db_athlete.o: sport_db_athlete.c sport_db_athlete.h
	$(CC) $(CFLAGS) -c sport_db_athlete.c

# Compile the relationship-related source file into an object file
sport_db_relationship.o: sport_db_relationship.c sport_db_relationship.h
	$(CC) $(CFLAGS) -c sport_db_relationship.c

# Clean up the build artifacts
clean:
	rm -f *.o sport_db
