//
//  QSort.hpp
//  exercise6
//
//  Created by 陆子旭 on 2017/12/25.
//  Copyright © 2017年 陆子旭. All rights reserved.
//

#ifndef QSort_hpp
#define QSort_hpp

#include <iostream>
using namespace std;

template <class T> class QSort {
private:
    int sum;                    //数组总数
    int *R;                     //排序数组指针
    T* linklist;                //外部数组指针
    int partition(int,int);     //分划操作
public:
    QSort();                    //构造函数
    ~QSort();                   //析构函数
    int frequency;              //比较次数
    void create(int);           //生成随机数列
    void find(int*,int,T*);     //取外部数组
    void sort(int,int);         //快速排序
    int* print();               //输出函数
};

//构造函数
QSort::QSort():sum(0),frequency(0){}

//析构函数
QSort::~QSort(){}

//生成随机数列
void QSort::create(int s){
    sum = s;
    frequency = 0;
    R = new int[sum+1];
    for (int i = 0; i<sum ; i++) {
        R[i] = rand()%999991+10;
    }
    R[sum] = 1000001;
}

//取外部数组
template <class T> void QSort::find(int *k,int s,T* t){
    linklist = t;
    sum = s;
    frequency = 0;
    R = new int[sum+1];
    for (int i = 0; i<sum ; i++) {
        R[i] = k[i];
    }
    R[sum] = 1000001;
}

//分划操作
template <class T> int QSort::partition(int m, int n){
    int i,j,k,temp;
    T tempp;
    i = m;
    j = n+1;
    k = R[m];
    while (i<j) {
        i++;
        while (R[i]<=k) i++;
        j--;
        while (R[j]> k) j--;
        if (i<j) {
            temp = R[i];
            R[i] = R[j];
            R[j] = temp;
            tempp = linklist[i];
            linklist[i] = linklist[j];
            linklist[j] = tempp;
        }
    }
    frequency += n-m+2;
    temp = R[m];
    R[m] = R[j];
    R[j] = temp;
    tempp = linklist[m];
    linklist[m] = linklist[j];
    linklist[j] = tempp;
    return j;
}

//快速排序
void QSort::sort(int m=0, int n=sum){
    int j;
    frequency++;
    if (m<n) {
        j = partition(m,n);
        sort(m,j-1);
        sort(j+1,n);
    }
}

//输出函数
int* QSort::print(){
    return R;
}

#endif /* QSort_hpp */
