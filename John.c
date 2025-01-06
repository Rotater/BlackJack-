#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

int r;
int choice;
char yn;


int b_deck[] = {1,1,1,1,
2,2,2,2,
3,3,3,3,
4,4,4,4,
5,5,5,5,
6,6,6,6,
7,7,7,7,
8,8,8,8,
9,9,9,9,
10,10,10,10,
10,10,10,10,
10,10,10,10,
10,10,10,10
};

int deck [52];

int ph [5];
int pc = 0;

int dh [5];
int dc = 0;

int turn = 2;
int i;
int k = 0;

int p_money = 1000;
int bet;

bool stood = false;
bool p_win = false;
bool d_win = false;

int deck_length = (sizeof(deck)/ sizeof(deck[0]));

void initialize_deck(){
    for(i = 0; i < deck_length; i++){
        *(deck + i) = *(b_deck + i);
    }
}

void shuffle(){
    for(i = 0; i<deck_length; i++){
        int temp = *(deck + i);
        *(deck + i) = *(deck + r);
        *(deck + r) = temp;
        r = (rand() % 52);
    }
}
void clear_hands(){
    pc = 0;
    dc = 0;
    for(i = 0; i < 5; i++){
        *(ph + i) = 0;
        *(dh + i) = 0;
    }

}

void drawp(){
    i = 0;
    int j;
    int cho;
    while(((*(deck+i)) == 0) && (k <= 50)){
        i++;
    }
    if(k > 50){
        initialize_deck();
        printf("Shuffling");
        shuffle();
        k = 0;
    }
    if(*(deck + i) == 1){
        int p_total = 0;
        for(j = 0; j < pc; j++){
            p_total += *(ph + i);
        }
        if(p_total <= 10){
            printf("%s", "Ace");
            printf("%s", "1 or 11? :");
            scanf("%d", &cho);
            if(cho == 11){
                *(deck + i) = 11;
            }
        }
    }
    *(ph + pc) = *(deck + i);
    *(deck + i) = 0;
    pc++;
}
void drawd(){
    i = 0;
    int j;
    while(((*(deck+i)) == 0) &&(k <= 50)){
        i++;
    }
    if(k > 50){
        initialize_deck();
        printf("Shuffling");
        shuffle();
        k = 0;
    }

    if(*(deck + i) == 1){
        int d_total = 0;
        for(j = 0; j < dc; j++){
            d_total += *(dh + j);
        }
        if(d_total <= 10){
            *(deck + i) = 11;
        }

    }
    *(dh + dc) = *(deck + i);
    *(deck + i) = 0;
    dc++;
}
void jack_start(){
    printf("%s\n", "Dealer Hand: ");
    drawd();
    drawd();
    printf("%d",*(dh));
    printf("%s"," ");
    printf("?\n");

    printf("%s\n"," ");
    printf("%s\n", "Your Hand: ");
    drawp();
    printf("%d",*(ph));
    printf("%s"," ");
    drawp();
    printf("%d\n",*(ph + 1));
}
void manage_turn(){
    turn++;
    printf("%s\n", "Dealer Hand: ");
    for (i = 0; i< dc-1; i++){
        printf("%d", *(dh +i));
        printf("%s", " ");
    }
    printf("?");
    printf("%s\n", " ");

    printf("%s\n", "Player Hand: ");
    for (i = 0; i< pc ; i++){
        printf("%d", *(ph +i));
        printf("%s", " ");
    }
    printf("%s\n", " ");


}
void check_game(){
    int p_total = 0;
    int d_total = 0;
    for(i = 0; i < 5; i++){
        p_total += *(ph +i);
        d_total += *(dh + i);
    }
    if(stood==true){
        if ((d_total >= p_total) && (d_total <= 21)){
            d_win = true;
        }
    }
    if(p_total > 21){
        d_win = true;
    }
    else if (d_total > 21){
        p_win = true;
    }
    else{
    }
}
int take_turn(){
    int p_total = 0;
    int d_total = 0;
    if(stood == true){
        drawd();
    }
    else{
        printf("%s\n", "hit (0) or stand? (1) : ");
        scanf("%d",&choice);
        if (choice == 0){
            drawp();
            for(i = 0; i < 5; i++){
                p_total += *(ph +i);
                d_total += *(dh + i);
            }
            if((d_total < p_total) && (p_total <= 21)){
                drawd();
            }
        }
        else{
            stood = true;
        }
    }
}





int main() {
    srand(time(0));
    r = (rand() % 52);
    initialize_deck();
    shuffle();
    printf("Total money: ");
    printf("%d\n", p_money);
    printf("How much would you like to bet? :");
    scanf("%d",&bet);
    p_money -= bet;
    jack_start();
    check_game();
    while(!(p_win || d_win)){
        take_turn();
        manage_turn();
        check_game();
    }
    if(p_win){
        printf("%s\n", "Player wins");
        p_money += (bet * 2);

    }
    else{
        printf("%s\n", "Dealer wins");

    }
    p_win = false;
    d_win = false;
    stood = false;
    clear_hands();
    while((p_money > 0)){
        printf("Total money: ");
        printf("%d\n", p_money);
        printf("How much would you like to bet? :");
        scanf("%d",&bet);
        p_money -= bet;
        jack_start();
        check_game();
        while(!(p_win || d_win)){
            take_turn();
            manage_turn();
            check_game();
        }
        if(p_win){
            printf("%s\n", "Player wins");

        }
        else{
            printf("%s\n", "Dealer wins");
        }
        p_win = false;
        d_win = false;
        stood = false;
        clear_hands();

    }
    printf("total earnings: ");
    printf("%d", p_money);




}
