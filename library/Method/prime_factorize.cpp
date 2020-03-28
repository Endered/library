#include<bits/stdc++.h>
using namespace std;

//firstが基底secondが乗数です
vector<pair<long long,long long>> prime_factorize(long long x){
	using P = pair<long long,long long>;
	vector<P> res;
	for(int i=2;i*i<=x;++i){
		int cnt = 0;
		while(x%i==0){
			x /= i;
			++cnt;
		}
		if(cnt){
			res.emplace_back(i,cnt);
		}
	}
	if(x>1)res.emplace_back(x,1);
	return res;
}

int main(){
	int n;
	cin >> n;
	vector<pair<long long,long long>> ans = prime_factorize(n);
	for(auto &i:ans){
		cout << i.first << "^" << i.second << endl;
	}
}
