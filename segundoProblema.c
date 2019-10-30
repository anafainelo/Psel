/*
    Ana Carolina Fainelo de Oliveira 
    28/10/2019
    
    Programa que recebe como entrada uma configuracao de jogo da velha e indica quem ganhou, se houve empate,
    se a configuracao eh invalida ou quem eh o proximo a jogar.
*/

#include <stdio.h>
#include <stdlib.h>

#define FIRST  0
#define SECOND 9
#define NO_WINNWER -1

//-----------------------------------------------------------------------------------------------------------------------
char getWinner(char matrix[3][3]){
    int i, j;
    char winner = NO_WINNWER; //ninguem venceu ainda

    /*  A seguir, faremos a verificacao com todas as possibilidades para garantir que
        nao haja mais de uma vitoria, como nos seguintes casos (configuracao invalida):
        |X|X|X|     |X|X|X|     |0|X|X|     
        |X|0|X|     |X|0|0|     |0|0|0|
        |0|0|0|     |X|0|0|     |X|X|0|
    */

    //percorrendo linhas e colunas matriz procurando um vencedor
    for(i = 0; i < 3; i++){
        //se houver (vencedor em alguma linha) OU (vencedor em alguma coluna)
        if((matrix[i][0] == matrix[i][1] && matrix [i][1] == matrix[i][2]) 
            || (matrix[0][i] == matrix[1][i] && matrix [1][i] == matrix[2][i]) ){
           
            if(matrix[i][i] == 'X') winner += 1;
            else if(matrix[i][i] == '0') winner += 10;
        }
    }

    //se houver (vencedor na diagonal principal) OU (vencedor na outra diagonal)
    if((matrix[0][0] == matrix[1][1] && matrix[1][1]==matrix[2][2]) 
        || (matrix[0][2]==matrix[1][1] && matrix[1][1]==matrix[2][0]) ){
        
        if(matrix[1][1] == 'X') winner += 1;
        else if(matrix[1][1] == '0') winner += 10;
    }



    return winner;
}

//-----------------------------------------------------------------------------------------------------------------------
int main(){
    char matrix[3][3];
    int i, j, qtdX = 0, qtd0 = 0;
    char winner, trash;


    //lendo matriz de entrada
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            scanf("%c", &matrix[i][j] );
            //contando a quantidade de X's e Y's
            if(matrix[i][j] == 'X') qtdX++;
            else if (matrix[i][j] == '0') qtd0++;
        }
        scanf("%c", &trash); //pegando o \n (enter)
    }


    //a diferenca entre a quantidade de X's e 0's deve ser no maximo 1, senao a configuracao eh invalida
    i = (qtdX < qtd0)? qtd0 - qtdX : qtdX - qtd0; //Pegando o  modulo da diferenca das quantidades
    if (i > 1){
        printf("inválido\n");
    }
    //verifico na matriz quem ganhou (primeiro, segundo, empate)
    else {
       winner = getWinner(matrix);

        if(winner == FIRST)
           printf("primeiro_venceu\n");
        else if (winner == SECOND)
            printf("segundo_venceu\n");
        else if(winner == NO_WINNWER){
            //se ainda nao houver vencedor e a matriz nao estiver preenchida, verifico qual eh o proximo jogador:
            if(qtdX + qtd0 < 9){
                if(qtdX >  qtd0) printf("segundo\n");
                else printf("primeiro\n");
            }
            //se nao houver vencedor mas a matriz esta preenchida, deu empate:
            else{
                printf("empate\n");
            }
        }
        //caso em que ha mais de uma possibilidade de vitoria:
        else{
            printf("inválido\n");
        }

    }

}