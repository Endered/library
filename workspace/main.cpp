#include <bits/stdc++.h>
#include <ranges>

#define rep(i, a, ...)                                                         \
  for (int i = (a) * (strlen(#__VA_ARGS__) != 0);                              \
       i < (int)(strlen(#__VA_ARGS__) ? __VA_ARGS__ : (a)); ++i)
#define per(i, a, ...)                                                         \
  for (int i = (strlen(#__VA_ARGS__) ? __VA_ARGS__ : (a)) - 1;                 \
       i >= (int)(strlen(#__VA_ARGS__) ? (a) : 0); --i)
#define foreach(i, n) for (auto &i : (n))
#define all(x) (x).begin(), (x).end()
#define bit(x) (1ll << (x))
#define lambda(RES_TYPE, ...)                                                  \
  (function<RES_TYPE(__VA_ARGS__)>)[&](__VA_ARGS__)->RES_TYPE
#define method(FUNC_NAME, RES_TYPE, ...)                                       \
  function<RES_TYPE(__VA_ARGS__)> FUNC_NAME = lambda(RES_TYPE, __VA_ARGS__)
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
// const ll MOD = (ll)1e9+7;
const ll MOD = 998244353;
const int INF = (ll)1e9 + 7;
const ll INFLL = (ll)1e18;
template <class t> using vvector = vector<vector<t>>;
template <class t> using vvvector = vector<vector<vector<t>>>;
template <class t>
using priority_queuer = priority_queue<t, vector<t>, greater<t>>;
template <class t, class u> bool chmax(t &a, u b) {
  if (a < b) {
    a = b;
    return true;
  }
  return false;
}
template <class t, class u> bool chmin(t &a, u b) {
  if (a > b) {
    a = b;
    return true;
  }
  return false;
}
#ifdef DEBUG
#define debug(x)                                                               \
  cout << "LINE " << __LINE__ << ": " << #x << " = " << x << endl;
#else
#define debug(x) (void)0
#endif

namespace templates {
ll modpow(ll x, ll b, ll mod = MOD) {
  ll res = 1;
  while (b) {
    if (b & 1)
      res = res * x % mod;
    x = x * x % mod;
    b >>= 1;
  }
  return res;
}

ll modinv(ll x) { return modpow(x, MOD - 2); }

bool was_output = false;

void print();
template <class t> void print(const vector<t> &);
template <class t, class u> void print(const pair<t, u> &);
template <class t> void print(const t &);
template <class Head, class... Tail> void print(const Head &, const Tail &...);

template <class t> void println(const vector<vector<t>> &);
template <class t> void println(const vector<t> &);
template <class t> void println(const t &);
template <class Head, class... Tail>
void println(const Head &, const Tail &...);
void println();
void newline();

void print() { return; }

template <class t> void print(const vector<t> &x) {
  for (const t &i : x)
    print(i);
}
template <class t, class u> void print(const pair<t, u> &p) {
  print(p.first);
  print(p.second);
}
template <class t> void print(const t &x) {
  if (was_output)
    cout << " ";
  cout << x;
  was_output = true;
}
template <class Head, class... Tail>
void print(const Head &head, const Tail &...tail) {
  print(head);
  print(tail...);
}

template <class t> void println(const vector<vector<t>> &x) {
  for (vector<t> i : x)
    println(i);
}
template <class t> void println(const vector<t> &x) {
  for (const t &i : x)
    print(i);
  println();
}
template <class t> void println(const t &x) {
  print(x);
  println();
}
void println() {
  if (was_output) {
    cout << endl;
    was_output = false;
  }
}
template <class Head, class... Tail>
void println(const Head &head, const Tail &...tail) {
  print(head);
  println(tail...);
}

void newline() {
  was_output = true;
  println();
}

template <class t> istream &operator>>(istream &is, vector<t> &x) {
  for (auto &i : x)
    is >> i;
  return is;
}

template <class t, class u> istream &operator>>(istream &is, pair<t, u> &x) {
  is >> x.first >> x.second;
  return is;
}

template <class t> ostream &operator<<(ostream &os, vector<t> &v) {
  os << "{";
  for (t &i : v) {
    os << i << ", ";
  }
  os << "}";
  return os;
}

template <class t = long long> t in() {
  t res;
  cin >> res;
  return res;
}

template <class t>
vector<t> sorted(
    vector<t> line,
    function<bool(t, t)> comp = [](t a, t b) { return a < b; }) {
  sort(line.begin(), line.end(), comp);
  return line;
}

template <class t> vector<t> reversed(vector<t> line) {
  reverse(line.begin(), line.end());
  return line;
}
string reversed(string str) {
  reverse(str.begin(), str.end());
  return str;
}

long long gcd(long long a, long long b) {
  while (b) {
    a %= b;
    swap(a, b);
  }
  return a;
}

long long lcm(long long a, long long b) { return a / gcd(a, b) * b; }

class output_initializer {
public:
  output_initializer() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << setprecision(20);
  }
};
output_initializer OUTPUT_INITIALIZER_INSTANCE = output_initializer();
} // namespace templates

using namespace templates;

int main() {
    return 0;
}
