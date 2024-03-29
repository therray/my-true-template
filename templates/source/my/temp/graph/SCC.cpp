 
vector<int> SCC(vector<vector<int>> g) {
  int n = int(g.size());
  vector<int> ord;
  vector<bool> vis(n);
  function<void(int)> Dfs = [&](int v) {
    vis[v] = true;
    for (auto u : g[v]) {
      if (!vis[u]) {
        Dfs(u);
      }
    }
    ord.push_back(v);
  };
  vector<vector<int>> rg(n);
  for (int v = 0; v < n; ++v) {
    for (auto u : g[v]) {     
      assert(u >= 0 && u < n);
      rg[u].push_back(v);
    }
  }

  vector<int> comp(n, -1);
  function<void(int)> Dfs_comp = [&](int v) {
    for (auto u : rg[v]) {
      if (comp[u] == -1) {
        comp[u] = comp[v];
        Dfs_comp(u);
      }
    }
  };

  for (int i = 0; i < n; ++i) {
    if (!vis[i]) {
      Dfs(i);
    }
  }
  reverse(ord.begin(), ord.end());
  int c = 0;
  for (auto v : ord) {
    if (comp[v] == -1) {
      comp[v] = c++;
      Dfs_comp(v);
    }
  }
  return comp;
}
