template<typename max_lift_type = int> struct BinaryLift {
  int n, lg = 1;
  max_lift_type max_lift = 1;
  vector<vector<int>> anc;
  vector<int> d;
  bool built = false;
  bool lca_built = false;

  bool reserve(max_lift_type new_max_lift) {
    assert(built);
    assert(new_max_lift >= 0);
    if (new_max_lift <= max_lift) {
      return false;
    }
    int new_lg = __lg(new_max_lift) + 1;
    anc.resize(new_lg);
    for (int j = lg; j < new_lg; ++j) {
      anc[j].resize(n);
      for (int i = 0; i < n; ++i) {
        anc[j][i] = anc[j - 1][anc[j - 1][i]];
      }
    }
    swap(max_lift, new_max_lift);
    swap(lg, new_lg);
    return true;
  }

  BinaryLift() { }
  BinaryLift(vector<int> first) {
    n = int(first.size());
    for (int i = 0; i < n; ++i) {
      if (first[i] < 0 || first[i] >= n) {
        first[i] = i;
      }
    }
    lca_built = false;
    for (int i = 0; i < n; ++i) {
      lca_built |= (first[i] == i);
    }
    anc.resize(1, first);
    built = true;
    reserve(n - 1);
  }

  BinaryLift(const vector<vector<int>>& g, int root = 0) {
    n = int(g.size());
    vector<int> par(n, root);
    d.resize(n);
    auto Bfs = [&](int s) {
      queue<int> que;
      que.push(s);
      while (!que.empty()) {
        int v = que.front();
        que.pop();
        for (auto u : g[v]) {
          if (u != par[v]) {
            d[u] = d[v] + 1;
            par[u] = v;
            que.push(u);
          }
        }
      }
    };

    if (root == -1) {
      for (int i = 0; i < n; ++i) {
        if (par[i] == -1) {
          par[i] = i;
          Bfs(i);
        }
      }
    } else {
      Bfs(root);
    }
    anc.resize(1, par);
    built = true;
    lca_built = true;
    reserve(n - 1);
  }

  int go(int v, max_lift_type x) {
    assert(built);
    assert(v >= 0 && v < n);
    assert(x >= 0 && x <= max_lift);
    for (int i = 0; x > 0; ++i, x >>= 1) {
      if (x & 1) {
        v = anc[i][v];
      }
    }
    return v;
  }

  int lca(int v, int u) {
    assert(lca_built);
    assert(max_lift <= n);
    assert(v >= 0 && v < n && u >= 0 && u < n);
    if (d[v] > d[u]) {
      swap(v, u);
    }
    u = go(u, d[u] - d[v]);
    if (v == u) {
      return v;
    }
    for (int i = lg - 1; i >= 0; --i) {
      if (anc[i][v] != anc[i][u]) {
        v = anc[i][v];
        u = anc[i][u];
      }
    }
    return anc[0][v];
  }

  int dist(int v, int u) {
    return d[v] + d[u] - d[lca(v, u)] * 2;
  }

  int go_from_path(int v, int u, int k = 2) {
    assert(built);
    assert(v >= 0 && v < n && u >= 0 && u < n);
    assert(k <= dist(v, u) + 1);
    int l = lca(v, u);
    int v_l = dist(v, l);
    if (v_l + 1 >= k) {
      return go(v, k - 1);
    } else {
      int left = dist(l, u) - (k - v_l - 1);
      return go(u, left);
    }
  }
};
/*
  constructor(edge[]): for directed graphs which all vertices
  has one out degree or trees which you can get directly parents as input
  constructor(g[][], root): regular binary lift build, for unrooted forests, root = -1
  reserve(max_lift): reserves enough space for max_lift (default max_lift is n - 1)
  go(v, x): go x edges from v
  lca(v, u): lowest common ancestor of v and u
  dist(v, u): distance between v and u
  go_from_path(v, u, k): start at v and go k - 1 edges from path between v to u
*/

