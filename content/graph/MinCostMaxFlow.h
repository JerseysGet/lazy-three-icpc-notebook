template <const int MAX_N, typename flow_t, 
typename cost_t, flow_t FLOW_INF, 
cost_t COST_INF, const int SCALE = 16>
struct CostScalingMCMF {
#define sz(a) a.size()
#define zero_stl(v, sz) fill(v.begin(), v.begin() + (sz), 0)
  struct Edge {
    int v;
    flow_t c;
    cost_t d;
    int r;
    Edge() = default;
    Edge(int v, flow_t c, cost_t d, int r) : v(v), c(c), d(d), r(r) {}
  };
  vector<Edge> g[MAX_N];
  cost_t negativeSelfLoop;
  array<cost_t, MAX_N> pi, excess;
  array<int, MAX_N> level, ptr;
  CostScalingMCMF() { negativeSelfLoop = 0; }
  void clear() {
    negativeSelfLoop = 0;
    for (int i = 0; i < MAX_N; i++) g[i].clear();
  }
  void addEdge(int s, int e, flow_t cap, cost_t cost) {
    if (s == e) {
      if (cost < 0) negativeSelfLoop += cap * cost;
      return;
    }
    g[s].push_back(Edge(e, cap, cost, sz(g[e])));
    g[e].push_back(Edge(s, 0, -cost, sz(g[s]) - 1));
  }
  flow_t getMaxFlow(int V, int S, int T) {
    auto BFS = [&]() {
      zero_stl(level, V);
      queue<int> q;
      q.push(S);
      level[S] = 1;
      for (q.push(S); !q.empty(); q.pop()) {
        int v = q.front();
        for (const auto &e : g[v])
          if (!level[e.v] && e.c) q.push(e.v), level[e.v] = level[v] + 1;
      }
      return level[T];
    };
    function<flow_t(int, flow_t)> DFS = [&](int v, flow_t fl) {
      if (v == T || fl == 0) return fl;
      for (int &i = ptr[v]; i < (int)g[v].size(); i++) {
        Edge &e = g[v][i];
        if (level[e.v] != level[v] + 1 || !e.c) continue;
        flow_t delta = DFS(e.v, min(fl, e.c));
        if (delta) {
          e.c -= delta;
          g[e.v][e.r].c += delta;
          return delta;
        }
      }
      return flow_t(0);
    };
    flow_t maxFlow = 0, tmp = 0;
    while (BFS()) {
      zero_stl(ptr, V);
      while ((tmp = DFS(S, FLOW_INF))) maxFlow += tmp;
    }
    return maxFlow;
  }
  pair<flow_t, cost_t> maxflow(int N, int S, int T) {
    flow_t maxFlow = 0;
    cost_t eps = 0, minCost = 0;
    stack<int, vector<int>> stk;
    auto c_pi = [&](int v, const Edge &edge) { return edge.d + pi[v] - pi[edge.v]; };
    auto push = [&](int v, Edge &edge, flow_t delta, bool flag) {
      delta = min(delta, edge.c);
      edge.c -= delta;
      g[edge.v][edge.r].c += delta;
      excess[v] -= delta;
      excess[edge.v] += delta;
      if (flag && 0 < excess[edge.v] && excess[edge.v] <= delta) stk.push(edge.v);
    };
    auto relabel = [&](int v, cost_t delta) { pi[v] -= delta + eps; };
    auto lookAhead = [&](int v) {
      if (excess[v]) return false;
      cost_t delta = COST_INF;
      for (auto &e : g[v]) {
        if (e.c <= 0) continue;
        cost_t cp = c_pi(v, e);
        if (cp < 0)
          return false;
        else
          delta = min(delta, cp);
      }
      relabel(v, delta);
      return true;
    };
    auto discharge = [&](int v) {
      cost_t delta = COST_INF;
      for (int i = 0; i < sz(g[v]); i++) {
        Edge &e = g[v][i];
        if (e.c <= 0) continue;
        cost_t cp = c_pi(v, e);
        if (cp < 0) {
          if (lookAhead(e.v)) {
            i--;
            continue;
          }
          push(v, e, excess[v], true);
          if (excess[v] == 0) return;
        } else
          delta = min(delta, cp);
      }
      relabel(v, delta);
      stk.push(v);
    };
    zero_stl(pi, N);
    zero_stl(excess, N);
    for (int i = 0; i < N; i++)
      for (auto &e : g[i]) minCost += e.c * e.d, e.d *= MAX_N + 1, eps = max(eps, e.d);
    maxFlow = getMaxFlow(N, S, T);
    while (eps > 1) {
      eps /= SCALE;
      if (eps < 1) eps = 1;
      stk = stack<int, vector<int>>();
      for (int v = 0; v < N; v++)
        for (auto &e : g[v])
          if (c_pi(v, e) < 0 && e.c > 0) push(v, e, e.c, false);
      for (int v = 0; v < N; v++)
        if (excess[v] > 0) stk.push(v);
      while (stk.size()) {
        int top = stk.top();
        stk.pop();
        discharge(top);
      }
    }
    for (int v = 0; v < N; v++)
      for (auto &e : g[v]) e.d /= MAX_N + 1, minCost -= e.c * e.d;
    minCost = minCost / 2 + negativeSelfLoop;
    return {maxFlow, minCost};
  }
};

void solve() {
  CostScalingMCMF<102, int, int, 100, 100> flow;
  int n, m;
  cin >> n >> m;
  int start = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int inp;
      cin >> inp;
      if (inp) {
        flow.addEdge(i + 1, n + 1 + j, 1, 0);
        start++;
      } else
        flow.addEdge(i + 1, n + 1 + j, 1, 1);
    }
  }
  int counta = 0, countb = 0;
  for (int i = 0; i < n; i++) {
    int inp;
    cin >> inp;
    counta += inp;
    flow.addEdge(0, i + 1, inp, 0);
  }
  for (int i = 0; i < m; i++) {
    int inp;
    cin >> inp;
    countb += inp;
    flow.addEdge(n + i + 1, n + m + 1, inp, 0);
  }
  if (counta != countb) {
    cout << -1 << endl;
    return;
  }
  pii t = flow.maxflow(102, 0, n + m + 1);
  if (t.first != counta) {
    cout << -1 << endl;
    return;
  }
  cout << t.second + start + t.second - counta << endl;
}
