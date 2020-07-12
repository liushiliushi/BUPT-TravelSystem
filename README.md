# BUPT-TravelSystem
北邮数据结构课设，旅行模拟系统
(程序使用说明详见[用户使用手册]())
## 总体方案设计说明
### 软件开发环境
* **编程语言**：c++
* **版本库**：Qt：5.12.7
* **IDE**：visual studio2017
* **系统**：Windows10

### 总体结构
![](软件结构图.png)
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
![](总体设计图形界面.png)
左边是**mapWidget**用于绘制地图和旅客的出行路线。用不同颜色区分不同的旅客路线，以免混淆。用不同图标区分旅客乘坐的交通工具，并且把旅客的名字画在交通工具上方。

右边是一个**tabWidget**，有两栏，第一个用于**添加旅客**，第二个用于**查询、修改、删除**旅客信息。中间一栏用于显示旅客的路线。下方是用于操作旅行模拟功能的按钮，和显示时间的控件。
#### 时刻表查询界面
![](时刻表查询.png)
