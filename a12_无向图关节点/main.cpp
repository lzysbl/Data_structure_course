#include"Graph.h"
#include <opencv2/opencv.hpp>

//画图
void drawGraph(Graph g){
    //找关节点
    g.findArticulationPoints();
    //画图
    Point center(500,500);
    cv::Mat a(1000,1000,CV_8UC3,cv::Scalar(255,255,255));
    //画点
    int j = 0;
    for(int i=0;i<MAX_VERTICES;i++){
        if(g.isExist[i]){
            g.headpoint[i].x = center.x + 400*cos(2*3.1415926*j/(g.V));
            g.headpoint[i].y = center.y + 400*sin(2*3.1415926*j/(g.V));
            cv::circle(a,cv::Point(g.headpoint[i].x,g.headpoint[i].y),10,cv::Scalar(255,191,0),-2);
            g.headpoint[i].y = g.headpoint[i].y;
            j++;
        }
    }
   
    //画边
    for(int i=0;i<MAX_VERTICES;i++){
        for(int j=0;j<MAX_VERTICES;j++){
            if(g.adjMatrix[i][j]){
                cv::line(a,cv::Point(g.headpoint[i].x,g.headpoint[i].y),cv::Point(g.headpoint[j].x,g.headpoint[j].y),cv::Scalar(255,191,0),2);
            }
        }
    }
     //画关节点
    for(int i=0;i<MAX_VERTICES;i++){
        if(g.ArticulationPoint[i]){
            cv::circle(a,cv::Point(g.headpoint[i].x,g.headpoint[i].y),10,cv::Scalar(0,0,255),-2);
        }
    }
    //画节点编号
    for(int i=0;i<MAX_VERTICES;i++){
        if(g.isExist[i]){
            cv::putText(a,std::to_string(i),cv::Point(g.headpoint[i].x,g.headpoint[i].y),cv::FONT_HERSHEY_SIMPLEX,1,cv::Scalar(0,0,0),2);
        }
    }
    //显示
    cv::putText(a,"ArticulationPoints is in red color",cv::Point(50,50),cv::FONT_HERSHEY_SIMPLEX,1,cv::Scalar(0,0,255),2);
    cv::putText(a,"Other points is in blue color",cv::Point(50,100),cv::FONT_HERSHEY_SIMPLEX,1,cv::Scalar(255,191,0),2);
    cv::imshow("无向图",a);
    cv::waitKey(0);
}


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
