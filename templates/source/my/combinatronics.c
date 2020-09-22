
long long power(long long b, long long p) {
  long long res = 1;
  while (p) {
    if (p & 1) (res *= b) %= mod;
    (b *= b) %= mod;
    p >>= 1;
  }
  return res;
}

vector<long long> fac(1, 1), inv_fac(1, 1);
long long C(int x, int y) {
  if (x < y) return 0;
  while ((int) fac.size() <= x) {
    fac.push_back((fac.back() * (int) fac.size()) % mod);
    inv_fac.push_back(power(fac.back(), mod - 2));
  }
  return fac[x] * inv_fac[y] % mod * inv_fac[x - y] % mod;
}
long long P(int x, int y) {
  if (x < y) return 0;
  while ((int) fac.size() <= x) {
    fac.push_back((fac.back() * (int) fac.size()) % mod);
    inv_fac.push_back(power(fac.back(), mod - 2));
  }
  return fac[x] * inv_fac[y] % mod;
} 
