// AirplaceSystem.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
using namespace std;

class flight                        //定义一个航班信息的类
{
public:
	int flight_number;        //航班号
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
	void dataloading();										  //航班信息录入
	void current_information_view();					  //航班信息浏览
	void check_information();							      //航班信息查询
	void ticket_booking();									  //预订机票
	void ticket_returning();									  //退票
	void flight_list();											  //相应航班排序
	void flight_recommended();						      //航班线路设计
	void output_route();									      //航班网络输出
	void best_route_recommended();			      //最优航班线路推荐
};

int main()
{
    return 0;
}

