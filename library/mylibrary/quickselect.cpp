#include<bits/stdc++.h>
using namespace std;

template<class T>
class quickselect{
	public:
		vector<T> line;
		quickselect(vector<T> a){
			line=a;
		}

		quickselect(){

		}
		T select(int k){
			return select(line, k, 0, line.size());
		}

		T select(vector<T> &array, int k, int start, int end){
			int pivotindex;
			do{
				T pivotvalue = pivot(array, start, end);
				pivotindex = partition(array, start, end, pivotvalue);

				if(pivotindex < k){
					start = pivotindex + 1;
				}else if(pivotindex > k){
					end = pivotindex;
				}
			}while(pivotindex != k);
			return array[k];
		}

		T pivot(vector<T> &array, int start, int end){
			if(end-start==1)return array[start];
			vector<T> medians;
			for(int i=start;i<end;i+=5){

				int substart = i;
				int subend=min(i+5, end);

				T median = median5(array, substart, subend);

				medians.push_back(median);
			}

			start = 0;
			end = medians.size();
			int k = end/2;
			return select(medians, k, start, end);
		}

		T median5(vector<T> &array, int start, int end){
			for(int i=start;i<end-1;++i){
				int index = i;
				for(int j=i+1;j<end;++j){
					if(array[index]<array[j])index=j;
				}
				swap(array[i], array[index]);
			}
			return array[start + (end-start) / 2];
		}

		int partition(vector<T> &array, int start, int end, T value){
			int lp=start;
			for(int i=start;i<end;++i){
				if(array[i]>value){
					swap(array[lp], array[i]);
					++lp;
				}
			}
			for(int i=lp;i<end;++i){
				if(value==array[i]){
					swap(array[lp], array[i]);
					break;
				}
			}
			return lp;
		}
};

int main(){
	int n;
	cin >> n; 
	vector<int> line(n);
	for(auto &i:line)cin>>i;
	cout << quickselect<int>(line).select(n/2) << endl;
	return 0;
}
