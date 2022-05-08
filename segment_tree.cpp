#include<bits/stdc++.h>
using namespace std;

int a[100000], seq[100000*4];

void build(int ind, int low, int high){
	if(low == high){
		seq[ind] = a[low];
		return;
	}
	int mid = (low+high)/2;
	build(ind*2+1, low, mid);
	build(ind*2+2, mid+1, high);
	seq[ind] = max(seq[ind*2+1], seq[ind*2+2]);
	return;
}

int getmax(int ind, int low, int high, int l, int r){
	if(l<=low && high<=r) return seq[ind];
	else if(high<l || r<low) return INT_MIN;
	else{
		int mid = (low+high)/2;
		return max(getmax(ind*2+1, low, mid, l ,r), getmax(ind*2+2, mid+1, high, l ,r));
	}
}

int main(){
	int i, j, n, l, r, q;
	cin >> n;
	for(i=0; i<n; i++){
		cin >> a[i];
	}
	build(0, 0, n-1);
	cin >> q;
	while(q--){
		cin >> l >> r;
		cout << getmax(0, 0, n-1, l, r) << endl;
	}
	return 0;
}