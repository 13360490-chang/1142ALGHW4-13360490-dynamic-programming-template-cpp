#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>

using namespace std;

// ==============================
// 邊的資料結構
// ==============================
struct Edge {
    int to;
    int weight;
};

// ==============================
// 回復路徑用
// ==============================
void printPath(const vector<int>& parent, int v, const vector<string>& name) {
    if (v == -1) return;
    
    // 如果不是起點，先遞迴處理父節點，再印出當前節點（達成 S -> A -> T 順序）
    if (parent[v] != -1) {
        printPath(parent, parent[v], name);
        cout << " -> ";
    }
    cout << name[v];
}

// ==============================
// 最短路徑 DP
// ==============================
void shortestPathDP(const vector<vector<Edge>>& graph,
                    const vector<int>& topo,
                    int source,
                    int target,
                    const vector<string>& name) {
    const int INF = numeric_limits<int>::max() / 2;
    int n = graph.size();

    vector<int> dist(n, INF);
    vector<int> parent(n, -1);

    // Step 1. 初始化
    dist[source] = 0;

    // Step 2. 依照 topo 順序做 DP
    for (int u : topo) {
        if (dist[u] != INF) {
            for (const auto& edge : graph[u]) {
                int v = edge.to;
                int weight = edge.weight;
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                }
            }
        }
    }

    cout << "Shortest Path DP\n";
    cout << "Distance = ";

    if (dist[target] >= INF) {
        cout << "INF\n";
        cout << "Path: No path\n\n";
    } else {
        cout << dist[target] << "\n";
        cout << "Path: ";
        printPath(parent, target, name);
        cout << "\n\n";
    }
}

// ==============================
// 最長路徑 DP
// ==============================
void longestPathDP(const vector<vector<Edge>>& graph,
                   const vector<int>& topo,
                   int source,
                   int target,
                   const vector<string>& name) {
    const int NEG_INF = numeric_limits<int>::min() / 2;
    int n = graph.size();

    vector<int> dist(n, NEG_INF);
    vector<int> parent(n, -1);

    // Step 1. 初始化
    dist[source] = 0;

    // Step 2. 依照 topo 順序做 DP
    for (int u : topo) {
        if (dist[u] != NEG_INF) {
            for (const auto& edge : graph[u]) {
                int v = edge.to;
                int weight = edge.weight;
                if (dist[u] + weight > dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                }
            }
        }
    }

    cout << "Longest Path DP\n";
    cout << "Distance = ";

    if (dist[target] <= NEG_INF) {
        cout << "-INF\n";
        cout << "Path: No path\n\n";
    } else {
        cout << dist[target] << "\n";
        cout << "Path: ";
        printPath(parent, target, name);
        cout << "\n\n";
    }
}

// ==============================
// 最大乘積路徑 DP
// ==============================
void maxProductPathDP(const vector<vector<Edge>>& graph,
                      const vector<int>& topo,
                      int source,
                      int target,
                      const vector<string>& name) {
    int n = graph.size();

    vector<long long> prod(n, 0);
    vector<int> parent(n, -1);

    // Step 1. 初始化
    prod[source] = 1;

    // Step 2. 依照 topo 順序做 DP
    for (int u : topo) {
        if (prod[u] > 0) {
            for (const auto& edge : graph[u]) {
                int v = edge.to;
                long long weight = edge.weight;
                long long candidate = prod[u] * weight;
                if (candidate > prod[v]) {
                    prod[v] = candidate;
                    parent[v] = u;
                }
            }
        }
    }

    cout << "Maximum Product Path DP\n";
    cout << "Product = ";

    if (prod[target] == 0) {
        cout << "0\n";
        cout << "Path: No path\n\n";
    } else {
        cout << prod[target] << "\n";
        cout << "Path: ";
        printPath(parent, target, name);
        cout << "\n\n";
    }
}

// ==============================
// 主程式
// ==============================
int main() {
    vector<string> name = {"S", "A", "B", "C", "D", "E", "F", "G", "T"};
    int n = 9;

    vector<vector<Edge>> graph(n);

    // 依照題目加邊 (Index: 0:S, 1:A, 2:B, 3:C, 4:D, 5:E, 6:F, 7:G, 8:T)
    graph[0].push_back({1, 6});  // S -> A
    graph[0].push_back({2, 5});  // S -> B
    graph[0].push_back({3, 7});  // S -> C
    graph[0].push_back({4, 4});  // S -> D

    graph[1].push_back({5, 3});  // A -> E
    graph[1].push_back({6, 10}); // A -> F

    graph[2].push_back({5, 2});  // B -> E
    graph[2].push_back({7, 2});  // B -> G

    graph[3].push_back({6, 1});  // C -> F
    graph[4].push_back({7, 3});  // D -> G

    graph[5].push_back({8, 2});  // E -> T
    graph[6].push_back({8, 9});  // F -> T
    graph[7].push_back({8, 5});  // G -> T

    vector<int> topo = {0, 1, 2, 3, 4, 5, 6, 7, 8};

    int source = 0; // S
    int target = 8; // T

    shortestPathDP(graph, topo, source, target, name);
    longestPathDP(graph, topo, source, target, name);
    maxProductPathDP(graph, topo, source, target, name);

    return 0;
}