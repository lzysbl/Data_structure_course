#include <iostream>
#include <fstream>
#define MAX_VERTICES 100
// 图类
class Point {
public:
    float x;
    float y;
    Point(){
        x = 0;
        y = 0;
    }
    Point(float x,float y){
        this->x = x;
        this->y = y;
    }

};
class Graph {
public: 
    int V;  // 顶点数
    int E;  // 边数
    bool adjMatrix[MAX_VERTICES][MAX_VERTICES];  // 邻接矩阵
    bool visited[MAX_VERTICES];  // 访问标记数组
    bool isExist[MAX_VERTICES]; //顶点是否存在
    int  numberArticulationPoints; //关节点数
    bool ArticulationPoint[MAX_VERTICES]; //关节点数组
    //深度优先搜索
    void DFSUtil(int v);
    Point headpoint[MAX_VERTICES]; //顶点坐标
    Graph();
    //添加边
    void addEdge(int v, int w);
    //删除边
    void removeEdge(int v, int w);
    //用户自定义添加
    void userAddEdge();
    //用户自定义删除
    void userRemoveEdge();
    //找关节点
    void findArticulationPoints();
    //修改关节点
    void modifyArticulationPoint();
    // 其他功能...
    int DFSConnectivityCheck(int v, bool visited[], bool adjMatrix_copy[][MAX_VERTICES]);
    //判断删除节点后图是否连通
    bool isConnectedAfterRemoval(int u);
    //查询是否为关节点
    void isArticulationPoint();
    //添加多个边
    void userAddEdges();
    //统计
    void getNumberArticulationPoints();
    //图的遍历
    ~Graph();
};