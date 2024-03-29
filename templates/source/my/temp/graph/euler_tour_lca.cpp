struct EulerTourLCA {
  int n;
  vector<int> d, tin, tout;
  SparseTable<int> st;
  EulerTourLCA(vector<vector<int>> g, int root = 0) {
    n = int(g.size());
    vector<int> tour;
    d.resize(n);
    tin.resize(n);
    tout.resize(n);
    function<void(int, int)> Dfs = [&](int v, int pr) {
      tin[v] = tout[v] = int(tour.size());
      tour.push_back(v);
      for (auto u : g[v]) {
        if (u == pr) {
          continue;
        }
        d[u] = d[v] + 1;
        Dfs(u, v);
        tout[v] = int(tour.size());
        tour.push_back(v);
      }
    };
    if (root == -1) {
      for (int i = 0; i < n; ++i) {
        if (d[i] == 0) {
          Dfs(i, -1);
        }
      }
    } else {
      Dfs(root, -1);
    }  
    st = SparseTable<int>(tour, [&](int x, int y) {
      return (d[x] < d[y] ? x : y);
    }); 
  }

  int is_ancestor(int v, int u) {
    return tin[v] <= tin[u] && tout[v] >= tout[u];  
  }

  int lca(int v, int u) {
    assert(v >= 0 && u >= 0 && v < n && u < n);
    if (tin[v] > tin[u]) {
      swap(v, u);
    }
    return (is_ancestor(v, u) ? v : st.get(tout[v], tin[u]));
  } 
};
