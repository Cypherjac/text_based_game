#include <stdio.h>

int main(){
    for(int i = 30; i < 38; i++){
        printf("\033[%dm%d\t\t", i, i);
        printf("\033[%dm%d\n", i+60, i+60);
    }
}