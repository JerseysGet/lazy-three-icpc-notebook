template <typename T, typename F>
struct SegTree {
    int n;
    vector<T> t;
    const T id;
    F f;
    SegTree(const vector<T> &a, T id, F f) : n(sz(a)), t(2 * n), id(id), f(f) {
        for (int i = 0; i < n; i++) t[n + i] = a[i];
        for (int i = n - 1; i >= 1; i--)
            t[i] = f(t[2 * i], t[2 * i + 1]);
    }
    T query(int l, int r) {
        T resl(id), resr(id);
        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l == r) {
                resl = f(resl, t[l]);
                break;
            }
            if (l & 1) resl = f(resl, t[l++]);
            if (!(r & 1)) resr = f(t[r--], resr);
        }
        return f(resl, resr);
    }
    void update(int v, T value) {
        for (t[v += n] = value; v >>= 1;)
            t[v] = f(t[2 * v], t[2 * v + 1]);
    }
};