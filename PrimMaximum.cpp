#include <bits/stdc++.h>
using namespace std;

typedef pair <int,int> ii;
typedef vector <ii> vii;
typedef vector <vii> graph;
bool operator< (ii a, ii b){
	return (a.second)<(b.second);
}
bool operator>=(ii a,ii b){
	return(a.second)>=(b.second);
}
bool operator>(ii a ,ii b){
	return (a.second)>(b.second);
}
bool operator<=(ii a, ii b){
	return (a.second)<=(b.second);
}
bool operator==(ii a ,ii b){
	return (a.second)==(b.second);
}
bool operator!=(ii a,ii b){
	return (a.second)!=(b.second);
}
class Heap{
	int getLeft(int i){
		return i*2;
	}
	int getRight(int i){
		return (i*2)-1;
	}
	int getParent(int i){
		return i/2;
	}
public:
	vii heap;
	int size;
	Heap(){
		heap.push_back(ii(0,0));
		size= 0;
	}
	void push(ii x){
		size++;
		heap.resize(size+1);
		heap[size] = x;
		int key = size;
		int parent = getParent(key);
		while(parent>=1 && (heap[key])>(heap[parent])){
			ii t = heap[key];
			heap[key] = heap[parent];
			heap[parent] = t;
			key = parent;
			parent = getParent(key);
		}
	}
	ii top(){
		return heap[1];
	}
	void max_heapify(int i){
		int largest,left,right;
		left = getLeft(i);
		right = getRight(i);
		if(left<=size&&heap[left]>heap[i]) largest = left;
		else largest = i;
		if (right<=size&&heap[right]>heap[i]) largest = right;
		if(i!=largest){
			ii t = heap[i];
			heap[i] = heap[largest];
			heap[largest] = t;
			max_heapify(largest);
		}
	}
	bool empty(){
		return size==0;
	}
	ii pop(){
		if(size>0){
			ii item = heap[1];
			heap[1] = heap[size];
			size--;
			heap.resize(size);
			max_heapify(1);
			return item;
		}
		return ii(INT_MIN,INT_MIN);
	}
	void Increase_Priority(int z,int w){
		for(int i =1;i<=size;i++){
			if(heap[i].first==z){
				cout<<i<<endl;
				if(i!=size) {heap[i] = heap[size];
				heap.resize(size);
				size--;
				this->max_heapify(i);
				}else{
					heap.resize(size);
					size--;
				}
				this->push(make_pair(z,w));
				break;
			}
		}
	}
};
typedef Heap pii;
int V;
pii criar_pq(int custo[]){
	pii h;
	for(int v = 0; v<V ; v++) h.push (ii (v,custo[v]));
	return h;
}
int* Prim(graph g,int v0){
	int custo[V],*prev = new int[V]; 
	bool mstSet[V];
	for(int u = 0 ;u<V; u++){
		custo[u] = INT_MIN;
		prev[u] = -1;
		mstSet[u] = false;
	}
	custo[v0] = 0;
	mstSet[v0] = true;
	pii H = criar_pq(custo);
	while(!H.empty()){
		int v = H.top().first;
		mstSet[v] = true;
		H.pop();
		for(auto z : g[v]){
			if(custo[z.first] < z.second && !mstSet[z.first]){
				custo[z.first] = z.second;
				H.Increase_Priority(z.first,custo[z.first]);
				prev[z.first] = v;
			}
		}
	}
	return prev;
}
void addEdge(graph *g,int v1,int v2,int w){
	(g->at(v1)).push_back(ii(v2,w));
	(g->at(v2)).push_back(ii(v1,w));
}



int main(){	
	cout<<"Diga o numero de vertices do grafo\n";
	cin>>V;
	cout<<"Diga o numero de arestas do grafo\n";
	int E;
	cin>>E;
	graph g;
	g.resize(V);
	int a,b,w;
	for(int i =0;i<E;i++){
		cout<<"Diga os vertices e peso da aresta\n";
		cin>>a>>b>>w;
		addEdge(&g,a,b,w);
	}
	int* t = Prim(g,0);
	for (int i = 0; i< V;i++)
	cout<<i<<" pai :"<<t[i]<<endl;
	return 0;
}