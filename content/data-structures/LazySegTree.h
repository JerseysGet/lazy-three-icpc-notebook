template <typename T, typename U>
struct LazySegTree {
  int n, off, ct;
  vector<T> t;
  const T id;
  const U noop;
  vector<bool> dirty;
  vector<U> prop;
  LazySegTree(const vector<T> &a, T _id = T(), U _noop = U()) : n(sz(a)), t(2 * n), id(_id), noop(_noop), dirty(2 * n), prop(2 * n, noop) {
    off = 1 << 32 - __builtin_clz(n);
    ct = 2 * (n ^ off >> 1);
    copy_n(begin(a), ct, off + begin(t));
    copy_n(rbegin(a), n - ct, rend(t) - off);
    for (int i = n - 1; i >= 1; i--) t[i] = t[2 * i] + t[2 * i + 1];
  }
  int i2leaf(int i) { return i + off - (i < ct ? 0 : n); }
  int leaf2i(int l) { return l - off + (l < off ? n : 0); }
  void apply(int i, U &upd) {
    t[i] = upd(t[i]);
    if (i < n) {
      prop[i] = prop[i] + upd;
      dirty[i] = true;
    }
  }
  void rebuild(int i) {
    for (int l = i / 2; l; l /= 2)
      t[l] = prop[l](t[2 * l] + t[2 * l + 1]);
  }
  void propagate(int i) {
    for (int h = 31 - __builtin_clz(i); h > 0; h--) {
      int l = i >> h;
      if (dirty[l]) {
        apply(2 * l, prop[l]);
        apply(2 * l + 1, prop[l]);
        prop[l] = noop, dirty[l] = false;
      }
    }
  }
  template <bool isupd, typename F>
  T process(int l, int r, F f) {
    int i = i2leaf(l), j = i2leaf(r);
    propagate(i), propagate(j);
    l = i * (1 + (l >= ct));
    r = j * (1 + (r >= ct));
    r += (r >= 2 * n);
    T resl(id), resr(id);
    for (; l <= r; l /= 2, r /= 2) {
      if (l & 1) resl = resl + f(l++);
      if (!(r & 1)) resr = f(r--) + resr;
    }
    if constexpr (isupd) return rebuild(i), rebuild(j), id;
    return resl + resr;
  }
  T query(int l, int r) {
    return process<false>(l, r, [&](int i) { return t[i]; });
  }
  T update(int l, int r, U upd) {
    return process<true>(l, r, [&](int i) { apply(i, upd); return id; });
  }
};