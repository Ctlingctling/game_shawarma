# game_shawarma
# 🌯 Shawarma Legend (Console Edition)

> **Developer**: Ctling  
> **Environment**: C++  
> **Platform**: Windows (Partially compatible with Linux/Mac logic)

## 📖 Project Overview

This program is a **C++ console replica** of the simulation game "Shawarma Legend".  
Operating within a command-line interface, it implements **real-time time progression**, a **simplified dynamic economy**, **randomized customer attributes**, and a **shop upgrade system**.

---

## 🏗️ Core Architecture: C-Style Structs + Pointers

Although the program primarily uses C-style syntax, the architectural design effectively implements **Object-Oriented (OO)** and **Data-Driven** design patterns.

### 1. Structs as Objects

To avoid using scattered global variables, I encapsulated the game state into two main structures:

- **struct game_state**: Acts as the GameManager class. It encapsulates money, fame, current workstation state (current_shawarma), and the inventory object (inventory).
    
- **struct customer_data**: Acts as the Customer class. It encapsulates attributes such as requirements, mood, and arrival time.
    

### 2. Pointers as this

All logic functions manipulate data by passing **struct pointers**.  
For example:

code C++

```
void add_meat(struct game_state* state);
```

Logically, this is equivalent to a member function in a C++ class:

code C++

```
// Logically equivalent to
class GameState {
    void add_meat() { this->... }
};
```

This approach separates **data from logic**, making the code easier to maintain and debug (e.g., simply printing variables within the struct reveals the entire game state). It is a humble imitation of the Object-Oriented implementation style found in the Linux kernel.

---

## ⚙️ Key Gameplay Mechanisms

### 1. 🔄 "Snowball" Mechanic: Reputation System

The game simulates a **Dynamic Difficulty Balancing** mechanism.

- **Positive Feedback**: Higher fame increases the customer's base patience (max_patience), increasing the player's margin for error.
    
- **Negative Feedback**: Lower fame makes customers impatient, leading to potential operation errors and a "Death Spiral".
    
- **Game Over**: Failed orders deduct fame. If fame <= 0, the game ends immediately.
    
- **Benefit**: This lowers error tolerance and enhances replayability.
    

### 2. 💰 Economic Cycle (Income & Expenses)

The game features a relatively complete closed-loop economy:

- **Income**: Pricing is based on ingredient complexity. Owning the "Gold Plate" item provides a 25% revenue premium.
    
- **Expenses**:
    
    - **Rent**: Fixed daily deduction.
        
    - **Smart Restock**: Implemented via the smart_restock function. The system prioritizes restocking low-inventory items based on current funds, rather than performing a simple full restock.
        

### 3. ⚡ Non-blocking Real-time I/O

To achieve **"real-time countdown updates"** while simultaneously **"responding to player input"**, the program utilizes:

- _kbhit() from <conio.h> to detect keyboard state.
    
- _getch() to capture input without pausing the program.
    
- time(NULL) timestamps to calculate delta time.  
    This establishes a basic **Game Loop**: Input -> Update -> Render, replacing the traditional turn-based console wait.
    

---

## 🎮 Gameplay Features

### 🛠️ Strict Production Workflow

- **Independent Containers**: Fries consume "Fries Boxes" and Soda consumes "Paper Cups," decoupled from the wrap production.
    
- **Strict Order**: Bread must be placed first before adding ingredients (except for independent snacks).
    
- **Inventory Cap**: Warehouse capacity is limited to 50 to prevent infinite hoarding.
    

### 🆙 Shop & Upgrades

Access "Bryant's Shop" at the end of each day:

- **Gold Plate ($1000)**: Increases revenue per order.
    
- **Auto Cutter ($1500)**: Automatically cuts meat when cooked meat runs out but raw meat is available.
    
- **Auto Fries ($2000)**: A hidden upgrade that automatically fries potatoes.
    

### 🥚 Easter Eggs

- Input n in the game interface: Triggers the exclusive NJU (Nanjing University) easter egg.
    
- Input h in the shop interface: Buy the hidden Auto Fries machine.
    
- Shop Dialogue: A tribute to the classic "Mamba Out".
    

---

## 🚀 Compile & Run

### Compilation

code Bash

```
g++ main.cpp -o shawarma.exe
```

### Controls

- a-f: Add ingredients/snacks
    
- g: Wrap/Pack
    
- h/i: Cut meat / Fry potatoes
    
- j: **Serve Customer** (Critical action)
    
- q: Quit
    

---

**Thank you for playing! Chew the roots, achieve exllence.**

# 🌯 沙威玛传奇控制台版

> **开发者**: Ctling
> **开发环境**: C++ 
> **运行平台**: Windows (部分代码符合 Linux/Mac 逻辑)

## 📖 项目简介
我的程序是对《沙威玛传奇》经营模拟游戏的**C++ 控制台复刻版**。
在命令行界面下，实现了 **实时时间流逝** 、 **简单动态经济** 、 **顾客随机数值** 以及 **一次店铺升级**。

---

## 🏗️ 主要结构：C 语言风格的 结构体嵌套+结构体指针+函数

这个程序虽然主要使用 C 风格的语法，但在结构上大体实现了 **面向对象** 和 **数据驱动** 的思想。

### 1. 结构体<=>对象 
在不使用使用零散的全局变量的前提下，我将游戏状态封装为主要的两个结构体：
*   **`struct game_state`**：相当于 `GameManager` 类。它封装了金钱、声誉、当前制作台状态 (`current_shawarma`) 以及库存对象 (`inventory`)。
*   **`struct customer_data`**：相当于 `Customer` 类。封装了顾客的需求、心情、到达时间等属性。

### 2. 用指针代替 `this` 
所有的逻辑函数都通过传递 **结构体指针** 来操作数据。
例如：
```cpp
void add_meat(struct game_state* state);
```
这种写法在逻辑上等同于 C++ 类中的成员函数：
```cpp
// 逻辑等价于
class GameState {
    void add_meat() { this->... }
};
```
我将 **数据与逻辑分离** ，使代码更易于维护，例如在Debug时只需打印出结构体中的变量就可以了解游戏的状态，找到反常的数据，在内存中也更清晰，拙劣地模仿了 Linux 内核式的面向对象实现。

---

## ⚙️ 主要玩法机制

### 1. 🔄 初级“滚雪球”机制：声誉系统 
游戏模拟了**动态难度平衡** 机制。
*   **正反馈**：`fame` 越高，顾客的基础耐心值 (`max_patience`) 越高，玩家容错率提升。
*   **负反馈**：`fame` 越低，顾客越急躁，容易导致操作失误，形成“死亡螺旋”。
*   **结算影响**：订单失败不仅扣除声誉，一旦 `fame <= 0`，游戏直接失败（Game Over）。
*   **优点**：降低容错率，提高可玩性。

### 2. 💰 货币的开销收入
游戏初步具有较为完整的货币闭环：
*   **收入：根据配料复杂度定价。拥有“金盘子”道具可获得 25% 溢价。
*   **支出：
    *   **房租**：每日固定扣除。
	*   **智能补货**：通过 `smart_restock` 函数自动补充货物。系统会根据当前资金，优先补齐短                       缺物资，而不是简单的全量补货。

### 3. ⚡ 非阻塞实时输入 (计时器和输入输出刷新)
为了实现 **“倒计时实时跳动”** 的同时还能 **“响应玩家按键”**，我的程序使用了以下方法。
*   使用 `<conio.h>` 中的 `_kbhit()` 检测键盘状态。
*   使用 `_getch()` 抓取按键而不暂停程序。
*   结合 `time(NULL)` 时间戳计算 `delta time`。
这样就有了一个基础的 **游戏循环** ：`Input -> Update -> Render`，而不是控制台回合制等待。

---

## 🎮 玩法特性

### 🛠️ 符合要求的制作流程
*   **独立容器管理**：薯条需要消耗薯条盒，可乐需要消耗纸杯，与卷饼制作解耦。
*   **严格顺序**：必须先放置面饼才能添加配料（薯条/可乐除外）。
*   **库存上限**：仓库容量限制为 50，防止无限囤积。

### 🆙 商店与升级 
每日结束后进入 "Bryant's Shop"：
*   **Gold Plate ($1000)**：提升单笔订单收入。
*   **Auto Cutter ($1500)**：当熟肉耗尽且有生肉时，自动切肉。
*   **Auto Fries ($2000)**：隐藏升级项，自动炸薯条。

### 🥚 彩蛋
*   交互页面中输入 `n`：触发 NJU 专属彩蛋。
*   商店页面中输入`h`：可以买下炸薯条机器
*   商店对话：致敬经典梗 (Mamba Out)。

---

## 🚀 编译与运行

### 编译
```bash
g++ main.cpp -o shawarma.exe
```

### 操作指南
*   `a-f`: 添加配料/小吃
*   `g`: 打包
*   `h/i`: 切肉/炸薯条
*   `j`: **提交订单** (最关键的操作)
*   `q`: 退出

---

**感谢体验！嚼得菜根，做得大事。**
