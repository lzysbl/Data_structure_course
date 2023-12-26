#include"Graph.h"

//构造函数
Graph::Graph(){
    V = 0;
    E = 0;
    numberArticulationPoints = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        isExist[i] =false;
        ArticulationPoint[i] = false; //关节点数组
        for (int j = 0; j < MAX_VERTICES; j++) {
            adjMatrix[i][j] = false;
        }
        visited[i] = false;
    }
}
//添加边
void Graph::addEdge(int v, int w) {
    // 确保顶点编号在范围内
    if (v >= 0 && v < MAX_VERTICES && w >= 0 && w < MAX_VERTICES) {
        // 添加边
        adjMatrix[v][w] = true;
        adjMatrix[w][v] = true;
        // 更新顶点数和边数
        if(!isExist[v]){
            //更新顶点数
            V++;
            isExist[v] = true;
        }
        if(!isExist[w]){
            //更新顶点数
            V++;
            isExist[w] = true;
        }
        // 更新边数
        E++;
    }
}
//用户自定义输入
void Graph::userAddEdge(){
    int v,w;
    std::cout<<"请输入要添加的边(0-99之间,空格隔开输入)：";
    std::cin>>v>>w;
    addEdge(v,w);
}
//添加多个边
void Graph::userAddEdges(){
    std::cout<<"请输入要添加的边的数量：";
    int n;
    std::cin>>n;
    for(int i=0;i<n;i++){
        userAddEdge();
    }
}
//删除边
void Graph::removeEdge(int v, int w) {
    // 确保顶点编号在范围内
    if (v >= 0 && v < MAX_VERTICES && w >= 0 && w < MAX_VERTICES) {
        adjMatrix[v][w] = false;
        adjMatrix[w][v] = false;
        bool isV = false;
        bool isW = false;
        for(int i=0;i<MAX_VERTICES;i++){
            if(adjMatrix[v][i]){
                isV = true;
                break;
            }
        }
        for(int i=0;i<MAX_VERTICES;i++){
            if(adjMatrix[w][i]){
                isW = true;
                break;
            }
        }
        if(!isV){
            isExist[v] = false;
            V--;
        }
        if(!isW){
            isExist[w] = false;
            V--;
        }
        // 更新边数
        E--;
    }
}
//用户自定义删除
void Graph::userRemoveEdge(){
    int v,w;
    std::cout<<"请输入要删除的边(0-99之间,空格隔开输入)：";
    std::cin>>v>>w;
    removeEdge(v,w);
}
//是否为关节点
void Graph::DFSUtil(int u) {
    bool adjMatrix_copy[MAX_VERTICES][MAX_VERTICES] = {false};  
    bool visited_copy[MAX_VERTICES] = {false};
    // 复制邻接矩阵，除去与顶点u相关的边
    int start = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            if (i == u || j == u) {
                continue;
            }
            adjMatrix_copy[i][j] = adjMatrix[i][j];
            if(adjMatrix[i][j]){
                start = i;
            }
        }
    }
    // 复制访问标记数组，除去顶点u
    int node_number = DFSConnectivityCheck(start, visited_copy, adjMatrix_copy);
    if(node_number != V-1){
        ArticulationPoint[u] = true;
        numberArticulationPoints++;
    }
}
//深度优先搜索
int Graph::DFSConnectivityCheck(int v, bool visited[], bool adjMatrix_copy[][MAX_VERTICES]) {
    visited[v] = true;
    int count = 1;  // 记录当前节点
    for (int i = 0; i < MAX_VERTICES; i++) {
        if (adjMatrix_copy[v][i] && !visited[i]) {
            count += DFSConnectivityCheck(i, visited, adjMatrix_copy);  // 递归调用并累加访问过的节点数
        }
    }
    return count;  // 返回访问过的节点总数
}
//查找关节点
void Graph::findArticulationPoints() {
    // 初始化
    for (int i = 0; i < MAX_VERTICES; i++) {
        visited[i] = false;
    }
    // 从第一个顶点开始深度优先搜索
    for (int i = 0; i < MAX_VERTICES; i++) {
        if (!visited[i]&&isExist[i]) {
            DFSUtil(i);
        }
    }
}
//查询是否为关节点
void Graph::isArticulationPoint(){
    findArticulationPoints();
        std::cout<<"请输入要查询的点：";
        int v;
        std::cin>>v;
        if(v >= 0 && v < MAX_VERTICES&&isExist[v]){
            if(ArticulationPoint[v]){std::cout<<"是关节点"<<std::endl;}
            else{std::cout<<"不是关节点"<<std::endl;}
        }else{
            std::cout<<"不是合法点"<<std::endl;
        }
    }
//统计
void Graph::getNumberArticulationPoints(){
    findArticulationPoints();
    std::cout<<"节点数："<<V<<std::endl;
    std::cout<<"边数："<<E<<std::endl;
    std::cout<<"当前的关节点数量为："<<numberArticulationPoints<<std::endl;
    
    std::cout<<std::endl;
    std::cout<<"当前的点有："<<std::endl;
    for(int i=0;i<MAX_VERTICES;i++){
        if(isExist[i]){
            std::cout<<i<<",";
        }
    }
    std::cout<<std::endl;
    std::cout<<"当前的边有："<<std::endl;
    for(int i=0;i<MAX_VERTICES;i++){
        for(int j=0;j<MAX_VERTICES;j++){
            if(adjMatrix[i][j]){
                std::cout<<i<<"-"<<j<<",";
            }
        }
    }
    std::cout<<std::endl;
    std::cout<<"当前的关节点有："<<std::endl;
    for(int i=0;i<MAX_VERTICES;i++){
        if(ArticulationPoint[i]){
            std::cout<<i<<"";
        }
    } 
    std::cout<<std::endl;
}
//修改关节点
void Graph::modifyArticulationPoint(){
    findArticulationPoints();
    std::cout<<"当前的关节点有："<<std::endl;
    for(int i=0;i<MAX_VERTICES;i++){
        if(ArticulationPoint[i]){
            std::cout<<i<<" ";
        }
    }
    std::cout<<std::endl;
    int v;
    std::cout<<"请输入要修改的关节点：";
    std::cin>>v;
    while(!ArticulationPoint[v]){
        std::cout<<"不是关节点，请重新输入：";
        std::cout<<"请输入要修改的关节点：";
        std::cin>>v;
    }
    int connectPoint[MAX_VERTICES]={0};
    int k=0;
    //遍历关节点,找到与v相连的点
    if(ArticulationPoint[v]){
        for(int j = 0;j < MAX_VERTICES;j++){
            if(adjMatrix[v][j]){
                connectPoint[k] = j;
                k++;
            }
        }
    }
    //删除关节点并且删除与关节点相连的边
    for(int i = 0;i < MAX_VERTICES;i++){
        if(adjMatrix[v][i]){
            adjMatrix[v][i] = false;
            E--;
        }
        if(adjMatrix[i][v]){
            adjMatrix[i][v] = false;
            E--;
        }
    }
    //删除关节点后图的顶点数减一
    ArticulationPoint[v] = false;
    //删除关节点后图片的节点数减一
    V--;
    //删除关节点数量减一
    numberArticulationPoints --;
    //删除关节点设置为不存在
    isExist[v] = false;
    //链接图剩余节点
    for(int i=0;i<k;i++){
        for(int j=i+1;j<k;j++){
            addEdge(connectPoint[i],connectPoint[j]);
        }
    }
}
//析构函数
Graph::~Graph(){
}