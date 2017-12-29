//
//  Airplane_System.hpp
//  Iplane
//
//  Created by 杨溢 管清泉 陆子旭 on 2017/12/22.
//  Copyright © 2017年 杨溢 管清泉 陆子旭. All rights reserved.
//

#ifndef Airplane_System_hpp
#define Airplane_System_hpp

#include "stdafx.h"
#include <string>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

//定义一个航班信息的类
class flight
{
public:
    string flight_number;   //航班号
    string starting_point;  //起始城市
    string finishing_point; //到达城市
    long long start_time;   //起飞时间
    long long finish_time;  //到达时间
    int price;              //飞机票价
    int discount;           //票价折扣
    string company;         //所属公司
    int seat_number;        //座位总数
    int book_number;        //已预定总数
};

//定义一个飞机订票系统的类
class Airplane_System
{
public:
    Airplane_System();                                          //构造函数
    ~Airplane_System();                                         //析构函数
    void dataloading();                                         //航班信息录入
    void current_information_view();                            //航班信息浏览
    void check_information();                                   //航班信息查询
    void ticket_booking();                                      //预订机票
    void ticket_returning(string);                              //退票(航班号)
    void flight_list(int,long long,long long,string,string);    //相应航班排序
    void flight_recommended();                                  //航班线路设计
    void output_route();                                        //航班网络输出
    void best_route_recommended(long long,long long,string,string);//最优航班线路推荐
private:
    //边链表
    struct edge
    {
        int next_point;     //终点城市
        edge* next;         //下一条边
        int flight_node;    //航班节点信息(vector数组下标)
    };
    //顶点数组
    struct point
    {
        string cityname;    //城市名称
        edge* address;      //边链表的头指针
    };
    int number_of_city;                 //开放航线的城市个数
    int total;                          //航班总数
    flight flight_table;                //表头
    vector <flight> flight_totalnumber; //flight数组(暂时不得进行排序，删除，添加元素等操作)
    vector <point> point_link;          //邻接表顶点数组
    bool int_compare(int, int);         //int比较，判断第一个int是否小于第二个int
    bool string_compare(string, string);//string比较，比较两个string,是否相同
    //用于用于vector的起始时间排序函数
    static bool vector_start_time_compare(const flight &a, const flight &b){
        return a.start_time < b.start_time;
    }
    //用于用于vector的价格排序函数
    static bool vector_price_compare(const flight &a, const flight &b){
        return a.price < b.price;
    }
    //用于vector的查找函数(自定义类的方式实现)
    class findx {
    private: string test;
    public:
        findx(const string str):test(str) {}
        bool operator()(point& dValue) {
            if(dValue.cityname == test) return true;
            else return false;
        }
    };
    void print_flight_data(flight);     //输出航班信息

    void print_lzx(int);                //定义的相关输出函数 by 陆子旭
};

void Airplane_System::flight_recommended()
{
    string city_takeoff;
    string city_arrive;
    int time_takeoff;
    int time_arrive;
    int index;
    edge* edge_guodu;
    bool flag = false;
    vector<point>::iterator result;
    cout << "请输入您的出发城市"<<endl;
    cin >> city_takeoff;
    cout << "请输入您的目的城市" << endl;
    cin >> city_arrive;
    cout << "请输入您可以接受出发的时间" << endl;
    cin >> time_takeoff;
    cout << "请输入您可以接受到达的时间" << endl;
    cin >> time_arrive;
    result = find(point_link.begin(), point_link.end(), city_takeoff);
    index = int(result - point_link.begin());
    edge_guodu = point_link[index].address;
    while (edge_guodu)
    {
        if (point_link[edge_guodu->next_point].cityname == city_arrive)
        {
            flag = true;
        }
        edge_guodu = edge_guodu->next;
    }
    if (!flag)
    {

    }
}

//构造函数
Airplane_System::Airplane_System(){

}

//析构函数
Airplane_System::~Airplane_System(){

}

//输出航班信息
void print_flight_data(flight temp){
    cout << temp.flight_number << '\t' << temp.starting_point << '\t' << temp.finishing_point <<'\t'<< temp.start_time << '\t' << temp.finish_time << '\t' << temp.price << '\t'<<temp.discount<< '\t'<< temp.company << '\t' << temp.seat_number << '\t' << temp.book_number << endl;
}

//int比较，判断第一个int是否小于第二个int
bool Airplane_System::int_compare(int temp_first,int temp_last){
    if (temp_first < temp_last) {
        return true;
    }else{
        return false;
    }
};

//string比较，比较两个string,是否相同
bool Airplane_System::string_compare(string temp_first, string temp_last){
    if (temp_first == temp_last) {
        return true;
    }else{
        return false;
    }
}

//信息录入  从文件录入到程序
//输出vector数组，邻接表 by 管清泉
void Airplane_System::dataloading() {
    ifstream file;                  //读入文件
    flight temp_flight;             //临时航班类
    point temp_point;               //临时顶点节结点
    edge *temp_edge1,*temp_edge2;   //临时边结点
    vector<point>::iterator result; //vector迭代器
    file.open("C:/Users/97263/Desktop/Airplace_System/file.txt");
    if (file.is_open() == false)
    {
        cerr << "error";
        exit(1);
    }
    //读表头
    if (!file.eof()) {
        file >> flight_table.starting_point;
        file >> flight_table.finishing_point;
        file >> flight_table.company;
        file >> flight_table.flight_number;
        file >> flight_table.start_time;
        file >> flight_table.finish_time;
        file >> flight_table.price;
        file >> flight_table.discount;
        file >> flight_table.seat_number;
        file >> flight_table.book_number;
        flight_totalnumber.push_back(temp_flight);
    }
    while (!file.eof()) {
        //统计航线数目
        total++;
        //读数据
        file >> temp_flight.starting_point;
        file >> temp_flight.finishing_point;
        file >> temp_flight.company;
        file >> temp_flight.flight_number;
        file >> temp_flight.start_time;
        file >> temp_flight.finish_time;
        file >> temp_flight.price;
        file >> temp_flight.discount;
        file >> temp_flight.seat_number;
        file >> temp_flight.book_number;
        flight_totalnumber.push_back(temp_flight);
        //生成邻接表
        //判断终点城市结点
        result = find_if(point_link.begin(),point_link.end(),findx(temp_flight.finishing_point));
        if (result == point_link.end()) {
            temp_point.cityname = temp_flight.finishing_point;
            temp_point.address = NULL;
            point_link.push_back(temp_point);
        }
        //生成边结点
        temp_edge1 = new edge;
        temp_edge1->next_point = int(result - point_link.begin());
        temp_edge1->flight_node = total - 1;
        temp_edge1->next = NULL;
        //判断起点城市结点
        result = find_if(point_link.begin(),point_link.end(),findx(temp_flight.starting_point));
        if (result == point_link.end()) {
            temp_point.cityname = temp_flight.starting_point;
            temp_point.address = NULL;
            point_link.push_back(temp_point);
        }
        //将边加入邻接表
        if (!point_link[result - point_link.begin()].address) {
            point_link[result - point_link.begin()].address = temp_edge1;
        }else{
            temp_edge2 = point_link[result - point_link.begin()].address;
            while (temp_edge2->next) {
                temp_edge2 = temp_edge2->next;
            }
            temp_edge2->next = temp_edge1;
        }
        //城市数目
        number_of_city = int(point_link.size());
    }
    file.close();
}

void Airplane_System::current_information_view()
{
    for (int i = 0; i < total; i++)
        cout << number1[i] << endl;
}

void Airplane_System::flight_recommended()
{
    string where_to_start;
    string where_to_go;
    int time_to_go;
    int time_to_arrive;
    cout << "请输入出发地:" << endl;
    cin >> where_to_start;
    cout << "请输入目的地" << endl;
    cin >> where_to_go;

}

//陆子旭定义的相关输出函数 by 陆子旭
void Airplane_System::print_lzx(int temp_a){
    switch (temp_a) {
        case -1:cout << "退票成功!" << endl;break;
        case -2:cout << "退票失败!" << endl;break;
        default:cout << temp_a << endl;break;
    }
}

//退票 by 陆子旭
void Airplane_System::ticket_returning(string flight_num){
    for (int i = 0; i <total; i++) {
        if (flight_totalnumber[i].flight_number == flight_num) {
            if (flight_totalnumber[i].book_number > 0) {
                flight_totalnumber[i].book_number --;
                print_lzx(-1);
            }else{
                print_lzx(-2);
            }
            break;
        }
    }
}

//相应航班排序 by 陆子旭
//参数分别为：
//升降序（sort_bool）： 1为时间从低到高，2为时间从高到低，3为价格从低到高，4为价格从高到低；
//对于起飞时间起始时间限制（timef_bool）；
//对于起飞时间结束时间限制（timel_bool）；
//起始城市（start_bool）；
//到达城市（arrive_bool）；
void Airplane_System::flight_list
(int sort_bool=1,long long timef_bool=201708010000,
 long long timel_bool=201708020000,
 string start_bool="长春",string arrive_bool="长春"){
    vector<flight> temp;    //临时中间量
    int sum(0);             //总数
    //筛选
    for (int i = 0; i <total; i++) {
        if (flight_totalnumber[i].start_time > timef_bool&&
            flight_totalnumber[i].start_time < timel_bool&&
            flight_totalnumber[i].starting_point == start_bool&&
            flight_totalnumber[i].starting_point == arrive_bool
            ) {
            temp.push_back(flight_totalnumber[i]);
            sum++;
        }
    }
    switch (sort_bool) {
        case 1:
            sort(temp.begin(), temp.end(), vector_start_time_compare);
            for (int i = 0; i <sum; i++) {
                print_flight_data(flight_totalnumber[i]);
            }
        case 2:
            sort(temp.begin(), temp.end(), vector_start_time_compare);
            for (int i = sum-1; i >=0; i--) {
                print_flight_data(flight_totalnumber[i]);
            }
        case 3:
            sort(temp.begin(), temp.end(), vector_price_compare);
            for (int i = 0; i <sum; i++) {
                print_flight_data(flight_totalnumber[i]);
            }
        case 4:
            sort(temp.begin(), temp.end(), vector_price_compare);
            for (int i = sum-1; i >=0; i--) {
                print_flight_data(flight_totalnumber[i]);
            }
        default:
            break;
    }

}

//最优航班线路推荐 by 陆子旭
//采用广度优先搜索
//参数分别为：
//对于起飞时间起始时间限制（timef_bool）；
//对于起飞时间结束时间限制（timel_bool）；
//起始城市（start_bool）；
//到达城市（arrive_bool）；
void Airplane_System::best_route_recommended(long long timef_bool=201708010000,
                                             long long timel_bool=201708020000,string start_bool="长春",string arrive_bool="长春"){
    int visit[number_of_city];
    queue<int> Q;
    edge *p;
    for (int i=0; i<number_of_city; i++){
        visit[i] = 0;
    }
    for (int i=0; i<number_of_city; i++) {
        int j(0);
        if (visit[i]) {
            continue;
        }
        print_flight_data(flight_totalnumber[i]);
        visit[i] = 1;
        Q.push(i);
        while (!Q.empty()){
            j=Q.front();
            Q.pop();
            p = point_link[j].address;
            while (p){
                if (!visit[p->next->next_point]){
                    visit[p->next->next_point] = 1;
                    print_flight_data(flight_totalnumber[p->next->flight_node]);
                    Q.push(p->next->next_point);
                }
                p = p->next;
            }
        }
    }
}

//航班信息查询 by 杨溢
void Airplane_Syetem::check_information(){
    string flightnum;
    cout << "请输入想要查询的航班号：\n" << endl;
    cin >> flightnum;
    for (int i = 0; i < total; i++){
        if (flight_totalnumber[i].flight_number == flight){
            cout << "起降时间：" << flight_totalnumber[i].start_time << "-" << flight_totalnumber[i].finish_time << endl;
            cout << "航行地点：" << flight_totalnumber[i].starting_point << "-" << flight_totalnumber[i].finishing_point << endl;
            cout << "飞机票价：" << flight_totalnumber[i].price << endl;
            cout << "票价折扣：" << flight_totalnumber[i].discount << endl;
            cout << "所属公司：" << flight_totalnumber[i].company << endl;
            cout << "剩余票数：" << flight_totalnumber[i].seat_number - flight_totalnumber[i].book_number << endl;
            return;
        }
    }
}

//订票系统 by 杨溢
void Airplane_System::ticktet_booking(){
    int if_site=0; //是否有符合条件的
    vector<int>the_other_choice;
    int ordinal,ticket_position;
    string date,flight_num;
    string date1, date2;//表示日期
    cout << "请输入航班日期，航班号：";
    cin >> date >> flight_num;
    date1 = "2017" + date + "0000";//用来表示一整天
    date2 = "2017" + date + "2359";
    for (ticket_position=0;ticket_position<total&&if_site==0;ticket_position++){//用位置信息和起始城市进行匹配
        if(date1<flight_totalnumber[i].start_time&&date2>flight_totalnumber[i].start_time&&flight_totalnumber[i].flight_number==flight_num){
            if(flight_totalnumber[i].seat_number>flight_totalnumber[i].book_number){//有空位
                if_site=1;
            }
        }

    }
    if(ticket_positon==total&&if_site==0){//信息查找失败
        cout<<"信息输入有误，没有找到符合条件的信息\n";
        return;
    }
    if(if_site==0&&ticket_position<total){//无票
        cout<<"该航班已无票\n";
        string st_po,fi_po;
        st_po=flight_totalnumber[ticket_position].starting_point;
        fi_po=flight_totalnumber[ticket_position].finishing_point;
        for(int i=0;i<total;i++){
            if(i==ticket_position)
            continue;
            if(date1<flight_totalnumber[i].start_time&&date2>flight_totalnumber[i].start_time&&flight_totalnumber[i].starting_point==st_po&&flight_totalnumber[i].finishing_point==fi_po){
                the_other_choice.push_back(i);
                }
        }
        cout<<"系统推荐的其他符合条件的航班信息为：\n"<<endl;
        for(int i=0;i<the_other_choice.size;i++){
            cout<<i<<". "<<endl;
            cout<<"航班号："<<flight_totalnumber[the_other_choice[i]].flight_number<<" "<<endl;
            cout<<"起降时间:"<<flight_totalnumber[the_other_choice[i]].start_time<< "-" << flight_totalnumber[the_other_choice[i]].finish_time <<endl;
            cout<<"航行地点:"<<flight_totalnumber[the_other_choice[i]].starting_point << "-" << flight_totalnumber[the_other_choice[i]].finishing_point << endl;
            cout<<"飞机票价："<<flight_totalnumber[the_other_choice[i]].price << endl;
            cout<<"票价折扣："<<flight_totalnumber[the_other_choice[i]].discount << endl;
            cout<<"所属公司："<<flight_totalnumber[the_other_choice[i]].company << endl;
            cout<<"剩余票数："<<flight_totalnumber[the_other_choice[i]].seat_number - flight_totalnumber[the_other_choice[i]].book_number<<endl;
            cout<<"\n";
        }
        cout<<"输入想要选择的序号";
        cin>>ordinal;
        flight_totalnumber[the_other_choice[ordinal]].book_number++;
    }
    if(if_site==1){//有符合条件的航班
        cout<<"订票成功";
    }
}

#endif /* Airplane_System_hpp */

