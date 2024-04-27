/******************
*
* Daniel Arguello de Souza
* Trabalho 1
* Professor(a): Diego Rubert
*
*/

#include <stdio.h>
#define MAX 1004

typedef struct {
        int numero;         /* Número da capivara = posição na largada */
        int ultrapass;      /* Quantidade de ultrapassagens feitas */
    } capivara;

void fazer_ultrapassagem(capivara vetor_capivaras[], int numero_ultrapassagem, int n){
    int i, indice;
    capivara aux;

    /* Procura índice da Capivara que fez a Ultrapassagem */
    for(i = 0; i < n; i++){
        if(vetor_capivaras[i].numero == numero_ultrapassagem)
             indice = i;
    }

    /* Contabiliza um ponto  = 1 ultrapassagem */
    vetor_capivaras[indice].ultrapass += 1;

    /* Realiza a Ultrapassagem */
    aux = vetor_capivaras[indice - 1];
    vetor_capivaras[indice - 1] = vetor_capivaras[indice];
    vetor_capivaras[indice] = aux;
}

void merge(capivara vetor_capivaras[], int esquerda, int meio, int direita){
    int i, j, k;
    int n1 = meio - esquerda + 1;
    int n2 = direita - meio;

    /* Vetores temporarios */
    capivara L[n1], R[n2];

    /* Passa os dados para L[] e R[] */
    for (i = 0; i < n1; i++)
        L[i] = vetor_capivaras[esquerda + i];
    for (j = 0; j < n2; j++)
        R[j] = vetor_capivaras[meio + 1 + j];

    /* Vetores temporários de volta em vetor_capivaras[] */
    i = 0;
    j = 0;
    k = esquerda;

    while (i < n1 && j < n2) {
        if (L[i].ultrapass > R[j].ultrapass) {
            vetor_capivaras[k] = L[i];
            i++;
        } else if (L[i].ultrapass < R[j].ultrapass) {
            vetor_capivaras[k] = R[j];
            j++;
        } else {

            /* Em caso de Empate nas Ultrapassagens, Desempate pelo Número da Capivara */
            if (L[i].numero < R[j].numero) {
                vetor_capivaras[k] = L[i];
                i++;
            } else {
                vetor_capivaras[k] = R[j];
                j++;
            }
        }
        k++;
    }

    /* Copia os elementos restantes de L[], caso haja */
    while (i < n1) {
        vetor_capivaras[k] = L[i];
        i++;
        k++;
    }

    /* Copia os elementos restantes de R[], caso haja */
    while (j < n2) {
        vetor_capivaras[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(capivara vetor_capivaras[], int esquerda, int direita){
    if(esquerda < direita){
        int meio = esquerda + (direita - esquerda) / 2;

        mergeSort(vetor_capivaras, esquerda, meio);
        mergeSort(vetor_capivaras, meio + 1, direita);

        /* Combina as metades classificadas */
        merge(vetor_capivaras, esquerda, meio, direita);
    }
}

int main(){
    int n;
    int i, numero_ultrapassagem;

    /* Entrada - Número de Participantes */
    printf("Insira a quantidade de Capivaras:\n");
    scanf("%d", &n);

    capivara vetor_capivaras[MAX];

    /* Define o numero das capivaras de 1 a n */
    for(i = 0; i < n; i++){
        vetor_capivaras[i].numero = i + 1;
    }

    /* Quebra de linha */
    printf("\n");

    /* Capivara X faz uma Ultrapassagem */
    printf("Insira agora as ultrapassagens (Número da Capivara):\n");
    while(scanf("%d", &numero_ultrapassagem) != EOF){

        fazer_ultrapassagem(vetor_capivaras, numero_ultrapassagem, n);
        /* Ultrapassagem feita */
    }

    /* Quebra de linha */
    printf("\n");

    /* Fim das Ultrapassagens */

    /* Imprime a ordem de Chegada */
    printf("**** ORDEM DE CHEGADA ****\n");

    for(i = 0; i < n; i++){
        printf("%d ", vetor_capivaras[i].numero);
    }

    /* Quebra de linha */
    printf("\n");

    /* Contagem das Ultrapassagens e Classificação das Capivaras (MergeSort) */

    /* Quebra de linha */
    printf("\n");

    mergeSort(vetor_capivaras, 0, n - 1);

    /* Imprime a Classificação das Capivaras */
    printf("***** CLASSIFICACAO *****\n");

    for(i = 0; i < n; i++){
        printf("%d ", vetor_capivaras[i].numero);
    }
    /* Quebra de linha */
    printf("\n");
}
