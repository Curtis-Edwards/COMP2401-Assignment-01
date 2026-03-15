#include <stdio.h>

// These are defined values.
// They do not reserve memory like a variable.
// Instead, the first phase of building - "pre-processing"
// Will essentially find-and-replace with what is written to the right.
// You should define some yourself to avoid "magic numbers",
// unchanging numbers that might need explanation or appear multiple times.
// It's a bit like commenting the value.
#define MAX_ENTRIES 16
#define C_OK  0
#define C_ERR_EMPTY_ARRAY  -1
#define C_ERR_INVALID_EMF  -2
#define C_ERR_INVALID_ROOM -3

// These are "forward declarations".
// It tells the rest of the code to expect to find a function
// that works like this somewhere once we compile and link our code.
// We will NOT put the body of the function here, to keep things clean.
// Instead, we will leave this forward declaration untouched, 
// and define the functions in another file: `readings.c`.
// These are like promises; "When I link other files, you'll find them"
int get_entries(int ids[], float readings[]);
int print_entries(int ids[], float readings[], int size);
int sort_entries(int ids[], float readings[], int size);
int find_max_index(float readings[], int size);
int invalid_room(int id);
int invalid_reading(float reading);

int main(void) {
    int roomIds[MAX_ENTRIES] = {};
    float emfReadings[MAX_ENTRIES] = {};
    
    int arraySize = get_entries(roomIds, emfReadings);
    print_entries(roomIds, emfReadings, arraySize);
    sort_entries(roomIds, emfReadings, arraySize);
    print_entries(roomIds, emfReadings, arraySize);

    return 0;
}


