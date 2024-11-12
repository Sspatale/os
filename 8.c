#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_TRACK 199  // Maximum number of tracks in the disk (0-199)

// Function to compare two integers (used for qsort)
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Function to calculate the total head movement for SSTF
int SSTF(int requests[], int n, int initial_head) {
    int head = initial_head;
    int total_head_movement = 0;
    int visited[n];
    for (int i = 0; i < n; i++) {
        visited[i] = 0;  // Initialize visited array to track visited requests
    }

    for (int i = 0; i < n; i++) {
        int min_distance = 9999;
        int min_index = -1;

        // Find the request with the shortest distance from the current head
        for (int j = 0; j < n; j++) {
            if (!visited[j]) {
                int distance = abs(head - requests[j]);
                if (distance < min_distance) {
                    min_distance = distance;
                    min_index = j;
                }
            }
        }

        // Move the head to the selected request
        visited[min_index] = 1;
        total_head_movement += min_distance;
        head = requests[min_index];  // Update head position
    }
    return total_head_movement;
}

// Function to calculate the total head movement for SCAN
int SCAN(int requests[], int n, int initial_head, int max_track) {
    int head = initial_head;
    int total_head_movement = 0;
    int left[MAX_TRACK + 1], right[MAX_TRACK + 1];
    int left_count = 0, right_count = 0;

    // Separate requests into left and right of the head
    for (int i = 0; i < n; i++) {
        if (requests[i] < head) {
            left[left_count++] = requests[i];
        } else {
            right[right_count++] = requests[i];
        }
    }

    // Sort the requests
    qsort(left, left_count, sizeof(int), compare);
    qsort(right, right_count, sizeof(int), compare);

    // Move towards the left end first, if possible, or the right end
    total_head_movement += abs(head - right[right_count - 1]); // Move to the farthest right request
    head = right[right_count - 1]; // Update head position

    // Service requests towards the left end of the disk
    for (int i = right_count - 2; i >= 0; i--) {
        total_head_movement += abs(head - right[i]);
        head = right[i];
    }

    // Now service the remaining requests towards the far left
    total_head_movement += abs(head - left[left_count - 1]);
    head = left[left_count - 1];

    // Service the left requests in reverse order
    for (int i = left_count - 2; i >= 0; i--) {
        total_head_movement += abs(head - left[i]);
        head = left[i];
    }

    return total_head_movement;
}

// Function to calculate the total head movement for C-Look
int C_Look(int requests[], int n, int initial_head, int max_track) {
    int head = initial_head;
    int total_head_movement = 0;
    int left[MAX_TRACK + 1], right[MAX_TRACK + 1];
    int left_count = 0, right_count = 0;

    // Separate requests into left and right of the head
    for (int i = 0; i < n; i++) {
        if (requests[i] < head) {
            left[left_count++] = requests[i];
        } else {
            right[right_count++] = requests[i];
        }
    }

    // Sort the requests
    qsort(left, left_count, sizeof(int), compare);
    qsort(right, right_count, sizeof(int), compare);

    // Move towards the right end first
    total_head_movement += abs(head - right[right_count - 1]); // Move to the farthest right request
    head = right[right_count - 1]; // Update head position

    // Now jump to the farthest left request (as in C-Look)
    total_head_movement += abs(head - left[0]);
    head = left[0];  // Update head position

    // Service the left requests in order
    for (int i = 1; i < left_count; i++) {
        total_head_movement += abs(head - left[i]);
        head = left[i];
    }

    return total_head_movement;
}

// Driver code
int main() {
    int n, initial_head, max_track;
    
    // Get the number of requests
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);
    
    // Declare an array for disk requests
    int requests[n];

    // Get the request sequence
    printf("Enter the disk requests (separate each by space): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    // Get the initial head position and max track number
    printf("Enter the initial head position: ");
    scanf("%d", &initial_head);

    printf("Enter the maximum track number: ");
    scanf("%d", &max_track);

    printf("\nDisk Scheduling Algorithms: SSTF, SCAN, C-Look\n");

    // SSTF
    int total_head_movement_SSTF = SSTF(requests, n, initial_head);
    printf("SSTF: Total head movement = %d\n", total_head_movement_SSTF);

    // SCAN
    int total_head_movement_SCAN = SCAN(requests, n, initial_head, max_track);
    printf("SCAN: Total head movement = %d\n", total_head_movement_SCAN);

    // C-Look
    int total_head_movement_C_Look = C_Look(requests, n, initial_head, max_track);
    printf("C-Look: Total head movement = %d\n", total_head_movement_C_Look);

    return 0;
}

