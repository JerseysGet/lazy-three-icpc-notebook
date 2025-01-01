struct SCC {
    int n;
    vi val, cc, z;
    vvi comps;
    SCC(vvi& adj) : n(sz(adj)), val(n), cc(n, -1) {
        int timer = 0;
        function<int(int)> dfs = [&] (int x) {
            int low = val[x] = ++timer, b; z.push_back(x);
            for (auto y : adj[x]) if (cc[y] < 0)
                low = min(low, val[y] ?: dfs(y));

            if (low == val[x]) {
                comps.push_back(vi());
                do {
                    b = z.back(); z.pop_back();
                    comps.back().push_back(b);
                    cc[b] = sz(comps) - 1;
                } while (x != b);
            } 
            return val[x] = low;
        };
        for (int i = 0; i < n; i++) if (cc[i] < 0) dfs(i);
    }
    int operator[](int i) { return cc[i]; }
    int size(int i) { return sz(comps[cc[i]]); }
};