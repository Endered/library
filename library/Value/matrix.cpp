template<class t>
class matrix{
    public:
        vector<vector<t>> v;
        int row;
        int col;
        matrix(int row,int col):v(row,vector<t>(col,0)),row(row),col(col){}
        matrix(const matrix&m):v(m.v),col(m.col),row(m.row){ }
        matrix(vector<vector<t>> v):row(v.size()),col(v.front().size()),v(v){}
        vector<t>& operator[](int p){
            return v[p];
        }
        matrix& operator+=(const matrix&m){
            for(int i=0;i<row;++i){
                for(int j=0;j<col;++j){
                    v[i][j] += m.v[i][j];
                }
            }
            return *this;
        }
        matrix& operator-=(const matrix&m){
            for(int i=0;i<row;++i){
                for(int j=0;j<col;++j){
                    v[i][j] -= m.v[i][j];
                }
            }
            return *this;
        }
        matrix operator+(const matrix&m){
            return matrix(*this) += m;
        }
        matrix operator-(const matrix&m){
            return matrix(*this) -= m;
        }
        matrix operator*(const matrix&m){
            matrix res(row,m.col);
            rep(i,row){
                rep(j,m.col){
                    rep(k,col){
                        res[i][j] += v[i][k] * m.v[k][j];
                    }
                }
            }
            return res;
        }
        matrix& operator*=(const matrix&m){
            matrix tmp = *this * m;
            return *this = tmp;
        }

        matrix pow(ll y){
            assert(col==row);
            matrix res(col,col);
            for(int i=0;i<col;++i){
                res[i][i] = 1;
            }
            matrix sum = *this;
            while(y){
                if(y&1)res *= sum;
                sum *= sum;
                y >>= 1;
            }
            return res;
        }
};

template<class t>
ostream& operator<<(ostream& os,matrix<t> m){
    for(int i=0;i<m.row;++i){
        for(int j=0;j<m.col;++j){
            if(j)os << " ";
            os << m[i][j];
        }
        os << endl;
    }
    return os;
}
