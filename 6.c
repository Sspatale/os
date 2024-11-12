#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PAGES 100

// Function Prototypes
void FCFS(int pages[], int n, int frames);
void LRU(int pages[], int n, int frames);
void Optimal(int pages[], int n, int frames);
int getNextUse(int pages[], int n, int current_index, int page);

// Main Function
int main() {
    int n, frames;
    int pages[MAX_PAGES];

    // Input the number of pages and the page reference string
    printf("Enter the number of page references: ");
    scanf("%d", &n);
    printf("Enter the page reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    // Input the number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &frames);

    // Check that frame size is at least 3
    if (frames < 3) {
        printf("Frame size must be at least 3.\n");
        return -1;
    }

    // Simulate the page replacement algorithms
    printf("\n--- FCFS Page Replacement ---\n");
    FCFS(pages, n, frames);

    printf("\n--- LRU Page Replacement ---\n");
    LRU(pages, n, frames);

    printf("\n--- Optimal Page Replacement ---\n");
    Optimal(pages, n, frames);

    return 0;
}

// FCFS Page Replacement Algorithm
void FCFS(int pages[], int n, int frames) {
    int page_frames[frames];
    int page_faults = 0;
    int current_frame = 0;

    // Initialize the frames with -1 (empty)
    for (int i = 0; i < frames; i++) {
        page_frames[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        bool found = false;

        // Check if the page is already in the frame
        for (int j = 0; j < frames; j++) {
            if (page_frames[j] == page) {
                found = true;
                break;
            }
        }

        if (!found) {
            // Page fault occurs
            page_frames[current_frame] = page;
            current_frame = (current_frame + 1) % frames;
            page_faults++;
        }

        printf("Page reference: %d, Frames: [", page);
        for (int j = 0; j < frames; j++) {
            if (page_frames[j] == -1) {
                printf(" -,");
            } else {
                printf(" %d,", page_frames[j]);
            }
        }
        printf("] Page faults: %d\n", page_faults);
    }
}

// LRU Page Replacement Algorithm
void LRU(int pages[], int n, int frames) {
    int page_frames[frames];
    int page_faults = 0;

    // Initialize the frames with -1 (empty)
    for (int i = 0; i < frames; i++) {
        page_frames[i] = -1;
    }

    // Simulate the LRU algorithm
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        bool found = false;

        // Check if the page is already in the frame
        for (int j = 0; j < frames; j++) {
            if (page_frames[j] == page) {
                found = true;

                // Move the page to the front (indicating recent use)
                for (int k = j; k > 0; k--) {
                    page_frames[k] = page_frames[k - 1];
                }
                page_frames[0] = page;
                break;
            }
        }

        if (!found) {
            // Page fault occurs
            for (int j = frames - 1; j > 0; j--) {
                page_frames[j] = page_frames[j - 1];
            }
            page_frames[0] = page;
            page_faults++;
        }

        printf("Page reference: %d, Frames: [", page);
        for (int j = 0; j < frames; j++) {
            if (page_frames[j] == -1) {
                printf(" -,");
            } else {
                printf(" %d,", page_frames[j]);
            }
        }
        printf("] Page faults: %d\n", page_faults);
    }
}

// Optimal Page Replacement Algorithm
void Optimal(int pages[], int n, int frames) {
    int page_frames[frames];
    int page_faults = 0;

    // Initialize the frames with -1 (empty)
    for (int i = 0; i < frames; i++) {
        page_frames[i] = -1;
    }

    // Simulate the Optimal page replacement
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        bool found = false;

        // Check if the page is already in the frame
        for (int j = 0; j < frames; j++) {
            if (page_frames[j] == page) {
                found = true;
                break;
            }
        }

        if (!found) {
            // Page fault occurs
            int farthest = -1;
            int replace_index = -1;

            // Find the page that will not be used for the longest time in the future
            for (int j = 0; j < frames; j++) {
                int next_use = getNextUse(pages, n, i, page_frames[j]);

                if (next_use == -1) {
                    replace_index = j;
                    break;
                }

                if (next_use > farthest) {
                    farthest = next_use;
                    replace_index = j;
                }
            }

            // Replace the page at replace_index with the new page
            page_frames[replace_index] = page;
            page_faults++;
        }

        printf("Page reference: %d, Frames: [", page);
        for (int j = 0; j < frames; j++) {
            if (page_frames[j] == -1) {
                printf(" -,");
            } else {
                printf(" %d,", page_frames[j]);
            }
        }
        printf("] Page faults: %d\n", page_faults);
    }
}

// Helper function to find the next use of a page in the reference string
int getNextUse(int pages[], int n, int current_index, int page) {
    for (int i = current_index + 1; i < n; i++) {
        if (pages[i] == page) {
            return i;
        }
    }
    return -1;  // Page not used in the future
}

