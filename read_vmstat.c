#include <stdio.h>      
#include <string.h>     
int main() {
    // Open the virtual memory stats file in read mode
    FILE *file = fopen("/proc/vmstat", "r");
    
    // Check if the file was opened successfully
    if (!file) {
        perror("Failed to open /proc/vmstat");  // Print error message if failed
        return 1;  // Exit with error code
    }

    char line[256];  // Buffer to store each line read from the file

    printf("\n--- Virtual Memory Stats ---\n");

    // Read the file line by line
    while (fgets(line, sizeof(line), file)) {
        // Filter and print only important memory stats
        if (strstr(line, "pgfault")     ||  
            strstr(line, "pgmajfault")  || 
            strstr(line, "pgfree")      ||  
            strstr(line, "pgsteal")) {      
            printf("%s", line); 
        }
    }

    // Close the file
    fclose(file);

    return 0;  // Successful termination
}
