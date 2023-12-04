# ATowerDefenceDemo

一个用UE4C++做的类似于保卫萝卜的简单塔防游戏。<br>
场景大小是12*10固定的，但是可以自由指定草地道路范围，每一块地形有三种状态：草地、道路、河流。只有草地可以摆放炮塔，只有道路可以行走。根据道路的摆放利用了Dijkistra算法会自动计算路径。
<br>  
![road](https://github.com/fallwindy/ATowerDefenceDemo/blob/main/image/road.png)
<br>  
如果设计的路径不可达，或者生成点不在路径上，会提示需要重写设计地图路径。  

炮塔其实只有一种，但是有三种属性，四种级别。

- 普通炮塔只有简单的攻击效果
- 火属性炮塔能够增强伤害效果
- 冰属性攻击力不高，但是有减速变慢的效果

  ![attack](https://github.com/fallwindy/ATowerDefenceDemo/blob/main/image/attack.png)

  干掉敌人可以得到金币，金币数量足够可以对炮塔进行升级
    ![upgrade](https://github.com/fallwindy/ATowerDefenceDemo/blob/main/image/upgrade.png)
  
