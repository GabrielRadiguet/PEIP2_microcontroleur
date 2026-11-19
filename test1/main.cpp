#include "mbed.h"
#include <cstdio>
#include "LM75B.h"
#include "C12832.h"

//Frequences des notes en gamme 3
#define DO  262.0
#define DOd 277.0
#define RE  294.0
#define REd 311.0
#define MI 330.0
#define FA  349.0
#define FAd 370.0
#define SOL  392.0
#define SOLd 415.0
#define LA  440.0
#define LAd 466.0
#define SI  494.0
float freq_notes[7]      = {DO, RE,  MI, FA, SOL, LA, SI};
float azerty2notes[26]      = {DO, 4*DO, 2*LAd, 2*DO, RE, 2*DOd, 2*RE, 2*REd, SOL, 2*MI, 2*FA, 2*FAd, 2*SOL, 4*DOd, SOLd, LA, LAd, REd, SI, MI, FAd, 2*SI, 2*SOLd, 2*LA, FA, DOd} ;

float volume;
int gamme;
int note;

PwmOut Speaker(p26);
AnalogIn pot1(p19);
AnalogIn pot2(p20);
C12832 LCD(p5, p7, p6, p8, p11);

void PlayNote(float freq, float vol){
    Speaker.period(1/freq);
    Speaker=vol;
}

int AnalogIn2Index(float v, int n){
    return (int) n * v;
}




DigitalIn Down(p12);
DigitalIn Up(p15);
DigitalIn Left(p13);
DigitalIn Right(p16);

#define x_max 32
#define y_max 8
int game_state[x_max][y_max];
int game_state_save[x_max][y_max];
int tete[2] = {0,0};
int queue[2] = {0,0};

void reset_game_state(){
    for (int i = 0; i < x_max; i++) {
        for (int j = 0; j < y_max; j++) {
            game_state[i][j] = 0;
            game_state_save[i][j] = 0;
        }
    }
}

void print_screen()
{
    for (int i = 0; i < x_max; i++) {
        for (int j = 0; j < y_max; j++) {
            LCD.pixel(i,j,1);
        }
    }

    //LCD.fillrect(0, 0, 10, 10, 1);
}

void deplacements(int move[2])
{
    if(Down == 1){
        move[0] = 0;
        move[1] = 1;
    }else if(Up == 1){
        move[0] = 0;
        move[1] = -1;
    }else if(Right == 1){
        move[0] = 0;
        move[1] = 1;   
    }else{
        move[0] = 0;
        move[1] = -1;      
    }
}

void reduce(){
    for (int i = 0; i < x_max; i++) {
        for (int j = 0; j < y_max; j++) {
            if(game_state[i][j] > 0 && game_state[i][j] < 255){
                game_state[i][j] -= 1;
            }
        }
    }
}

bool game_tick(){
    int move[2] = {0,0};
    deplacements(move);

    if((tete[0] + move[0] < 0) || (tete[0] + move[0] >= x_max) ||
    (tete[1] + move[1] < 0) || (tete[1] + move[1] >= y_max)){
        return true;
    }
    
    bool pomme = (game_state[tete[0] + move[0]][tete[1] + move[1]] == 255);
    game_state[tete[0] + move[0]][tete[1] + move[1]] = game_state[tete[0]][tete[1]] + 1;

    tete[0] += move[0];
    tete[1] += move[1];

}

int main()
{
    reset_game_state();
    print_screen();

    while(true){
        if(game_tick()){
            break;
        }
        LCD.copy_to_lcd();
        wait_us(500000);
    }
}