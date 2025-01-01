u64 mult(u64 a, u64 b, u64 m = M) {
  i64 ret = a * b - m * (u64)(1.L / m * a * b);
  return ret + m * (ret < 0) - m * (ret >= (i64)m);
}
u64 pw(u64 b, u64 e, u64 m = M) {
  u64 ret = 1;
  for (; e; b = mult(b, b, m), e >>= 1)
    if (e & 1) ret = mult(ret, b, m);
  return ret;
}
bool isPrime(u64 n) {  // determistic upto 7e^18
  if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
  u64 A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
      s = __builtin_ctzll(n - 1), d = n >> s;
  for (u64 a : A) {
    u64 p = pw(a % n, d, n), i = s;
    while (p != 1 && p != n - 1 && a % n && i--)
      p = mult(p, p, n);
    if (p != n - 1 && i != s) return 0;
  }
  return 1;
}