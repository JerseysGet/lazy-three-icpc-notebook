/* Description: Can be used for convolutions modulo specific nice primes of the form 2^a b+1, where the convolution result has size at most 2^a
 * (125000001 << 3) + 1 = 1e9 + 7, therefore do not use this for M = 1e9 + 7. 
 * For $p < 2^30$ there is also e.g. (5 << 25, 3), (7 << 26, 3), 
 * For other primes/integers, use two different primes and combine with CRT. (479 << 21, 3) and (483 << 21, 5). The last two are > 10^9
 * Inputs must be in [0, mod).
 */
// Requires mod func
const int M = 998244353;
const int root = 3;
// (119 << 23) + 1, root = 3;  // for M = 998244353
void ntt(int* x, int* temp, int* roots, int N, int skip) {
  if (N == 1) return;
  int n2 = N / 2;
  ntt(x, temp, roots, n2, skip * 2);
  ntt(x + skip, temp, roots, n2, skip * 2);
  for (int i = 0; i < N; i++) temp[i] = x[i * skip];
  for (int i = 0; i < n2; i++) {
    int s = temp[2 * i], t = temp[2 * i + 1] * roots[skip * i];
    x[skip * i] = (s + t) % M;
    x[skip * (i + n2)] = (s - t) % M;
  }
}
void ntt(vi& x, bool inv = false) {
  int e = pw(root, (M - 1) / sz(x));
  if (inv) e = pw(e, M - 2);
  vi roots(sz(x), 1), temp = roots;
  for (int i = 1; i < sz(x); i++) roots[i] = roots[i - 1] * e % M;
  ntt(&x[0], &temp[0], &roots[0], sz(x), 1);
}
// Usage: just pass the two coefficients list to get a*b (modulo M)
vi conv(vi a, vi b) {
  int s = sz(a) + sz(b) - 1;
  if (s <= 0) return {};
  int L = s > 1 ? 32 - __builtin_clzll(s - 1) : 0, n = 1 << L;
  if (s <= 200) {  // (factor 10 optimization for |a|,|b| = 10)
    vi c(s);
    for (int i = 0; i < sz(a); i++)
      for (int j = 0; j < sz(b); j++)
        c[i + j] = (c[i + j] + a[i] * b[j]) % M;
    return c;
  }
  a.resize(n);
  ntt(a);
  b.resize(n);
  ntt(b);
  vi c(n);
  int d = pw(n, M - 2);
  for (int i = 0; i < n; i++) c[i] = a[i] * b[i] % M * d % M;
  ntt(c, true);
  c.resize(s);
  return c;
}