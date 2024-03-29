
vector<int> SCC(vector<vector<int>> g) {
  int n = int(g.size());
  vector<int> res(n), low(n), tin(n);
  vector<bool> vis(n), act(n);
  stack<int> st;
  int t = 0;
  int c = 0;
  function<void(int)> Dfs = [&](int v) {
    vis[v] = true;
    act[v] = true;    
    low[v] = tin[v] = t++;
    st.push(v);
    for (auto u : g[v]) {
      if (!vis[u]) {
        Dfs(u);
      }
      if (act[u]) {
        low[v] = min(low[v], low[u]);
      }
    }
	
    if (tin[v] == low[v]) {
      while (act[v]) {
        int u = st.top();
        st.pop();
        act[u] = false;
        res[v] = c;
      }
      ++c;
    }
  };

  for (int i = 0; i < n; ++i) {
    if (!vis[i]) {
      Dfs(i);
    }
  }
  return res;
}
