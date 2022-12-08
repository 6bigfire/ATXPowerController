# ATXPowerController

 利用ITX机箱，为P310S型小主机扩展了显卡，做成了一体机，为了能让ATX电源能够与小主机同步开关机，所以基于ArduinoNano设计了一个小电源控制器。

![asm0001.jpg](https://github.com/6bigfire/ATXPowerController/blob/main/Images/asm0001.jpg)

## 控制器接口说明

看图说话，正常使用时，只需要用到JP2和JP3两个插座。

![pcb_3d.png](https://github.com/6bigfire/ATXPowerController/blob/main/Images/pcb_3d.png)

### JP2 接口说明

JP2连接小主机的开机信号线及主机上电指示。

| 描述  | Pin No. | Pin No. | 描述          |
| GND | 1       | 2       | HOSTCONTROL |
| GND | 3       | 4       | HOSTPOWER   |

Pin2 连接小主机的电源控制信号，低电平表示主机电源按钮按下，高电平表示电源按钮放开。

Pin3 连接小主机内的+5V电源，主机上电后为高电平，主机待机时为低电平。

### JP3 接口说明

JP3连接机箱前面板的电源按钮和LED指示灯

| 描述    | Pin No. | Pin No. | 描述           |
| +3.3V | 1       | 2       | LED1         |
| GND   | 3       | 4       | LED0         |
| GND   | 5       | 6       | POWER_BUTTON |

Pin5、Pin6 连接机箱面板的电源按钮，按钮开关本身是无源的，无方向性。

Pin2、Pin4 用来控制机箱前面板LED指示灯，低电平表示灯亮。

## 控制器工作原理

|           |          |             |          |          |                |               |
| --------- | -------- | ----------- | -------- | -------- | -------------- | ------------- |
| STATUS    | LED      | ACTION      |          |          |                |               |
| HostPower | ATXPower | PowerButton | pinLED0  | pinLED1  | pinHostControl | pinATXControl |
| OPEN      | OPEN     | —           | POWERON  | POWERON  | PowerButton    | POWERON       |
| OPEN      | CLOSE    | —           | POWERON  | POWEROFF | PowerButton    | POWERON       |
| CLOSE     | OPEN     | —           | POWEROFF | POWERON  | PowerButton    | POWEROFF      |
| CLOSE     | CLOSE    | —           | POWEROFF | POWEROFF | PowerButton    | POWEROFF      |

## 小主机改造

### 引出HOSTCONTROL

Pin1 连接主板上电源按钮的外壳GND。

Pin2连接在电源按钮旁的贴片三极管的集电极，该脚接地时代表主机电源按钮被按下。

![HOSTCONTROL.jpg](https://github.com/6bigfire/ATXPowerController/blob/main/Images/HOSTCONTROL.jpg)

### 引出HOSTPOWER

Pin4 HOSTPOWER 改造如下图所示，连接在了主板声卡芯片的供电电感上，当主机上电时为+5V高电平，主机关机时为低电平。

Pin2 接旁边的GND焊点。

![HOSTPOWER.jpg](https://github.com/6bigfire/ATXPowerController/blob/main/Images/HOSTPOWER.jpg)
