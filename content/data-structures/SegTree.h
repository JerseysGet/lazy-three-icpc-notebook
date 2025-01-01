template <typename T, typename F>
struct SegTree {
	int n, off, ct;
	vector<T> t;
	const T id;
	F f;
	SegTree(const vector<T>& a, T _id, F _f)
		: n(sz(a)), off(1 << 32 - __builtin_clz(n)), ct(n ^ off >> 1), t(2 * n), id(_id), f(_f) {
		for (int i = 0; i < 2 * ct; i++) t[off + i] = a[i];
		for (int i = 2 * ct; i < n; i++) t[i + off - n] = a[i];
		for (int i = n - 1; i >= 1; i--) t[i] = f(t[2 * i], t[2 * i + 1]);
	}
	int i2leaf(int i) { return i + off - (i < 2 * ct ? 0 : n); }
	int leaf2i(int l) { return l - off + (l < off ? n : 0); }
	T query(int l, int r) {
		l = (l < 2 * ct) ? (l + off) : 2 * (l + off - n);
		r = (r < 2 * ct) ? (r + off) : 2 * (r + off - n);
		r += (r >= 2 * n);
		T resl(id), resr(id);
		for (; l <= r; l >>= 1, r >>= 1) {
				if (l == r) {
						resl = f(resl, t[l]);
						break;
				}
				if (l & 1) resl = f(resl, t[l++]);
				if (!(r & 1)) resr = f(t[r--], resr);
		}
		return f(resl, resr);
	}
	void update(int v, T value) {
		for (t[v = i2leaf(v)] = value; v >>= 1;)
				t[v] = f(t[2 * v], t[2 * v + 1]);
	}
	int lower_bound(int k) {
		if (t[1] < k) return n;
		T rem = id;
		int v = 1;
		while (v < n) {
				T resl = f(rem, t[2 * v]);
				if (resl >= k) {
						v = 2 * v;
				} else {
						rem = resl;
						v = 2 * v + 1;
				}
		}
		return leaf2i(v);
	}
};