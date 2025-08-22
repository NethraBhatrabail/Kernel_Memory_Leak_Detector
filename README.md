# Kernel_Memory_Leak_Detector (User-Space C Implementation)

📌 Overview
*This project is a Kernel Memory Leak Detector implemented in C from user space.
It monitors Linux kernel slab caches by reading from /proc/slabinfo and /proc/vmstat, logs memory usage over time, detects abnormal growth trends, and visualizes results in a simple CLI-based tool with ASCII graphs.
The tool is lightweight and modular, demonstrating Linux OS concepts such as file I/O, process management, CLI interaction, and testing.

🚀 Features
Reads kernel memory slab statistics from /proc/slabinfo
Logs cache details (cache_name, active_objs, total_objs) with timestamps
Reads selected virtual memory stats from /proc/vmstat
Detects abnormal growth trends in slab caches
CLI interface for logging, analyzing, and viewing results
ASCII-based text graph visualization with thresholds
Includes basic test cases for verification
