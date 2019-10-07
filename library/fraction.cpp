template<class t>
class fraction{
	public:
		t numerator;
		t denominator;

		fraction():numerator(t(0)), denominator(t(1)){}
		fraction(t a, t b):numerator(a), denominator(b){}
		fraction(long long a, long long b):numerator(a), denominator(b){}
		fraction(const fraction &a):numerator(a.numerator), denominator(a.denominator){}

		fraction pow(long long k){
			fraction res(1, 1);
			fraction sum(*this);
			while(k){
				if(k&1)res*=sum;
				sum*=sum;
				k>>=1;
			}
			return res;
		}

		fraction& operator+=(fraction a){
			numerator = numerator * a.denominator + a.numerator * denominator;
			denominator *= a.denominator;
			return *this;
		}

		fraction& operator-=(fraction a){
			numerator = numerator * a.denominator - a.numerator * denominator;
			denominator *= a.denominator;
			return *this;
		}

		fraction& operator*=(fraction a){
			numerator *= a.numerator;
			denominator *= a.denominator;
			return *this;
		}

		fraction& operator/=(fraction a){
			numerator *= a.denominator;
			denominator *= a.numerator;
			return *this;
		}

		fraction operator+(fraction a){return fraction(*this) += a;}
		fraction operator-(fraction a){return fraction(*this) -= a;}
		fraction operator*(fraction a){return fraction(*this) *= a;}
		fraction operator/(fraction a){return fraction(*this) /= a;}
};

