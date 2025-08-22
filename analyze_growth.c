#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENTRIES 10000
#define NAME_LEN 64

typedef struct {
    char name[NAME_LEN];
    int start_value;
    int end_value;
    int count;
    int growing;  // 1 if growing, 0 if not
} SlabStat;

int main() {
    FILE *log = fopen("slab_log.csv", "r");
    if (log == NULL) {
        perror("Error opening log file");
        return 1;
    }

    SlabStat slabs[MAX_ENTRIES];
    int slab_count = 0;

    char line[256];
    while (fgets(line, sizeof(line), log)) {
        char timestamp[64], name[NAME_LEN];
        int active, total;

        if (sscanf(line, "%[^,],%[^,],%d,%d", timestamp, name, &active, &total) == 4) {
            int found = 0;
            for (int i = 0; i < slab_count; i++) {
                if (strcmp(slabs[i].name, name) == 0) {
                    if (active > slabs[i].end_value)
                        slabs[i].growing = 1;
                    slabs[i].end_value = active;
                    slabs[i].count++;
                    found = 1;
                    break;
                }
            }

            if (!found && slab_count < MAX_ENTRIES) {
                strcpy(slabs[slab_count].name, name);
                slabs[slab_count].start_value = active;
                slabs[slab_count].end_value = active;
                slabs[slab_count].count = 1;
                slabs[slab_count].growing = 0;
                slab_count++;
            }
        }
    }

    fclose(log);

    printf("\nSlab Caches with consistent growth:\n");
    printf("%-30s %-10s %-10s %-10s\n", "Cache Name", "Start", "End", "Growth");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < slab_count; i++) {
        if (slabs[i].growing && slabs[i].count >= 2) {
            printf("%-30s %-10d %-10d %-10d\n",
                   slabs[i].name,
                   slabs[i].start_value,
                   slabs[i].end_value,
                   slabs[i].end_value - slabs[i].start_value);
        }
    }

    return 0;
} 
