# Iplane:飞机订票系统
## [实验目的]
综合运用线性表、图、队列和文件等数据结构知识，同时考虑使用有效的存储结构，掌握并提高分析、设计、实现及测试程序的综合能力。
## [实验内容及要求]
#### 设计一个飞机订票系统，完成对航空客运订票的业务管理。<br>该系统至少包括如下功能模块：航班信息浏览、查询航线、客票预订和办理退票等。
* 录入：可以录入航班情况（数据可以存储在一个数据文件中，数据结构、具体数据自定）;
* 航班信息浏览:预览已经建立的全部航线的相关信息；
* 查询：可以查询某个航线的情况（如输入航班号，可以查询起、降时间，起飞、抵达城市，航班票价，票价折扣，所属航空公司、确定航班是否满仓等）；
* 订票：（订票情况可以存在一个数据文件中，结构自己设定）可以订票，如果该航班已经无票，可以提供相关可选择航班；
* 退票： 可退票，退票后修改相关数据文件；
#### 进一步，该系统还可以提供如下高级应用：
* 排序：可以根据票价、时间等信息对相关航线（如相同起飞、抵达城市航线）进行排序；
* 合理设计线路：输入两个城市名称，可以根据条件（如出发、到达时间）设计这两座城市之间可能的线路，进而推荐合理线路；
* 输出：以城市作为顶点，航线作为边（若两个城市之间具有多条线路，则选取当前最低票价航线），选择合适形式输出航线网络；
* 推荐最优化线路：以机票价钱低作为最优量度标准，设计两座城市之间最优线路并输出之；
* 在实现上述功能应用后，可完善系统的其他功能。
## [测试数据]
可以参考实际航空公司信息或者自行编制虚拟数据作为测试数据，要求城市数目不小于30，航线数目不小于600。
