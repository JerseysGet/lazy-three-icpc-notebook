struct SCC {
  int n;
  vvi &adjLists, transposeLists;
  vi scc, leader;
  int sccCount = 0;
  vi sccSize;
  SCC(vvi& _adjLists) : n(sz(_adjLists)), adjLists(_adjLists), transposeLists(n), scc(n, -1), leader(n, -1) {
    for (int u = 0; u < n; u++) {
      for (int v : adjLists[u]) transposeLists[v].push_back(u);
    }
    vb visited(n);
    stack<int> topoSort;
    function<void(int)> topoDFS = [&](int from) {
      visited[from] = true;
      for (auto to : adjLists[from]) {
        if (visited[to]) continue;
        topoDFS(to);
      }

      topoSort.push(from);
    };
    for (int i = 0; i < n; i++)
      if (not visited[i]) topoDFS(i);
    visited.assign(n, false);
    int sccPtr = 0;
    sccSize.assign(n, 0);
    function<void(int)> sccDFS = [&](int from) {
      scc[from] = sccPtr;
      sccSize[sccPtr]++;
      visited[from] = true;
      for (auto to : transposeLists[from]) {
        if (visited[to]) continue;
        sccDFS(to);
      }
    };
    while (not empty(topoSort)) {
      int i = topoSort.top();
      topoSort.pop();
      if (visited[i]) continue;
      sccDFS(i);
      leader[sccPtr] = i;
      sccPtr++;
    }

    sccCount = sccPtr;
  }
  int size(int index) {  // Returns size of scc of index
    return sccSize[scc[index]];
  }
  const int& operator[](int index) {
    return scc[index];
  }
  vi indexInCycle;
  void sccEnumeration() {
    indexInCycle.assign(n, 0);
    vb visited(n);
    int index = 0;
    function<void(int, int)> sccDFS = [&](int from, int sc) {
      indexInCycle[from] = index++;
      visited[from] = true;
      for (auto to : adjLists[from]) {
        if (scc[to] != sc) continue;
        if (visited[to]) continue;
        sccDFS(to, sc);
      }
    };
    for (int i = 0; i < sccCount; i++) {
      index = 0;
      sccDFS(leader[i], i);
    }
  }
};