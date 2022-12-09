# ATXPowerController

利用ITX机箱为TinyMonstor小主机（P310S型）扩展了显卡做成了一体机，为了能让显卡的外置ATX电源能够与小主机同步开关机，所以开发了一个基于ArduinoNano的小电源控制器。

![asm0001.jpg](https://github.com/6bigfire/ATXPowerController/blob/main/Images/asm0001.jpg)

## 控制器接口说明

看图说话，正常使用时，只需要用到JP2和JP3两个插座。

![pcb_3d.png](https://github.com/6bigfire/ATXPowerController/blob/main/Images/pcb_3d.png)

### JP2 接口说明

JP2连接小主机的开机信号线及主机上电指示。

| 描述  | Pin No. | Pin No. | 描述          |
|:---:|:-------:|:-------:|:-----------:|
|     |         |         |             |
| GND | 1       | 2       | HOSTCONTROL |
| GND | 3       | 4       | HOSTPOWER   |

Pin2 连接小主机的电源控制信号，低电平表示主机电源按钮按下，高电平表示电源按钮放开。

Pin3 连接小主机内的+5V电源，主机上电后为高电平，主机待机时为低电平。

### JP3 接口说明

JP3连接机箱前面板的电源按钮和LED指示灯。

| 描述    | Pin No. | Pin No. | 描述           |
|:-----:|:-------:|:-------:|:------------:|
|       |         |         |              |
| +3.3V | 1       | 2       | LED1         |
| GND   | 3       | 4       | LED0         |
| GND   | 5       | 6       | POWER_BUTTON |

Pin5、Pin6 连接机箱面板的电源按钮，按钮开关本身是无源的，无方向性。

Pin2、Pin4 用来控制机箱前面板LED指示灯，低电平表示灯亮。

## 控制器工作原理

### 输入信号与输出控制之间的逻辑关系

- ATXCONTROL输出状态与HOSTPOWER保持一致，小主机上电时ATXCONTROL输出低电平打开ATX电源，小主机关机时ATXCONTROL输出高电平关闭ATX供电。
- HOSTCONTROL输出状态与POWERBUTTON保持一致，机箱面板电源按钮按下时HOSTCONTROL输出低电平，机箱面板电源按钮释放时HOSTCONTRL输出高电平。
- LED1输出状态与ATXPOWER保持一致，ATX电源打开时LED1输出低电平，ATX电源关断时LED1输出高电平。
- LED0输出状态与HOSTPOWER保持一致，主机开机后LED0输出低电平，主机关机后LED0输出高电平。

| STATUS    | STATUS   | STATUS      | LED      | LED      | ACTION         | ACTION        |
| --------- | -------- | ----------- | -------- | -------- | -------------- | ------------- |
|           |          |             |          |          |                |               |
| HostPower | ATXPower | PowerButton | pinLED0  | pinLED1  | pinHostControl | pinATXControl |
| OPEN      | OPEN     | —           | POWERON  | POWERON  | PowerButton    | POWERON       |
| OPEN      | CLOSE    | —           | POWERON  | POWEROFF | PowerButton    | POWERON       |
| CLOSE     | OPEN     | —           | POWEROFF | POWERON  | PowerButton    | POWEROFF      |
| CLOSE     | CLOSE    | —           | POWEROFF | POWEROFF | PowerButton    | POWEROFF      |

### 关于显卡外置电源上电跟随主机开关机时，上电顺序的可行性

一般从经验和电气原理上来讲，将外部设备连接到主机的时候都需要先给外部设备接通电源，然后再将信号线与主机连接，这样保证主机与外部设备连接时状态的可靠性。但在目前的设计中选择了将显卡外置电源ATX电源供电与主机供电伴随，那就意味着显卡外置供电上电时间要晚于主机上电时间，虽然在上电顺序上存在着与经验原理不一致的情况，但实际测试效果和使用效果却非常稳定，分析后发现，通过PCIEx16连接的显卡本身已经获得了主板的供电，在小主机上电待机状态下时已经进入了正常的工作状态，显卡的外置供电是属于备用补能供电，上电顺序并不影响主机对显卡的正常检测和配置，这与完全依赖独立供电的热插拔外置设备是有本质的区别的，本次用的控制逻辑精实践检验和理论分析后证明是合理可行的。

## 小主机改造

### 引出HOSTCONTROL

Pin1 连接主板上电源按钮的外壳GND。

Pin2连接在电源按钮旁的贴片三极管的集电极，该脚接地时代表主机电源按钮被按下。

![HOSTCONTROL.jpg](https://github.com/6bigfire/ATXPowerController/blob/main/Images/HOSTCONTROL.jpg)

### 引出HOSTPOWER

Pin4 HOSTPOWER 改造如下图所示，连接在了主板声卡芯片的供电电感上，当主机上电时为+5V高电平，主机关机时为低电平。

Pin2 接旁边的GND焊点。

![HOSTPOWER.jpg](https://github.com/6bigfire/ATXPowerController/blob/main/Images/HOSTPOWER.jpg)

## 一体机成品图

![](https://github.com/6bigfire/ATXPowerController/blob/main/Images/allin1l.jpg)

![](https://github.com/6bigfire/ATXPowerController/blob/main/Images/allin1r.jpg)

## 把TinyMostor装进ITX机箱中

![](https://github.com/6bigfire/ATXPowerController/blob/main/Images/allin1i.jpg)

## 控制器成品图

![](https://github.com/6bigfire/ATXPowerController/blob/main/Images/controller.jpg)

![](https://github.com/6bigfire/ATXPowerController/blob/main/Images/using.jpg)
