#include <iostream>
#include <vector>
#include <stack>
#include <limits>
#include <algorithm>
#include <queue>
#include <functional>
#include <map>
using namespace std;
#define Maxsize 100

class CompactGraph {
private:
    vector<int> list; // 存储顶点的邻接顶点
    vector<int> h;    // 存储顶点的邻接表在向量 list 中的起始位置
    vector<int> inDegree; // 存储每个顶点的入度
    vector<int> outDegree;//出度
    map<pair<int, int>, int> weights; // 存储边的权重值 
    
public:
    CompactGraph(int n, bool weighted) : list(), h(n, -1), inDegree(n, 0), outDegree(n, 0), isWeighted(weighted) {}

    //增加边
    void addEdge(int from, int to, int weight = 1) {
        list.push_back(to);
        inDegree[to]++;
        outDegree[from]++;
        if (h[from] == -1) {
            h[from] = list.size() - 1;
        }
        weights[make_pair(from, to)] = weight;
    }
    //邻接矩阵转换成紧缩邻接表
    void addEdgesFromMatrix(const vector<vector<pair<int, int>>>& matrix) {
        int n = matrix.size();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j].first == 1) {
                    int weight = isWeighted ? matrix[i][j].second : 1;
                    addEdge(i, j, weight);
                }
            }
        }
    }
    //显示邻接表
    void printAdjacencyList() {
        cout << "邻接表：" << endl;
        for (int i = 0; i < h.size(); ++i) {
            if (h[i] != -1) {
                cout << "顶点 " << i << ": ";
                for (int j = h[i]; j != -1 && j < list.size(); ) {
                    cout << list[j] << " ";
                    if (isWeighted) {
                        cout << "(权重: " << weights[make_pair(i, list[j])] << ") ";
                    }
                    if (j != h.size() - 1 && j < h[i + 1] - 1) {
                        j++;
                    }
                    else if (i == h.size() - 1 && i < list.size() - 1) {
                        j++;
                    }
                    else {
                        j = -1;
                    }
                }
                cout << endl;
            }
            else cout << endl;
        }
    }
    // 入度计算和显示
    void calculateInDegrees() {
        cout << "节点的入度：" << endl;
        for (int i = 0; i < inDegree.size(); ++i) {
            cout << "顶点 " << i << " 的入度为: " << inDegree[i] << endl;
        }
    }
    // 出度计算和显示
    void calculateOutDegrees() {
        cout << "节点的出度：" << endl;
        for (int i = 0; i < outDegree.size(); ++i) {
            cout << "顶点 " << i << " 的出度为: " << outDegree[i] << endl;
        }
    }
    // Kahn算法实现拓扑排序函数
    vector<int> topologicalSort() {
        int n = h.size();
        int k = 0; // 有效输入节点数
        for (int i = 0; i < h.size(); i++) {
            if (h[i] != -1) {
                k++;
            }
        }
        vector<int> result;
        stack<int> s;

        // 将入度为0的顶点入栈
        vector<int> inDegreeCopy = inDegree; // 使用拷贝，防止影响原始数据
        for (int i = 0; i < n; ++i) {
            if (inDegreeCopy[i] == 0) {
                s.push(i);
            }
        }

        while (!s.empty()) {
            int current = s.top();
            s.pop();
            result.push_back(current);
            // 遍历当前顶点的邻接顶点
            for (int i = h[current]; i != -1 && i < list.size(); ) {
                int neighbor = list[i];
                if (--inDegreeCopy[neighbor] == 0) {
                    s.push(neighbor);
                }
                if (current != k - 1 && i < h[current + 1] - 1) {
                    i++;
                }
                else if (current == k - 1 && i < list.size() - 1) {
                    i++;
                }
                else {
                    i = -1;
                }
            }
        }
        // 如果结果中的顶点数量不等于总顶点数量，则图中存在环
        if (result.size() != n) {
            cout << "图中存在环，无法进行拓扑排序" << endl;
            result.clear(); // 返回一个空结果表示存在环
        }
        return result;
    }
    // DFS算法实现拓扑排序
    vector<int> topologicalSortDFS() {
        int n = h.size();
        vector<int> result;
        vector<bool> visited(n, false);
        stack<int> s;

        function<void(int)> dfs = [&](int vertex) {
            visited[vertex] = true;

            for (int i = h[vertex]; i != -1 && i < list.size(); ) {
                int neighbor = list[i];
                if (!visited[neighbor]) {
                    dfs(neighbor);
                }

                if (vertex != n - 1 && i < h[vertex + 1] - 1) {
                    i++;
                }
                else if (vertex == n - 1 && i < list.size() - 1) {
                    i++;
                }
                else {
                    i = -1;
                }
            }

            s.push(vertex);
        };

        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                dfs(i);
            }
        }

        while (!s.empty()) {
            result.push_back(s.top());
            s.pop();
        }

        return result;
    }
    // Dijkstra's 最短路径
    vector<int> dijkstraShortestPath(int source) {
        int n = h.size();
        vector<int> dist(n, numeric_limits<int>::max());
        vector<bool> visited(n, false);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        dist[source] = 0;
        pq.push({ 0, source });

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (visited[u]) {
                continue;
            }

            visited[u] = true;

            for (int i = h[u]; i != -1 && i < list.size(); ) {
                int v = list[i];
                int weight = weights[make_pair(u, v)];  // Use the weight of the edge

                if (!visited[v] && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({ dist[v], v });
                }

                if (u != n - 1 && i < h[u + 1] - 1) {
                    i++;
                }
                else if (u == n - 1 && i < list.size() - 1) {
                    i++;
                }
                else {
                    i = -1;
                }
            }
        }

        return dist;
    }
    // Dijkstra's algorithm
    void printShortestDistances(int source, const vector<int>& distances) {
        cout << "从顶点 " << source << " 到其他顶点的最短路径：" << endl;
        for (int i = 0; i < distances.size(); ++i) {
            cout << "顶点 " << source << " 到顶点 " << i << " 的最短路径距离为: ";
            if (distances[i] == numeric_limits<int>::max()) {
                cout << "无穷大" << endl;
            }
            else {
                cout << distances[i] << endl;
            }
        }
    }
    bool isWeighted; // 记录图是否是有权图
};

int main() {
    bool isWeighted;
    // 用户选择图的类型
    cout << "请选择图的类型：" << endl;
    cout << "1. 有向无权图" << endl;
    cout << "2. 有向有权图" << endl;

    int graphType;
    cin >> graphType;

    if (graphType == 1) {
        isWeighted = false;
    }
    else if (graphType == 2) {
        isWeighted = true;
    }
    else {
        cout << "无效的选择，程序退出。" << endl;
        return 0;
    }
    int vertices, edges;
    // 获取图的顶点数和边数
    std::cout << "请输入图的顶点数: ";
    std::cin >> vertices;

    cout << "请输入图的边数: ";
    cin >> edges;

    CompactGraph graph(vertices, isWeighted);

    // 邻接矩阵存储边的起点、终点和权重值
    vector<vector<pair<int, int>>> adjacencyMatrix(vertices, vector<pair<int, int>>(vertices, make_pair(0, 0)));

    // 输入边的信息
    cout << "请输入每条边的起点和终点(若是有权图增加权重)：" << endl;
    for (int i = 0; i < edges; ++i) {
        int from, to, weight;

        cout << "边 " << i + 1 << ": ";

        cin >> from >> to;
        if (isWeighted) {
            cout << "请输入边的权重: ";
            cin >> weight;
        }
        else {
            weight = 1; // 默认权重为1
        }

        while (from >= vertices || to >= vertices) {
            cout << "输入非法 请检测后重新输入" << endl;
            cin >> from >> to;
        }

        //邻接矩阵
        adjacencyMatrix[from][to] = make_pair(1, weight);
    }
    // 邻接矩阵的转变
    graph.addEdgesFromMatrix(adjacencyMatrix);
    while (true) {
        cout << "请选择操作：" << endl;
        cout << "1. 计算入度" << endl;
        cout << "2. 计算出度" << endl;
        cout << "3.打印邻接表" << endl;
        cout << "4.Kahn算法实现拓扑排序" << endl;
        cout << "5.DFS算法实现拓扑排序" << endl;
        cout << "6.选择源节点进行Dijkstra算法" << endl;
        cout << "0. 退出" << endl;

        int choice;
        cin >> choice;
        switch (choice) {
        case 1:
            graph.calculateInDegrees();
            break;
        case 2:
            graph.calculateOutDegrees();
            break;
        case 3:
            graph.printAdjacencyList();
            break;
        case 4: {
            // Kahn算法实现拓扑排序
            vector<int> result = graph.topologicalSort();
            if (!result.empty()) {
                std::cout << "Kahn算法拓扑排序结果: ";
                for (int vertex : result) {
                    std::cout << vertex << " ";
                }
                std::cout << endl;

            }
            break;

        }
        case 5: {
            //DFS算法实现拓扑排序
            vector<int> resultDFS = graph.topologicalSortDFS();
            if (!resultDFS.empty()) {
                std::cout << "DFS拓扑排序结果：";
                for (int vertex : resultDFS) {
                    std::cout << vertex << " ";
                }
                std::cout << endl;

            }
            break;
        }

        case 6: {
            // 选择源节点进行Dijkstra算法
            int source;
            cout << "请输入Dijkstra算法的源节点: ";
            cin >> source;

            vector<int> distances = graph.dijkstraShortestPath(source);
            graph.printShortestDistances(source, distances);
            break;
        }

        case 0:
            cout << "退出程序。" << endl;
            return 0;
        default:
            cout << "无效的选择，请重新输入。" << endl;
        }
    }
    return 0;
}
