#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    FILE *file = fopen("/proc/slabinfo", "r");
    if (file == NULL) {
        perror("Error opening /proc/slabinfo");
        return 1;
//Opens the virtual kernel file /proc/slabinfo If it fails (e.g., permission denied), it prints an error and exits

    }

    FILE *log = fopen("slab_log.csv", "a");  // Append mode
    if (log == NULL) {
        perror("Error opening log file");
        fclose(file);
        return 1;
//Opens a file named slab_log.csv to append new log entries. If it can’t open that file, the program also exits after cleaning up
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char timestamp[64];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", t);
//Gets the current time
Converts it into a human-readable date & time
Stores it in the format: YYYY-MM-DD HH:MM:SS//


    char line[512];
    int line_count = 0;

    while (fgets(line, sizeof(line), file)) {
        line_count++;
        if (line_count <= 2) continue;  // Skip headers
//Reads the /proc/slabinfo line by line. Skips the first 2 header lines which are not data rows

        char cache_name[64];
        int active_objs, total_objs;

        if (sscanf(line, "%s %d %d", cache_name, &active_objs, &total_objs) == 3) {
            fprintf(log, "%s,%s,%d,%d\n", timestamp, cache_name, active_objs, total_objs);

        }
    }

    fclose(file);
    fclose(log);
    printf("Slab info logged to slab_log.csv\n");
    return 0;
}
