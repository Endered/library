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

class my_priority_queue{
public:
	vector<int> line;
	my_priority_queue(){
		line.assign(1, 0);
	}

	void max_heapify(int i){
		int l = i * 2;
		int r = i * 2 + 1;
		int largest = i;
		if(l < line.size() && line[i] < line[l]){
			largest = l;
		}
		if(r < line.size() && line[largest] < line[r]){
			largest = r;
		}
		if(largest != i){
			swap(line[i], line[largest]);
			max_heapify(largest);
		}
	}

	void push(int key){
		line.push_back(key);
		int i = line.size() - 1;
		while(i){
			max_heapify(i);
			i /= 2;
		}
	}

	int pop(){
		int res = line[1];
		line[1] = line.back();
		line.pop_back();
		if(line.size()>1){
			max_heapify(1);
		}
		return res;
	}
};

int main(){
	my_priority_queue pq;
	string op;
	while(cin>>op&&op!="end"){
		if(op=="insert"){
			int key;
			cin >> key;
			pq.push(key);
		}else{
			cout  << pq.pop() << endl;
		}
	}
	return 0;
}
