#include <iostream>
#include <bits/stdc++.h>
using namespace std;

typedef pair <int,int> ii;
typedef vector <ii> vii;

vector<int> parent;
vector<int> k_rank;

void make_set(int x){
	parent[x] = x;
	k_rank[x] = 0;
}

int find_set(int x){
	if(parent[x] != x){
		parent[x] = find_set(parent[x]);
	}
	return parent[x];
}

void union_set(int x, int y){
	
	if(k_rank[x] >= k_rank[y]){
		parent[y] = x;
		if(k_rank[x] == k_rank[y]){
			k_rank[x]++;
		}
	}

	else{
		parent[x] = y;
	}
}

vector <pair<int, ii>> kruskal(vector <vii> adj_list, vector <pair<int, ii>> edgeList, int m){

	vector <pair<int, ii>> T;

	for(int v = 0; v < adj_list.size(); v++){
		make_set(v);
	}
	for(auto uv : edgeList){
		if(find_set(uv.second.first) != find_set(uv.second.second)){
			T.push_back(uv);
			union_set(find_set(uv.second.first),find_set(uv.second.second));
		}
	}

	return T;

}


int main(){

	vector <vii> adj_list;
	vector <pair<int, ii>> edgeList;

	int n, m, s, g, i, u, v, w;

	printf("Number of vertex:\n");
	scanf("%d", &n);
	printf("Number of edges:\n");
	scanf("%d", &m);
	printf("Graph:\n");

	adj_list.resize(n);
	parent.resize(n);
	k_rank.resize(n);

	for (i=0; i < m; ++i)
	{
	   scanf("%d%d%d", &u, &v, &w);
	   adj_list[u].push_back( ii(v, w) );
	   adj_list[v].push_back( ii(u, w) );
	   edgeList.push_back(make_pair(w, ii(u,v)));
	}

	sort(edgeList.begin(), edgeList.end());

	vector <pair<int, ii>> Tree = kruskal(adj_list, edgeList, m);

	for(i = 0; i < Tree.size(); i++){
		printf("(%d,%d)\n", Tree[i].second.first, Tree[i].second.second);
	}

	return 0;

}