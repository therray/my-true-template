template<typename T, typename max_lift_type = int, typename F = function<T(const T&, const T&)>>
struct ValueLift {
  bool VALUES_ON_VERTICES;
  BinaryLift<max_lift_type> bl;
  int &n = bl.n;
  int &lg = bl.lg;
  max_lift_type &max_lift = bl.max_lift;
  bool &built = bl.built;
  bool &lca_built = bl.built;
  vector<vector<int>> &anc = bl.anc;
  vector<int> &d = bl.d;
  F op;
  T def;
  vector<vector<T>> lift;
  void build(vector<T> values) {
    lift.resize(lg, vector<T>(n));
    lift[0] = values;
    for (int j = 1; j < lg; ++j) {
      for (int i = 0; i < n; ++i) {
        lift[j][i] = op(lift[j - 1][anc[j - 1][i]], lift[j - 1][i]);
      }
    }
  }

  bool reserve(max_lift_type new_max_lift) {
    int old_lg = lg;
    if (!reserve(new_max_lift)) {
      return false;
    }
    lift.resize(lg);
    for (int j = old_lg; j < lg; ++j) {
      lift[j].resize(n);
      for (int i = 0; i < n; ++i) {
        lift[j][i] = op(lift[j - 1][anc[j - 1][i]], lift[j - 1][i]);
      }
    }
    return true;
  }

  ValueLift() { }
  ValueLift(vector<int> first, vector<T> values, F _op, T _def = T{}, bool _VALUES_ON_VERTICES = true) : def(_def), op(_op) {
    bl = BinaryLift<max_lift_type>(first);
    build(values);
    VALUES_ON_VERTICES = _VALUES_ON_VERTICES;
  }

  ValueLift(vector<vector<pair<int, T>>> g, F _op, T _def = T{}) : def(_def), op(_op) {
    vector<vector<int>> bl_g(int(g.size()));
    for (int i = 0; i < int(g.size()); ++i) {
      for (auto[u, foo] : g[i]) {
        bl_g[i].push_back(u);
      }
    }
    bl = BinaryLift<max_lift_type>(bl_g, -1);
    vector<T> values(n, def);
    for (int i = 0; i < n; ++i) {
      for (auto[u, w] : g[i]) {
        if (anc[0][u] == i) {
          values[u] = w;
        }
      }
    }
    build(values);
    VALUES_ON_VERTICES = false;
  }

  ValueLift(vector<vector<int>> g, vector<T> values, F _op, T _def = T{}) : def(_def), op(_op) {
    bl = BinaryLift<max_lift_type>(g, -1);
    build(values);
    VALUES_ON_VERTICES = true;
  }

  int go(int v, max_lift_type x) {
    return bl.go(v, x);
  }

  int go_from_path(int v, int u, int k = 2) {
    return bl.go_from_path(v, u, k);
  }

  int lca(int v, int u) {
    return bl.lca(v, u);
  }

  int dist(int v, int u) {
    return bl.dist(v, u);
  }

  T get(int v, max_lift_type x) {
  assert(x >= 0 && x <= max_lift);
    T res = def;
    for (int j = 0; x > 0; x >>= 1, ++j) {
      if (x & 1) {
        res = op(res, lift[j][v]);
        v = anc[j][v];
      }
    }
    return res;
  }

  T path(int v, int u) {
    int l = lca(v, u);
    T res = op(get(v, d[v] - d[l]), get(u, d[u] - d[l]));
    if (VALUES_ON_VERTICES) {
      res = op(res, get(l, 1));
    }
    return res;
  }
};
/*
  constructor(first, values, op, def, values_on_vertices): for directed graphs
  or graphs which you can directly get parents and values of edges/vertices
  as input, values_on_vertices is true as default
  constructor(g[][][], op, def): regular tree with values on edges
  constructor(g[][], values, op, def): regular tree with values on vertices
  reserve(max_lift): reserves enough space for max_lift (default max_lift is n - 1)
  go(v, x): go x edges from v
  lca(v, u): lowest common ancestor of v and u
  dist(v, u): distance between v and u
  get(v, x): op sum of x values from v
  path(v, u): op sum of values between v and u
  go_from_path(v, u, k): start at v and go k - 1 edges from path between v to u
*/
