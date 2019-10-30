/*
    Ana Carolina Fainelo de Oliveira 
    28/10/2019
    
    *Programa que calcula o minimo custo para dois pontos em um eixo X se encontrarem.
    *O eixo X eh de numeros inteiros, um passo significa incrementar ou decrementar a posicao do ponto em 1 neste eixo.
    *Primeiro passo: custo 1; segundo passo: custo 2 ; terceiro passo: custo 3 .... assim por diante.
    *Ou seja, se um ponto der 3 passos, o custo sera de 1+2+3 = 6.
*/

#include <stdlib.h>
#include <stdio.h>

int main(){
    int i, a, b, dist, cost;

    //lendo entrada
    scanf("%d", &a);
    scanf("%d", &b);

    //calculando a distancia em modulo dos pontos
    dist = (a < b)? b-a : a-b;

    //ambos os pontos andarao um em direcao ao outro, andando a mesma distancia:
    cost = 0;
    for(i = 1; i <= (int)(dist/2); i++){
        cost += i;
    }
    cost *= 2;

    //se a distancia for um numero impar, um dos pontos devera andar um passo a mais
    if(dist % 2 != 0){
        cost = cost + i;
    }

    printf("%d\n", cost);
    
}