
typedef struct{
    int dia, mes, ano;
}Data;

typedef struct{
    int hora, minuto;
}Horario;

typedef struct{
    Data data;
    Horario horario_inicio;
    Horario horario_fim;
    char descricao[50];
    char local[50];
}Evento;


////////////////////////////////// ESTETICAS
void limpa_buffer(int r);
void clear();

void erro();
void sucesso();
void atencao();

void segura();
void carregando();
int menu();


////////////////////////////////// VERIFICACOES
int v_dia(int v);
int v_mes(int v);
int v_ano(int v);
int v_hora(int v);
int v_minuto(int v);


////////////////////////////////// BRUTAS
void mostra_evento(Evento x);
int le_data(int n, Evento *vetor);
void le_hora_inicio(int n, int r, Evento *vetor );
void le_hora_fim(int n, int r, Evento *vetor );

int hora_mais_antiga(Horario *p1, Horario *p2);
int data_mais_antiga(Data *p1, Data *p2);
void reordena(int n, Evento *e);


////////////////////////////////// MENU
// OPC 1
void le_evento(int n, Evento *p);
// OPC 2
void mostra_eventos_geral(int n, Evento *e);
// OPC 3
void mostra_eventos_data(int n, Evento *e);
// OPC 4
void mostra_eventos_desc(int n, Evento *e);
// OPC 5
int remover_evento(int n, Evento **e);
// OPC 6
void sair_do_sistema(int n, Evento *e);