/* Description: Complexity O(VE log U) where U = max {cap}.
 * O(min(E^{1/2}, V^{2/3})E) if $U = 1$; O(\sqrt{V}E) for bipartite matching.
 */
template <class T = int>
class Dinic {
 public:
  struct Edge {
    Edge(int a, T b) {
      to = a;
      cap = b;
    }
    int to;
    T cap;
  };

  Dinic(int n) {
    edges.resize(n);
    this->n = n;
  }

  T maxFlow(int src, int sink) {
    T ans = 0;
    while (bfs(src, sink)) {
      T flow;
      pt = vector<int>(n, 0);
      while ((flow = dfs(src, sink))) {
        ans += flow;
      }
    }
    return ans;
  }

  void addEdge(int from, int to, T cap = 1) {
    edges[from].push_back(list.size());
    list.push_back(Edge(to, cap));
    edges[to].push_back(list.size());
    list.push_back(Edge(from, 0));
  }

 private:
  int n;
  vector<vector<int>> edges;
  vector<Edge> list;
  vector<int> h, pt;
  T dfs(int on, int sink, T flow = 1e9) {
    if (flow == 0) {
      return 0;
    }
    if (on == sink) {
      return flow;
    }
    for (; pt[on] < sz(edges[on]); pt[on]++) {
      int cur = edges[on][pt[on]];
      if (h[on] + 1 != h[list[cur].to]) {
        continue;
      }
      T got = dfs(list[cur].to, sink, min(flow, list[cur].cap));
      if (got) {
        list[cur].cap -= got;
        list[cur ^ 1].cap += got;
        return got;
      }
    }
    return 0;
  }
  bool bfs(int src, int sink) {
    h = vector<int>(n, n);
    h[src] = 0;
    queue<int> q;
    q.push(src);
    while (!q.empty()) {
      int on = q.front();
      q.pop();
      for (auto a : edges[on]) {
        if (list[a].cap == 0) {
          continue;
        }
        int to = list[a].to;
        if (h[to] > h[on] + 1) {
          h[to] = h[on] + 1;
          q.push(to);
        }
      }
    }
    return h[sink] < n;
  }
};
void solve() {
  int n, m;
  cin >> n >> m;
  vi a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  Dinic<int> flow(n + 2);
  map<int, map<int, int>> factors;
  for (int i = 0; i < n; i++) {
    for (int j = 2; j * j <= a[i]; j++) {
      while (a[i] % j == 0) {
        factors[j][i + 1]++;
        a[i] /= j;
      }
    }
    if (a[i] > 1) {
      factors[a[i]][i + 1]++;
    }
  }
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    if (u % 2 == 0) {
      swap(u, v);
    }
    flow.addEdge(u, v, 100);
  }
  int ans = 0;
  for (auto t : factors) {
    Dinic<int> tempflow = flow;
    for (auto t1 : t.second) {
      if (t1.first % 2 == 0) {
        tempflow.addEdge(t1.first, n + 1, t1.second);
      } else {
        tempflow.addEdge(0, t1.first, t1.second);
      }
    }
    ans += tempflow.maxFlow(0, n + 1);
  }
  cout << ans << endl;
}