# Kernel Memory Leak Detector in User Space

📌 Overview
* This project is a Kernel Memory Leak Detector implemented in C from user space.
* It monitors Linux kernel slab caches by reading from /proc/slabinfo and /proc/vmstat, logs memory usage over time, detects abnormal growth trends, and visualizes results in a simple CLI-based tool with ASCII graphs.
* The tool is lightweight and modular, demonstrating Linux OS concepts such as file I/O, process management, CLI interaction, and testing.

🚀 Features
* Reads kernel memory slab statistics from /proc/slabinfo
* Logs cache details (cache_name, active_objs, total_objs) with timestamps
* Reads selected virtual memory stats from /proc/vmstat
* Detects abnormal growth trends in slab caches
* CLI interface for logging, analyzing, and viewing results
* ASCII-based text graph visualization with thresholds
* Includes basic test cases for verification

Implimentation details:
* read_slab.c will be first C program to read and print slab cache info.
* read_vmstat.c contains program which is used to monitor virtual memory statistics such as page faults, free pages, and page steals, which helps in understanding overall memory behavior along with slab usage.
* slab_log.c will read /proc/slabinfo, Log the following to a file: timestamp, cache name, active, total and save it in a .csv format (easy to view later)
* analyze_growth.c will read the slab_log.csv file, compare entries over time, detect caches where Active objects keep growing and print those as suspected memory leaks.
* main_cli.c will displays a simple menu and based on the user's choice: Log Slab Info, Show Logged Slab Info, Analyze Growth,Show Growth Graph, Exit
* test_all.c  is Functional Testing (also called Unit-style testing for system components)


