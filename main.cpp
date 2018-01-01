//
//  main.cpp
//  Iplane
//
//  Created by 陆子旭 管清泉 杨溢 on 2017/12/22.
//  Copyright © 2017年 陆子旭 管清泉 杨溢. All rights reserved.
//

#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include "Airplane_System.hpp"

using namespace std;
int main(int argc, const char * argv[]) {
    Airplane_System test;
    test.dataloading("/Users/luzixu/Documents/my project/Iplane/Iplane/File");
    //    test.flight_list(4,201710310000,201712310000,"长春","北京");
    test.best_route_recommended(1,201711150000,201711220000,"长春","北京");
    return 0;
}
