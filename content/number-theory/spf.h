#define SIEVE_TILL (int)1e6
vector<int> primes;
vector<int> spf;
void sieve() {
  spf = vector<int>(SIEVE_TILL + 1, 0);
  for (int i = 2; i <= SIEVE_TILL; i++) {
    if (spf[i] == 0) primes.push_back(i), spf[i] = i;
    for (int j = 0; j < sz(primes) and i * primes[j] <= SIEVE_TILL; j++) {
      spf[i * primes[j]] = primes[j];
      if (spf[i] == primes[j]) break;
    }
  }
}
bool isPrime(int n) {
  if (n <= 1) return false;
  return spf[n] == n;
}