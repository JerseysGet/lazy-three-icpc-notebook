#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//#pragma GCC target("bmi,bmi2,lzcnt,popcnt")
//#pragma GCC optimize("O2,unroll-loops")
//#pragma GCC target("avx2")

//#pragma GCC optimize("O2")
//#pragma GCC optimize("Ofast")
//#pragma GCC target("avx,avx2,fma")
using namespace std;
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> o_set;
// order_of_key (val): returns the no. of values less than val
// find_by_order (k): returns the kth largest element.(0-based)
template <typename T>
using minHeap = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using maxHeap = priority_queue<T>;
#define int long long
#define all(s) s.begin(), s.end()
#define sz(s) (int)s.size()
using longer = __int128_t;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = numeric_limits<int>::max();
const int M = 1e9 + 7;
void solve() {}
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(NULL);
  cout.tie(NULL);
  int tt;
  cin >> tt;
  while (tt--) solve();
}