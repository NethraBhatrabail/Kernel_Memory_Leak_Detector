#include <stdio.h>
#include <stdlib.h>

// Helper function to check if file exists and is non-empty
int file_has_content(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) return 0;

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fclose(fp);
    return size > 0;
}

int main() {
    int pass = 0, total = 0;

    printf("\n=== TEST CASES FOR KERNEL MEMORY LEAK DETECTOR ===\n");

    // Test 1: Run read_slab
    total++;
    printf("Test 1: Running 'read_slab'... ");
    int result = system("sudo ./read_slab > /dev/null 2>&1");
    if (result == 0 && file_has_content("slab_log.csv")) {
        printf("PASS\n"); pass++;
    } else {
        printf("FAIL\n");
    }

    // Test 2: Run analyze_growth
    total++;
    printf("Test 2: Running 'analyze_growth'... ");
    result = system("./analyze_growth > analyze_output.txt 2>&1");
    if (result == 0 && file_has_content("analyze_output.txt")) {
        printf("PASS\n"); pass++;
    } else {
        printf("FAIL\n");
    }

    // Test 3: Run CLI with invalid input
    total++;
    printf("Test 3: Simulate invalid CLI input... ");
    result = system("echo 99 | ./kernel_leak_detector > /dev/null 2>&1");
    if (result == 0) {
        printf("PASS\n"); pass++;
    } else {
        printf("FAIL\n");
    }

    // Test 4: Show graph output
    total++;
    printf("Test 4: Running 'show_graph'... ");
    result = system("./show_graph > /dev/null 2>&1");
    if (result == 0) {
        printf("PASS\n"); pass++;
    } else {
        printf("FAIL\n");
    }

    // Summary
    printf("\n=== Test Summary ===\n");
    printf("Passed: %d/%d\n", pass, total);
    if (pass == total) {
        printf("All tests passed successfully \n");
    } else {
        printf("Some tests failed  — check logs and outputs.\n");
    }

    return 0;
}
