
/**
 * --------------------------------
 * 251240041
 * --------------------------------
 */

/**
 * --------------------------------
 * [-] Mark
 * include libraries and headers.
 * --------------------------------
 */

#include<iostream>
#include<cstdio>
#include<ctime>
#include<conio.h>
#include<windows.h>

/**
 * --------------------------------
 * [-] Mark
 * global variables & constants.
 * --------------------------------
 */

#define MAX_STORAGE 50

/**
 * --------------------------------
 * [-] Mark
 * data structures
 * --------------------------------
 */

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

    time_t arrival_time;
    int max_patience;

    struct shawarma_data order;
};

struct inventory {
    int bread_count;
    int raw_count;
    int cucumber_count;
    int sauce_count;
    int potato_count;

    int wrap_count;
    int soda_count;
    int fries_box_count;

    int meat_count;
    int fries_count;
};

struct game_state {
    int money = 500;
    int fame  = 500;
    int day   = 1;

    bool has_gold_plate  = false;
    bool has_auto_cutter = false;
    bool has_auto_fries  = false;

    struct shawarma_data current_shawarma = {
        false, // bread
        false, // meat
        false, // cucumber
        false, // sauce
        false, // fries
        false, // raw
        false, // potato
        false, // takeaway
        false  // soda
    };

    struct inventory shop = {
        50, // bread_count
        50, // raw_count
        50, // cucumber_count
        50, // sauce_count
        50, // potato_count

        50, // wrap_count
        50, // soda_count
        50, // fries_box_count

        0,  // meat_count
        0,  // fries_count
    };
};

/**
 * --------------------------------
 * [-] Mark
 * function declarations
 * --------------------------------
 */

int  validate_order(struct shawarma_data order, struct shawarma_data current_shawarma, int mood);

void nju_easteregg();

void reset_shawarma(struct game_state *state);
void cook_meat(struct game_state *state);
void cook_fries(struct game_state *state);
void add_bread(struct game_state *state);
void add_meat(struct game_state *state);
void add_fries(struct game_state *state);
void add_cucumber(struct game_state *state);
void add_sauce(struct game_state *state);
void add_soda(struct game_state *state);
void wrap_shawarma(struct game_state *state);
void auto_cutter(struct game_state *state);
void auto_fries(struct game_state *state);

void init_random();
void customer_generate(struct game_state *state, struct customer_data *customer);
bool check_patience(struct customer_data *customer, struct game_state *state);

int  smart_restock(int *current, int *money, int *price);
bool update_day(struct game_state *state);
void update_trade(struct game_state *state);
void update_fame(struct game_state *state, struct customer_data *customer);
void game_refresh(struct game_state *state, struct customer_data *customer);

void draw_patience_bar(int current, int max);
void start_game();
void ui_prototype(struct game_state *game, struct customer_data *customer);
void shop_upgrade(struct game_state *game);
void ui_end_counting(struct game_state *game);

void handle_input(char input, struct game_state *state, struct customer_data *customer, bool *running, int *served_count);


/**
 * --------------------------------
 * [-] Mark
 * mainfunction
 * --------------------------------
 */

int main()
{
    init_random();
    start_game();
    printf("Goodbye!\n");
    return 0;
}

/**
 * --------------------------------
 * [-] Mark
 * functions below are related to order validation.
 * --------------------------------
 */

int validate_order(struct shawarma_data order, struct shawarma_data current_shawarma, int mood)
{
    int answer = mood;

    if (order.meat && current_shawarma.meat) {
        answer += 5;
    } else if (order.meat && !current_shawarma.meat) {
        answer -= 20;
    } else if (!order.meat && current_shawarma.meat) {
        answer -= 5;
    }

    if (order.cucumber && current_shawarma.cucumber) {
        answer += 5;
    } else if (order.cucumber && !current_shawarma.cucumber) {
        answer -= 20;
    }else if (!order.cucumber && current_shawarma.cucumber) {
        answer -= 5;
    }

    if (order.sauce && current_shawarma.sauce) {
        answer += 5;
    } else if (order.sauce && !current_shawarma.sauce) {
        answer -= 20;
    } else if (!order.sauce && current_shawarma.sauce) {
        answer -= 5;
    }

    if (order.fries && current_shawarma.fries) {
        answer += 5;
    } else if (order.fries && !current_shawarma.fries) {
        answer -= 20;
    }else if (!order.fries && current_shawarma.fries) {
        answer -= 5;
    }

    if (order.soda && current_shawarma.soda) {
        answer += 5;
    } else if (order.soda && !current_shawarma.soda) {
        answer -= 20;
    } else if (!order.soda && current_shawarma.soda) {
        answer -= 5;
    }

    if (order.takeaway && current_shawarma.takeaway) {
        answer += 5;
    } else if (order.takeaway && !current_shawarma.takeaway) {
        answer -= 20;
    } else if (!order.takeaway && current_shawarma.takeaway) {
        answer -= 2;
    }

    if (current_shawarma.bread) {
        answer += 2;
    } else {
        answer -= 50;
    }

    if (current_shawarma.raw) {
        answer -= 50;
    }
    if (current_shawarma.potato) {
        answer -= 50;
    }

    return answer;
}

/**
 * --------------------------------
 * [-] Mark
 * below functions are related to making shawarma.
 * --------------------------------
 */

void nju_easteregg()
{
    printf("-------------NJU------------\n");
    printf("[---]嚼得菜根，做得大事[---]\n");
    printf("----------------------------\n");
}

void reset_shawarma(struct game_state *state)
{
    state->current_shawarma.bread    = false;
    state->current_shawarma.meat     = false;
    state->current_shawarma.cucumber = false;
    state->current_shawarma.sauce    = false;
    state->current_shawarma.fries    = false;
    state->current_shawarma.raw      = false;
    state->current_shawarma.potato   = false;
    state->current_shawarma.takeaway = false;
    state->current_shawarma.soda     = false;
}

void cook_meat(struct game_state *state)
{
    if (state->shop.raw_count <= 0)
        return;
    state->shop.raw_count --;
    state->shop.meat_count ++;
}

void cook_fries(struct game_state *state)
{
    if (state->shop.potato_count <= 0)
        return;
    state->shop.potato_count --;
    state->shop.fries_count ++;
}

void add_bread(struct game_state *state)
{
    if (state->shop.bread_count <= 0)
        return;
    state->shop.bread_count --;
    state->current_shawarma.bread = true;
}

void add_meat(struct game_state *state)
{
    if (state->current_shawarma.bread == false)
        return;
    if (state->shop.meat_count <= 0)
        return;
    state->shop.meat_count --;
    state->current_shawarma.meat = true;
}

void add_fries(struct game_state *state)
{
    if (state->shop.fries_box_count <= 0)
        return;
    if (state->shop.fries_count <= 0)
        return;
    state->shop.fries_box_count --;
    state->shop.fries_count --;
    state->current_shawarma.fries = true;
}

void add_cucumber(struct game_state *state)
{
    if (state->current_shawarma.bread == false)
        return;
    if (state->shop.cucumber_count <= 0)
        return;
    state->shop.cucumber_count --;
    state->current_shawarma.cucumber = true;
}

void add_sauce(struct game_state *state)
{
    if (state->current_shawarma.bread == false)
        return;
    if (state->shop.sauce_count <= 0)
        return;
    state->shop.sauce_count --;
    state->current_shawarma.sauce = true;
}

void add_soda(struct game_state *state)
{
    if (state->shop.soda_count <= 0)
        return;
    state->shop.soda_count --;
    state->current_shawarma.soda = true;
}

void wrap_shawarma(struct game_state *state)
{
    if (state->shop.wrap_count <= 0)
        return;
    state->shop.wrap_count --;
    state->current_shawarma.takeaway = true;
}

void auto_cutter(struct game_state *state)
{
    if (state->has_auto_cutter && state->shop.meat_count == 0 && state->shop.raw_count > 0) {
        cook_meat(state);
    }
}

void auto_fries(struct game_state *state)
{
    if (state->has_auto_cutter && state->shop.fries_count == 0 && state->shop.potato_count > 0) {
        cook_fries(state);
    }
}

/**
 * --------------------------------
 * [-] Mark
 * below functions are related to customer generating.
 * --------------------------------
 */

void init_random()
{
    std::srand(std::time(nullptr));
}

void customer_generate(struct game_state *state, struct customer_data *customer)
{
    customer -> id ++;
    customer -> mood = std::rand() % 11 - 5;

    customer -> arrival_time = std::time(nullptr);

    int fame_bonus = (state -> fame - 500) / 20;

    customer -> max_patience = 30 + (customer -> mood * 2) + fame_bonus;

    if (customer -> max_patience < 10)
        customer -> max_patience = 10;

    customer -> order.bread    = true;
    customer -> order.meat     = std::rand() % 2;
    customer -> order.cucumber = std::rand() % 2;
    customer -> order.sauce    = std::rand() % 2;
    customer -> order.fries    = std::rand() % 2;
    customer -> order.raw      = false;
    customer -> order.potato   = false;
    customer -> order.takeaway = std::rand() % 2;
    customer -> order.soda     = std::rand() % 2;

    if (! customer -> order.meat  && ! customer -> order.cucumber &&
        ! customer -> order.sauce && ! customer -> order.fries &&
        ! customer -> order.soda){
            customer -> order.meat  = true;
            customer -> order.sauce = true;
    }

    return;
}

/**
 * --------------------------------
 * [-] Mark
 * below functions are related to npc activitiess.
 * --------------------------------
 */

bool check_patience(struct customer_data *customer, struct game_state *state)
{
    time_t current_time = std::time(nullptr);
    int time_delta = (int)(current_time - customer -> arrival_time);
    int patience_left = customer -> max_patience - time_delta;

    if (patience_left <= 0) {
        state -> fame -= 20;

        system("cls");
        printf("\n[!!!]Customer %d has left due to impatience! Fame -20.\n", customer -> id);
        
        Sleep(1000);
        return true;
    }
    return false;
}

/**
 * --------------------------------
 * [-] Mark
 * below functions are related to economic system & fame calculations.
 * add: new functions for refreshing game running.
 * --------------------------------
 */

int  smart_restock(int *current, int *money, int price)
{
    int needed = MAX_STORAGE - (*current);

    if (needed <= 0)
        return 0;

    int affordable = (*money) / (price);

    int actual_buy = (affordable < needed) ? affordable : needed;

    (*current) += actual_buy;
    (*money)   -= actual_buy * price;

    return actual_buy;
}

bool update_day(struct game_state *state)
{
    state->day++;

    if (state->money <= 0 && state->shop.raw_count <= 0 && state->shop.meat_count <= 0) {
        return false;
    }

    state->money -= 15;

    if (state->money < 0) {
        return false;
    }

    int bought = 0;

    bought += smart_restock(&state->shop.raw_count,    &state->money, 30);
    bought += smart_restock(&state->shop.potato_count, &state->money, 30);
    bought += smart_restock(&state->shop.bread_count,  &state->money, 20);

    bought += smart_restock(&state->shop.cucumber_count, &state->money, 15);
    bought += smart_restock(&state->shop.sauce_count,    &state->money, 15);

    bought += smart_restock(&state->shop.wrap_count,      &state->money, 15);
    bought += smart_restock(&state->shop.soda_count,      &state->money, 20);
    bought += smart_restock(&state->shop.fries_box_count, &state->money, 15);

    return true;
}

void update_trade(struct game_state *state)
{
    int price = 0;
    if (state -> current_shawarma.bread)
        price += 15;
    if (state -> current_shawarma.meat)
        price += 20;
    if (state -> current_shawarma.cucumber)
        price += 15;
    if (state -> current_shawarma.sauce)
        price += 15;
    if (state -> current_shawarma.fries)
        price += 20;
    if (state -> current_shawarma.soda)
        price += 15;
    if (state -> current_shawarma.takeaway)
        price += 15;

    if (state -> has_gold_plate)
        price = (int)(price * 2);

    state -> money += price;
    return;
}

void update_fame(struct game_state *state, struct customer_data *customer)
{
    int rating = validate_order(customer -> order, state -> current_shawarma, customer -> mood);

    if (rating > 0) {
        state -> fame += (10 + 2 * rating);
    } else {
        state -> fame += (5 * rating);
    }

    if (state -> fame < 0)
        state -> fame = 0;
    return;
}

void game_refresh(struct game_state *state, struct customer_data *customer)
{
    bool running = true;
    int served_count = 0;
    time_t last_check = 0;

    system("cls");
    ui_prototype(state, customer);
    draw_patience_bar(customer -> max_patience, customer -> max_patience);

    while (running) {

        auto_cutter(state);
        auto_fries(state);

        bool left = check_patience(customer, state);

        if (left) {
            if (state -> fame <= 0 || state -> money <= 0) {
                system("cls");
                ui_end_counting(state);
                running = false;
                break;
            }

            reset_shawarma(state);
            customer_generate(state, customer);
            last_check = 0;
        }

        time_t current_time = std::time(nullptr);

        if (_kbhit() || (current_time - last_check >= 1)) {
            int time_passed   = (int)(current_time - customer -> arrival_time);
            int patience_left = customer -> max_patience - time_passed;

            ui_prototype(state, customer);
            draw_patience_bar(patience_left, customer -> max_patience);
            last_check = current_time;
        }

        if (_kbhit()) {
            char input = _getch();
            handle_input(input, state, customer, &running, &served_count);
            last_check = 0;
        }
        Sleep(50);
    }
}

/**
 * --------------------------------
 * [-] Mark
 * below functions are related to UI surface.
 * add: ui time update function
 * --------------------------------
 */

void start_game()
{
    bool game_running = true;

    while (game_running) {
        system("cls");
        printf("=======================================================\n");
        printf("   _____  _                                            \n");
        printf("  / ____|| |                                           \n");
        printf(" | (___  | |__    __ _ __      __ __ _  _ __  _ __ ___  __ _ \n");
        printf("  \\___ \\ | '_ \\  / _` |\\ \\ /\\ / // _` || '__|| '_ ` _ \\/ _` |\n");
        printf("  ____) || | | || (_| | \\ V  V /| (_| || |   | | | | | | (_| |\n");
        printf(" |_____/ |_| |_| \\__,_|  \\_/\\_/  \\__,_||_|   |_| |_| |_|\\__,_|\n");
        printf("                                                       \n");
        printf("               SHAWARMA LEGEND (Console Edition)       \n");
        printf("=======================================================\n");
        printf("\n");
        printf("    [1] START NEW GAME\n");
        printf("    [Q] QUIT\n");
        printf("\n");
        printf("=======================================================\n");
        printf("Select an option: ");

        char choice = _getch(); 

        switch (choice) {
            case '1': {
                struct game_state game;
                game.money = 500;
                game.fame = 500;
                game.day = 1;
                game.shop = {50, 50, 50, 50, 50, 50, 50, 50, 0, 0};
                reset_shawarma(&game);

                struct customer_data current_customer = {0};
                customer_generate(&game, &current_customer);

                game_refresh(&game, &current_customer);
                
                break; 
            }
            case '2': {
                system("cls");
                printf("=================================\n");
                printf("           CREDITS               \n");
                printf("=================================\n");
                printf(" Student ID: 251240041\n");
                printf(" Platform:  Visual Studio Code\n");
                printf(" Special Thanks: Google Gemini 3.0 Pro\n");
                printf("=================================\n");
                printf("Press any key to back...");
                _getch();
                break;
            }
            case 'q':
            case 'Q':
                game_running = false;
                break;
            default:
                break;
        }
    }
}

void draw_patience_bar(int current, int max)
{
    if (current <= 0)
        current = 0;
    printf("patience:");
    for (int i = 0; i < max; i++) {
        if (i < current) {
            printf("#");
        } else {
            printf("_");
        }
    }
    printf("\n");
}

void ui_prototype(struct game_state *game, struct customer_data *customer)
{
    system("cls");
    printf("=============================================\n");
    printf("========= Welcome to Shawarma Game! =========\n");
    printf("=============================================\n");
    printf("------------------Info_board-----------------\n");
    printf("raw meat:%d|cookedmeat:%d|potato: %d|fries:%d\n",
           game -> shop.raw_count,
           game -> shop.meat_count,
           game -> shop.potato_count,
           game -> shop.fries_count);
    printf("cucumber:%d|sauce:%d    |bread:%d  |wrap:%d\n",
           game -> shop.cucumber_count,
           game -> shop.sauce_count,
           game -> shop.bread_count,
           game -> shop.wrap_count);
    printf("soda:%d    |money:%d   |fame:%d  |day:%d\n",
           game -> shop.soda_count,
           game -> money,
           game -> fame,
           game -> day);
    printf("fries box:%d\n", game -> shop.fries_box_count);
    printf("------------------your_table-----------------\n");
    printf("[!]current shawarma:\n");
    printf("[0]bread:");
    if (game -> current_shawarma.bread) {
        printf("yes \n");
    } else {
        printf("no  \n");
    }

    printf("[1]meat:");
    if (game -> current_shawarma.meat) {
        printf("yes \n");
    } else {
        printf("no  \n");
    }

    printf("[2]cucumber:");
    if (game -> current_shawarma.cucumber) {
        printf("yes \n");
    } else {
        printf("no  \n");
    }

    printf("[3]sauce:");
    if (game -> current_shawarma.sauce) {
        printf("yes \n");
    } else {
        printf("no  \n");
    }

    printf("[4]fries:");
    if (game -> current_shawarma.fries) {
        printf("yes \n");
    } else {
        printf("no  \n");
    }

    printf("[5]soda:");
    if (game -> current_shawarma.soda) {
        printf("yes \n");
    } else {
        printf("no  \n");
    }
    printf("------------------customer-------------------\n");
    if (customer -> order.bread)
        printf("bread ");
    if (customer -> order.meat)
        printf("meat ");
    if (customer -> order.cucumber)
        printf("cucumber ");
    if (customer -> order.sauce)
        printf("sauce ");
    if (customer -> order.fries)
        printf("fries ");
    if (customer -> order.soda)
        printf("soda ");
    if (customer -> order.takeaway)
        printf("takeaway ");
    printf("\n");
    printf("mood:%d\n", customer -> mood);
    printf("=============================================\n");
    printf("------------------commands-------------------\n");
    printf("[a] add_bread\n");
    printf("[b] add_meat\n");
    printf("[c] add_cucumber\n");
    printf("[d] add_sauce\n");
    printf("[e] add_fries\n");
    printf("[f] add_soda\n");
    printf("[g] wrap_shawarma\n");
    printf("[h] cook_meat\n");
    printf("[i] cook_fries\n");
    printf("[j] serve_customer\n");
    printf("=============================================\n");
    printf("Enter your command: \n");
}

void shop_upgrade(struct game_state *state)
{
    bool in_shop = true;
    while (in_shop) {
        system("cls");
        printf("=============================================\n");
        printf("      BRYANTS' UPGRADE SHOP                  \n");
        printf("=============================================\n");
        printf(" Money: $%d\n", state->money);
        printf("---------------------------------------------\n");
        
        // 商品 1: 金盘子
        printf(" [1] Gold Plate ($1000)\n");
        printf("     Effect: Price +25%%\n");
        printf("     Status: %s\n", state->has_gold_plate ? "[OWNED]" : "$1000");
        
        printf("\n");

        // 商品 2: 自动切肉机
        printf(" [2] Auto Cutter ($1500)\n");
        printf("     Effect: Auto-refill cooked meat\n");
        printf("     Status: %s\n", state->has_auto_cutter ? "[OWNED]" : "$1500");

        printf("---------------------------------------------\n");
        printf(" [q] Next Day >>\n");
        printf("=============================================\n");
        printf(" Command: ");

        char input = _getch(); 

        if (input == 'q') {

            in_shop = false;
            printf("\n[#] Bryant: Man! See you again.\n");
            
        } else if (input == '1') {

            if (!state->has_gold_plate && state->money >= 1000) {
                state->money -= 1000;
                state->has_gold_plate = true;
                printf("\n>>> Purchased Gold Plate!\n");
                printf("\n[#] Bryant: Man! Go and get some money.\n");
            } else if (state->has_gold_plate) {
                printf("\n>>> Already Owned!\n");
                printf("\n[#] Bryant: Man, got so rich, huh?\n");
            } else {
                printf("\n>>> Not enough money!\n");
                printf("\n[#] Bryant: MANBA OUT!");
            }

            Sleep(500);
        } else if (input == '2') {

            if (!state->has_auto_cutter && state->money >= 1500) {
                state->money -= 1500;
                state->has_auto_cutter = true;
                printf("\n>>> Purchased Auto Cutter!\n");
                printf("\n[#] Bryant: Man! Got so quick with this baby.\n");
            } else if (state->has_auto_cutter) {
                printf("\n>>> Already Owned!\n");
                printf("\n[#] Bryant: Man! Really like cutting meat, huh?\n");
            } else {
                printf("\n>>> Not enough money!\n");
                printf("\n[#] Bryant: MANBA OUT!");
            }

            Sleep(500);
        } else if (input == 'h') {

            if (!state->has_auto_fries && state->money >= 2000) {
                state->money -= 2000;
                state->has_auto_fries = true;
                printf("\n>>> [easter egg!]Purchased Auto Fries!\n");
                printf("\n[#] Bryant: Man! That was my favourite! Eyes so sharp?\n");
            } else if (state->has_auto_fries) {
                printf("\n>>> Already Owned!\n");
                printf("\n[#] Bryant: Man! I got nothing to sale.");
            } else {
                printf("\n>>> Invalid command!\n");
                printf("\n[#] Bryant: MANBA OUT!");
            }

            Sleep(500);
        } else {
            printf("\n>>> Invalid command!\n");
            printf("\n[#] Bryant: MANBA OUT!");
            Sleep(500);
        }
    }
}

void ui_end_counting(struct game_state *game)
{    
    printf("\n=============================================\n");
    printf("                   GAME OVER                 \n");
    printf(" [D]Final Day:   %d\n", game->day);
    printf(" [$]Final Money: %d\n", game->money);
    printf(" [!]Final Fame:  %d\n", game->fame);
    printf("=============================================\n");

    system("pause");
    printf(">>>Press Enter to return to the main menu...<<<");
    _getch();
}

/**
 * --------------------------------
 * [-] Mark
 * below functions are related to commandline interactions.
 * --------------------------------
 */

void handle_input(char input, struct game_state *state, struct customer_data *customer, bool *running, int *served_count)
{
    switch (input) {
        case 'a': add_bread(state); break;
        case 'b': add_meat (state); break;
        case 'c': add_cucumber(state); break;
        case 'd': add_sauce(state); break;
        case 'e': add_fries(state); break;
        case 'f': add_soda(state); break;
        case 'g': wrap_shawarma(state); break;
        case 'h': cook_meat(state); break;
        case 'i': cook_fries(state); break;
        case 'j': {
            int rating = validate_order(customer -> order, state -> current_shawarma, customer -> mood);

            if (rating >= 0) {
                update_fame(state, customer);
                update_trade(state);
                printf("\n>>> Successful! Earned Money & Fame. <<<\n");
            } else {
                update_fame(state, customer);
                printf("\n>>> Order Incorrect! Lost Fame. <<<\n");
            }

            if (state -> fame <= 0 || state -> money <= 0) {
                system("cls");
                ui_end_counting(state);
                *running = false;
                return;
            }

            (*served_count) ++;
            reset_shawarma(state);
            customer_generate(state, customer);

            printf("----------------------------------------\n");
            printf("Current Money: %d | Current Fame: %d\n", state->money, state->fame);
            printf("Press Enter to next customer...");

            system("pause");
            system("cls");

            if ((*served_count) % 5 == 0) {
                printf("\n========= Day %d Ended =========\n", state->day);
                printf("Paying rent and restocking...\n");
                printf("Press Enter to start next day...");
                _getch();

                bool alive = update_day(state);
                if (! alive) {
                    system("cls");
                    ui_end_counting(state);
                    *running = false;
                    return;
                }

                printf("\n[#] Bryant(Sales man): Man, Look at these upgrades! What can I say?\n");
                printf(">>> Press Enter to enter the shop...");
                _getch();

                shop_upgrade(state);

                system("cls");
            }
        }
        break;
        case 'q': {
            *running = false;
            system("cls");
            printf("Exiting game. Goodbye!\n");
            return;
            break;
        }
        case 'n': {
            nju_easteregg();
            printf("Press Enter to continue...");
            system("pause");
            Sleep(80);
            system("cls");
            break;
        }
        default:{
            printf("Invalid command. Try again.\n");
            break;
        }
    }
}