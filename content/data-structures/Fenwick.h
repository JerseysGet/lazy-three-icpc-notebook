template <typename T>
struct Fenwick {
    vector<T> bit;
    vector<T>& original;
    Fenwick(vector<T>& _arr) : bit(_arr.size(), 0LL), original(_arr) {
        int n = sz(_arr);
        for (int i = 0; i < n; i++) {
            bit[i] = bit[i] + _arr[i];
            if ((i | (i + 1)) < n) bit[(i | (i + 1))] = bit[(i | (i + 1))] + bit[i];
        }
    }
    // returns smallest index i, st. sum[0..i] >= x, returns -1 if no such i exists
    // returns n if x >= sum of array
    // ASSUMES NON NEGATIVE ENTRIES IN TREE
    int lower_bound(int x) {
        if (x < 0) return -1;
        if (x == 0) return 0;
        int pos = 0;
        for (int pw = 1LL << 20; pw; pw >>= 1)
            if (pw + pos <= sz(bit) and bit[pos + pw - 1] < x)
                pos += pw, x -= bit[pos - 1];
        return pos;
    }
    T query(int r) {
        assert(r < sz(bit));
        int ret = 0;
        for (r++; r > 0; r &= r - 1) ret += bit[r - 1];
        return ret;
    }
    T query(int l, int r) {
        T ret = query(r);
        if (l != 0) ret -= query(l - 1);
        return ret;
    }
    void update(int i, int x) {
        int n = bit.size();
        T diff = x - original[i];
        original[i] = x;
        for (; i < n; i = i | i + 1) bit[i] += diff;
    }
};