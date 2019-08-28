#include <iostream> 
#include <vector> 
#include <utility>
#include<algorithm>
#include <climits>
#include<bits/stdc++.h>
using namespace std;

typedef pair <int,int> ii;
typedef vector <ii> vii;


void dijkstra(vector <vii> adj_list, int s, int g, int n){
	
	priority_queue < ii, vii, greater<ii> > H;

	vector<int> dist(n, INT_MAX);
	vector<int> prev(n, -1);

	dist[s] = 0;
	H.push(make_pair(dist[s],s));

	while(!H.empty()){
		
		int u = H.top().second;
		H.pop();
		
		for(int j = 0; j < adj_list[u].size(); ++j){

			ii w = adj_list[u][j];

			if(dist[w.first] > (dist[u] + w.second)){
				
				dist[w.first] = (dist[u] + w.second);
				prev[w.first] = u;

				H.push(make_pair(dist[w.first],w.first));
			}
		}
	}

	printf("[%d]\n", dist[g]);

}

int main(){

	vector <vii> adj_list;

	int n, m, s, g, i, u, v, w;

	printf("Number of vertex:\n");
	scanf("%d", &n);
	printf("Number of edges:\n");
	scanf("%d", &m);
	printf("Source:\n");
	scanf("%d", &s);
	printf("Goal:\n");
	scanf("%d", &g);
	printf("Graph:\n");

	adj_list.resize(n);

	for (i=0; i < m; ++i)
	{
	   scanf("%d%d%d", &u, &v, &w);
	   adj_list[u].push_back( ii(v, w) );
	}

	dijkstra(adj_list, s, g, n);

	return 0;

}
