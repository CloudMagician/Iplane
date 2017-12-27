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
#include <vector>
using namespace std;

//定义一个航班信息的类
class flight
{
public:
	string flight_number;   //航班号
	string starting_point;  //起始城市
	string finishing_point; //到达城市
	int start_time;         //起飞时间
	int finish_time;        //到达时间
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
    Airplane_System();                                  //构造函数
    ~Airplane_System();                                 //析构函数
	void dataloading();							        //航班信息录入
	void current_information_view();			        //航班信息浏览
	void check_information();					        //航班信息查询
	void ticket_booking();						        //预订机票
	void ticket_returning(string);                      //退票(航班号)
	void flight_list(int,string,string,int,int);        //相应航班排序
	void flight_recommended();					        //航班线路设计
	void output_route();						        //航班网络输出
	void best_route_recommended();			            //最优航班线路推荐
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
	index = result - point_link.begin();
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
    cout << temp.string flight_number << '\t' << temp.starting_point << '\t' << temp.finishing_point << '\t'
    << temp.start_time << '\t' << temp.finish_time << '\t' << temp.price << '\t' << temp.discount << '\t'
    << temp.company << '\t' << temp.seat_number << '\t' << temp.book_number << endl;
}

//int比较，判断第一个int是否小于第二个int
bool Airplane_System::int_compare(int temp_first, int temp_last){
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
        file >> flight_table.strat_time;
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
        file >> temp_flight.strat_time;
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
        temp_edge1->next_point = result - point_link.begin();
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
        number_of_city = point_link.size();
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
        case 1:cout << "退票成功!" << endl;break;
        case 2:cout << "退票失败!" << endl;break;
        default:
            break;
    }
}

//退票 by 陆子旭
void Airplane_System::ticket_returning(string flight_num){
    for (int i = 0; i <total; i++) {
        if (flight_totalnumber[i].flight_number == flight_num) {
            if (flight_totalnumber[i].book_number > 0) {
                flight_totalnumber[i].book_number --;
                print_lzx(1);
            }else{
                print_lzx(2);
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
void Airplane_System::flight_list(int sort_bool=1,int timef_bool=201708010000,int timel_bool=201708020000,
                                  string start_bool="长春",string arrive_bool="长春"){
    vector<flight> temp;    //临时中间量
    int sum(0);             //总数
    Qsort qsort;            //快速排序
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
            qsort.find(flight_totalnumber->price,sum,flight_totalnumber);
            qsort.sort();
            for (int i = 0; i <sum; i++) {
                print(flight_totalnumber[i]);
            }
        default:
            break;
    }
    
}
#endif /* Airplane_System_hpp */
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
	int have_site[20],hs=0;//存放符合要求信息的下标（可以动态申请吗？） ,hs用来指向次数组的位置 
	int if_site=0; //是否有符合条件的 
	int ordinal;
	string date,start,finish;
	string date1, date2;//表示日期 
	cout << "请输入航班日期，起始城市，终止城市：";
	cin >> date >> start >> finish;
	date1 = "2017" + date + "0000";//用来表示一整天 
	date2 = "2017" + date + "2359";
	for (int i = 0; i < total; i++){//用位置信息和起始城市进行匹配 
		if(date1<flight_totalnumber[i].start_time&&date2>flight_totalnumber[i].start_time&&flight_totalnumber[i].starting_point==start&&flight_totalnumber[i].finishing_point==finish){
			if(flight_totalnumber[i].seat_number>flight_totalnumber[i].book_number){//有空位 
				have_site[hs]=i;
				hs++;
				if_site=1;
			}
		}
		
	}
	if(if_site==1){//有符合条件的航班 
		cout<<"符合条件的航班信息为：\n"<<endl;
		for(int i=0;i<hs;i++){
			cout<<i<<". "<<endl;
			cout<<"航班号："<<flight_totalnumber[have_site[i]].flight_number<<" "<<endl;
			cout<<"起降时间:"<<flight_totalnumber[have_site[i]].start_time<< "-" << flight_totalnumber[have_site[i]].finish_time <<endl;
			cout<<"航行地点:"<<flight_totalnumber[have_site[i]].starting_point << "-" << flight_totalnumber[have_site[i]].finishing_point << endl;
			cout<<"飞机票价："<<flight_totalnumber[have_site[i]].price << endl;
			cout<<"票价折扣："<<flight_totalnumber[have_site[i]].discount << endl;
			cout<<"所属公司："<<flight_totalnumber[have_site[i]].company << endl;
			cout<<"剩余票数："<<flight_totalnumber[have_site[i]].seat_number - flight_totalnumber[have_site[i]].book_number<<endl;
			cout<<"\n";
		}
		cout<<"输入想要选择的序号";
		cin>>ordinal;
		flight_totalnumber[have_site[ordinal]].book_number++;
	}
	if(if_site==0){//没有符合条件的航班 
		
	}
}