#pragma once
// AirplaceSystem.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

class flight                        //定义一个航班信息的类
{
public:
	string flight_number;        //航班号
	string starting_point;   //起始城市
	string finishing_point;   //到达城市
	int strat_hour;              //起飞时间（小时）
	int start_minute;          //起飞时间（分钟）
	int finish_hour;            //到达时间（小时）
	int finish_minute;         //到达时间（分钟）
	int price;                      //飞机票价
	int discount;               //票价折扣
	string company;           //所属公司
	int isfull;                       //是否满仓（0、1表示是否满仓)
};

class Airplane_System										  //定义一个飞机订票系统的类
{
public:
	int total;															//航班总数
	string number1[300];										//过渡string数组，无重要作用，可忽略
	void dataloading();										  //航班信息录入
	void current_information_view();					  //航班信息浏览
	void check_information();							      //航班信息查询
	void ticket_booking();									  //预订机票
	void ticket_returning();									  //退票
	void flight_list();											  //相应航班排序
	void flight_recommended();						      //航班线路设计
	void output_route();									      //航班网络输出
	void best_route_recommended();			      //最优航班线路推荐
private:
	//	flight flight_totalnumber[300];
	//	vector<flight> flight_totalnumber[1];
	flight* flight_totalnumber;                         //动态flight类数组的数组名（指针）
};

//思想：把各个航班的具体信息（如航班号、起飞时间地点等等）分别用数组进行保存，方便队友在调用的时候方便，之后进行初始化，new total（total具体含义在下文有
//）个对象，然后再对对象里面的数据成员进行赋值
void Airplane_System::dataloading()
{
	ifstream file;
	file.open("C:/Users/97263/Desktop/Airplace_System/file.txt");
	if (file.is_open() == false)
	{
		cerr << "error";
		exit(1);
	}
	string number;
	//	int total;                                                                           //total为所有航班的总是
	getline(file, number);
	total = stoi(number);                                                       //取出一共有几个航班
																				//	string number1[300];                                                 //配合string数组，过渡作用，无需细究。flight_totalnumber
	flight_totalnumber = new flight[total];
	string startingpoint[300];                                          //航班的起始地点
	string finishingpoint[300];										 //航班的结束地点
	int startingtime[300];												 //航班的起飞时间
	int finishingtime[300];												 //航班的落地时间
	string fcompany[300];											      //航班所属航空公司
	int fprice[300];															   //航班票价
	int fdiscount[300];													  //航班折扣
	int ftotalnumber[300];											     //航班的最大承载量
	int fisfull[300];														     //航班是否满仓
	string flightnumber[300];                                          //航班的航班号
	for (int i = 0; i <total; i++)
	{
		getline(file, number1[i]);
	}
	//	cout << number << endl;
	for (int i = 0; i < total; i++)
	{
		istringstream istr;
		//	string haoma;
		istr.str(number1[i]);
		istr >> flightnumber[i];
		istr >> startingpoint[i];
		istr >> finishingpoint[i];
		istr >> startingtime[i];
		istr >> finishingtime[i];
		istr >> fcompany[i];
		istr >> fprice[i];
		istr >> fdiscount[i];
		istr >> ftotalnumber[i];
		istr >> fisfull[i];
		//   	cout << number1[i] << endl;
	}
	for (int j = 0; j < total; j++)                                                           //给类的对象赋值
	{
		flight_totalnumber[j].company = fcompany[j];
		flight_totalnumber[j].discount = fdiscount[j];
		flight_totalnumber[j].finishing_point = finishingpoint[j];
		flight_totalnumber[j].finish_hour = finishingtime[j] / 100;
		flight_totalnumber[j].finish_minute = finishingtime[j] % 100;
		flight_totalnumber[j].flight_number = flightnumber[j];
		flight_totalnumber[j].isfull = fisfull[j];
		flight_totalnumber[j].price = fprice[j];
		flight_totalnumber[j].starting_point = startingpoint[j];
		flight_totalnumber[j].start_minute = startingtime[j] % 100;
		flight_totalnumber[j].strat_hour = startingtime[j] / 100;
	}
	file.close();
}

void Airplane_System::current_information_view()
{
	for (int i = 0; i < total; i++)
		cout << number1[i] << endl;
}
