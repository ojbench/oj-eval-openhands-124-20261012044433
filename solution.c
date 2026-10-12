#include <stdio.h>

#define MAX_STATIONS 1000005

int available[MAX_STATIONS];

int main() {
    int x, k, p;
    scanf("%d %d %d", &x, &k, &p);
    
    // Initialize available seats for each segment (station i to i+1)
    for (int i = 1; i <= x; i++) {
        available[i] = k;
    }
    
    for (int i = 0; i < p; i++) {
        int u, v, n;
        scanf("%d %d %d", &u, &v, &n);
        
        // Check if all segments from u to v-1 have at least n available seats
        int can_fulfill = 1;
        for (int j = u; j < v; j++) {
            if (available[j] < n) {
                can_fulfill = 0;
                break;
            }
        }
        
        if (can_fulfill) {
            printf("T\n");
            // Update all segments from u to v-1
            for (int j = u; j < v; j++) {
                available[j] -= n;
            }
        } else {
            printf("N\n");
        }
    }
    
    return 0;
}