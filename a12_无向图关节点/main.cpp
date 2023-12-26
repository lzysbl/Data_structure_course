#include"Graph.h"

int main() {
    Graph g;
    // 示例：添加边和查找关节点
    while(1){

        std::cout<<"请选择功能："<<std::endl;
        std::cout<<"1.添加单个边"<<std::endl;
        std::cout<<"2.添加多个边"<<std::endl;
        std::cout<<"3.删除边"<<std::endl;
        std::cout<<"4.查询是否为关节点"<<std::endl;
        std::cout<<"5.统计"<<std::endl;
        std::cout<<"6.修改关节点"<<std::endl;
        std::cout<<"7.画出无向图"<<std::endl;
        std::cout<<"8.退出"<<std::endl;
        int choice;
        std::cin>>choice;
        std::system("clear");
        if(choice == 1){
            g.userAddEdge();
        }else if(choice == 2){
            g.userAddEdges();
        }else if(choice == 3){
            g.userRemoveEdge();
        }else if(choice == 4){
            g.isArticulationPoint();
        }else if(choice == 5){
            g.getNumberArticulationPoints();
        }else if(choice == 6){
            g.modifyArticulationPoint();
        }else if(choice == 7){
            drawGraph(g);
        }else if(choice == 8){
            break;
        }else{
            std::cout<<"输入错误，请重新输入"<<std::endl;
        }
        std::cout<<"按任意键继续"<<std::endl;
    }
    return 0;
}
