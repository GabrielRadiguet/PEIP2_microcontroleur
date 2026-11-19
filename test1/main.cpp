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

/*A : DO
Z : DOd
E : RE
R : REd
T : MI
Y : FA
U : FAd
I : SOL
O : SOLd
P LA
Q LAd
S SI
D 2*DO
F 2*DOd
G 2*RE
H 2*REd
J 2*MI
K 2*FA
L 2*FAd
M 2*SOL
W 2*SOLd
X 2*LA
C 2*LAd
V 2*SI
B 4*DO
N 4*DOd*/

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

void reset_game_state(){
    for (int i = 0; i < x_max; i++) {
        for (int j = 0; j < y_max; j++) {
            game_state[i][j] = 0;
        }
    }
}

void queue()
{
    
}

void deplacements()
{

}

void print_screen()
{
    LCD.pixel(1,1,1);
}

int main()
{
    float pot1v;
    float pot2v;
    PlayNote(DO, 0.9);
    int n;
    while(true){
        pot1v = pot1.read();
        pot2v = pot2.read();
        
        n = AnalogIn2Index(pot1v, 7);

        PlayNote(freq_notes[n], pot2v);
        
        LCD.locate(0, 0);
        LCD.printf("pot1 : %d", n + 1);

        LCD.locate(0, LCD.height()/3);
        LCD.printf("pot1 : %f", pot2v);
    }
    printf("test");
}