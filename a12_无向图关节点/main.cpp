#include"Graph.h"

int main() {
    Graph g;
    // 示例：添加边和查找关节点
    while(1){
        std::cout<<"请选择功能："<<std::endl;
        std::cout<<"-1.重置图"<<std::endl;
        std::cout<<"0.随机生成连通图"<<std::endl;
        std::cout<<"1.添加单个边"<<std::endl;
        std::cout<<"2.添加多个边"<<std::endl;
        std::cout<<"3.删除边"<<std::endl;
        std::cout<<"4.查询是否为关节点"<<std::endl;
        std::cout<<"5.统计"<<std::endl;
        std::cout<<"6.修改关节点"<<std::endl;
        std::cout<<"7.删除并修改关节点"<<std::endl;
        std::cout<<"8.画出无向图"<<std::endl;
        std::cout<<"9.写入文件"<<std::endl;
        std::cout<<"10.读取文件"<<std::endl;
        std::cout<<"11.退出"<<std::endl;
        int choice;
        std::cin>>choice;
        std::system("clear");
        if(choice == -1){
            g = Graph();
        }
        else if(choice == 0){
            g.randomGraph();
        }else if(choice == 1){
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
            g.deleteArticulationPoint();
        }else if(choice == 8){
            drawGraph(g);
        }else if(choice == 9){
            g.userWriteToFile();
        }else if(choice == 10){
            g.userReadFromFile();
        }else if(choice == 11){
            break;
        }else{
            std::cout<<"输入错误，请重新输入"<<std::endl;
        }
    }
    return 0;
}
