#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

int main(int argc, char const *argv[])
{
    int n;
    Evento *e;

    FILE *f = fopen("./agenda.txt", "rt");
    if( f == NULL ){
        printf("Arquivo inexistente!\n");
        e = NULL;
        n = 0;
    }
    else{

        fscanf( f , "%d", &n);
        printf("Quantidade %d lida...\n", n);

        e = malloc( sizeof(Evento) * n );
    
        for(int i = 0 ; i < n ; i++ ){
            fscanf(f, "%d %d %d", &e[i].data.dia, &e[i].data.mes, &e[i].data.ano );
            fscanf(f, "%d %d", &e[i].horario_inicio.hora,&e[i].horario_inicio.minuto);
            fscanf(f, "%d %d", &e[i].horario_fim.hora,&e[i].horario_fim.minuto);
            fscanf(f, " %49[^\n]", e[i].descricao);
            fscanf(f, " %49[^\n]", e[i].local);
        }
        fclose( f );
    }
    
    /*
    
    *DISCLAIMER!
     Esse comentário não é do gpt não KKKKK
     Fiz ele para deixar ciente as liberdades que tomei ao fazer esse código.

    O MEU sistema serve para gerenciamento de eventos diário! 
    Todas as verificações de horário foram criadas em cima desse objetivo, gerir eventos com inicio e fim no mesmo dia!

    O sistema segue todas os critérios definidos, não permitindo que mais de um evento ocorra simultâneamente:
        - Não permite que um evento englobe outro
        - Não permite que um evento inicie dentro da faixa de outro evento
        - Não permite que um evento encerre dentro da faixa de outro evento
        - Não permite que um evento encerre antes do horário de início                                                               REFORMULAR DISCLAIMER KKKKK
        - etc                                                                                                                        JÁ MUDEI QUASE TUDO ISSO

        Porém, por escolha minha, permito que o usuário inicie e encerre um evento na mesma hora e minuto,
        Por que?
        Para impedir que o sistema fique sem saída:

            Exemplo: Tenho um evento no sistema que começa as 16:57 e termina as 20:00
                      Crio um evento que inicia as 16:56
                           - Não permite o fim antes das 16:56 (pois seria finalizar o evento antes do início)
                           - Não permite o fim após as 16:56 (pois começa a englobar a faixa de outro evento)
                       Nesse ponto o usuário não teria saída alguma, por isso permito que ele bote o horário de fim igual o de início.
                       No pior do casos, não sendo proposital, ele pode apagar o evento de qualquer forma.    
    */

    while(1==1){
        switch(menu()){
            case 1: // Cadastrar (um evento)
                n++;
                e = realloc(e,sizeof(Evento)*n);
                le_evento(n,e);
                reordena(n,e);
                break;
            case 2: // Mostrar todos os eventos na agenda
                mostra_eventos_geral(n, e);
                break;
            case 3: // Mostrar todos os eventos de uma data
                mostra_eventos_data(n, e);
                break;
            case 4: // Mostrar evento por Descrição
                mostra_eventos_desc(n, e);
                break;
            case 5: // Remover evento
                n = remover_evento(n, &e);
                break;
            case 6: // Sair
                sair_do_sistema(n, e);
                free(e);
                return 0;
        }
    }
}