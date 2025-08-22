#include <stdio.h>     // For input/output operations like printf, fopen, fgets, etc.
#include <stdlib.h>    // For general utilities like exit status codes
#include <string.h>    // For string handling (not used explicitly here but included by habit)

int main() {
    // Open the file /proc/slabinfo in read mode. This file contains kernel slab allocator info.
    FILE *file = fopen("/proc/slabinfo", "r");

    // Check if the file was opened successfully
    if (file == NULL) {
        // If not, print the error and exit
        perror("Error opening /proc/slabinfo");
        return 1;
    }

    char line[512];       // Buffer to store each line from the file
    int line_count = 0;   // Counter to track the number of lines read

    // Print table headers for the output
    printf("%-30s %-10s %-10s\n", "Cache Name", "Active", "Total");
    printf("----------------------------------------------------------\n");

    // Read the file line by line
    while (fgets(line, sizeof(line), file)) {
        line_count++;  // Increment the line counter

        // The first two lines in /proc/slabinfo are headers, so we skip them
        if (line_count <= 2) continue;

        char cache_name[64];   // Variable to store the cache name
        int active_objs;       // Variable to store number of active objects
        int total_objs;        // Variable to store total number of objects

        // Parse the line using sscanf - only take the first 3 fields
        if (sscanf(line, "%s %d %d", cache_name, &active_objs, &total_objs) == 3) {
            // Print the parsed info in a formatted table row
            printf("%-30s %-10d %-10d\n", cache_name, active_objs, total_objs);
        }
    }

    // Close the file after reading all lines
    fclose(file);

    return 0;   // Exit the program
}
