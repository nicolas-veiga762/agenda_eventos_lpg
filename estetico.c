#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>

////////////////////////////////////////////// ESTÉTICO

#ifdef _WIN32
    #include <windows.h>
    #define sleep_ms(x) Sleep(x)
#else
    #include <unistd.h>
    #define sleep_ms(x) usleep((x) * 1000)
#endif

int menu(){
    int i,r;
    do{
        clear();
        printf("\nAgenda de Eventos\n");
        printf("\n\t{Menu}\n");
        printf("\n\t1. Cadastrar (somente um) novo evento na agenda");
        printf("\n\t2. Mostrar todos os eventos da agenda");
        printf("\n\t3. Mostrar todos os eventos de X data");
        printf("\n\t4. Mostrar todos os eventos que tenham X descrição");
        printf("\n\t5. Remover evento");
        printf("\n\t6. Sair do programa");
        printf("\n\n[Escolha uma opção]: ");
        r = scanf("%d",&i);                    
        limpa_buffer(r);
    }while(i < 1 || i > 6);

    return i;
}

void carregando(){
    for(int i = 0; i < 4; i++){
        printf(" .");
        sleep_ms(400);
        fflush(stdout);    // força a impressão imediata
    }
    printf("\n");
}

void segura(){
    printf("\n[Press Enter]: ");
    while(getchar() != '\n');   // limpa o buffer
        getchar();
}

void erro(char texto[]){
    printf("\033[1;31m%s\033[0m",texto);    // 31 vermelho
}

void sucesso(char texto[]){
    printf("\033[1;32m%s\033[0m",texto);    // 32 verde
}

void atencao(char texto[]){
    printf("\033[1;33m%s\033[0m",texto);    // 33 amarelo
}

void clear(){
    system("clear"); // apaga tela (funciona para linux apenas)
}

void limpa_buffer(int r){               // não permitir caracter não numérica
    if(r==0){                           // esse r recebe: 1 se foi lido corretamente, 0 se não
        while (getchar() != '\n');      
    }
}