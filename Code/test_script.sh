#!/usr/bin/expect -f

# Set a timeout
set timeout -1

# Start the program
spawn ./sport_db

# Function to send a command and handle timeout
proc send_command {pattern command} {
    expect {
        -re $pattern { send "$command\r" }
        timeout { puts "Timeout waiting for $pattern"; exit 1 }
    }
}

# Insert event
send_command ".*Input the desired command:.*" "e"
send_command ".*Input the desired command:.*" "i"
send_command ".*Enter.*event.*code:.*" "101"
send_command ".*Input the name of the event:.*" "Test Event"
send_command ".*Input the number of competitors.*" "20"
send_command ".*What is the gender of the event.*" "m"

# Insert athlete
send_command ".*Input the desired command:.*" "a"
send_command ".*Input the desired command:.*" "i"
send_command ".*Enter.*athlete.*code:.*" "201"
send_command ".*Input the name of the athlete:.*" "John Doe"
send_command ".*Input the age of the athlete.*" "25"
send_command ".*Input the nationality code of the athlete:.*" "USA"

# Insert relationship
send_command ".*Input the desired command:.*" "r"
send_command ".*Input the desired command:.*" "i"
send_command ".*Enter the relationship code:.*" "301"
send_command ".*Enter the event code:.*" "101"
send_command ".*Enter the athlete code:.*" "201"

# Try to insert a relationship with a duplicate relationship code
send_command ".*Input the desired command:.*" "r"
send_command ".*Input the desired command:.*" "i"
send_command ".*Enter the relationship code:.*" "301"

# Try to insert a relationship with a non-existent event code
send_command ".*Input the desired command:.*" "r"
send_command ".*Input the desired command:.*" "i"
send_command ".*Enter the relationship code:.*" "302"
send_command ".*Enter the event code:.*" "999"
send_command ".*Enter the athlete code:.*" "201"

# Try to insert a relationship with a non-existent athlete code
send_command ".*Input the desired command:.*" "r"
send_command ".*Input the desired command:.*" "i"
send_command ".*Enter the relationship code:.*" "303"
send_command ".*Enter the event code:.*" "101"
send_command ".*Enter the athlete code:.*" "999"

# Print all relationships
send_command ".*Input the desired command:.*" "r"
send_command ".*Input the desired command:.*" "p"

# Insert additional events
send_command ".*Input the desired command:.*" "e"
send_command ".*Input the desired command:.*" "i"
send_command ".*Enter.*event.*code:.*" "701"
send_command ".*Input the name of the event:.*" "Event 701"
send_command ".*Input the number of competitors.*" "30"
send_command ".*What is the gender of the event.*" "m"

send_command ".*Input the desired command:.*" "e"
send_command ".*Input the desired command:.*" "i"
send_command ".*Enter.*event.*code:.*" "702"
send_command ".*Input the name of the event:.*" "Event 702"
send_command ".*Input the number of competitors.*" "35"
send_command ".*What is the gender of the event.*" "w"

# Insert additional athletes
send_command ".*Input the desired command:.*" "a"
send_command ".*Input the desired command:.*" "i"
send_command ".*Enter.*athlete.*code:.*" "901"
send_command ".*Input the name of the athlete:.*" "Bob Brown"
send_command ".*Input the age of the athlete.*" "22"
send_command ".*Input the nationality code of the athlete:.*" "AUS"

send_command ".*Input the desired command:.*" "a"
send_command ".*Input the desired command:.*" "i"
send_command ".*Enter.*athlete.*code:.*" "902"
send_command ".*Input the name of the athlete:.*" "Eve White"
send_command ".*Input the age of the athlete.*" "24"
send_command ".*Input the nationality code of the athlete:.*" "NZL"

# Insert relationships
send_command ".*Input the desired command:.*" "r"
send_command ".*Input the desired command:.*" "i"
send_command ".*Enter the relationship code:.*" "701"
send_command ".*Enter the event code:.*" "101"
send_command ".*Enter the athlete code:.*" "901"

send_command ".*Input the desired command:.*" "r"
send_command ".*Input the desired command:.*" "i"
send_command ".*Enter the relationship code:.*" "702"
send_command ".*Enter the event code:.*" "102"
send_command ".*Enter the athlete code:.*" "902"

send_command ".*Input the desired command:.*" "r"
send_command ".*Input the desired command:.*" "i"
send_command ".*Enter the relationship code:.*" "703"
send_command ".*Enter the event code:.*" "701"
send_command ".*Enter the athlete code:.*" "201"

send_command ".*Input the desired command:.*" "r"
send_command ".*Input the desired command:.*" "i"
send_command ".*Enter the relationship code:.*" "704"
send_command ".*Enter the event code:.*" "702"
send_command ".*Enter the athlete code:.*" "202"

# Print all relationships
send_command ".*Input the desired command:.*" "r"
send_command ".*Input the desired command:.*" "p"

# Insert additional events
send_command ".*Input the desired command:.*" "e"
send_command ".*Input the desired command:.*" "i"
send_command ".*Enter.*event.*code:.*" "501"
send_command ".*Input the name of the event:.*" "Event 501"
send_command ".*Input the number of competitors.*" "40"
send_command ".*What is the gender of the event.*" "m"

send_command ".*Input the desired command:.*" "e"
send_command ".*Input the desired command:.*" "i"
send_command ".*Enter.*event.*code:.*" "502"
send_command ".*Input the name of the event:.*" "Event 502"
send_command ".*Input the number of competitors.*" "45"
send_command ".*What is the gender of the event.*" "w"

# Insert additional athletes
send_command ".*Input the desired command:.*" "a"
send_command ".*Input the desired command:.*" "i"
send_command ".*Enter.*athlete.*code:.*" "801"
send_command ".*Input the name of the athlete:.*" "Charlie Green"
send_command ".*Input the age of the athlete.*" "26"
send_command ".*Input the nationality code of the athlete:.*" "USA"

send_command ".*Input the desired command:.*" "a"
send_command ".*Input the desired command:.*" "i"
send_command ".*Enter.*athlete.*code:.*" "802"
send_command ".*Input the name of the athlete:.*" "Dana Blue"
send_command ".*Input the age of the athlete.*" "28"
send_command ".*Input the nationality code of the athlete:.*" "UK"

# Insert relationships for the same athlete with different events
send_command ".*Input the desired command:.*" "r"
send_command ".*Input the desired command:.*" "i"
send_command ".*Enter the relationship code:.*" "501"
send_command ".*Enter the event code:.*" "501"
send_command ".*Enter the athlete code:.*" "801"

send_command ".*Input the desired command:.*" "r"
send_command ".*Input the desired command:.*" "i"
send_command ".*Enter the relationship code:.*" "502"
send_command ".*Enter the event code:.*" "502"
send_command ".*Enter the athlete code:.*" "801"

# Insert relationships for a different athlete with other events
send_command ".*Input the desired command:.*" "r"
send_command ".*Input the desired command:.*" "i"
send_command ".*Enter the relationship code:.*" "503"
send_command ".*Enter the event code:.*" "501"
send_command ".*Enter the athlete code:.*" "802"

send_command ".*Input the desired command:.*" "r"
send_command ".*Input the desired command:.*" "i"
send_command ".*Enter the relationship code:.*" "504"
send_command ".*Enter the event code:.*" "502"
send_command ".*Enter the athlete code:.*" "802"

# Print all relationships
send_command ".*Input the desired command:.*" "r"
send_command ".*Input the desired command:.*" "p"

# Remove relationship
send_command ".*Input the desired command:.*" "r"
send_command ".*Input the desired command:.*" "e"
send_command ".*Enter the relationship code:.*" "301"

# Print all relationships to confirm removal
send_command ".*Input the desired command:.*" "r"
send_command ".*Input the desired command:.*" "p"

# Dump the database
send_command ".*Input the desired command:.*" "e"
send_command ".*Input the desired command:.*" "d"
send_command ".*Enter the output file name:.*" "event_dump.dat"

send_command ".*Input the desired command:.*" "a"
send_command ".*Input the desired command:.*" "d"
send_command ".*Enter the output file name:.*" "athlete_dump.dat"

send_command ".*Input the desired command:.*" "r"
send_command ".*Input the desired command:.*" "d"
send_command ".*Enter the output file name:.*" "relationship_dump.dat"

# Quit the program
send_command ".*Input the desired command:.*" "q"

# Start the program
spawn ./sport_db

# Function to send a command and handle timeout
proc send_command {pattern command} {
    expect {
        -re $pattern { send "$command\r" }
        timeout { puts "Timeout waiting for $pattern"; exit 1 }
    }
}

# Restore the database
send_command ".*Input the desired command:.*" "e"
send_command ".*Input the desired command:.*" "r"
send_command ".*Enter the input file name:.*" "event_dump.dat"

send_command ".*Input the desired command:.*" "a"
send_command ".*Input the desired command:.*" "r"
send_command ".*Enter the input file name:.*" "athlete_dump.dat"

send_command ".*Input the desired command:.*" "r"
send_command ".*Input the desired command:.*" "r"
send_command ".*Enter the input file name:.*" "relationship_dump.dat"

# Quit the program
send_command ".*Input the desired command:.*" "q"

# End the session
expect eof
