struct DSU {
    int n;
    vector<int> parent;
    vector<int> size;
    DSU(int _n) : n(_n), parent(n), size(n, 1) { iota(parent.begin(), parent.end(), 0); }
    int find_set(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find_set(parent[x]);
    }
    int getSize(int x) { return size[find_set(x)]; }  // returns size of component of x
    void union_sets(int x, int y) {
        x = find_set(x);
        y = find_set(y);
        if (x == y) return;
        if (size[x] > size[y]) {
            parent[y] = x;
            size[x] += size[y];
        } else {
            parent[x] = y;
            size[y] += size[x];
        }
    }
};