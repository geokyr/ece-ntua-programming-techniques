#include <iostream>
#include <list>

using namespace std;

class Graph {
  private:
    int ver;
    list<int>* adj;

  public:
    Graph(int V);
    ~Graph();
    void addEdge(int v, int w);

    void DFS(int v, bool visited[]);
    bool isConnected();
    int isEulerian();
    void result();
};

Graph::Graph(int V) {
  ver = V;
  adj = new list<int>[ver];
}

Graph::~Graph() {
  delete [] adj;
}

void Graph::addEdge(int v, int w) {
  adj[v].push_back(w);
  adj[w].push_back(v);
}

void Graph::DFS(int v, bool visited[]) {
  visited[v] = true;
  list<int>::iterator i;
  for(i=adj[v].begin(); i!=adj[v].end(); ++i) {
    if(!visited[*i]) {
      DFS(*i, visited);
    }
  }
}

bool Graph::isConnected() {
  bool visited[ver];
  int i;
  for(i=0; i<ver; i++) {
    visited[i] = false;
  }
  for(i=0; i<ver; i++) {
    if(adj[i].size() != 0) {
      break;
    }
  }
  if(i == ver) {
    return true;
  }
  DFS(i, visited);
  for(i=0; i<ver; i++) {
    if(visited[i] == false && adj[i].size() > 0) {
      return false;
    }
  }
  return true;
}

int Graph::isEulerian() {
  if(isConnected() == false) {
    return 0;
  }
  int odd = 0;
  for(int i=0; i<ver; i++) {
    if(adj[i].size() & 1) {
      odd++;
    }
  }
  if(odd > 2) {
    return 0;
  }
  return (odd)? 1 : 2;
}

void Graph::result() {
  int u = 0, v = 0;
  if(isEulerian() == 0) {
    cout << "IMPOSSIBLE" << endl;
  }
  else if(isEulerian() == 2) {
    cout << "CYCLE" << endl;
  }
  else {
    int i;
    for(i=0; i<ver; i++) {
      if(adj[i].size() & 1) {
        u = i++;
        break;
      }
    }
    while(i<ver) {
      if(adj[i].size() & 1) {
        v = i;
        break;
      }
      i++;
    }
    if(u > v) {
      swap(u, v);
    }
    cout << "PATH " << u << " " << v << endl;
  }
}

int main() {
  int V, E;
  cin >> V >> E;
  Graph g(V);
  for(int i=0; i<E; ++i) {
    int u, v;
    cin >> u >> v;
    g.addEdge(u, v);
  }
  g.result();
}