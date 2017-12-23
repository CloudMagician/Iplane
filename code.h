#pragma once
// AirplaceSystem.cpp: �������̨Ӧ�ó������ڵ㡣
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

class flight                        //����һ��������Ϣ����
{
public:
	string flight_number;        //�����
	string starting_point;   //��ʼ����
	string finishing_point;   //�������
	int strat_hour;              //���ʱ�䣨Сʱ��
	int start_minute;          //���ʱ�䣨���ӣ�
	int finish_hour;            //����ʱ�䣨Сʱ��
	int finish_minute;         //����ʱ�䣨���ӣ�
	int price;                      //�ɻ�Ʊ��
	int discount;               //Ʊ���ۿ�
	string company;           //������˾
	int isfull;                       //�Ƿ����֣�0��1��ʾ�Ƿ�����)
};

class Airplane_System										  //����һ���ɻ���Ʊϵͳ����
{
public:
	int total;															//��������
	string number1[300];										//����string���飬����Ҫ���ã��ɺ���
	void dataloading();										  //������Ϣ¼��
	void current_information_view();					  //������Ϣ���
	void check_information();							      //������Ϣ��ѯ
	void ticket_booking();									  //Ԥ����Ʊ
	void ticket_returning();									  //��Ʊ
	void flight_list();											  //��Ӧ��������
	void flight_recommended();						      //������·���
	void output_route();									      //�����������
	void best_route_recommended();			      //���ź�����·�Ƽ�
private:
	//	flight flight_totalnumber[300];
	//	vector<flight> flight_totalnumber[1];
	flight* flight_totalnumber;                         //��̬flight���������������ָ�룩
};

//˼�룺�Ѹ�������ľ�����Ϣ���纽��š����ʱ��ص�ȵȣ��ֱ���������б��棬��������ڵ��õ�ʱ�򷽱㣬֮����г�ʼ����new total��total���庬����������
//��������Ȼ���ٶԶ�����������ݳ�Ա���и�ֵ
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
	//	int total;                                                                           //totalΪ���к��������
	getline(file, number);
	total = stoi(number);                                                       //ȡ��һ���м�������
																				//	string number1[300];                                                 //���string���飬�������ã�����ϸ����flight_totalnumber
	flight_totalnumber = new flight[total];
	string startingpoint[300];                                          //�������ʼ�ص�
	string finishingpoint[300];										 //����Ľ����ص�
	int startingtime[300];												 //��������ʱ��
	int finishingtime[300];												 //��������ʱ��
	string fcompany[300];											      //�����������չ�˾
	int fprice[300];															   //����Ʊ��
	int fdiscount[300];													  //�����ۿ�
	int ftotalnumber[300];											     //�������������
	int fisfull[300];														     //�����Ƿ�����
	string flightnumber[300];                                          //����ĺ����
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
	for (int j = 0; j < total; j++)                                                           //����Ķ���ֵ
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
