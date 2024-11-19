#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void get_cpu_usage() {
    FILE *fp;
    unsigned long long int prev_times[10], curr_times[10];
    unsigned long long int prev_total = 0, curr_total = 0;
    unsigned long long int prev_idle = 0, curr_idle = 0;

    // First reading
    fp = fopen("/proc/stat", "r");
    if (!fp) {
        perror("Failed to open /proc/stat");
        exit(EXIT_FAILURE);
    }
    fscanf(fp, "cpu  %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu",
           &prev_times[0], &prev_times[1], &prev_times[2], &prev_times[3], &prev_times[4],
           &prev_times[5], &prev_times[6], &prev_times[7], &prev_times[8], &prev_times[9]);
    fclose(fp);

    for (int i = 0; i < 10; i++) {
        prev_total += prev_times[i];
    }
    prev_idle = prev_times[3] + prev_times[4]; // idle + iowait

    // Sleep for a short interval
    sleep(1);

    // Second reading
    fp = fopen("/proc/stat", "r");
    if (!fp) {
        perror("Failed to open /proc/stat");
        exit(EXIT_FAILURE);
    }
    fscanf(fp, "cpu  %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu",
           &curr_times[0], &curr_times[1], &curr_times[2], &curr_times[3], &curr_times[4],
           &curr_times[5], &curr_times[6], &curr_times[7], &curr_times[8], &curr_times[9]);
    fclose(fp);

    for (int i = 0; i < 10; i++) {
        curr_total += curr_times[i];
    }
    curr_idle = curr_times[3] + curr_times[4]; // idle + iowait

    // Calculate CPU usage
    double total_diff = (double)(curr_total - prev_total);
    double idle_diff = (double)(curr_idle - prev_idle);
    double cpu_usage = ((total_diff - idle_diff) / total_diff) * 100.0;

    printf("CPU Usage: %.2f%%\n", cpu_usage);
}

void get_memory_usage() {
    FILE *fp;
    char buffer[256];
    unsigned long mem_total = 0, mem_free = 0, buffers = 0, cached = 0;
    int found_total = 0, found_free = 0, found_buffers = 0, found_cached = 0;
    unsigned long value;

    fp = fopen("/proc/meminfo", "r");
    if (!fp) {
        perror("Failed to open /proc/meminfo");
        exit(EXIT_FAILURE);
    }

    while (fgets(buffer, sizeof(buffer), fp)) {
        if (sscanf(buffer, "MemTotal: %lu kB", &value) == 1) {
            mem_total = value;
            found_total = 1;
        } else if (sscanf(buffer, "MemFree: %lu kB", &value) == 1) {
            mem_free = value;
            found_free = 1;
        } else if (sscanf(buffer, "Buffers: %lu kB", &value) == 1) {
            buffers = value;
            found_buffers = 1;
        } else if (sscanf(buffer, "Cached: %lu kB", &value) == 1) {
            cached = value;
            found_cached = 1;
        }

        if (found_total && found_free && found_buffers && found_cached) {
            break;
        }
    }
    fclose(fp);

    if (found_total && found_free && found_buffers && found_cached) {
        unsigned long used_memory = mem_total - mem_free - buffers - cached;
        double memory_usage = ((double)used_memory / mem_total) * 100.0;
        printf("Memory Usage: %.2f%%\n", memory_usage);
    } else {
        printf("Memory Usage: Unable to calculate\n");
    }
}

int main() {
    // Print header
    printf("System Monitor\n");
    printf("==============\n");

    // Collect and print stats
    get_cpu_usage();
    get_memory_usage();

	printf("\n");
    return 0;
}
