#include "funcoes.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////// VERIFICAÇÕES

int v_dia(int v){
    if(v < 1 || v > 31){
        erro("\tEscolha um dia valido!\n");
        return 1;
    }
    return 0;
}

int v_mes(int v){
    if(v < 1 || v > 12){
        erro("\tEscolha um mes valido!\n");
        return 1;
    }
return 0;
}

int v_ano(int v){
    if(v < 2025){
        erro("\tEscolha um ano valido!\n");
        return 1;
    }
return 0;
}

int v_hora(int v){
    if(v < 1 || v > 23){
        erro("\tEscolha uma hora valida!\n");
        return 1;
    }
return 0;
}

int v_minuto(int v){
    if(v < 0 || v > 59){
        erro("\tEscolha um minuto valido!\n");
        return 1;
    }
return 0;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////// BRUTAS

void mostra_evento(Evento x){
	printf("\n >[ %02d / %02d / %d ]\n  Inicio:\t%02d:%02d\n  Fim:\t\t%02d:%02d\n  Descricao:\t%s\n  Local:\t%s\n"
        
    ,x.data.dia,x.data.mes,x.data.ano,
     x.horario_inicio.hora,x.horario_inicio.minuto,
     x.horario_fim.hora,x.horario_fim.minuto,
     x.descricao,
     x.local);
}

int le_data(int n, Evento *vetor){
    Data *evento_atual = &vetor[n-1].data; 
    
    do{ 
        printf("\tDia: ");
        scanf("%d", &evento_atual->dia);
    }while(v_dia(evento_atual->dia)!=0);

    do{
        printf("\tMes: ");
        scanf("%d", &evento_atual->mes);
    }while(v_mes(evento_atual->mes)!=0);
    
    do{
        printf("\tAno: ");
        scanf("%d", &evento_atual->ano);
    }while(v_ano(evento_atual->ano)!=0);

    for(int i = 0; i < (n-1); i++){ // não verifico na posição n, pq eu estou nela
        int r = data_mais_antiga(evento_atual, &vetor[i].data);
        if(r == 2){
            return i;
        }
    }
    return -1;
}

void le_hora_inicio(int n, int r, Evento *vetor ){
    Horario *evento_atual_inicio = &vetor[n-1].horario_inicio; 
    
    while(1==1){
        int vira = 0;
        do{
            printf("\tHora: ");
            scanf("%d", &evento_atual_inicio->hora);
        }while(v_hora(evento_atual_inicio->hora)!=0);
        
        do{
            printf("\tMinuto: ");           
            scanf("%d", &evento_atual_inicio->minuto);
        }while(v_minuto(evento_atual_inicio->minuto)!=0);
    
        if(r != -1){
            for(int i = 0; i < (n-1); i++){ // não verifico na posição n, pq eu estou nela
                
                int w = data_mais_antiga(&vetor[n-1].data, &vetor[i].data);
                
                if(w == 2){
                    if(hora_mais_antiga(evento_atual_inicio, &vetor[i].horario_inicio) == 1 ||
                       hora_mais_antiga(&vetor[i].horario_fim, evento_atual_inicio) == 1){
        
                        ;

                    }else{
                        vira = 1;
                        erro("\tJá existe um evento que ocupa esse horário:");
                        printf(" %s - %s - [%02d:%02d] ~ [%02d:%02d]\n",
                                
                                vetor[i].descricao,
                                vetor[i].local,
                                vetor[i].horario_inicio.hora,
                                vetor[i].horario_inicio.minuto,
                                vetor[i].horario_fim.hora,
                                vetor[i].horario_fim.minuto);
                    }
                }
            }
            if(vira == 0){
                break;
            }
        }
        else{
            break;
        }
    }
}

void le_hora_fim(int n, int r, Evento *vetor ){
    Horario *evento_atual_fim = &vetor[n-1].horario_fim; 
    Horario *evento_atual_inicio = &vetor[n-1].horario_inicio; 

    while(1==1){
        int vira = 0;
        while(1==1){
            do{
                printf("\tHora: ");
                scanf("%d", &evento_atual_fim->hora);
            }while(v_hora(evento_atual_fim->hora)!=0);
            
            do{
                printf("\tMinuto: ");           
                scanf("%d", &evento_atual_fim->minuto);
            }while(v_minuto(evento_atual_fim->minuto)!=0);
            
            if(hora_mais_antiga(evento_atual_fim, evento_atual_inicio) == 1 ){
                erro("\tHorário de termino invalido! Deve ser depois do horário de inicio!\n");
            }
            else{
                break;
            }
        }
        if(r != -1){
            for(int i = 0; i < (n-1); i++){ // não verifico na posição n, pq eu estou nela
                int w = data_mais_antiga(&vetor[n-1].data, &vetor[i].data);
                if(w == 2){
                    //atencao("\nVAI VERIFICAR\n");
                    if(hora_mais_antiga(evento_atual_inicio, &vetor[i].horario_inicio) == 1){ // o evento atual começa antes do evento já existente
                        if(hora_mais_antiga(evento_atual_fim, &vetor[i].horario_inicio) == 1){
                            //sucesso("\tdeu certo\n");
                            ;
                        }
                        else{
                            vira = 1;
                            erro("\tO horário de término do evento atual não deve ultrapassar o inicio do evento já existente:");
                            printf(" %s - %s - [%02d:%02d] ~ [%02d:%02d]\n",
                                
                                vetor[i].descricao,
                                vetor[i].local,
                                vetor[i].horario_inicio.hora,
                                vetor[i].horario_inicio.minuto,
                                vetor[i].horario_fim.hora,
                                vetor[i].horario_fim.minuto);
                        }
                    }
                    else{
                        if(hora_mais_antiga(&vetor[i].horario_fim, evento_atual_inicio) == 1){ // o evento atual começa depois do evento já existente
                            if(hora_mais_antiga(&vetor[i].horario_fim, evento_atual_fim) == 1){
                                //sucesso("\tdeu certo\n");
                                ;
                            }
                            else{
                                vira = 1;
                                erro("\tpqp como tu conseguiu esse erro? kkkkkkkkk\n");
                            }
                        }
                    }
                }
            }
            if(vira == 0){
                break;
            }
        }
        else{
            break;
        }
    }
}

int hora_mais_antiga(Horario *p1, Horario *p2){
    if(p1->hora < p2->hora){
        return 1; // p1 é mais antigo
    }
    else{
        if(p2->hora < p1->hora){
            return 0; // p2 é mais antigo
        }
        else{ // acontecem na mesma hora
            
            if(p1->minuto < p2->minuto){
                return 1; // p1 é mais antigo
            }
            else{
                if(p2->minuto < p1->minuto){
                    return 0; // p2 é mais antigo
                }
                else{ // acontecem no mesmo ano
                    return 2; // acontece na mesma hora  e mesmo minuto
                }
            }        
        }
    }
}

int data_mais_antiga(Data *p1, Data *p2){
    if(p1->ano < p2->ano){
        return 1; // p1 é mais antigo
    }
    else{
        if(p2->ano < p1->ano){
            return 0; // p2 é mais antigo
        }
        else{ // acontecem no mesmo ano
            
            if(p1->mes < p2->mes){
                return 1; // p1 é mais antigo
            }
            else{
                if(p2->mes < p1->mes){
                    return 0; // p2 é mais antigo
                }
                else{ // acontecem no mesmo mes
                    
                    if(p1->dia < p2->dia){
                        return 1; // p1 é mais antigo
                    }
                    else{
                        if(p2->dia < p1->dia){
                            return 0; // p2 é mais antigo
                        }
                        else{ // acontecem no mesmo dia
                            return 2; // como acontece no mesmo dia, mesmo mes e mesmo ano, deve ser desenpatado pelo horário
                        }
                    }
                }
            }
        }
    }
}


void reordena(int n, Evento *e){
    
    if(n > 1){
        for(int pass  = 0; pass < (n-1); pass++){
            for(int i = 0; i < (n-1) -pass; i++){
                
                int data = data_mais_antiga(&e[i].data, &e[i+1].data);
    
                if(data == 0){ // trocar
    
                    Evento temp = e[i];
                    e[i] = e[i+1];
                    e[i+1] = temp;
    
                }else{
                    if(data == 2){ // mesma data, verifica horario
                        int hora = hora_mais_antiga(&e[i].horario_inicio, &e[i+1].horario_inicio);
                        if(hora == 0){
    
                            Evento temp = e[i];
                            e[i] = e[i+1];
                            e[i+1] = temp;
    
                        }
                    }
                }
            }
        }
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////// OPCOES

// OPC 1
void le_evento(int n, Evento *vetor){ // é o vetor completo com os "600bytes" englobando todos os eventos
    Evento *evento_atual = &vetor[n-1];
    clear();
    printf("Cadastro de Evento:\n\n");
	printf("  .Data\n");
	int indice_mesma_data = le_data(n, vetor);          
    if(indice_mesma_data != -1){
        atencao("\tJá existem evento(s) nesse dia.\n");
    }        
    // ver se já existe outro evento nesse dia, se sim, começar a verificar o horario
    printf("  .Horario de inicio\n");
	le_hora_inicio(n, indice_mesma_data, vetor);       
    printf("  .Horario de fim\n");
	le_hora_fim(n, indice_mesma_data, vetor);       
    printf("  .Descricao: ");
	scanf(" %49[^\n]", evento_atual->descricao);  
    printf("  .Local: ");
	scanf(" %49[^\n]", evento_atual->local);
}

// OPC 2
void mostra_eventos_geral(int n, Evento *e){
    clear();
    if(n == 0){
        erro("Nenhum evento cadastrado...\n");
        segura();
    }
    else{
        printf("Todos os %d eventos:\n\n",n);
        for(int i = 0 ; i < n ; i++ ){
            mostra_evento(e[i]);
        }
        segura();
    }
}

// OPC 3
void mostra_eventos_data(int n, Evento *e){
    clear();
    if(n == 0){
        erro("Nenhum evento cadastrado...\n");
        segura();
    }
    else{

        int dia, mes, ano;
        printf("Todos os eventos que ocorre na seguinte data:\n\n");
    
        do{ 
            printf("\tDia: ");
            scanf("%d", &dia);
        }while(v_dia(dia)!=0);
    
        do{
            printf("\tMes: ");
            scanf("%d", &mes);
        }while(v_mes(mes)!=0);
        
        do{
            printf("\tAno: ");
            scanf("%d", &ano);
        }while(v_ano(ano)!=0);
    
    
        int cont = 0;
        for(int i = 0 ; i < n ; i++ ){
            if(e[i].data.dia == dia && e[i].data.mes == mes && e[i].data.ano == ano){
                mostra_evento(e[i]);
                cont++;
            }
        }
        printf("\nTotal de %d evento(s) ocorre(m) no dia %02d/%02d/%02d...\n",cont,dia,mes,ano);
        segura();
    }
}

// OPC 4
void mostra_eventos_desc(int n, Evento *e){
    clear();
    if(n == 0){
        erro("Nenhum evento cadastrado...\n");
        segura();
    }
    else{
        char desc[50];
        printf("Todos os eventos com a seguinte descricao: "); 
        scanf(" %49[^\n]",desc);
    
        int cont = 0;
        for(int i = 0 ; i < n ; i++ ){
            if(strcmp(e[i].descricao, desc) == 0){
                mostra_evento(e[i]);
                cont++;
            }
        }
        printf("\nTotal de %d evento(s) com a descricao: %s...\n",cont,desc);
        segura();
    }
}

// OPC 5
int remover_evento(int n, Evento **e){
    clear();
    int dia, mes, ano, minuto, hora;
    char decisao;
    erro("Remover evento que ocorre na seguinte data:\n\n");

    do{ 
        printf("\tDia: ");
        scanf("%d", &dia);
    }while(v_dia(dia)!=0);

    do{
        printf("\tMes: ");
        scanf("%d", &mes);
    }while(v_mes(mes)!=0);
    
    do{
        printf("\tAno: ");
        scanf("%d", &ano);
    }while(v_ano(ano)!=0);

    erro("\nE no seguinte horario de inicio:\n\n");

    do{
        printf("\tHora: ");
        scanf("%d", &hora);
    }while(v_hora(hora)!=0);
    
    do{
        printf("\tMinuto: ");           
        scanf("%d", &minuto);
    }while(v_minuto(minuto)!=0);

    int cont = 0;
    int indice = 0;
    for(int i = 0 ; i < n ; i++ ){
        if((*e)[i].data.dia == dia && (*e)[i].data.mes == mes && (*e)[i].data.ano == ano && (*e)[i].horario_inicio.hora == hora && (*e)[i].horario_inicio.minuto == minuto){
            mostra_evento((*e)[i]);
            indice = i;
            cont++;
        }
    }

    if(cont == 0){
        printf("\nEvento não encontrado...\n");
        segura();
    }
    else{
        erro("\nDESEJAS REMOVER ESSA EVENTO [s/n]: ");
        scanf(" %c",&decisao);  
        if(decisao == 'N' || decisao == 'n'){
            segura();
        }               
        if(decisao == 'S' || decisao == 's'){
            if(indice != (n-1)){           // só faz toda a reordenação se ele não for o último elemento
                for(int i = indice; i < (n-1); i++){
                    (*e)[i] = (*e)[i+1];
                }   
            }
            n--;
            *e = realloc(*e,sizeof(Evento)*n);
        }
        sucesso("\nEvento removido com sucesso...");
        segura();

    }
    return n;
}

// OPC 6
void sair_do_sistema(int n, Evento *e){


    FILE *f = fopen("/home/infantaria/Desktop/UDESC/LPG/TRABALHOS/TRABALHO_STRUCT/agenda.txt", "wt");
    if( f == NULL ){
        printf("Erro no arquivo!\n");
        segura();
    }

    fprintf( f , "%d\n", n);
    for(int i = 0 ; i < n ; i++ ){
        fprintf(f, "%d %d %d\n", e[i].data.dia, e[i].data.mes, e[i].data.ano );
        fprintf(f, "%d %d\n", e[i].horario_inicio.hora, e[i].horario_inicio.minuto);
        fprintf(f, "%d %d\n", e[i].horario_fim.hora, e[i].horario_fim.minuto);
        fprintf(f, "%s\n", e[i].descricao);
        fprintf(f, "%s\n", e[i].local);
    }
    
    fclose( f );

    clear();
    printf("Saindo do sistema");
    carregando();
    clear();
    printf("Um trabalho de Luca && Nicolas && Isabela\n");
}