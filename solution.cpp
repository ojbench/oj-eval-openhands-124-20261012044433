#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class LazySegmentTree {
private:
    vector<int> tree;
    vector<int> lazy;
    int n;
    
    void build(int node, int start, int end, int val) {
        if (start == end) {
            tree[node] = val;
        } else {
            int mid = (start + end) / 2;
            build(2 * node, start, mid, val);
            build(2 * node + 1, mid + 1, end, val);
            tree[node] = min(tree[2 * node], tree[2 * node + 1]);
        }
    }
    
    void push(int node, int start, int end) {
        if (lazy[node] != 0) {
            tree[node] += lazy[node];
            if (start != end) {
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }
    
    int query(int node, int start, int end, int l, int r) {
        push(node, start, end);
        if (r < start || end < l) {
            return INT_MAX;
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        int left_min = query(2 * node, start, mid, l, r);
        int right_min = query(2 * node + 1, mid + 1, end, l, r);
        return min(left_min, right_min);
    }
    
    void update(int node, int start, int end, int l, int r, int val) {
        push(node, start, end);
        if (r < start || end < l) {
            return;
        }
        if (l <= start && end <= r) {
            lazy[node] += val;
            push(node, start, end);
            return;
        }
        int mid = (start + end) / 2;
        update(2 * node, start, mid, l, r, val);
        update(2 * node + 1, mid + 1, end, l, r, val);
        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }
    
public:
    LazySegmentTree(int size, int initial_val) {
        n = size;
        tree.resize(4 * n);
        lazy.resize(4 * n, 0);
        build(1, 1, n, initial_val);
    }
    
    int query(int l, int r) {
        return query(1, 1, n, l, r);
    }
    
    void update(int l, int r, int val) {
        update(1, 1, n, l, r, val);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int x, k, p;
    scanf("%d %d %d", &x, &k, &p);
    
    // Create segment tree for x-1 segments (station i to i+1)
    LazySegmentTree st(x - 1, k);
    
    for (int i = 0; i < p; i++) {
        int u, v, n;
        scanf("%d %d %d", &u, &v, &n);
        
        // Check if all segments from u to v-1 have at least n available seats
        int min_available = st.query(u, v - 1);
        
        if (min_available >= n) {
            printf("T\n");
            // Update all segments from u to v-1 by subtracting n
            st.update(u, v - 1, -n);
        } else {
            printf("N\n");
        }
    }
    
    return 0;
}