#include <stdio.h>     
#include <stdlib.h>     
#include <string.h>    

#define MAX_LINE 256            // Max line length while reading files
#define GROWTH_THRESHOLD 10    // Minimum slab growth to consider for graph display

// Function to display the contents of the log file
void show_logged_info() {
    printf("\n--- Logged Slab Info (slab_log.csv) ---\n");
    system("cat slab_log.csv");  // Uses shell command to print contents of CSV
}

// Function to analyze growth in slab caches over time
void analyze_growth() {
    FILE *log = fopen("slab_log.csv", "r");         
    FILE *growth = fopen("growth_log.csv", "w");    

    if (!log || !growth) {                          // If either file can't be opened
        perror("Error opening files");
        return;
    }

    char line[MAX_LINE], name[64];                  // Buffers to store one line and slab name
    int start = -1, end = -1;                       // Start and end values of a slab’s total count
    int active, total;                              // Active and total objects from CSV

    fprintf(growth, "Name Start End Growth\n");     // Header for growth report

    while (fgets(line, sizeof(line), log)) {        // Read each line from the slab log
        // Extract slab name, active object count, and total object count from the line
        if (sscanf(line, "%*[^,],%[^,],%d,%d", name, &active, &total) == 3) {
            if (start == -1) {
                // If this is the first entry
                start = total;
                strcpy(line, name);  // Store slab name (re-using 'line' here)
            } else {
                end = total;                               // Set end value for comparison
                int growth_val = end - start;              // Calculate difference
                if (growth_val > 0) {
                    // If growth found, log it to growth file
                    fprintf(growth, "%s %d %d %d\n", name, start, end, growth_val);
                }
                start = end;                               // Update start for next line
            }
        }
    }

    fclose(log);                                           // Close both files
    fclose(growth);
    printf("\nGrowth analysis completed.\n");
}

// Function to display a simple text-based graph for slab cache growth
void show_growth_graph() {
    FILE *file = fopen("growth_log.csv", "r");             // Open file with growth details
    if (!file) {
        perror("Error opening growth_log.csv");
        return;
    }

    char line[MAX_LINE], name[64];                         // Line and name buffers
    int start, end, growth;

    // Print header
    printf("\n--- Slab Cache Growth Graph (Threshold > %d) ---\n", GROWTH_THRESHOLD);
    fgets(line, sizeof(line), file);                       // Skip CSV header line

    while (fgets(line, sizeof(line), file)) {
        // Parse name, start, end, and growth values from each line
        if (sscanf(line, "%s %d %d %d", name, &start, &end, &growth) == 4) {
            if (growth > GROWTH_THRESHOLD) {               // Only consider if growth exceeds threshold
                printf("%-20s [%4d] | ", name, growth);    // Print label
                for (int i = 0; i < growth / 100; i++) {   // Show bar proportional to growth
                    printf("#");
                }
                printf("\n");
            }
        }
    }

    fclose(file);                                          // Close the file
}

// Main function: Displays CLI and handles user choices
int main() {
    int choice;

    while (1) {
        // Display menu
        printf("\n=== Kernel Memory Leak Detector CLI ===\n");
        printf("1. Log Slab Info\n");
        printf("2. Show Logged Slab Info\n");
        printf("3. Analyze Growth\n");
        printf("4. Show Growth Graph (Threshold > %d)\n", GROWTH_THRESHOLD);
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);                              // Get user input

        // Perform action based on user choice
        if (choice == 1) {
            system("sudo ./read_slab");                    // Run the slab reader binary
        } else if (choice == 2) {
            show_logged_info();                            // Call log viewer
        } else if (choice == 3) {
            analyze_growth();                              // Call growth analyzer
        } else if (choice == 4) {
            show_growth_graph();                           // Call graph display
        } else if (choice == 5) {
            printf("Exiting...\n");
            break;                                         // Exit loop and end program
        } else {
            printf("Invalid choice. Try again.\n");        // Handle invalid input
        }
    }

    return 0;                                               
}
