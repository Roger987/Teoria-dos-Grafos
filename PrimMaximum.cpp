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
	Heap(int s){
		size = 0;
		heap.resize(s);
		heap.push_back(ii(0,0));
	}
	Heap(){
		heap.push_back(ii(0,0));
		size= 0;
	}
	void push(ii x){
		heap.push_back(x);
		size++;
		int key = size;
		int parent = getParent(key);
		while(parent>=1 && (heap[key])>(heap[parent])){
			ii t = heap[key];
			heap[key] = heap[parent];
			heap[parent] = t;
			key = parent;
			parent = getParent(key);
		}
		//cout<<heap[size].first<<" "<<heap[size].second<<endl;
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
			max_heapify(1);
			return item;
		}
		return ii(INT_MIN,INT_MIN);
	}
	void Swap(Heap h){
		auto tmp = heap;
		heap = h.heap;
		h.heap = tmp;
		auto s = size;
		size = h.size;
		h.size = s;
	}
	
};
typedef Heap pii;
int V;
pii criar_pq(int custo[]){
	pii h;
	for(int v = 0; v<V ; v++) h.push (ii (v,custo[v]));
	return h;
}
pii increased_priority(pii h,int v,int custo){
	pii tmp;
	while(!h.empty()){
		ii iii = h.top();
		h.pop();
		if(iii.first==v) tmp.push(ii (iii.first,custo));
		else tmp.push(ii(iii.first,iii.second));
	}
	return tmp;
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
		//cout<<"prev["<<v<<"] :"<<prev[v]<<endl;
		mstSet[v] = true;
		H.pop();
		//cout<<g[v][0].first<<endl;
		for(auto z : g[v]){
			if(custo[z.first] < z.second && !mstSet[z.first]){
				custo[z.first] = z.second;
				auto tmp = increased_priority(H,z.first,custo[z.first]);
				H.Swap(tmp);
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
	graph g;
	g.resize(6);
	addEdge(&g,0,1,4);
	addEdge(&g,1,2,3);
	addEdge(&g,2,0,1);
	addEdge(&g,2,3,2);
	addEdge(&g,3,0,4);
	addEdge(&g,3,1,4);
	addEdge(&g,4,5,5);
	addEdge(&g,5,2,4);
	addEdge(&g,5,3,6);
	V = 6;
	int* t = Prim(g,0);
	for (int i = 0; i< 6;i++)
	cout<<i<<" pai :"<<t[i]<<endl;
	return 0;
}