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
    vector<int> list; // �洢������ڽӶ���
    vector<int> h;    // �洢������ڽӱ������� list �е���ʼλ��
    vector<int> inDegree; // �洢ÿ����������
    vector<int> outDegree;//����
    map<pair<int, int>, int> weights; // �洢�ߵ�Ȩ��ֵ 
    
public:
    CompactGraph(int n, bool weighted) : list(), h(n, -1), inDegree(n, 0), outDegree(n, 0), isWeighted(weighted) {}

    //���ӱ�
    void addEdge(int from, int to, int weight = 1) {
        list.push_back(to);
        inDegree[to]++;
        outDegree[from]++;
        if (h[from] == -1) {
            h[from] = list.size() - 1;
        }
        weights[make_pair(from, to)] = weight;
    }
    //�ڽӾ���ת���ɽ����ڽӱ�
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
    //��ʾ�ڽӱ�
    void printAdjacencyList() {
        cout << "�ڽӱ�" << endl;
        for (int i = 0; i < h.size(); ++i) {
            if (h[i] != -1) {
                cout << "���� " << i << ": ";
                for (int j = h[i]; j != -1 && j < list.size(); ) {
                    cout << list[j] << " ";
                    if (isWeighted) {
                        cout << "(Ȩ��: " << weights[make_pair(i, list[j])] << ") ";
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
    // ��ȼ������ʾ
    void calculateInDegrees() {
        cout << "�ڵ����ȣ�" << endl;
        for (int i = 0; i < inDegree.size(); ++i) {
            cout << "���� " << i << " �����Ϊ: " << inDegree[i] << endl;
        }
    }
    // ���ȼ������ʾ
    void calculateOutDegrees() {
        cout << "�ڵ�ĳ��ȣ�" << endl;
        for (int i = 0; i < outDegree.size(); ++i) {
            cout << "���� " << i << " �ĳ���Ϊ: " << outDegree[i] << endl;
        }
    }
    // Kahn�㷨ʵ������������
    vector<int> topologicalSort() {
        int n = h.size();
        int k = 0; // ��Ч����ڵ���
        for (int i = 0; i < h.size(); i++) {
            if (h[i] != -1) {
                k++;
            }
        }
        vector<int> result;
        stack<int> s;

        // �����Ϊ0�Ķ�����ջ
        vector<int> inDegreeCopy = inDegree; // ʹ�ÿ�������ֹӰ��ԭʼ����
        for (int i = 0; i < n; ++i) {
            if (inDegreeCopy[i] == 0) {
                s.push(i);
            }
        }

        while (!s.empty()) {
            int current = s.top();
            s.pop();
            result.push_back(current);
            // ������ǰ������ڽӶ���
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
        // �������еĶ��������������ܶ�����������ͼ�д��ڻ�
        if (result.size() != n) {
            cout << "ͼ�д��ڻ����޷�������������" << endl;
            result.clear(); // ����һ���ս����ʾ���ڻ�
        }
        return result;
    }
    // DFS�㷨ʵ����������
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
    // Dijkstra's ���·��
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
        cout << "�Ӷ��� " << source << " ��������������·����" << endl;
        for (int i = 0; i < distances.size(); ++i) {
            cout << "���� " << source << " ������ " << i << " �����·������Ϊ: ";
            if (distances[i] == numeric_limits<int>::max()) {
                cout << "�����" << endl;
            }
            else {
                cout << distances[i] << endl;
            }
        }
    }
    bool isWeighted; // ��¼ͼ�Ƿ�����Ȩͼ
};

int main() {
    bool isWeighted;
    // �û�ѡ��ͼ������
    cout << "��ѡ��ͼ�����ͣ�" << endl;
    cout << "1. ������Ȩͼ" << endl;
    cout << "2. ������Ȩͼ" << endl;

    int graphType;
    cin >> graphType;

    if (graphType == 1) {
        isWeighted = false;
    }
    else if (graphType == 2) {
        isWeighted = true;
    }
    else {
        cout << "��Ч��ѡ�񣬳����˳���" << endl;
        return 0;
    }
    int vertices, edges;
    // ��ȡͼ�Ķ������ͱ���
    std::cout << "������ͼ�Ķ�����: ";
    std::cin >> vertices;

    cout << "������ͼ�ı���: ";
    cin >> edges;

    CompactGraph graph(vertices, isWeighted);

    // �ڽӾ���洢�ߵ���㡢�յ��Ȩ��ֵ
    vector<vector<pair<int, int>>> adjacencyMatrix(vertices, vector<pair<int, int>>(vertices, make_pair(0, 0)));

    // ����ߵ���Ϣ
    cout << "������ÿ���ߵ������յ�(������Ȩͼ����Ȩ��)��" << endl;
    for (int i = 0; i < edges; ++i) {
        int from, to, weight;

        cout << "�� " << i + 1 << ": ";

        cin >> from >> to;
        if (isWeighted) {
            cout << "������ߵ�Ȩ��: ";
            cin >> weight;
        }
        else {
            weight = 1; // Ĭ��Ȩ��Ϊ1
        }

        while (from >= vertices || to >= vertices) {
            cout << "����Ƿ� �������������" << endl;
            cin >> from >> to;
        }

        //�ڽӾ���
        adjacencyMatrix[from][to] = make_pair(1, weight);
    }
    // �ڽӾ����ת��
    graph.addEdgesFromMatrix(adjacencyMatrix);
    while (true) {
        cout << "��ѡ�������" << endl;
        cout << "1. �������" << endl;
        cout << "2. �������" << endl;
        cout << "3.��ӡ�ڽӱ�" << endl;
        cout << "4.Kahn�㷨ʵ����������" << endl;
        cout << "5.DFS�㷨ʵ����������" << endl;
        cout << "6.ѡ��Դ�ڵ����Dijkstra�㷨" << endl;
        cout << "0. �˳�" << endl;

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
            // Kahn�㷨ʵ����������
            vector<int> result = graph.topologicalSort();
            if (!result.empty()) {
                std::cout << "Kahn�㷨����������: ";
                for (int vertex : result) {
                    std::cout << vertex << " ";
                }
                std::cout << endl;

            }
            break;

        }
        case 5: {
            //DFS�㷨ʵ����������
            vector<int> resultDFS = graph.topologicalSortDFS();
            if (!resultDFS.empty()) {
                std::cout << "DFS������������";
                for (int vertex : resultDFS) {
                    std::cout << vertex << " ";
                }
                std::cout << endl;

            }
            break;
        }

        case 6: {
            // ѡ��Դ�ڵ����Dijkstra�㷨
            int source;
            cout << "������Dijkstra�㷨��Դ�ڵ�: ";
            cin >> source;

            vector<int> distances = graph.dijkstraShortestPath(source);
            graph.printShortestDistances(source, distances);
            break;
        }

        case 0:
            cout << "�˳�����" << endl;
            return 0;
        default:
            cout << "��Ч��ѡ�����������롣" << endl;
        }
    }
    return 0;
}
