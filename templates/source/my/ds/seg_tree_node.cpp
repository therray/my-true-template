struct node {
  //variables default values should be uneffective
  @@HERE@@
  void modify(int l, int r, ..) {
    assert(l == l && r == r); // no to warnings
    ..
  }

  node operator+ (const node& x) {
    node res;
    ..
    return res;
  }

  int get (int l, int r) {
    return l + r;
  }
};
