template<long long mod>
class modint{
	public:
		long long x;
		modint(long long a){x=a%mod;if(x<0)x+=mod;}
		modint(){x=0;}

		modint pow(long long a){
			modint res(1), b(x);
			while(a){
				if(a&1)res*=b;
				b*=b;
				a>>=1;
			}
			return res;
		}

		modint inv(){return pow(mod-2);}

		modint& operator+=(modint a){x=(x+a.x)%mod;return *this;}
		modint& operator-=(modint a){x=x-a.x;if(x<0)x+=mod;return *this;}
		modint& operator*=(modint a){x=x*a.x%mod;return *this;}
		modint& operator/=(modint a){x=x*a.inv().x%mod;return *this;}

		modint operator+(modint a){return modint(x)+=a;}
		modint operator-(modint a){return modint(x)-=a;}
		modint operator*(modint a){return modint(x)*=a;}
		modint operator/(modint a){return modint(x)/=a;}

		modint operator-(){return modint(x);}

		bool operator==(const modint a){return x == a.x;}
		bool operator<(const modint a){return x < a.x;}
		bool operator>(const modint a){return x > a.x;}
};

template<long long mod>
ostream& operator<<(ostream& os, const modint<mod>& a){
	os << a.x;
	return os;
}

