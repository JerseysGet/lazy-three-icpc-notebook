template <const i32 mod>
struct mint {
  constexpr mint(i32 x = 0) : val(x % mod + (x < 0) * mod) {}
  mint &operator+=(const mint &b) {
    val += b.val;
    val -= mod * (val >= mod);
    return *this;
  }
  mint &operator-=(const mint &b) {
    val -= b.val;
    val += mod * (val < 0);
    return *this;
  }
  mint &operator*=(const mint &b) {
    val = 1ll * val * b.val % mod;
    return *this;
  }
  mint &operator/=(const mint &b) { return *this *= b.inv(); }
  mint inv() const {
    i32 x = 1, y = 0, t;
    for (i32 a = val, b = mod; b; swap(a, b), swap(x, y))
      t = a / b, a -= t * b, x -= t * y;
    return mint(x);
  }
  mint pow(int b) const {
    mint a = *this, res(1);
    for (; b; a *= a, b /= 2)
      if (b & 1) res *= a;
    return res;
  }
  friend mint operator+(const mint &a, const mint &b) { return mint(a) += b; }
  friend mint operator-(const mint &a, const mint &b) { return mint(a) -= b; }
  friend mint operator*(const mint &a, const mint &b) { return mint(a) *= b; }
  friend mint operator/(const mint &a, const mint &b) { return mint(a) /= b; }
  friend bool operator==(const mint &a, const mint &b) { return a.val == b.val; }
  friend bool operator!=(const mint &a, const mint &b) { return a.val != b.val; }
  friend bool operator<(const mint &a, const mint &b) { return a.val < b.val; }
  friend ostream &operator<<(ostream &os, const mint &a) { return os << a.val; }
  i32 val;
};