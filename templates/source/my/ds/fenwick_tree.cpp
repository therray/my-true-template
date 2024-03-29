template<typename T> struct fenwick {
  int n;
  vector<T> tree;
 
  void build(vector<T> x) {        
    vector<T> pref(n + 1);
    for (int i = 1; i <= n; ++i) {
      pref[i] = pref[i - 1] + x[i - 1];
      tree[i] = pref[i] - pref[i - (i & -i)];
    }
  }
 
  fenwick(int _n, T def = T{}) : n(_n) {
    tree.resize(n + 1);
	tree[0] = def;
    build(vector<T>(n, def));
  }

 void modify(int i, T x) {
    assert(i >= 0 && i < n);
    ++i;
    while (i <= n) {
      tree[i] += x;
      i += (i & -i);
    }
  }

  T get(int i) {
    assert(i >= 0 && i < n);
    ++i;
    T res = tree[i];
	i -= (i & -i);
    while (i > 0) {
      res += tree[i];
      i -= (i & -i);
    }
    return res;
  }

  T get(int l, int r) {
    return (l == 0 ? get(r) : get(r) - get(l - 1));
  }

  template<class F, typename... Q> int find_first(F op, Q... qs) { 
    //true for suffix, find first index which returns true from suffix
    int cur = 0;
    T sum = tree[0];
    for (int i = __lg(n); i >= 0; --i) {
      if (cur + (1 << i) <= n && !op(sum + tree[cur + (1 << i)], qs...)) {
        cur += (1 << i);
        sum = sum + tree[cur];
      }
    }
    return (cur == n ? -1 : cur);
  }

  template<class F, typename... Q> int find_last(F op, Q... qs) { 
    //true for prefix, find last index which returns true from prefix
    int cur = 0;
    T sum = tree[0];
    for (int i = __lg(n); i >= 0; --i) {
      if (cur + (1 << i) <= n && op(sum + tree[cur + (1 << i)], qs...)) {
        cur += (1 << i);
        sum = sum + tree[cur];
      }
    }
    return (cur == 0 ? -1 : cur - 1);
  }

  void clear() {
    build(vector<T>(n, tree[0]));
  }
};
