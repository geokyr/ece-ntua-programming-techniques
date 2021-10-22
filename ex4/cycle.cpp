#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Graph {
  public:
    Graph(int V);
    ~Graph();

    void addEdge(int v, int w);

    bool cycle(vector<int> &path);

  private:
    int ver;
    list<int>* adj;
    vector<int> Path;
    int x;

    bool cycle(int v, bool visited[], bool *rs);
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
}

bool Graph::cycle(int v, bool visited[], bool *rs) {
  if(!visited[v]) {
    visited[v] = true;
    rs[v] = true;
    Path.push_back(v);
    list<int>::iterator i;
    for(i=adj[v].begin(); i!=adj[v].end(); ++i) {
      if(!visited[*i] && cycle(*i, visited, rs))
        return true;
      else if(rs[*i]) {
        x = *i;
        return true;
      }
    }
  }
  rs[v] = false;
  if(Path.size() != 0) {
    Path.pop_back();
  }
  return false;
}

bool Graph::cycle(vector<int> &path) {
  bool* visited = new bool[ver];
  bool* rs = new bool[ver];
  for(int i=0; i<ver; i++) {
    visited[i] = false;
    rs[i] = false;
  }
  for(int i=0; i<ver; i++)
    if(cycle(i, visited, rs)) {
      int j = 0;
      while(Path[j] != x) {
        j++;
      }
      for(int k = j; k<Path.size(); k++) {
        int a = Path[k];
        path.push_back(a);
      }
      return true;
    }
  return false;
}

#ifndef CONTEST
int main() {
  int V, E;
  cin >> V >> E;
  Graph g(V);
  for(int i=0; i<E; ++i) {
    int u, v;
    cin >> u >> v;
    g.addEdge(u, v);
  }
  vector<int> path;
  if(g.cycle(path)) {
    cout << "CYCLE: ";
    for (int i = 0; i < path.size(); ++i)
      cout << path[i] << (i == path.size() - 1 ? "\n" : " ");
  }
  else
    cout << "NO CYCLE" << endl;
}
#endif