#include<bits/stdc++.h>
#define ll long long
#define rep(i, n) for(int i=0;i<(n);++i)
#define per(i, n) for(int i=(n)-1;i>=0;--i)
#define repa(i, n) for(int i=1;i<(n);++i)
#define foreach(i, n) for(auto &i:(n))
#define pii pair<int, int>
#define pll pair<long long, long long>
#define all(x) (x).begin(), (x).end()
#define bit(x) (1ll << (x))
const ll MOD = (ll)1e9+7;
const int INF = (ll)1e9+7;
const ll INFLL = (ll)1e18;
using namespace std;
template<class t>
using vvector = vector<vector<t>>;
template<class t>
using vvvector = vector<vector<vector<t>>>;
template<class t>
using priority_queuer = priority_queue<t, vector<t>, greater<t>>;
template<class t, class u> bool chmax(t &a, u b){if(a<b){a=b;return true;}return false;}
template<class t, class u> bool chmin(t &a, u b){if(a>b){a=b;return true;}return false;}

ll modpow(ll x, ll b){
	ll res = 1;
	while(b){
		if(b&1)res = res * x % MOD;
		x = x * x % MOD;
		b>>=1;
	}
	return res;
}

ll modinv(ll x){
	return modpow(x, MOD-2);
}

bool was_output = false;
template<class t>
void output(t a){
	if(was_output)cout << " ";
	cout << a;
	was_output = true;
}
void outendl(){
	was_output = false;
	cout << endl;
}

class dijkstra{
public:
	int n;
	vvector<pll> edges;
	vector<ll> fast;
	dijkstra(int N):n(N){
		edges.resize(n);
	}

	void add_edge(int from, int to, ll cost){
		edges[from].emplace_back(to, cost);
	}

	void solve(int start){
		priority_queuer<pll> pq;
		fast.assign(n, INFLL);
		pq.emplace(0, 0);
		fast[start] = 0;
		pq.emplace(0, start);
		while(pq.size()){
			pll d = pq.top();
			pq.pop();
			if(d.first!=fast[d.second])continue;
			foreach(i, edges[d.second]){
				ll next_time = d.first + i.second;
				int to = i.first;
				if(fast[to] <= next_time)continue;
				fast[to] = next_time;
				pq.emplace(next_time, to);
			}
		}
	}
};


int main(){
	int n;
	cin >> n;
	dijkstra dij(n);
	rep(i, n){
		int from;
		cin >> from;
		int time;
		cin >> time;
		rep(j, time){
			int to;
			ll cost;
			cin >> to >> cost;
			dij.add_edge(from, to, cost);
		}
	}
	dij.solve(0);
	rep(i, n){
		output(i);
		output(dij.fast[i]);
		outendl();
	}
	return 0;
}
