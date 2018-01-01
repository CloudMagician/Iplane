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
    string starting_point;  //起始城市
    string finishing_point; //到达城市
    string company;         //所属公司
    string flight_number;   //航班号
    long long start_time;   //起飞时间
    long long finish_time;  //到达时间
    int price;              //飞机票价
    double discount;        //票价折扣
    int seat_number;        //座位总数
    int book_number;        //已预定总数
};

//定义一个飞机订票系统的类
class Airplane_System
{
public:
    Airplane_System();                                          //构造函数
    ~Airplane_System();                                         //析构函数
    void dataloading(string);                                   //航班信息录入
    void current_information_view();                            //航班信息浏览
    void check_information();                                   //航班信息查询
    void ticket_booking();                                      //预订机票
    void ticket_returning(string);                              //退票(航班号)
    void flight_list(int,long long,long long,string,string);    //相应航班排序
    void flight_recommended(long long,long long,string,string); //航班线路设计
    void output_route();                                        //航班网络输出
    void best_route_recommended
    (int,long long,long long,string,string);    //最优航班线路推荐
private:
    //航班数组相关
    //表头
    struct {
        string flight_number;   //航班号
        string starting_point;  //起始城市
        string finishing_point; //到达城市
        string start_time;      //起飞时间
        string finish_time;     //到达时间
        string price;           //飞机票价
        string discount;        //票价折扣
        string company;         //所属公司
        string seat_number;     //座位总数
        string book_number;     //已预定总数
    } flight_table;
    int number_of_city;                 //开放航线的城市个数
    int total;                          //航班总数
    vector <flight> flight_totalnumber; //flight数组(暂时不得进行排序，删除，添加元素等操作)
    
    //邻接表相关
    //边链表
    struct edge
    {
        int next_point;     //终点城市
        int flight_node;    //航班节点信息(vector数组下标)
        edge* next;         //下一条边
    };
    //顶点数组
    struct point
    {
        string cityname;    //城市名称
        edge* address;      //边链表的头指针
    };
    vector <point> point_link;          //邻接表顶点数组
    
    //公用相关函数
    bool int_compare(int, int);         //int比较，判断第一个int是否小于第二个int
    bool string_compare(string, string);//string比较，比较两个string,是否相同
    void print_flight_data(flight);     //输出航班信息
    
    //航班数组（用于第七题和第九题）
    vector<queue<int>> flight_queue(long long,long long,string,string);
    
    //用于vector的相关函数
    //用于vector<flight>的起始时间排序函数
    static bool vector_start_time_compare(const flight &a, const flight &b){
        return a.start_time < b.start_time;
    }
    //用于vector<flight>的价格排序函数
    static bool vector_price_compare(const flight &a, const flight &b){
        return a.price < b.price;
    }
    //用于vector<point>的查找函数(自定义类的方式实现)
    class findx {
    private: string test;
    public:
        findx(const string str):test(str) {}
        bool operator()(point& dValue) {
            if(dValue.cityname == test) return true;
            else return false;
        }
    };
    
    //定义的相关输出函数 by 陆子旭
    void print_lzx(int);
};



//构造函数
Airplane_System::Airplane_System(){
}

//析构函数
Airplane_System::~Airplane_System(){
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

//输出航班信息
void Airplane_System::print_flight_data(flight temp){
    cout << temp.flight_number << '\t' << temp.starting_point << '\t' << temp.finishing_point <<'\t'<< temp.start_time << '\t' << temp.finish_time << '\t' << temp.price << '\t'<<temp.discount<< '\t'<< temp.company << '\t' << temp.seat_number << '\t' << temp.book_number << endl;
}

//航班数组（用于第七题和第九题 by 陆子旭
//采用广度优先搜索
//参数分别为：
//对于起飞时间起始时间限制（timef_bool）；
//对于起飞时间结束时间限制（timel_bool）；
//起始城市（start_bool）；
//到达城市（arrive_bool）；
vector<queue<int>> Airplane_System::flight_queue(long long timef_bool=201710310000,
                                                 long long timel_bool=201712310000,string start_bool="长春",string arrive_bool="长春"){
    vector<point>::iterator result; //vector迭代器
    vector<queue<int>> temp_f;      //航线数组
    vector<queue<int>> temp_l;      //航线最终数组
    queue<int> temp_q;              //临时队列
    queue<int> Q,Q_f;               //广度搜索队列
    edge *p;                        //临时边
    int j(0),k(0);                  //临时城市点
    bool visit[total];              //航班访问数组
    for (int i = 0; i<total; i++) {
        visit[i] = false;
    }
    //直达航线统计
    result = find_if(point_link.begin(), point_link.end(), findx(start_bool));
    p = result->address;
    while (p){
        if (flight_totalnumber[p->flight_node].start_time>timef_bool&&
            flight_totalnumber[p->flight_node].finish_time<timel_bool){
            temp_q.push(p->flight_node);
            if (flight_totalnumber[p->flight_node].finishing_point==arrive_bool) {
                temp_l.push_back(temp_q);
            }else{
                temp_f.push_back(temp_q);
            }
            temp_q = queue<int>();
            Q.push(p->next_point);
            Q_f.push(p->flight_node);
            visit[p->flight_node] = true;
        }
        p = p->next;
    }
    //非直达航线统计
    while (!Q.empty()){
        j=Q.front();
        Q.pop();
        k=Q_f.front();
        Q_f.pop();
        p = point_link[j].address;
        while (p){
            if (flight_totalnumber[p->flight_node].start_time > flight_totalnumber[k].finish_time&&
                flight_totalnumber[p->flight_node].finish_time < timel_bool&&
                !visit[p->flight_node]){
                for (int i = 0; i<int(temp_f.end() - temp_f.begin()); i++) {
                    if (flight_totalnumber[temp_f[i].back()].finishing_point == point_link[j].cityname&&
                        flight_totalnumber[temp_f[i].back()].finish_time <
                        flight_totalnumber[p->flight_node].start_time) {
                        temp_q = temp_f[i];
                        temp_q.push(p->flight_node);
                        if (flight_totalnumber[p->flight_node].finishing_point==arrive_bool){
                            temp_l.push_back(temp_q);
                        }else{
                            temp_f.push_back(temp_q);
                        }
                        temp_q = queue<int>();
                    }
                }
                Q.push(p->next_point);
                Q_f.push(p->flight_node);
                visit[p->flight_node] = true;
            }
            p = p->next;
        }
    }
    return temp_l;
}

//信息录入  从文件录入到程序
//输出vector数组，邻接表 by 管清泉 陆子旭
void Airplane_System::dataloading(string file_address) {
    flight temp_flight;             //临时航班类
    point temp_point;               //临时顶点节结点
    edge *temp_edge1,*temp_edge2;   //临时边结点
    vector<point>::iterator result; //vector迭代器 可以用auto！！！(这句话是某个对auto有执念的人加上的)
    ifstream file(file_address);
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
    }
    while (file.good()) {
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
        file.get(); if (file.peek()==EOF) break;//获取之后一个字符，避免最后一行读两遍
        //生成邻接表
        //判断终点城市结点
        result = find_if(point_link.begin(),point_link.end(),findx(temp_flight.finishing_point));
        if (result == point_link.end()) {
            temp_point.cityname = temp_flight.finishing_point;
            temp_point.address = NULL;
            point_link.push_back(temp_point);
            result = point_link.end() - 1;
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
            result = point_link.end() - 1;
        }
        //将边加入邻接表
        if (!point_link[int(result - point_link.begin())].address) {
            point_link[int(result - point_link.begin())].address = temp_edge1;
        }else{
            temp_edge2 = point_link[int(result - point_link.begin())].address;
            while (temp_edge2->next) {
                temp_edge2 = temp_edge2->next;
            }
            temp_edge2->next = temp_edge1;
        }
    }
    //城市数目
    number_of_city = int(point_link.size());
}

//陆子旭定义的相关输出函数 by 陆子旭
void Airplane_System::print_lzx(int temp_a){
    switch (temp_a) {
        case -1:cout << "成功!" << endl;break;
        case -2:cout << "失败!" << endl;break;
        case -3:cout << endl;break;
        default:cout << temp_a << endl;break;
    }
}

//退票 by 陆子旭
//暂时以航班号为检索标准
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
//升降序（sort_bool）： 1为时间从低到高，2为时间从高到低，3为价格从低到高，4为价格从高到低；
//对于起飞时间起始时间限制（timef_bool）；
//对于起飞时间结束时间限制（timel_bool）；
//起始城市（start_bool）；
//到达城市（arrive_bool）；
void Airplane_System::flight_list(int sort_bool=1,long long timef_bool=201710310000,
                                  long long timel_bool=201712310000,string start_bool="长春",string arrive_bool="长春"){
    vector<flight> temp;    //临时中间量
    int sum(0);             //总数
    //筛选
    for (int i = 0; i <total; i++) {
        if (flight_totalnumber[i].start_time > timef_bool&&
            flight_totalnumber[i].finish_time < timel_bool&&
            flight_totalnumber[i].starting_point == start_bool&&
            flight_totalnumber[i].finishing_point == arrive_bool
            ) {
            temp.push_back(flight_totalnumber[i]);
        }
    }
    sum = int(temp.size());
    //根据不同选择进行排列
    if (sum == 0) {
        print_lzx(-2);
        return;
    }
    switch (sort_bool) {
        case 1:
            sort(temp.begin(), temp.end(), vector_start_time_compare);
            for (int i = 0; i <sum; i++) {
                print_flight_data(temp[i]);
            }
            break;
        case 2:
            sort(temp.begin(), temp.end(), vector_start_time_compare);
            for (int i = sum-1; i >=0; i--) {
                print_flight_data(temp[i]);
            }
            break;
        case 3:
            sort(temp.begin(), temp.end(), vector_price_compare);
            for (int i = 0; i <sum; i++) {
                print_flight_data(temp[i]);
            }
            break;
        case 4:
            sort(temp.begin(), temp.end(), vector_price_compare);
            for (int i = sum-1; i >=0; i--) {
                print_flight_data(temp[i]);
            }
            break;
        default:
            print_lzx(-2);
            break;
    }
}

//航班线路设计 by 陆子旭
//参数分别为：
//对于起飞时间起始时间限制（timef_bool）；
//对于起飞时间结束时间限制（timel_bool）；
//起始城市（start_bool）；
//到达城市（arrive_bool）；
void Airplane_System::flight_recommended(long long timef_bool=201710310000,
                                         long long timel_bool=201712310000,string start_bool="长春",string arrive_bool="长春"){
    queue<int> temp_q;              //临时队列
    vector<queue<int>> temp_l;      //航线最终数组
    //调用函数
    temp_l = flight_queue(timef_bool,timel_bool,start_bool,arrive_bool);
    //输出
    if (temp_l.size()==0) {
        print_lzx(-2);
        return;
    }
    for (vector<queue<int>>::iterator i = temp_l.begin(); i!=temp_l.end(); i++) {
        temp_q = *i;
        while (!temp_q.empty()) {
            print_flight_data(flight_totalnumber[temp_q.front()]);
            temp_q.pop();
        }
        print_lzx(-3);
    }
}

//最优航班线路推荐 by 陆子旭
//采用广度优先搜索
//参数分别为：
//升降序（sort_bool）： 1取最短时间，2取最低价格；
//对于起飞时间起始时间限制（timef_bool）；
//对于起飞时间结束时间限制（timel_bool）；
//起始城市（start_bool）；
//到达城市（arrive_bool）；
void Airplane_System::best_route_recommended(int sort_bool=1,long long timef_bool=201710310000,
                                             long long timel_bool=201712310000,string start_bool="长春",string arrive_bool="长春"){
    vector<queue<int>> temp_l;      //航线最终数组
    queue<int> temp_q;              //临时队列
    //调用函数
    temp_l = flight_queue(timef_bool,timel_bool,start_bool,arrive_bool);
    //取最优
    if (temp_l.size()==0) {
        print_lzx(-2);
        return;
    }
    switch (sort_bool) {
        case 1:
            for (vector<queue<int>>::iterator i = temp_l.begin(); i!=temp_l.end()-1;) {
                if (flight_totalnumber[i->back()].finish_time-
                    flight_totalnumber[i->front()].start_time >
                    flight_totalnumber[(i+1)->back()].finish_time-
                    flight_totalnumber[(i+1)->front()].start_time) {
                    i = temp_l.erase(i);
                }else{
                    i = temp_l.erase(i+1);
                    i--;
                }
            }
            temp_q = temp_l[0];
            while (!temp_q.empty()) {
                print_flight_data(flight_totalnumber[temp_q.front()]);
                temp_q.pop();
            }
            break;
        case 2:{
            int t1(0);
            int t2(0);
            temp_q = temp_l[0];
            while (!temp_q.empty()) {
                t1 += flight_totalnumber[temp_q.front()].price;
                temp_q.pop();
            }
            for (vector<queue<int>>::iterator i = temp_l.begin(); i!=temp_l.end()-1;) {
                t2 = 0;
                temp_q = *(i+1);
                while (!temp_q.empty()) {
                    t2 += flight_totalnumber[temp_q.front()].price;
                    temp_q.pop();
                }
                if (t1 > t2) {
                    i = temp_l.erase(i);
                    t1 = t2;
                }else{
                    i = temp_l.erase(i+1);
                    i--;
                }
            }
            temp_q = temp_l[0];
            while (!temp_q.empty()) {
                print_flight_data(flight_totalnumber[temp_q.front()]);
                temp_q.pop();
            }
            break;
        }
        default:
            print_lzx(-2);
            break;
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

