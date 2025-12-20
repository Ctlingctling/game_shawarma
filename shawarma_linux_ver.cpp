/**
 * --------------------------------
 * 251240041 - 曹特领
 * Shawarma Legend (Terminal Version)
 * --------------------------------
 */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <limits> // 用于 numeric_limits

// --- Data Structures ---

struct shawarma_data {
    bool bread;
    bool meat;
    bool cucumber;
    bool sauce;
    bool fries;
    bool raw;
    bool potato;
    bool takeaway;
    bool soda;
};

struct customer_data {
    int id;
    int mood;
    struct shawarma_data order;
};

struct inventory {
    int bread_count;
    int raw_count;
    int cucumber_count;
    int sauce_count;
    int potato_count;
    int wrap_count;
    int meat_count;
    int fries_count;
    int soda_count;    
};

struct game_state {
    int money;
    int fame;
    int day;
    struct shawarma_data current_shawarma;
    struct inventory shop;
};

// --- Helper Functions (Linux Style: tiny & static inline) ---

// 辅助计分函数：减少重复代码
static inline int calculate_score(bool needed, bool provided)
{
    if (needed && provided)  return 5;   // 完美匹配
    if (needed && !provided) return -20; // 漏放
    if (!needed && provided) return -5;  // 多放
    return 0;                            // 均无
}

// --- Order Validation ---

int validate_order(struct shawarma_data order, struct shawarma_data current, int mood) 
{
    int answer = mood;

    // 1. 基础检查
    if (current.bread) answer += 2;
    else answer -= 50;

    // 2. 违禁品检查
    if (current.raw || current.potato) answer -= 50;

    // 3. 通用配料检查 (使用辅助函数)
    answer += calculate_score(order.meat, current.meat);
    answer += calculate_score(order.cucumber, current.cucumber);
    answer += calculate_score(order.sauce, current.sauce);
    answer += calculate_score(order.fries, current.fries);
    answer += calculate_score(order.soda, current.soda);
    
    // 4. 打包单独处理 (轻微不同的惩罚机制)
    if (order.takeaway && current.takeaway) answer += 5;
    else if (order.takeaway && !current.takeaway) answer -= 20;
    else if (!order.takeaway && current.takeaway) answer -= 2;

    return answer;
}

// --- Game Actions ---

void nju_easteregg()
{
    printf("-------------NJU------------\n");
    printf("[---]嚼得菜根，做得大事[---]\n");
    printf("----------------------------\n");
}

void reset_shawarma(struct game_state *state)
{
    // 使用 C++ 聚合初始化重置，比逐行赋值更高效
    state->current_shawarma = {false}; 
}

void cook_meat(struct game_state *state)
{
    if (state->shop.raw_count <= 0) return;
    state->shop.raw_count--;
    state->shop.meat_count++;
}

void cook_fries(struct game_state *state)
{
    if (state->shop.potato_count <= 0) return;
    state->shop.potato_count--;
    state->shop.fries_count++;
}

void add_bread(struct game_state *state)
{
    if (state->shop.bread_count <= 0) return;
    state->shop.bread_count--;
    state->current_shawarma.bread = true;
}

void add_meat(struct game_state *state)
{
    if (!state->current_shawarma.bread || state->shop.meat_count <= 0) return;
    state->shop.meat_count--;
    state->current_shawarma.meat = true;
}

void add_fries(struct game_state *state)
{
    if (!state->current_shawarma.bread || state->shop.fries_count <= 0) return;
    state->shop.fries_count--;
    state->current_shawarma.fries = true;
}

void add_cucumber(struct game_state *state)
{
    if (!state->current_shawarma.bread || state->shop.cucumber_count <= 0) return;
    state->shop.cucumber_count--;
    state->current_shawarma.cucumber = true;
}

void add_sauce(struct game_state *state)
{
    if (!state->current_shawarma.bread || state->shop.sauce_count <= 0) return;
    state->shop.sauce_count--;
    state->current_shawarma.sauce = true;
}

void add_soda(struct game_state *state)
{
    if (state->shop.soda_count <= 0) return;
    state->shop.soda_count--;
    state->current_shawarma.soda = true;
}

void wrap_shawarma(struct game_state *state)
{
    if (state->shop.wrap_count <= 0) return;
    state->shop.wrap_count--;
    state->current_shawarma.takeaway = true;
}

// --- Customer Logic ---

void init_random()
{
    std::srand(std::time(NULL));
}

void customer_generate(struct game_state *state, struct customer_data *customer)
{
    customer->id++;
    customer->mood = std::rand() % 11 - 5;
    // 重置订单
    customer->order = {false}; 
    
    customer->order.bread = true;
    customer->order.meat     = std::rand() % 2;
    customer->order.cucumber = std::rand() % 2;
    customer->order.sauce    = std::rand() % 2;
    customer->order.fries    = std::rand() % 2;
    customer->order.takeaway = std::rand() % 2;
    customer->order.soda     = std::rand() % 2;

    // 防止空订单
    if (!customer->order.meat && !customer->order.cucumber &&
        !customer->order.sauce && !customer->order.fries &&
        !customer->order.soda) {
            customer->order.meat  = true;
            customer->order.sauce = true;
    }
}

// --- Economy & Logic ---

bool update_day(struct game_state *state)
{
    state->day++;

    if (state->money <= 0 || state->fame <= 0) {
        printf("[x] Game Over.\n");
        return false;
    } 
    
    // 补货逻辑
    int refresh = 50;
    int cost = 500;

    if (state->money < 500) {
        // 资金不足模式
        refresh = state->money / 10;
        cost = refresh * 10;
        printf("[!] Low funds. Restocked %d sets.\n", refresh);
    } else {
        printf("[!] Rent paid & Restocked fully.\n");
    }

    state->shop.raw_count      += refresh;
    state->shop.cucumber_count += refresh;
    state->shop.sauce_count    += refresh;
    state->shop.potato_count   += refresh;
    state->shop.bread_count    += refresh;
    state->shop.wrap_count     += refresh;
    state->shop.soda_count     += refresh;
    
    state->money -= cost;

    // 零钱转换声誉
    if (state->money > 0 && state->money < 10) {
        printf("[!] Spare change $%d converted to Fame!\n", state->money);
        state->fame += state->money;
        state->money = 0;
    }

    return true;
}

void update_trade(struct game_state *state)
{
    int price = 0;
    struct shawarma_data *s = &state->current_shawarma;
    
    if (s->bread)    price += 15;
    if (s->meat)     price += 20;
    if (s->cucumber) price += 15;
    if (s->sauce)    price += 15;
    if (s->fries)    price += 20;
    if (s->soda)     price += 15;
    if (s->takeaway) price += 15;
    
    state->money += price;
}

void update_fame(struct game_state *state, struct customer_data *customer)
{
    int rating = validate_order(customer->order, state->current_shawarma, customer->mood);
    
    if (rating > 0) {
        state->fame += (10 + 2 * rating);
    } else {
        state->fame += (5 * rating); // rating本身是负的
    }

    if (state->fame < 0) state->fame = 0;
}

// --- UI ---

void ui_prototype(struct game_state *game, struct customer_data *customer)
{
    system("clear");
    printf("=============================================\n");
    printf("========= Welcome to Shawarma Game! =========\n");
    printf("=============================================\n");
    
    // 简洁化库存显示
    printf("[Inventory] Meat:%d/%d | Potato:%d/%d | Bread:%d | Soda:%d\n", 
           game->shop.meat_count, game->shop.raw_count, 
           game->shop.fries_count, game->shop.potato_count,
           game->shop.bread_count, game->shop.soda_count);
    
    printf("[Status]    Money:$%d | Fame:%d | Day:%d\n", 
           game->money, game->fame, game->day);
    
    printf("---------------------------------------------\n");
    
    // 使用三目运算符简化显示代码
    struct shawarma_data *s = &game->current_shawarma;
    printf("[Hand] ");
    if (!s->bread) printf("(Empty) ");
    else {
        printf("Bread ");
        if (s->meat)     printf("+Meat ");
        if (s->cucumber) printf("+Cucumber ");
        if (s->sauce)    printf("+Sauce ");
        if (s->fries)    printf("+Fries ");
        if (s->soda)     printf("+Soda ");
        if (s->takeaway) printf("[Packed] ");
    }
    printf("\n");

    struct shawarma_data *o = &customer->order;
    printf("[Order] ");
    printf("Bread ");
    if (o->meat)     printf("+Meat ");
    if (o->cucumber) printf("+Cucumber ");
    if (o->sauce)    printf("+Sauce ");
    if (o->fries)    printf("+Fries ");
    if (o->soda)     printf("+Soda ");
    if (o->takeaway) printf("[Takeaway] ");
    printf("(Mood: %d)\n", customer->mood);

    printf("---------------------------------------------\n");
    printf("[a]Bread [b]Meat [c]Cucumber [d]Sauce [e]Fries [f]Soda\n");
    printf("[g]Wrap  [h]Cook Meat [i]Fry Potato  [j]Serve  [q]Quit\n");
    printf("=============================================\n");
    printf("Command: ");
}

// --- Interaction ---

void handle_input(char input, struct game_state *state, struct customer_data *customer, bool *running, int *served_count)
{
    switch (input) {
        case 'a': add_bread(state); break;
        case 'b': add_meat(state); break;
        case 'c': add_cucumber(state); break;
        case 'd': add_sauce(state); break;
        case 'e': add_fries(state); break;
        case 'f': add_soda(state); break;
        case 'g': wrap_shawarma(state); break;
        case 'h': cook_meat(state); break;
        case 'i': cook_fries(state); break;
        case 'j': {
            int rating = validate_order(customer->order, state->current_shawarma, customer->mood);

            printf("\n---------------- Result ----------------\n");
            if (rating > 0) {
                update_fame(state, customer);
                update_trade(state);
                printf(">>> [O] Success! Customer happy.\n");
            } else {
                update_fame(state, customer);
                printf(">>> [X] Failed! Customer angry.\n");
            }

            if (state->fame <= 0 || state->money <= 0) {
                printf("[!] Game Over: Bankrupt or Ruined.\n");
                *running = false;
                return;
            }

            (*served_count)++;
            reset_shawarma(state);
            customer_generate(state, customer);

            printf("----------------------------------------\n");
            printf("Current Money: %d | Current Fame: %d\n", state->money, state->fame);
            
            if ((*served_count) > 0 && (*served_count) % 5 == 0) {
                printf("\n========= Day %d Ended =========\n", state->day);
                printf("Paying rent & restocking... Press Enter.");
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();

                if (!update_day(state)) {
                    *running = false;
                    return;
                }
            } else {
                printf("Press Enter to next customer...");
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
            }
            break;
        }
        case 'q':
            *running = false;
            printf("Goodbye!\n");
            break;
        case 'n':
            nju_easteregg();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            break;
        default:
            break;
    }
}

// --- Main ---

int main() 
{
    init_random();
    
    // 初始化结构体
    struct game_state game = {
        500, 500, 1, 
        {false}, // current_shawarma
        {50, 50, 50, 50, 50, 50, 0, 0, 50} // shop
    };

    struct customer_data current_customer = {0};
    customer_generate(&game, &current_customer);

    char input;
    bool running = true;
    int served_count = 0;

    while (running) {
        ui_prototype(&game, &current_customer);
        std::cin >> input;
        handle_input(input, &game, &current_customer, &running, &served_count);
    }

    printf("\n=============================================\n");
    printf("                   GAME OVER                 \n");
    printf(" [D]Final Day:   %d\n", game.day);
    printf(" [$]Final Money: %d\n", game.money);
    printf(" [!]Final Fame:  %d\n", game.fame);
    printf("=============================================\n");
    
    return 0;
}