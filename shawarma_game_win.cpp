/**
 * --------------------------------
 * 251240041
 * --------------------------------
 */

#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<cstdbool>
#include<cstring>
#include<algorithm>
#include<ctime>

/**
 * --------------------------------
 * [-] Mark
 * data structures
 * --------------------------------
 */

struct shawarma_data
{
    bool bread;
    bool meat;
    bool cucumber;
    bool sauce;
    bool fries;
    bool raw;   //tricky players
    bool potato;//tricky players
    bool takeaway;
    bool soda;
};

struct customer_data
{
    int id;
    int mood;
    struct shawarma_data order;
};

struct inventory
{
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

struct game_state
{
    int money = 500;
    int fame  = 500;
    int day   = 1;

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
        0,  // meat_count
        0,  // fries_count
        50  // soda_count
    };
};

/**
 * --------------------------------
 * [-] Mark
 * functions below are related to order validation.
 * --------------------------------
 */

/**
 * [EXP] explaination:
 * -validate the order and the current shawarma
 * -the rating of the customer is based on mood
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

void reset_shawarma(struct game_state* state)
{
    state -> current_shawarma.bread    = false;
    state -> current_shawarma.meat     = false;
    state -> current_shawarma.cucumber = false;
    state -> current_shawarma.sauce    = false;
    state -> current_shawarma.fries    = false;
    state -> current_shawarma.raw      = false;
    state -> current_shawarma.potato   = false;
    state -> current_shawarma.takeaway = false;
    state -> current_shawarma.soda     = false;
}

//need an update
void cook_meat(struct game_state* state)
{
    if (state -> shop.raw_count <= 0)
        return;
    state -> shop.raw_count --;
    state -> shop.meat_count ++;
}

void cook_fries(struct game_state* state)
{
    if (state -> shop.potato_count <= 0)
        return;
    state -> shop.potato_count --;
    state -> shop.fries_count ++;
}

void add_bread(struct game_state* state)
{
    if (state -> shop.bread_count <= 0)
        return;
    state -> shop.bread_count --;
    state -> current_shawarma.bread = true;
}

void add_meat(struct game_state* state)
{
    if (state->current_shawarma.bread == false)
        return;
    if (state -> shop.meat_count <= 0)
        return;
    state -> shop.meat_count --;
    state -> current_shawarma.meat = true;
}

void add_fries(struct game_state* state)
{
    if (state->current_shawarma.bread == false)
        return;
    if (state -> shop.fries_count <= 0)
        return;
    state -> shop.fries_count --;
    state -> current_shawarma.fries = true;
}

void add_cucumber(struct game_state* state)
{
    if (state->current_shawarma.bread == false)
        return;
    if (state -> shop.cucumber_count <= 0)
        return;
    state -> shop.cucumber_count --;
    state -> current_shawarma.cucumber = true;
}

void add_sauce(struct game_state* state)
{
    if (state -> current_shawarma.bread == false)
        return;
    if (state -> shop.sauce_count <= 0)
        return;
    state -> shop.sauce_count --;
    state -> current_shawarma.sauce = true;
}

void add_soda(struct game_state* state)
{
    if (state -> shop.soda_count <= 0)
        return;
    state -> shop.soda_count --;
    state -> current_shawarma.soda = true;
}

void wrap_shawarma(struct game_state* state)
{
    if (state -> shop.wrap_count <= 0)
        return;
    state -> shop.wrap_count --;
    state -> current_shawarma.takeaway = true;
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

void customer_generate(struct game_state* state, struct customer_data* customer)
{
    customer -> id ++;
    customer -> mood = std::rand() % 11 - 5;
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

//to be implemented

/**
 * --------------------------------
 * [-] Mark
 * below functions are related to economic system & fame calculations.
 * --------------------------------
 */

bool update_day(struct game_state* state)
{
    state -> day ++;

    if (state -> money <= 0 || state -> fame <= 0) {
        printf("[x]game over.\n");
        return false;
    } else if (state -> money <= 500) {

        int refresh = state -> money / 10;

        state -> shop.raw_count      += refresh;
        state -> shop.cucumber_count += refresh;
        state -> shop.sauce_count    += refresh;
        state -> shop.potato_count   += refresh;
        state -> shop.bread_count    += refresh;
        state -> shop.wrap_count     += refresh;
        state -> shop.soda_count     += refresh;
        state -> money               -= (refresh * 10);

        if (state->money > 0) {
            printf("[!] Remaining $%d converted to Fame (+%d)!\n", state->money, state->money);
            state->fame += state->money; 
            state->money = 0;
        }

        return true;
    } else {
        state -> money               -= 500;
        state -> shop.raw_count      += 50;
        state -> shop.cucumber_count += 50;
        state -> shop.sauce_count    += 50;
        state -> shop.potato_count   += 50;
        state -> shop.bread_count    += 50;
        state -> shop.wrap_count     += 50;
        state -> shop.soda_count     += 50;
        return true;
    }
}

void update_trade(struct game_state* state)
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

/**
 * --------------------------------
 * [-] Mark
 * below functions are related to UI surface.
 * --------------------------------
 */

void ui_prototype(struct game_state* game, struct customer_data* customer)
{
    //system("clear");
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
    printf("Enter your command: ");
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
            } else {
                update_fame(state, customer);
            }

            if (state -> fame <= 0 || state -> money <= 0) {
                //system("clear");
                system("cls");
                printf("[x]game over.\n");
                *running = false;
                return;
            }

            (*served_count) ++;
            reset_shawarma(state);
            customer_generate(state, customer);

            printf("----------------------------------------\n");
            printf("Current Money: %d | Current Fame: %d\n", state->money, state->fame);
            printf("Press Enter to next customer...");

            char temp;
            std::cin.ignore();
            std::cin.get(temp);
            //system("clear");
            system("cls");

            if ((*served_count) % 5 == 0) {
                printf("\n========= Day %d Ended =========\n", state->day);
                printf("Paying rent (-500) and restocking...\n");
                printf("Press Enter to start next day...");
                std::cin.ignore();
                std::cin.get();

                bool alive = update_day(state);
                if (! alive) {
                    //system("clear");
                    system("cls");
                    printf("[x]game over.\n");
                    *running = false;
                    return;
                }
            }
        }
        break;
        case 'q': {
            *running = false;
            //system("clear");
            system("cls");
            printf("Exiting game. Goodbye!\n");
            return;
            break;
        }
        case 'n': {
            nju_easteregg();
            printf("Press Enter to continue...");
            char temp;
            std::cin.ignore();
            std::cin.get(temp);
            //system("clear");
            system("cls");
            break;
        }
        default:{
            printf("Invalid command. Try again.\n");
            break;
        }
    }
}

/**
 * --------------------------------
 * [-] Mark
 * mainfunction
 * --------------------------------
 */

int main() 
{
    init_random();
    struct game_state game;
    game.money = 500;
    game.fame = 500;
    game.day = 1;
    game.shop = {50, 50, 50, 50, 50, 50, 0, 0, 50}; 
    reset_shawarma(&game);

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