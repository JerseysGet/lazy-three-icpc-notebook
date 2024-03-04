struct HLD {
  int n, timer = 0;
  vi top, tin, p, sub;
  HLD(vvi &adj) : n(sz(adj)), top(n), tin(n), p(n, -1), sub(n, 1) {
    vi ord(n + 1);
    for (int i = 0, t = 0, v = ord[i]; i < n; v = ord[++i])
      for (auto &to : adj[v])
        if (to != p[v]) p[to] = v, ord[++t] = to;
    for (int i = n - 1, v = ord[i]; i > 0; v = ord[--i]) sub[p[v]] += sub[v];
    for (int v = 0; v < n; v++)
      if (sz(adj[v])) iter_swap(begin(adj[v]), max_element(all(adj[v]), [&](int a, int b) { return make_pair(a != p[v], sub[a]) < make_pair(b != p[v], sub[b]); }));
    function<void(int)> dfs = [&](int v) {
      tin[v] = timer++;
      for (auto &to : adj[v])
        if (to != p[v]) {
          top[to] = (to == adj[v][0] ? top[v] : to);
          dfs(to);
        }
    };
    dfs(0);
  }
  int lca(int u, int v) {
    return process(u, v, [](...) {});
  }
  template <class B>
  int process(int a, int b, B op, bool ignore_lca = false) {
    for (int v;; op(tin[v], tin[b]), b = p[v]) {
      if (tin[a] > tin[b]) swap(a, b);
      if ((v = top[b]) == top[a]) break;
    }
    if (int l = tin[a] + ignore_lca, r = tin[b]; l <= r) op(l, r);
    return a;
  }
  template <class B>
  void subtree(int v, B op, bool ignore_lca = false) {
    if (sub[v] > 1 or !ignore_lca) op(tin[v] + ignore_lca, tin[v] + sub[v] - 1);
  }
};