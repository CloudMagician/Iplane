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

//定义一个飞机订票系统的类
class Airplane_System
{
public:
	//基本函数
	Airplane_System();                                          //构造函数
	Airplane_System(string, string, string, string);               //构造函数（包含文件名）
	~Airplane_System();                                         //析构函数

																//用户操作
	void Register(string, string, bool);                          //注册
	void SignIn(string, string);                                 //登录

																 //题目要求
	void dataloading();                                         //航班信息录入
	void current_information_view();                            //航班信息浏览
	void check_information(string);                             //航班信息查询
	void ticket_booking(string, string, long long);               //订票
	void ticket_returning(string, string, long long);             //退票
	void flight_list(int, long long, long long, string, string);    //相应航班排序
	void flight_recommended(long long, long long, string, string); //航班线路设计
	void output_route();                                        //航班网络输出
	void best_route_recommended
	(int, long long, long long, string, string);                    //最优航班线路推荐
private:
	//文件名
	string FlightFile;      //航班信息文件
	string UserFile;        //用户名信息文件
	string OutFile;         //输出文件
	string BoolFile;        //判断文件

							//航班数组相关
							//定义一个航班信息的类
	struct flight {
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
	void DataWrite();                   //航班信息输出

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
		string cityname;        //城市名称
		edge* address;          //边链表的头指针
	};
	vector <point> point_link;  //邻接表顶点数组

								//用户相关
								//一个用户
	struct User {
		string name;
		string password;
		bool IsAdministrator;
		vector<flight> information;
	}ThisUser;                          //当前用户
	vector<User> UsersInformation;      //记录所有用户的数组
	void ReadUsers();                   //读入用户信息
	void WriteUsers();                  //输出用户信息

										//公用相关函数
	void print_flight_data();                           //输出航班信息
	void print_flight_data(flight);                     //输出航班信息
	void print_flight_data(flight, string);              //输出航班信息
	void print_lzx(int);                                //输出判断函数

														//输出航班数组（用于第七题和第九题）
	vector<queue<int>> flight_queue(long long, long long, string, string);

	//用于vector的相关函数
	//用于vector<flight>的起始时间排序函数
	static bool vector_start_time_compare(const flight &a, const flight &b) {
		return a.start_time < b.start_time;
	}
	//用于vector<flight>的价格排序函数
	static bool vector_price_compare(const flight &a, const flight &b) {
		return a.price < b.price;
	}
	//用于vector<point>的查找函数(自定义类的方式实现)
	class findx {
	private: string test;
	public:
		findx(const string str) :test(str) {}
		bool operator()(point& dValue) {
			if (dValue.cityname == test) return true;
			else return false;
		}
	};
	//用于vector<User>的查找函数(自定义类的方式实现)
	class findu {
	private: string test;
	public:
		findu(const string str) :test(str) {}
		bool operator()(User& dValue) {
			if (dValue.name == test) return true;
			else return false;
		}
	};
	//用于vector<flight>的查找函数(自定义类的方式实现)
	class findi {
	private: string test1; long long test2;
	public:
		findi(const string s, const long long t) :test1(s), test2(t) {}
		bool operator()(flight& dValue) {
			if (dValue.flight_number == test1&&
				dValue.start_time == test2) return true;
			else return false;
		}
	};
};


//构造函数
Airplane_System::Airplane_System() {
}

//构造函数（包含文件名） by 陆子旭
//参数分别为：
//航班文件名（file1）；
//用户文件名（file2）；
//输出文件名（file3）；
//判断文件名（file4）；
Airplane_System::Airplane_System(string file1, string file2, string file3, string file4) :
	FlightFile(file1), UserFile(file2), OutFile(file3), BoolFile(file4) {
}

//析构函数
Airplane_System::~Airplane_System() {
}

//航班信息输出 by 陆子旭
void Airplane_System::DataWrite() {
	ofstream file(FlightFile, ios::trunc);
	//输出表头
	file << flight_table.starting_point << '\t' << flight_table.finishing_point << '\t' << flight_table.company << '\t' << flight_table.flight_number << '\t' << flight_table.start_time << '\t' << flight_table.finish_time << '\t' << flight_table.price << '\t' << flight_table.discount << '\t' << flight_table.seat_number << '\t' << flight_table.book_number << endl;
	//输出数据
	for (int i = 0; i < flight_totalnumber.size(); i++) {
		print_flight_data(flight_totalnumber[i], FlightFile);
	}
}

//读入用户信息 by 杨溢 陆子旭
void Airplane_System::ReadUsers() {
	ifstream file(UserFile);    //文件
	User temp_user;             //临时用户
	flight temp_flight;         //临时航班
	int ticket_num;             //已定航班数
								//读用户信息
	while (file.good()) {
		file >> temp_user.name;
		file >> temp_user.password;
		file >> temp_user.IsAdministrator;
		file >> ticket_num;
		for (int i = 0; i<ticket_num; i++) {
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
			temp_user.information.push_back(temp_flight);
		}
		UsersInformation.push_back(temp_user);
		file.get(); if (file.peek() == EOF) break;
	}
}

//输出用户信息 by 陆子旭
void Airplane_System::WriteUsers() {
	ofstream file(UserFile, ios::trunc);   //文件
										   //输出用户信息
	for (int i = 0; i < UsersInformation.size(); i++) {
		file << UsersInformation[i].name << '\t';
		file << UsersInformation[i].password << '\t';
		file << UsersInformation[i].IsAdministrator << '\t';
		file << UsersInformation[i].information.size() << '\n';
		for (int j = 0; j < UsersInformation[i].information.size(); j++)
		{
			print_flight_data(UsersInformation[i].information[j], UserFile);
		}
		file << endl;
	}
}

//注册 by 陆子旭
//参数分别为：
//用户名（nam）；
//密码（pas）；
//是否为管理员（bo）；
void Airplane_System::Register(string nam, string pas, bool bo)
{
	User temp;
	temp.name = nam;
	temp.password = pas;
	temp.IsAdministrator = bo;
	UsersInformation.push_back(temp);
}

//登录 by 陆子旭
//参数分别为：
//用户名（nam）；
//密码（pas）；
void Airplane_System::SignIn(string nam, string pas) {
	ReadUsers();
	vector<User>::iterator result = find_if(UsersInformation.begin(), UsersInformation.end(), findu(nam));
	if (result == UsersInformation.end()) {
		print_lzx(-2);
		return;
	}
	else
	{
		if (result->password == pas) {
			ThisUser = *result;
		}
		else {
			print_lzx(-2);
			return;
		}
	}
	print_lzx(-1);
}

//输出航班信息 by 陆子旭
//参数分别为：
//航班类（temp）；
//输出文件名（file_name）（默认Outfile）；
void Airplane_System::print_flight_data() {
	ofstream file(OutFile, ios::app);
	file << endl;
	file.close();
}
void Airplane_System::print_flight_data(flight temp) {
	ofstream file(OutFile, ios::app);
	file << temp.starting_point << '\t' << temp.finishing_point
		<< '\t' <<
		temp.company << '\t' << temp.flight_number << '\t'
		<< temp.start_time << '\t' << temp.finish_time
		<< '\t' << temp.price << '\t' << temp.discount << '\t' << temp.seat_number << '\t' << temp.book_number << endl;
	file.close();
}
void Airplane_System::print_flight_data(flight temp, string file_name) {
	ofstream file(file_name, ios::app);
	file << temp.starting_point << '\t' << temp.finishing_point
		<< '\t' <<
		temp.company << '\t' << temp.flight_number << '\t'
		<< temp.start_time << '\t' << temp.finish_time
		<< '\t' << temp.price << '\t' << temp.discount << '\t' << temp.seat_number << '\t' << temp.book_number << endl;
	file.close();
}

//输出判断函数 by 陆子旭
void Airplane_System::print_lzx(int temp_a) {
	ofstream file(BoolFile, ios::trunc);
	switch (temp_a) {
	case -1:file << 1; break;
	case -2:file << 0; break;
	}
}

//航班数组（用于第七题和第九题 by 陆子旭
//采用广度优先搜索
//参数分别为：
//对于起飞时间起始时间限制（timef_bool）；
//对于起飞时间结束时间限制（timel_bool）；
//起始城市（start_bool）；
//到达城市（arrive_bool）；
vector<queue<int>> Airplane_System::flight_queue(long long timef_bool = 201710310000,
	long long timel_bool = 201712310000, string start_bool = "长春", string arrive_bool = "长春") {
	vector<point>::iterator result; //vector迭代器
	vector<queue<int>> temp_f;      //航线数组
	vector<queue<int>> temp_l;      //航线最终数组
	queue<int> temp_q;              //临时队列
	queue<int> Q, Q_f;               //广度搜索队列
	edge *p;                        //临时边
	int j(0), k(0);                  //临时城市点
	bool visit[5000];              //航班访问数组
	for (int i = 0; i<total; i++) {
		visit[i] = false;
	}
	//直达航线统计
	result = find_if(point_link.begin(), point_link.end(), findx(start_bool));
	p = result->address;
	while (p) {
		if (flight_totalnumber[p->flight_node].start_time>timef_bool&&
			flight_totalnumber[p->flight_node].finish_time<timel_bool) {
			temp_q.push(p->flight_node);
			if (flight_totalnumber[p->flight_node].finishing_point == arrive_bool) {
				temp_l.push_back(temp_q);
			}
			else {
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
	while (!Q.empty()) {
		j = Q.front();
		Q.pop();
		k = Q_f.front();
		Q_f.pop();
		p = point_link[j].address;
		while (p) {
			if (flight_totalnumber[p->flight_node].start_time > flight_totalnumber[k].finish_time&&
				flight_totalnumber[p->flight_node].finish_time < timel_bool &&
				!visit[p->flight_node]) {
				for (int i = 0; i<int(temp_f.end() - temp_f.begin()); i++) {
					if (flight_totalnumber[temp_f[i].back()].finishing_point == point_link[j].cityname&&
						flight_totalnumber[temp_f[i].back()].finish_time <
						flight_totalnumber[p->flight_node].start_time) {
						temp_q = temp_f[i];
						temp_q.push(p->flight_node);
						if (flight_totalnumber[p->flight_node].finishing_point == arrive_bool) {
							temp_l.push_back(temp_q);
						}
						else {
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
void Airplane_System::dataloading() {
	flight temp_flight;             //临时航班类
	point temp_point;               //临时顶点节结点
	edge *temp_edge1, *temp_edge2;   //临时边结点
	vector<point>::iterator result; //vector迭代器 可以用auto！！！(这句话是某个对auto有执念的人加上的)
	ifstream file(FlightFile);
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
		file.get(); if (file.peek() == EOF) break;//获取之后一个字符，避免最后一行读两遍
												  //生成邻接表
												  //判断终点城市结点
		result = find_if(point_link.begin(), point_link.end(), findx(temp_flight.finishing_point));
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
		result = find_if(point_link.begin(), point_link.end(), findx(temp_flight.starting_point));
		if (result == point_link.end()) {
			temp_point.cityname = temp_flight.starting_point;
			temp_point.address = NULL;
			point_link.push_back(temp_point);
			result = point_link.end() - 1;
		}
		//将边加入邻接表
		if (!point_link[int(result - point_link.begin())].address) {
			point_link[int(result - point_link.begin())].address = temp_edge1;
		}
		else {
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

//航班信息浏览
void Airplane_System::current_information_view() {

}

//航班信息查询 by 陆子旭
//参数分别为：
//航班号（flight_num）；
void Airplane_System::check_information(string flight_num) {
	for (int i = 0; i <total; i++) {
		if (flight_totalnumber[i].flight_number == flight_num) {
			print_flight_data(flight_totalnumber[i]);
		}
	}
}

//订票 by 杨溢 陆子旭
//参数分别为：
//用户名（user_name）；
//航班号（flight_num）；
//起飞时间（time）；
void Airplane_System::ticket_booking(string user_name, string flight_num, long long time) {
	ReadUsers();
	//判断并修改数据
	for (int i = 0; i <total; i++) {
		if (flight_totalnumber[i].flight_number == flight_num&&
			flight_totalnumber[i].start_time == time) {
			if (flight_totalnumber[i].book_number < flight_totalnumber[i].seat_number) {
				//改变航班大数组
				flight_totalnumber[i].book_number++;
				//改变用户数据
				vector<User>::iterator result = find_if(UsersInformation.begin(), UsersInformation.end(), findu(user_name));
				if (result == UsersInformation.end()) {
					print_lzx(-2);
					return;
				}
				else {
					result->information.push_back(flight_totalnumber[i]);
				}
			}
			else {
				print_lzx(-2);
				return;
			}
			break;
		}
	}
	DataWrite();
	WriteUsers();
	print_lzx(-1);
}

//退票 by 陆子旭
//参数分别为：
//用户名（user_name）；
//航班号（flight_num）；
//起飞时间（time）；
void Airplane_System::ticket_returning(string user_name, string flight_num, long long time) {
	ReadUsers();
	//判断并修改数据
	for (int i = 0; i <total; i++) {
		if (flight_totalnumber[i].flight_number == flight_num&&
			flight_totalnumber[i].start_time == time) {
			if (flight_totalnumber[i].book_number > 0) {
				//改变航班大数组
				flight_totalnumber[i].book_number--;
				//改变用户数据
				vector<User>::iterator result = find_if(UsersInformation.begin(), UsersInformation.end(), findu(user_name));
				if (result == UsersInformation.end()) {
					print_lzx(-2);
					return;
				}
				else {
					vector<flight>::iterator j =
						find_if(result->information.begin(), result->information.end(), findi(flight_num, time));
					j = result->information.erase(j);
				}
			}
			else {
				print_lzx(-2);
				return;
			}
			break;
		}
	}
	DataWrite();
	WriteUsers();
	print_lzx(-1);
}

//相应航班排序 by 陆子旭
//升降序（sort_bool）： 1为时间从低到高，2为时间从高到低，3为价格从低到高，4为价格从高到低；
//对于起飞时间起始时间限制（timef_bool）；
//对于起飞时间结束时间限制（timel_bool）；
//起始城市（start_bool）；
//到达城市（arrive_bool）；
void Airplane_System::flight_list(int sort_bool = 1, long long timef_bool = 201710310000,
	long long timel_bool = 201712310000, string start_bool = "长春", string arrive_bool = "长春") {
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
		for (int i = sum - 1; i >= 0; i--) {
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
		for (int i = sum - 1; i >= 0; i--) {
			print_flight_data(temp[i]);
		}
		break;
	default:
		print_lzx(-2);
		return;
	}
	print_lzx(-1);
}

//航班线路设计 by 陆子旭
//参数分别为：
//对于起飞时间起始时间限制（timef_bool）；
//对于起飞时间结束时间限制（timel_bool）；
//起始城市（start_bool）；
//到达城市（arrive_bool）；
void Airplane_System::flight_recommended(long long timef_bool = 201710310000, long long timel_bool = 201712310000,
	string start_bool = "长春", string arrive_bool = "长春") {
	queue<int> temp_q;              //临时队列
	vector<queue<int>> temp_l;      //航线最终数组
									//调用函数
	temp_l = flight_queue(timef_bool, timel_bool, start_bool, arrive_bool);
	//输出
	if (temp_l.size() == 0) {
		print_lzx(-2);
		return;
	}
	for (vector<queue<int>>::iterator i = temp_l.begin(); i != temp_l.end(); i++) {
		temp_q = *i;
		while (!temp_q.empty()) {
			print_flight_data(flight_totalnumber[temp_q.front()]);
			temp_q.pop();
		}
		print_flight_data();
	}
	print_lzx(-1);
}

//航班网络输出
void Airplane_System::output_route() {

}

//最优航班线路推荐 by 陆子旭
//参数分别为：
//升降序（sort_bool）： 1取最短时间，2取最低价格；
//对于起飞时间起始时间限制（timef_bool）；
//对于起飞时间结束时间限制（timel_bool）；
//起始城市（start_bool）；
//到达城市（arrive_bool）；
void Airplane_System::best_route_recommended(int sort_bool = 1, long long timef_bool = 201710310000,
	long long timel_bool = 201712310000, string start_bool = "长春",
	string arrive_bool = "长春") {
	vector<queue<int>> temp_l;      //航线最终数组
	queue<int> temp_q;              //临时队列
									//调用函数
	temp_l = flight_queue(timef_bool, timel_bool, start_bool, arrive_bool);
	//取最优
	if (temp_l.size() == 0) {
		print_lzx(-2);
		return;
	}
	switch (sort_bool) {
	case 1:
		for (vector<queue<int>>::iterator i = temp_l.begin(); i != temp_l.end() - 1;) {
			if (flight_totalnumber[i->back()].finish_time -
				flight_totalnumber[i->front()].start_time >
				flight_totalnumber[(i + 1)->back()].finish_time -
				flight_totalnumber[(i + 1)->front()].start_time) {
				i = temp_l.erase(i);
			}
			else {
				i = temp_l.erase(i + 1);
				i--;
			}
		}
		temp_q = temp_l[0];
		while (!temp_q.empty()) {
			print_flight_data(flight_totalnumber[temp_q.front()]);
			temp_q.pop();
		}
		break;
	case 2: {
		int t1(0);
		int t2(0);
		temp_q = temp_l[0];
		while (!temp_q.empty()) {
			t1 += flight_totalnumber[temp_q.front()].price;
			temp_q.pop();
		}
		for (vector<queue<int>>::iterator i = temp_l.begin(); i != temp_l.end() - 1;) {
			t2 = 0;
			temp_q = *(i + 1);
			while (!temp_q.empty()) {
				t2 += flight_totalnumber[temp_q.front()].price;
				temp_q.pop();
			}
			if (t1 > t2) {
				i = temp_l.erase(i);
				t1 = t2;
			}
			else {
				i = temp_l.erase(i + 1);
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
		return;
	}
	print_lzx(-1);
}

int main()
{
	Airplane_System air("C:/Users/97263/Desktop/code/jiemian/file.txt", "C:/Users/97263/Desktop/code/jiemian/information.txt",
		"C:/Users/97263/Desktop/code/jiemian/output.txt", "C:/Users/97263/Desktop/code/jiemian/panduan.txt");
	air.dataloading();
	string name;
	string flight1;
	string time;
	long long time2;
	ifstream file_in1;
	file_in1.open("C:/Users/97263/Desktop/code/jiemian/bookname.txt");
	getline(file_in1, name);
	ifstream file_in2;
	file_in2.open("C:/Users/97263/Desktop/code/jiemian/booknumber.txt");
	getline(file_in2, flight1);
	ifstream file_in3;
	file_in3.open("C:/Users/97263/Desktop/code/jiemian/booktime.txt");
	getline(file_in3, time);
	time2 = stoll(time);
	air.ticket_booking(name, flight1, time2);
	return 0;
}