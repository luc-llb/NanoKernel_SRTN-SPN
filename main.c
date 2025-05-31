#include <stdio.h>
#include <conio.h>
#include "shortTime.h"

void main (){
    Buffer b;
    Process fila[MAX_PROCESS];
    int op=0;

    get_dados(fila,"stdin.txt");
    init_clock_tick();

    while((op!=1)&&(op!=2)){
        printf("\nSelecione o escalonador:\n");
        printf("\n1-SRTN   2-SPN\n");
        scanf("%d", &op);

        switch(op){
            case 1:
                init_Buffer(&b,scheduler_SRTN);
                break;
            case 2:
                init_Buffer(&b,scheduler_SPN);
                break;
            default:
                printf("\nOpcao invalida.\n");
                break;
        }
    }
    kernel(&b,fila,"stdout.txt");
    return;
}
