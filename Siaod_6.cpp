#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void printGraph(const vector<vector<int>>& graph) {
	int n = graph.size();
	cout << "Adjacency Matrix:\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << graph[i][j] << " ";
		}
		cout << "\n";
	}
}

void findGraphCenter(vector<vector<int>>& graph) { //Определение центра графа 
	int n = graph.size();
	vector<vector<int> > dist(n, vector<int>(n, INT_MAX));

	for (int i = 0; i < n; i++) {
		dist[i][i] = 0;
		for (int j = 0; j < n; j++) {
			if (graph[i][j] != 0) {
				dist[i][j] = graph[i][j];
			}
		}
	}

	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
				}
			}
		}
	}

	int eccentricity = INT_MAX;
	for (int i = 0; i < n; i++) {
		int max_dist = *max_element(dist[i].begin(), dist[i].end());
		eccentricity = min(eccentricity, max_dist);
	}

	vector<int> centerNodes;
	for (int i = 0; i < n; i++) {
		int max_dist = *max_element(dist[i].begin(), dist[i].end());
		if (max_dist == eccentricity) {
			centerNodes.push_back(i);
		}
	}

	cout << "Graph Center Node(s): ";
	for (int node : centerNodes) {
		cout << node << " ";
	}
	cout << endl;
}

int p[100000];
int rk[100000];

void init_dsu() {
	for (int i = 0; i < 100000; i++) { p[i] = i; rk[i] = 1;}

}

int get_root(int v) {
	if (p[v] == v) return v;
	//На выходе из рекурсии переподвешиваем v:
	else return p[v] = get_root(p[v]);
}

bool merge(int a, int b) {
	int ra = get_root(a), rb = get_root(b);
	if (ra == rb) return false;
	else {
		if (rk[ra] < rk[rb]) p[ra] = rb;
		else if (rk[rb] < rk[ra])
			p[rb] = ra;
		else { p[ra] = rb; rk[rb]++;}
		return true;
	}
}

//Тип для представления ребер
struct edge {
	int a, b, len;
	bool operator<(const edge& other) {
		return len < other.len;
	}
};


int main() {
	vector<edge> edges;
	//Ввод edges

	int n;
	cout << "Enter the number of vertices: ";
	cin >> n;

	vector<vector<int>> graph(n, vector<int>(n));
	cout << "Enter the adjacency matrix (0 for no edge, weight for edge):\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> graph[i][j];
		}
	}

	printGraph(graph);

	sort(edges.begin(), edges.end());
	int mst_weight = 0;
	init_dsu();
	for (edge e : edges) {
		//Если a и b находятся в разных компонентах:
		if (merge(e.a, e.b)) {
			//Добавить ребро в минимальный остов:
			mst_weight += e.len;
		}
	}
	cout << "Minimum spanning tree weight: " << mst_weight << endl; //алгоритма Крускала 


}