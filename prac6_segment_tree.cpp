#include <bits/stdc++.h>
using namespace std;

vector<int> v(100005);
vector<int> seg(4*100005);

int query(int index, int low, int high, int l ,int r){
	if(l<=low && high<=r){
		return seg[index];
	}
	if(low>r || high<l) return 0;
	int mid = (low+high)/2;
	return query(index*2+1, low, mid, l, r)+query(index*2+2, mid+1, high, l, r);
}

void build(int index, int low, int high){
	if(low == high){
		seg[index] = v[low];
		return;
	}
	int mid = (low+high)/2;
	build((index*2)+1, low, mid);
	build((index*2)+2, mid+1, high);
	seg[index] = seg[(index*2)+1] + seg[(index*2)+2];
	return;
}

int main(){
	int i, j, n;
	cout<<"Enter lenght of array: ";
	cin >> n;
	cout<<"Enter array:";
	for(i=0; i<n; i++){
		cin >> v[i];
	}
	build(0, 0, n-1);
	cout<<"Enter no of query: ";
	int q;
	cin >> q;
	while(q--){
		int l, r;
		cout<<"Enter l and r :";
		cin >> l >> r;
		cout<<"sum is: "<< query(0, 0, n-1, l, r) <<endl;
	}
	return 0;
}