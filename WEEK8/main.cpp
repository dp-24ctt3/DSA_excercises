#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <queue>
using namespace std;

vector<vector<int>> convertMatrixToList(const string& filename) {
    vector<vector<int>> list = {};
    ifstream fin(filename);
    string line;

    // first line
    int size = 0;
    if (getline(fin, line)) {
        for (char i : line) {
            size += i - '0';
            size *= 10;
        }
        size /= 10;
    }
    list.push_back({size});

    // the rest
    while (getline(fin, line)) {
        int len = line.size();
        vector<int> tmp = {0};

        for (int i = 0; i < len; i++) {
            while (i < len && line[i] == ' ') i++;

            if (i < len && line[i] != '0') {
                tmp[0]++;
                tmp.push_back(i / 2 + i % 2);
            }
        }
        list.push_back(tmp);
        
    }

    // // output (to terminal)
    // for (int i = 0; i < list.size(); i++) {
    //     for (int j = 0; j < list[i].size(); j++) {
    //         cout << list[i][j] << ' ';
    //     }
    //     cout << endl;
    // }
    return list;
}

vector<vector<int>> convertListToMatrix(const string& filename) {
    vector<vector<int>> matrix = {};
    ifstream fin(filename);
    string line;

    // first line
    int size = 0;
    if (getline(fin, line)) {
        for (char i : line) {
            size += i - '0';
            size *= 10;
        }
        size /= 10;
    }
    matrix.push_back({size});

    // the rest
    while (getline(fin, line)) {
        int len = line.size();
        vector<int> tmp(size, 0);
        int cur = 0;
        // skip first number
        while (cur < len && line[cur] != ' ') cur++;
        while (cur < len && line[cur] == ' ') cur++;
        
        for (; cur < len; cur++) {
            int num = 0;
            while (cur < len && line[cur] != ' ') {
                num += line[cur] - '0';
                num *= 10;
                cur++;
            
            }
            num /= 10;
            tmp[num] = 1;
        }
        matrix.push_back(tmp);
    }

    // // output (to terminal)
    // for (int i = 0; i < matrix.size(); i++) {
    //     for (int j = 0; j < matrix[i].size(); j++) {
    //         cout << matrix[i][j] << ' ';
    //         if (j == matrix[i].size() - 1) cout << endl;
    //     }
    // }
    return matrix;
}

bool isDirected(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix[0][0];
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (adjMatrix[i + 1][j] != adjMatrix[j + 1][i]) return true;
        }
    }
    return false;
}

int countVertices(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix[0][0];
    for (int i = 0; i < n; i++) {
        if (adjMatrix[i + 1].size() != n) return -1;
    }
    return n;
}

int countEdges(const vector<vector<int>>& adjMatrix) {
    int count = 0;
    int n = adjMatrix[0][0];
    if (isDirected(adjMatrix)) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (adjMatrix[i + 1][j] != 0) count++;
            }
        }
    }
    else {
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                if (adjMatrix[i + 1][j] != 0) count++;
            }
        }
    } 
    return count;
}

vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix[0][0];
    bool is_isolated = false;
    vector<int> isolated = {};

    for (int i = 0; i < n; i++) {
        is_isolated = true;
        for (int j = 0; j < n; j++) {
            if (adjMatrix[i + 1][j] != 0) {
                is_isolated = false;
                break;
            }
        }
        if (is_isolated) isolated.push_back(i);
    }
    return isolated;
}

// Undirected Graph.
bool isCompleteGraph(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix[0][0];
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            // excluding self-loop
            if ((i == j && adjMatrix[i + 1][j] != 0) || (i != j && adjMatrix[i + 1][j] == 0)) return false;
        }
    }
    return true;
}

// Undirected Graph
bool isBipartite(const std::vector<std::vector<int>>& adjMatrix) {
    int n = adjMatrix[0][0];
    vector<int> mark(n, -1);

    // bfs
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (mark[i] == -1) {
            mark[i] = 0;
            q.push(i);
        }

        while (!q.empty()) {
            int cur_vertex = q.front();
            q.pop();

            for (int j = 0; j < n; j++) {
                if (adjMatrix[cur_vertex + 1][j] == 1) {
                    if (mark[j] == -1) {
                        mark[j] = 1 - mark[cur_vertex];
                        q.push(j);
                    }
                    else if (mark[j] == mark[cur_vertex]) return false;
                }
            }
        }
    }
    return true;
}

// Undirected Graph
bool isCompleteBipartite(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix[0][0];
    vector<int> mark(n, -1);

    // bfs - isBipartite?
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (mark[i] == -1) {
            mark[i] = 0;
            q.push(i);
        }

        while (!q.empty()) {
            int neighbors = q.size();
            int cur_vertex = q.front();
            q.pop();

            for (int j = 0; j < n; j++) {
                if (adjMatrix[cur_vertex + 1][j] == 1) {
                    if (mark[j] == -1) {
                        mark[j] = 1 - mark[cur_vertex];
                        q.push(j);
                    }
                    else if (mark[j] == mark[cur_vertex]) return false;
                }
            }
        }
    }

    // isCompleteBipartite?
    vector<int> set1, set2;
    for (int i = 0; i < n; i++) {
        if (mark[i] == 0) set1.push_back(i);
        else set2.push_back(i);
    }

    for (int i : set1) {
        for (int j : set2) {
            if (adjMatrix[i + 1][j] == 0) return false;
        }
    }
    return true;
}

vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix) {
    vector<vector<int>> UndirectedGraph = adjMatrix;
    int n = adjMatrix[0][0];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++) {
            if (adjMatrix[i + 1][j] != 0) 
            UndirectedGraph[j + 1][i] = UndirectedGraph[i + 1][j] = max(adjMatrix[j + 1][i], adjMatrix[i + 1][j]);
        }
    }
    return UndirectedGraph;
}

vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix[0][0];
    vector<vector<int>> ComplementGraph(n, vector<int>(n, 0));
    ComplementGraph.insert(ComplementGraph.begin(), adjMatrix[0]);

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++) {
            if (i != j && adjMatrix[i + 1][j] == 0) ComplementGraph[i + 1][j] = 1;
            if (i == j && adjMatrix[i + 1][j] != 0) ComplementGraph[i + 1][j] = 0;
        }
    }
    return ComplementGraph;
}

void dfsEuler(const int start, vector<int>& EulerCycle, vector<vector<int>>& visited_edges) {
    int n = visited_edges.size();    

    for (int i = 0; i < n; i++) {
        if (visited_edges[start][i] != 0) {
            visited_edges[start][i] = visited_edges[i][start] = 0;
            dfsEuler(i, EulerCycle, visited_edges);
        }
    }
    EulerCycle.push_back(start);
}

vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix[0][0];

    // count degree
    vector<int> degree(n, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adjMatrix[i + 1][j] != 0) degree[i]++;
        }
    }

    // if one vertex has an odd degree
    for (int i : degree) if (i % 2 == 1) return {};

    // get start vertex
    int start = 0;
    while (start < n && degree[start] == 0) start++;
    if (start >= n) return {};

    vector<int> EulerCycle;
    vector<vector<int>> visited_edges = adjMatrix;
    visited_edges.erase(visited_edges.begin());
    dfsEuler(start, EulerCycle, visited_edges);

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (visited_edges[i][j] != 0) return {};
        }
    }
    return EulerCycle;
}

void dfsTraversal(const vector<vector<int>>& adjMatrix, vector<bool>& visited, vector<vector<int>>& dfstree, int start) {
    visited[start] = true;

    for (int i = 0; i < adjMatrix[0][0]; i++) {
        if (adjMatrix[start + 1][i] != 0 && !visited[i]) {
            dfstree.push_back({start, i});
            dfsTraversal(adjMatrix, visited, dfstree, i);
        }
    }
}

vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
    int n = adjMatrix[0][0];
    if (n == 0) return {{0}};

    vector<vector<int>> dfstree;
    vector<bool> visited(n, false);
    
    dfsTraversal(adjMatrix, visited, dfstree, start);

    return dfstree;
}


vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
    int n = adjMatrix[0][0];
    if (n == 0) return {{0}};

    vector<vector<int>> bfstree;

    vector<bool> visited(n, false);
    visited[start] = true;
    queue<int> q;
    q.push(start);

    while (!q.empty()) {
        int cur_vertex = q.front();
        q.pop();

        for (int i = 0; i < n; i++) {
            if (adjMatrix[cur_vertex + 1][i] == 1 && !visited[i]) {
                visited[i] = true;
                q.push(i);
                bfstree.push_back({cur_vertex, i});
            }
        }
    }
    return bfstree;
}

bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix[0][0];
    vector<vector<int>> visited = adjMatrix;
    if (n == 0 || u > n || v > n) return false;
    if (u == v) return true;

    vector<int> neighbor = {};

    for (int i = 0; i < n; i++) {
        if (visited[u + 1][i] != 0) {
            if (i == v) return true;
            visited[u + 1][i] = 0;
            neighbor.push_back(i);
        }
    }

    for (int i = 0; i < neighbor.size(); i++) {
        if (isConnected(neighbor[i], v, visited)) return true;
    }
    return false;
}

vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix[0][0];
    if (n == 0 || start > n || end > n) return {};
    if (start == end) return {start};

    vector<int> prev(n, -1);

    vector<int> distance(n, INT_MAX);
    distance[start] = 0;
    
    // pq is a list of <distance, vertex>
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, start});

    // calculating distance
    while (!pq.empty()) {        
        int cur_vertex = pq.top().second;
        pq.pop();

        for (int i = 0; i < n; i++) {
            if (adjMatrix[cur_vertex + 1][i] > 0) {
                if (distance[i] > distance[cur_vertex] + adjMatrix[cur_vertex + 1][i]) {
                    distance[i] = distance[cur_vertex] + adjMatrix[cur_vertex + 1][i];
                    prev[i] = cur_vertex;
                    pq.push({distance[i], i});
                }
            }
        }
    }

    // get path
    vector<int> path;
    if (prev[end] > -1) {   // found path
        int cur = end;
        while (cur != start) {
            path.insert(path.begin(), cur);
            cur = prev[cur];
        }
        path.insert(path.begin(), cur);
    }

    return path;
}

vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix[0][0];
    if (n == 0 || start > n || end > n) return {};
    if (start == end) return {start};

    vector<int> prev(n, -1);
    vector<int> distance(n, INT_MAX);
    distance[start] = 0;
    

    for (int times = 0; times < n; times++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (adjMatrix[i + 1][j] != 0 && distance[i] != INT_MAX && distance[j] > distance[i] + adjMatrix[i + 1][j]) {
                    distance[j] = distance[i] + adjMatrix[i + 1][j];
                    prev[j] = i;
                }
                    
            }
        }
    }
    
    // negative cycles detecting
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // if there are negative cycles, a shortest path will not exist, therefore return blank path
            if (adjMatrix[i + 1][j] != 0 && distance[i] != INT_MAX && distance[j] > distance[i] + adjMatrix[i + 1][j])
                return {};
        }
    }

    vector<int> path;
    if (distance[end] != INT_MAX) { // found path
        int cur = end;
        while (cur != start && cur != -1) {
            path.insert(path.begin(), cur);
            cur = prev[cur];
        }
        path.insert(path.begin(), cur);
    }

    return path;
}