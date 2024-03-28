/*

ts.either(x, y);
ts.either(~x, ~y); these two do x xor y

ts.setValue(x, x); assert x is true

use ~x to denote not x

call ts.solve() to run the solver, returns if a solution exists
if exists: ts.values[i] contains the assignments

*/


struct TwoSat {
    int N;
    vector<vi> gr;
    vi values;  // 0 = false, 1 = true

    TwoSat(int n = 0) : N(n), gr(2 * n) {}

    int addVar() {  // (optional)
        gr.emplace_back();
        gr.emplace_back();
        return N++;
    }

    void either(int f, int j) {
        f = max(2 * f, -1 - 2 * f);
        j = max(2 * j, -1 - 2 * j);
        gr[f].push_back(j ^ 1);
        gr[j].push_back(f ^ 1);
    }
    void setValue(int x) { either(x, x); }

    void atMostOne(const vi& li) {  // (optional)
        if (sz(li) <= 1) return;
        int cur = ~li[0];
        for (int i = 2; i < sz(li); i++) {
            int next = addVar();
            either(cur, ~li[i]);
            either(cur, next);
            either(~li[i], next);
            cur = ~next;
        }
        either(cur, ~li[1]);
    }

    vi val, comp, z;
    int time = 0;
    int dfs(int i) {
        int low = val[i] = ++time, x;
        z.push_back(i);
        for (int e : gr[i])
            if (!comp[e])
                low = min(low, val[e] ?: dfs(e));
        if (low == val[i]) do {
                x = z.back();
                z.pop_back();
                comp[x] = low;
                if (values[x >> 1] == -1)
                    values[x >> 1] = x & 1;
            } while (x != i);
        return val[i] = low;
    }

    bool solve() {
        values.assign(N, -1);
        val.assign(2 * N, 0);
        comp = val;
        for (int i = 0; i < 2 * N; i++)
            if (!comp[i]) dfs(i);
        for (int i = 0; i < N; i++)
            if (comp[2 * i] == comp[2 * i + 1]) return 0;
        return 1;
    }
};