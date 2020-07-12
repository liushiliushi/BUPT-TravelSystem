# BUPT-TravelSystem
北邮数据结构课设，旅行模拟系统
(程序使用说明详见[用户使用手册](https://github.com/liushiliushi/BUPT-TravelSystem/blob/master/%E7%94%A8%E6%88%B7%E4%BD%BF%E7%94%A8%E6%89%8B%E5%86%8C.pdf))
## 总体方案设计说明
### 软件开发环境
* **编程语言**：c++
* **版本库**：Qt：5.12.7
* **IDE**：visual studio2017
* **系统**：Windows10

### 总体结构
![](https://github.com/liushiliushi/BUPT-TravelSystem/blob/master/images/%E8%BD%AF%E4%BB%B6%E7%BB%93%E6%9E%84%E5%9B%BE.png)
### 模块清单（详见各模块设计说明）
|模块名称|模块标识符|模块作用|
|:--:|:--:|:--:|
|管理|manager|做系统的管理|
|城市|city|保存城市信息|
|主窗口|MainWindow|ui界面上的控件设计|
|地图|mapWidget|绘制旅行地图|
|时刻表|schedule|保存车次信息|
|策略|strategy|计算最优路线|
|旅客|Traveler|保存旅客相关信息|
|时刻表查询|Query|用于查询并输出时刻表信息|
|配置文件|config.h|用于配置包括界面颜色、文件地址等在内的信息|

### 图形界面
#### 主界面
利用Qt中的控件设计图形界面，图形界面设计如下
![](https://github.com/liushiliushi/BUPT-TravelSystem/blob/master/images/%E6%80%BB%E4%BD%93%E8%AE%BE%E8%AE%A1%E5%9B%BE%E5%BD%A2%E7%95%8C%E9%9D%A2.PNG)
左边是**mapWidget**用于绘制地图和旅客的出行路线。用不同颜色区分不同的旅客路线，以免混淆。用不同图标区分旅客乘坐的交通工具，并且把旅客的名字画在交通工具上方。

右边是一个**tabWidget**，有两栏，第一个用于**添加旅客**，第二个用于**查询、修改、删除**旅客信息。中间一栏用于显示旅客的路线。下方是用于操作旅行模拟功能的按钮，和显示时间的控件。
#### 时刻表查询界面
![](https://github.com/liushiliushi/BUPT-TravelSystem/blob/master/images/%E6%97%B6%E5%88%BB%E8%A1%A8%E6%9F%A5%E8%AF%A2.PNG)
