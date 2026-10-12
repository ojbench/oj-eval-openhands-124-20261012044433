#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int x, k, p;
    scanf("%d %d %d", &x, &k, &p);
    
    // Initialize available seats for each segment (station i to i+1)
    vector<int> available(x + 1, k);
    
    for (int i = 0; i < p; i++) {
        int u, v, n;
        scanf("%d %d %d", &u, &v, &n);
        
        // Check if all segments from u to v-1 have at least n available seats
        bool can_fulfill = true;
        for (int j = u; j < v; j++) {
            if (available[j] < n) {
                can_fulfill = false;
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