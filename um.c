#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 10
#define COLS 10
#define TURNS 5

// game board
char game_board[ROWS][COLS];
char aux_game_board[ROWS][COLS];
int indice = 0;

// prototype
void print_board();
void draw_ships();
void player_turn();
int player_win();
void remaining_shots(int verify, int rows, int cols);


// master function
int main(){
    // gerando numeros aleatorios
    srand(time(0));

    // inicializando todo o tabuleiro com '-'
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            game_board[i][j] = '-';
            aux_game_board[i][j] = '-';
        }
    }
    // colocando os navios
    draw_ships();
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){

            if(j == 0){
                printf("\n %c", game_board[i][j]);
            }else{
                printf(" %c", game_board[i][j]);
            }
        }
    }
    player_turn(indice);

    return 0;
}

// funcao para imprimir o tabuleiro
void print_board() {
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){

            if(j == 0){
                printf("\n %c", aux_game_board[i][j]);
            }else{
                printf(" %c", aux_game_board[i][j]);
            }
        }
    }
}

// funcao para sortear os navios pelo tabuleiro
void draw_ships(){
    // 1 navio de quatro posicoes
    int verify = 0;
    while(verify != 1){
        int i = rand() % ROWS;
        int j = rand() % COLS;

        if(j + 3 < COLS){
            if(game_board[i][j] == '-' && game_board[i][j+1] == '-' && game_board[i][j+2] == '-' && game_board[i][j+3] == '-' && game_board[i][j+4] != 'w'){
                game_board[i][j] = 'w';
                game_board[i][j+1] = 'w';
                game_board[i][j+2] = 'w';
                game_board[i][j+3] = 'w';
                
                verify = verify + 1;
            }
        }else if(j - 3 >= 0){
            if(game_board[i][j] == '-' && game_board[i][j-1] == '-' && game_board[i][j-2] == '-' && game_board[i][j-3] == '-' && game_board[i][j-4] != 'w'){
                game_board[i][j] = 'w';
                game_board[i][j-1] = 'w';
                game_board[i][j-2] = 'w';
                game_board[i][j-3] = 'w';

                verify = verify + 1;
            }
        }
        indice++;
    }
    
    // 2 navios de tres posicoes
    verify = 0;
    while(verify != 2){
        int i = rand() % ROWS;
        int j = rand() % COLS;

        if(j + 2 < COLS){
            if(game_board[i][j] == '-' && game_board[i][j+1] == '-' && game_board[i][j+2] == '-' && game_board[i][j+3] != 'w'){
                game_board[i][j] = 'w';
                game_board[i][j+1] = 'w';
                game_board[i][j+2] = 'w';

                verify = verify + 1;
            }
        } else if(j - 2 >= 0){
            if(game_board[i][j] == '-' && game_board[i][j-1] == '-' && game_board[i][j-2] == '-' && game_board[i][j-3] != 'w'){
                game_board[i][j] = 'w';
                game_board[i][j-1] = 'w';
                game_board[i][j-2] = 'w';

                verify = verify + 1;
            }
        }
    }
    
    // 1 navio de duas posicoes
    verify = 0;
    while(verify != 1){
        int i = rand() % ROWS;
        int j = rand() % COLS;

        if(j + 1 < COLS){
            if(game_board[i][j] == '-' && game_board[i][j+1] == '-' && game_board[i][j+2] != 'w'){
                game_board[i][j] = 'w';
                game_board[i][j+1] = 'w';
                verify = verify + 1;
            }
        } else if(j - 1 >= 0){
            if(game_board[i][j] == '-' && game_board[i][j-1] == '-' && game_board[i][j-2] != 'w'){
                game_board[i][j] = 'w';
                game_board[i][j-1] = 'w';
                verify = verify + 1;
            }
        }
    }
    
    // 5 navios de uma posicao
    verify = 0;
    while(verify != 5){
        int i = rand() % ROWS;
        int j = rand() % COLS;

        if(game_board[i][j] == '-' && game_board[i][j+1] == '-' && game_board[i][j-1] == '-'){
            game_board[i][j] = 'w';
            verify = verify + 1;
        }
        
    }
}

// turno do jogador
void  player_turn(){    
    int verify = 0;
    while(verify != TURNS){

        // input rows e cols
        int linha, coluna;
        printf("\nDigite a linha: ");
        scanf("%d", &linha);
        printf("Digite a coluna: ");
        scanf("%d", &coluna);

        // humanizaçao
        linha = linha - 1;
        coluna = coluna - 1;

        // verificacao de acerto
        if(game_board[linha][coluna] == 'w'){
            game_board[linha][coluna] = 'x';
            aux_game_board[linha][coluna] = 'x';
            printf("\nTiro Certeiro!, Linha: %d, Coluna: %d", linha+1, coluna+1);
        } else if(game_board[linha][coluna] == '-'){
            game_board[linha][coluna] = 'o';
            aux_game_board[linha][coluna] = 'o';
            printf("\nTiro na agua!, Linha: %d, Coluna: %d", linha+1, coluna+1);
        }

        // imprimindo o tabuleiro
        print_board();

        // verificando vitoria
        verify++;
        if(player_win() == 0){
            printf("\nVoce Venceu!\n");
            return;  // Saia da função se o jogador ganhar
        }
        if(player_win() > 0 && indice == TURNS){
            printf("\nVoce Perdeu!\n");
        }
        // imprimindo a quantidade de tiros
        remaining_shots(verify, linha, coluna);
    }
}

// funcao para verificar a vitoria ou derrota
int player_win() {
    int contador = 0;
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(game_board[i][j] == 'w'){
                contador++;
            }
        }
    }
    return contador;
}

// funcao para os tiros restantes
void remaining_shots(int verify, int rows, int cols){
    if(verify > 0 ){
        if(TURNS - verify == 1){
            printf("\nVoce Tem %d Tiro Restante!", TURNS - verify);
        } else {
            printf("\nVoce Tem %d Tiros Restantes!", TURNS - verify);
        }
    }
}