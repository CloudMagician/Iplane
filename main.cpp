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

int main(int argc, const char * argv[]) {
    Airplane_System test("/Users/luzixu/Documents/my project/Iplane/Iplane/File",
                         "/Users/luzixu/Documents/my project/Iplane/Iplane/UserInformation",
                         "/Users/luzixu/Documents/my project/Iplane/Iplane/Out",
                         "/Users/luzixu/Documents/my project/Iplane/Iplane/Bool");
    test.dataloading();
    test.flight_recommended(201711310000,201712150000,"长春","北京");
    return 0;
}
