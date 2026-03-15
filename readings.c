#include <stdio.h>

#define MAX_ENTRIES 16
#define C_OK  0
#define C_ERR_EMPTY_ARRAY  -1
#define C_ERR_INVALID_EMF  -2
#define C_ERR_INVALID_ROOM -3
#define ID_MINIMUM 13300000
#define ID_MAXIMUM 13379999 
#define EMF_MINIMUM 0.00
#define EMF_MAXIMUM 5.00

int get_entries(int ids[], float readings[]);
int print_entries(int ids[], float readings[], int size);
int sort_entries(int ids[], float readings[], int size);
int find_max_index(float readings[], int size);
int invalid_room(int id);
int invalid_reading(float reading);


/*
Prompts the user to enter room IDs and EMF readings, validates them, and stores
the valid entries in the arrays `ids` and `readings`.

out ids[]: Array to store valid room IDs
out readings[]: Array to store valid EMF readings
Returns:
- Number of valid entries stored in the arrays
*/
int get_entries(int ids[], float readings[]) {
    int roomId;
    float emfReading;
    int arraySize = 0;

    while (1) {
        printf("Enter a Room ID and EMF (-1 -1 to quit): ");
        scanf("%d %f", &roomId, &emfReading);

        if (roomId == -1 && emfReading == -1) {
            break;
        } else if (arraySize >= MAX_ENTRIES) {
            printf("Maximum Entries Reached.\n");
            break;
        } else if (invalid_room(roomId) == C_ERR_INVALID_ROOM) {
            printf("Invalid Room ID: %d\n", roomId);
        } else if (invalid_reading(emfReading) == C_ERR_INVALID_EMF) {
            printf("Invalid EMF: %f\n", emfReading);
        } else {
            ids[arraySize] = roomId;
            readings[arraySize] = emfReading;
            arraySize++;
        }
    }

    return arraySize;
}


/*
Prints the contents of the `ids` and `readings` arrays in a formatted table.

in ids[]: Array of room IDs
in readings[]: Array of EMF readings
in size: Number of elements in `ids` and `readings`
Returns:
- C_OK on success
*/
int print_entries(int ids[], float readings[], int size) {
    printf("\nRoom ID      EMF\n");
    printf("--------    ----\n");
    for (int i = 0; i < size; i++) {
        printf("%d    %.2f\n", ids[i], readings[i]);
    }
    printf("--------    ----\n");
    printf("Total Entries: %d\n", size);

    return C_OK;
}

/*
Sorts the `ids` and `readings` arrays in descending order of EMF readings.

in/out ids[]: Array of IDs associated with EMF readings in `readings`
in/out readings[]: Array of EMF readings to be sorted
in size: Number of elements in `ids` and `readings`
Returns:
- C_OK on success
- C_ERR_EMPTY_ARRAY if no entries exist
*/
int sort_entries(int ids[], float readings[], int size) {
    int idsCopy[size];
    float readingsCopy[size];
    for (int i = 0; i < size; i++) {
        idsCopy[i] = ids[i];
        readingsCopy[i] = readings[i];
    }
    
    if (size <= 0) {
        return C_ERR_EMPTY_ARRAY;
    }

    for (int i = 0; i < size; i++) {
        int max_index = find_max_index(readingsCopy, size);

        ids[i] = idsCopy[max_index];
        readings[i] = readingsCopy[max_index];
        readingsCopy[max_index] = -1.0;
    }

    return C_OK;
}


/*
Finds the index of the maximum value in the `readings` array.

in readings[]: Array of EMF readings
in size: Number of elements in `readings`
Returns:
- Index of the maximum reading
- C_ERR_EMPTY_ARRAY if the array is empty
*/
int find_max_index(float readings[], int size) {
    int maxIndex = 0;
    float highestEMF = readings[0];

    if (size <= 0) {
        return C_ERR_EMPTY_ARRAY;
    }

    if (size == 1) {
        return 0;
    }

    for (int i = 1; i < size; i++) {
        if (readings[i] > highestEMF) {
            highestEMF = readings[i];
            maxIndex = i;
        }
    }

    return maxIndex;
}


/*
Checks whether a given room ID is within the valid range.

in id: Room ID to validate
Returns:
- C_OK if valid
- C_ERR_INVALID_ROOM if invalid
*/
int invalid_room(int id) {
    if (ID_MINIMUM <= id && id <= ID_MAXIMUM) {
        return C_OK;
    } else {
        return C_ERR_INVALID_ROOM;
    }
}


/*
Checks whether a given EMF reading is within the valid range.

in reading: EMF reading to validate
Returns:
- C_OK if valid
- C_ERR_INVALID_EMF if invalid
*/
int invalid_reading(float reading) {
    if (EMF_MINIMUM <= reading && reading <= EMF_MAXIMUM) {
        return C_OK;
    } else {
        return C_ERR_INVALID_EMF;
    }
}
