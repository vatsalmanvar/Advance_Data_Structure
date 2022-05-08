#include<bits/stdc++.h>

using namespace std;

int par[100000];
int _rank[100000];

void makeset(int n){
	for(int i=0; i<=n; i++){
		par[i] = i;
		_rank[i] = 0;
	}
	return;
}

int _findPar(int node){
	if(par[node] == node) return node;
	par[node] = _findPar(par[node]);
	return par[node];
}

bool _union(int node1, int node2){
	int par1 = _findPar(node1);
	int par2 = _findPar(node2);
	if(par1 == par2) return false;

	if(_rank[node1] == _rank[node2]){
		par[node1] = node2;
		_rank[node2]++;
	} else if(_rank[node1] > _rank[node2]) {
		par[node2] = node1;
	} else{
		par[node1] = node2;
	}
	return true;
}

int main(){
	int i, j, n, u, v, q;
	cin >> n;
	makeset(n);
	cin >> q;
	while(q--){
		cin >> u >> v;
		cout<< _union(u, v) << endl;
	}
    cout<<endl;
    for(i=0; i<n; i++) cout<<par[i]<<" ";
    cout<<endl;
    for(i=0; i<n; i++) cout<<_rank[i]<<" ";
    cout<<endl;
	return 0;
}






