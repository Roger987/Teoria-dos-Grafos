#include <bits/stdc++.h>
using namespace std;

typedef vector <int> vi;
typedef vector <vi> graph;
// Check Examples
int V,E;
bool bfs (graph g,int source,int terminal,int parent[]){
	bool visited[V];
	memset(visited,false,sizeof(bool)*V);
	visited[source] = true;
	queue<int> q;
	q.push(source);
	int dequeued;
	while(!q.empty()){
		dequeued = q.front();
		q.pop();
		for (int v = 0 ;v< V; v++){
			if(g[dequeued][v]>0&&!visited[v]){
				parent [v] = dequeued;
				visited [v] = true;
				q.push(v);
			}
		}
	}
	return visited[terminal];
}
bool min(int a,int b){
	return (a<b) ? a:b;
}
int ford_fulkerson(graph g,int source,int terminal) {
	int u,v,max_flow = 0;
	int *parent = new int[V];
	graph residual;
	residual.resize(V);
	for(int i = 0; i<V;i++) {
		residual[i].resize(V);
		for(int j = 0; j<V;j++) residual[i][j] = g[i][j];
	}
	while(bfs(residual,source,terminal,parent)){
		int path_flow = INT_MAX;
		for ( v = terminal;v!=source;v = parent[v]){
			u = parent[v];
			path_flow = min(residual[u][v],path_flow);
		}
		for( v = terminal;v!=source;v= parent[v]){
			u = parent[v];
			residual[u][v] -= path_flow;
			residual[v][u] += path_flow;
		}
		max_flow += path_flow;
	}
	return max_flow;
}
//Compiler version g++ 6.3.0
int main()
{
	graph g;
    cout<<"Diga o número de vértices do grafo"<<endl;
    cin>> V;
    cout <<"Diga o número de arestas do grafo\n";
    cin>>E;
    g.resize(V);
    for(int i = 0 ; i< V ; i++) g[i].resize(V);
    for (int i = 0 ; i< E ;i++) {
    	int tmp1,tmp2,w;
    	cout<<"Diga os vertices e peso da aresta\n";
    	cin>> tmp1>>tmp2>>w;
    	g[tmp1][tmp2] = w;
    }
    cout<<"Diga a fonte e o sumidouro do grafo\n";
    int s,t;
    cin>>s>>t;
    cout<<"O fluxo maximo desse grafo eh "<<ford_fulkerson(g,s,t)<<endl;
    return 0;
}
