const int N = 5e5 + 10, LOGN = 18;
int L[N * LOGN], R[N * LOGN], ST[N * LOGN];
int nodeid = 0;
// usage newrootId = update(i, 0, n - 1, val, oldrootId)
// [update index i to val]
int update(int pos, int l, int r, int val, int id) {
  if (pos < l or pos > r) return id;
  int ID = ++nodeid, m = (l + r) / 2;
  if (l == r) return (ST[ID] = val, ID);
  L[ID] = update(pos, l, m, val, L[id]);
  R[ID] = update(pos, m + 1, r, val, R[id]);
  return (ST[ID] = ST[L[ID]] + ST[R[ID]], ID);
}
// usage query(l, r, 0, n - 1, rootId)
int query(int ql, int qr, int l, int r, int id) {
  if (ql > r or qr < l) return 0;
  if (ql <= l and r <= qr) return ST[id];
  int m = (l + r) / 2;
  return (query(ql, qr, l, m, L[id])) + query(ql, qr, m + 1, r, R[id]);
}
// searches for upper bound of x, call as descent(0, n - 1, x, rootId)
int descent(int l, int r, int x, int id) {
  if (l == r) return l;
  int m = (l + r) / 2;
  int leftCount = ST[L[id]];
  if (leftCount <= x) {
    // is in right half
    return descent(m + 1, r, x - leftCount, R[id]);
  } else {
    // is in left half
    return descent(l, m, x, L[id]);
  }
}