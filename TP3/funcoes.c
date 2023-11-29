#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include "cartas.h"

#define VERDE 0
#define AMARELO 1
#define VERMELHO 2
#define AZUL 3
#define PRETO 4

#define PULAR 10
#define VOLTAR 11
#define MAIS_DOIS 12
#define CORINGA 13
#define MAIS_QUATRO 14

long long comparacoes = 0;
long long movimentacoes = 0;

const char* nomeCor(int cor) {
    switch (cor) {
        case VERDE:
            return "Verde";
        case AMARELO:
            return "Amarelo";
        case VERMELHO:
            return "Vermelho";
        case AZUL:
            return "Azul";
        case PRETO:
            return "Preto";
        default:
            return "Cor Inválida";
    }
}

// Função para imprimir as cartas em colunas
void PrintarCartas(Carta cards[], int n) {
    for (int i = 0; i < n; i++) {
        printf("[%d]%s ", i + 1, nomeCor(cards[i].cor));

        if (cards[i].numero >= 0 && cards[i].numero <= 9) {
            printf("%d", cards[i].numero);
        } else {
            switch (cards[i].numero) {
                case 10:
                    printf("Voltar");
                    break;
                case 11:
                    printf("Pular");
                    break;
                case 12:
                    printf("+2");
                    break;
                case 13:
                    printf("Coringa");
                    break;
                case 14:
                    printf("+4");
                    break;
                default:
                    printf("Erro: Numero invalido");
                    printf("%d", cards[i].numero);
            }
        }

        printf("\n");
    }
}

// Função para embaralhar as cartas
void embaralhar(Carta cards[], int n) {
    srand(time(NULL));
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        // Troca as cartas[i] e cartas[j]
        Carta temp = cards[i];
        cards[i] = cards[j];
        cards[j] = temp;
        movimentacoes += 3;  // 3 movimentações foram realizadas
    }
}

// Função para gerar uma carta aleatória
Carta gerarCartaAleatoria() {
    Carta carta;
    carta.cor = rand() % 4;    // Gera um número aleatório de 0 a 3 para representar uma cor
    carta.numero = rand() % 12 + 1; // Gera um número aleatório de 1 a 12 para representar um número de carta
    return carta;
}

// Quick Sort
void quickSort(Carta cards[], int low, int high);

// Declaração da função particao
int particao(Carta cards[], int low, int high) {
    Carta pivot = cards[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        comparacoes++;  // Para cada comparação
        // Compare primeiro as cores, em caso de igualdade compare os números
        if (cards[j].cor < pivot.cor || (cards[j].cor == pivot.cor && cards[j].numero < pivot.numero)) {
            i++;

            // Troca as cartas[i] e cartas[j]
            Carta temp = cards[i];
            cards[i] = cards[j];
            cards[j] = temp;
            movimentacoes += 3;  // 3 movimentações foram realizadas
        }
    }

    // Troca as cartas[i + 1] e cartas[high]
    Carta temp = cards[i + 1];
    cards[i + 1] = cards[high];
    cards[high] = temp;
    movimentacoes += 3;  // 3 movimentações foram realizadas

    return i + 1;
}
// Bubble Sort
void bubbleSort(Carta cards[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;  // Para cada comparação

            // Compare primeiro as cores, em caso de igualdade compare os números
            if (cards[j].cor > cards[j + 1].cor ||
                (cards[j].cor == cards[j + 1].cor && cards[j].numero > cards[j + 1].numero)) {
                // Troca as cartas[j] e cartas[j + 1]
                Carta temp = cards[j];
                cards[j] = cards[j + 1];
                cards[j + 1] = temp;
                movimentacoes += 3;  // 3 movimentações foram realizadas
            }
        }
    }
}


// Quick Sort
void quickSort(Carta cards[], int low, int high) {
    if (low < high) {
        int pi = particao(cards, low, high);

        quickSort(cards, low, pi - 1);
        quickSort(cards, pi + 1, high);
    }
}

// Heap Sort
void heapify(Carta cards[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n) {
        comparacoes++;  // Para cada comparação
        // Compare primeiro as cores, em caso de igualdade compare os números
        if (cards[left].cor > cards[largest].cor ||
            (cards[left].cor == cards[largest].cor && cards[left].numero > cards[largest].numero)) {
            largest = left;
        }
    }

    if (right < n) {
        comparacoes++;  // Para cada comparação
        // Compare primeiro as cores, em caso de igualdade compare os números
        if (cards[right].cor > cards[largest].cor ||
            (cards[right].cor == cards[largest].cor && cards[right].numero > cards[largest].numero)) {
            largest = right;
        }
    }

    if (largest != i) {
        // Troca as cartas[i] e cartas[largest]
        Carta temp = cards[i];
        cards[i] = cards[largest];
        cards[largest] = temp;
        movimentacoes += 3;  // 3 movimentações foram realizadas

        heapify(cards, n, largest);
    }
}

// Heap Sort
void heapSort(Carta cards[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(cards, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        // Troca as cartas[0] e cartas[i]
        Carta temp = cards[0];
        cards[0] = cards[i];
        cards[i] = temp;
        movimentacoes += 3;  // 3 movimentações foram realizadas

        heapify(cards, i, 0);
    }
}
void selectionSort(Carta cards[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;  // Para cada comparação
            // Compare primeiro as cores, em caso de igualdade compare os números
            if (cards[j].cor < cards[minIndex].cor ||
                (cards[j].cor == cards[minIndex].cor && cards[j].numero < cards[minIndex].numero)) {
                minIndex = j;
            }
        }
        // Troca as cartas[i] e cartas[minIndex]
        Carta temp = cards[i];
        cards[i] = cards[minIndex];
        cards[minIndex] = temp;
        movimentacoes += 3;  // 3 movimentações foram realizadas
    }
}

// Insertion Sort
void insertionSort(Carta cards[], int n) {
    for (int i = 1; i < n; i++) {
        Carta key = cards[i];
        int j = i - 1;

        while (j >= 0 && (cards[j].cor > key.cor ||
                          (cards[j].cor == key.cor && cards[j].numero > key.numero))) {
            comparacoes++;  // Para cada comparação
            // Move as cartas[j] para a posição correta
            cards[j + 1] = cards[j];
            movimentacoes++;
            j--;
        }

        cards[j + 1] = key;
        movimentacoes++;  // 1 movimentação foi realizada
    }
}

// Sheel Sort
void shellSort(Carta cards[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            Carta temp = cards[i];
            int j;

            for (j = i; j >= gap && (temp.cor < cards[j - gap].cor ||
                    (temp.cor == cards[j - gap].cor && temp.numero < cards[j - gap].numero)); j -= gap) {
                comparacoes++;
                cards[j] = cards[j - gap];
                movimentacoes++;
            }

            cards[j] = temp;
            movimentacoes++;
        }
    }
}



int lerCartaEspecial(const char* specialCard) {
    if (strcmp(specialCard, "Voltar") == 0) {
        return VOLTAR;
    } else if (strcmp(specialCard, "Pular") == 0) {
        return PULAR;
    } else if (strcmp(specialCard, "+2") == 0) {
        return MAIS_DOIS;
    } else {
        // Retorne -1 ou outro valor para indicar um erro
        return -1;
    }
}

int LerCartasArquivo(const char* filename, Carta cards[], int* n) { // n = 10 tamanho do conjunto
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    fscanf(file, "%d", n);

    for (int conjunto = 0; conjunto < *n; conjunto++) { // n = 10
        for (int i = 0; i < 10; i++) {
            char corStr[10];
            char numeroStr[10];

            // Leitura de cor e número
            if (fscanf(file, " (%9[^ ] %[^)])", corStr, numeroStr) != 2) {
                printf("Erro ao ler a carta %d do conjunto %d.\n", i + 1, conjunto + 1);
                fclose(file);
                return 0;
            }

            //printf("corStr: %s, numeroStr: %s\n", corStr, numeroStr);

            // Tradução da cor para o código correspondente
            if (strcmp(corStr, "Azul") == 0) {
                cards[conjunto * 10 + i].cor = AZUL; // * 10 pq cada conjunto tem 10 cartas

                if (strcmp(numeroStr, "Pular") == 0) {
                    cards[conjunto * 10 + i].numero = PULAR;
                } else if (strcmp(numeroStr, "Voltar") == 0) {
                    cards[conjunto * 10 + i].numero = VOLTAR;
                } else if (strcmp(numeroStr, "+2") == 0) {
                    cards[conjunto * 10 + i].numero = MAIS_DOIS;
                } else {
                    cards[conjunto * 10 + i].numero = atoi(numeroStr);
                }

                //printf("Cor: %d, Numero: %d\n", cards[conjunto * 10 + i].cor, cards[conjunto * 10 + i].numero);


            } else if (strcmp(corStr, "Amarelo") == 0) {
                cards[conjunto * 10 + i].cor = AMARELO;

                if (strcmp(numeroStr, "Pular") == 0) {
                    cards[conjunto * 10 + i].numero = PULAR;
                } else if (strcmp(numeroStr, "Voltar") == 0) {
                    cards[conjunto * 10 + i].numero = VOLTAR;

                } else if (strcmp(numeroStr, "+2") == 0) {
                    cards[conjunto * 10 + i].numero = MAIS_DOIS;
                } else {
                    cards[conjunto * 10 + i].numero = atoi(numeroStr);

                }

                //printf("Cor: %d, Numero: %d\n", cards[conjunto * 10 + i].cor, cards[conjunto * 10 + i].numero);


            } else if (strcmp(corStr, "Vermelho") == 0) {
                cards[conjunto * 10 + i].cor = VERMELHO;

                if (strcmp(numeroStr, "Pular") == 0) {
                    cards[conjunto * 10 + i].numero = PULAR;
                } else if (strcmp(numeroStr, "Voltar") == 0) {
                    cards[conjunto * 10 + i].numero = VOLTAR;
                } else if (strcmp(numeroStr, "+2") == 0) {
                    cards[conjunto * 10 + i].numero = MAIS_DOIS;
                } else {
                    cards[conjunto * 10 + i].numero = atoi(numeroStr);
                }

                //printf("Cor: %d, Numero: %d\n", cards[conjunto * 10 + i].cor, cards[conjunto * 10 + i].numero);


            } else if (strcmp(corStr, "Verde") == 0) {
                cards[conjunto * 10 + i].cor = VERDE;

                if (strcmp(numeroStr, "Pular") == 0) {
                    cards[conjunto * 10 + i].numero = PULAR;
                } else if (strcmp(numeroStr, "Voltar") == 0) {
                    cards[conjunto * 10 + i].numero = VOLTAR;
                } else if (strcmp(numeroStr, "+2") == 0) {
                    cards[conjunto * 10 + i].numero = MAIS_DOIS;
                } else {
                    cards[conjunto * 10 + i].numero = atoi(numeroStr);
                }

                //printf("Cor: %d, Numero: %d\n", cards[conjunto * 10 + i].cor, cards[conjunto * 10 + i].numero);


            } else if (strcmp(corStr, "Preto") == 0) {
                // Verificar se é uma carta especial ou normal
                if (strcmp(numeroStr, "Coringa") == 0) {

                    cards[conjunto * 10 + i].cor = PRETO;
                    cards[conjunto * 10 + i].numero = CORINGA;

                } else if (strcmp(numeroStr, "+4") == 0) {

                    cards[conjunto * 10 + i].cor = PRETO;
                    cards[conjunto * 10 + i].numero = MAIS_QUATRO;

                } else {
                    // Lidar com outras cartas pretas aqui (pode ser um número ou outro tipo)
                    //cards[conjunto * 10 + i].cor = PRETO;
                    //cards[conjunto * 10 + i].numero = atoi(numeroStr); // ou outra lógica para tratar cartas pretas não reconhecidas


                    printf("Erro: Carta preta invalida no arquivo.\n");
                    fclose(file);
                    return 0;


                }
            } else {
                // Se não é preto, então é uma carta normal com número
                //cards[conjunto * 10 + i].numero = atoi(numeroStr);

            }
        }
    }

    fclose(file);
    return 1;
}


void escolherAlgoritmo(Carta cards[], int n, int opcao) {
    clock_t start_time, end_time;
    double elapsed_time;

    switch (opcao) {
        case 1:
            start_time = clock();
            bubbleSort(cards, n);
            end_time = clock();
            elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
            printf("\nCartas Ordenadas (Bubble Sort):\n");
            break;
        case 2:
            start_time = clock();
            quickSort(cards, 0, n - 1);
            end_time = clock();
            elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
            printf("\nCartas Ordenadas (Quick Sort):\n");
            break;
        case 3:
            start_time = clock();
            heapSort(cards, n);
            end_time = clock();
            elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
            printf("\nCartas Ordenadas (Heap Sort):\n");
            break;
        case 4:
            start_time = clock();
            selectionSort(cards, n);
            end_time = clock();
            elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
            printf("\nCartas Ordenadas (Selection Sort):\n");
            break;
        case 5:
            start_time = clock();
            insertionSort(cards, n);
            end_time = clock();
            elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
            printf("\nCartas Ordenadas (Insertion Sort):\n");
            break;
        case 6:
            start_time = clock();
            shellSort(cards, n);
            end_time = clock();
            elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
            printf("\nCartas Ordenadas (Sheel Sort):\n");
            break;
        default:
            printf("Opção invalida.\n");
            return;
    }

    PrintarCartas(cards, n);
    printf("\nNumero de Comparacoes: %I64d\n", movimentacoes);
    printf("Numero de Movimentacoes: %I64d\n", comparacoes);
    printf("Tempo de execucao: %f segundos\n", elapsed_time);
}

void aplicar_algoritmo(Carta cards[], int n) {
    clock_t start_time, end_time;
    double elapsed_time;
    comparacoes = 0;
    movimentacoes = 0;

    printf("--------------INICIO CONJUNTO.--------------\n");

    start_time = clock();
    bubbleSort(cards, n);
    end_time = clock();
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("\nCartas Ordenadas (Bubble Sort):\n");
    PrintarCartas(cards, n);
    printf("\nNumero de Comparacoes: %I64d\n", movimentacoes);
    printf("Numero de Movimentacoes: %I64d\n", comparacoes);
    printf("Tempo de execucao: %f segundos\n", elapsed_time);

    comparacoes = 0;
    movimentacoes = 0;
    embaralhar
(cards, n);
    printf("\nCartas embaralhadas:\n");
    PrintarCartas(cards, n);
    start_time = clock();
    quickSort(cards, 0, n - 1);
    end_time = clock();
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("\nCartas Ordenadas (Quick Sort):\n");
    PrintarCartas(cards, n);
    printf("\nNumero de Comparacoes: %I64d\n", movimentacoes);
    printf("Numero de Movimentacoes: %I64d\n", comparacoes);
    printf("Tempo de execucao: %f segundos\n", elapsed_time);

    comparacoes = 0;
    movimentacoes = 0;
    embaralhar
(cards, n);
    printf("\nCartas embaralhadas:\n");
    PrintarCartas(cards, n);
    start_time = clock();
    heapSort(cards, n);
    end_time = clock();
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("\nCartas Ordenadas (Heap Sort):\n");
    PrintarCartas(cards, n);
    printf("\nNumero de Comparacoes: %I64d\n", movimentacoes);
    printf("Numero de Movimentacoes: %I64d\n", comparacoes);
    printf("Tempo de execucao: %f segundos\n", elapsed_time);

    comparacoes = 0;
    movimentacoes = 0;
    embaralhar
(cards, n);
    printf("\nCartas embaralhadas:\n");
    PrintarCartas(cards, n);
    start_time = clock();
    selectionSort(cards, n);
    end_time = clock();
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("\nCartas Ordenadas (Selection Sort):\n");
    PrintarCartas(cards, n);
    printf("\nNumero de Comparacoes: %I64d\n", movimentacoes);
    printf("Numero de Movimentacoes: %I64d\n", comparacoes);
    printf("Tempo de execucao: %f segundos\n", elapsed_time);

    comparacoes = 0;
    movimentacoes = 0;
    embaralhar
(cards, n);
    printf("\nCartas embaralhadas:\n");
    PrintarCartas(cards, n);
    start_time = clock();
    insertionSort(cards, n);
    end_time = clock();
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("\nCartas Ordenadas (Insertion Sort):\n");
    PrintarCartas(cards, n);
    printf("\nNumero de Comparacoes: %I64d\n", movimentacoes);
    printf("Numero de Movimentacoes: %I64d\n", comparacoes);
    printf("Tempo de execucao: %f segundos\n", elapsed_time);

    comparacoes = 0;
    movimentacoes = 0;
    embaralhar
(cards, n);
    printf("\nCartas embaralhadas:\n");
    PrintarCartas(cards, n);
    start_time = clock();
    shellSort(cards, n);
    end_time = clock();
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("\nCartas Ordenadas (Shell Sort):\n");
    PrintarCartas(cards, n);
    printf("\nNumero de Comparacoes: %I64d\n", movimentacoes);
    printf("Numero de Movimentacoes: %I64d\n", comparacoes);
    printf("Tempo de execucao: %f segundos\n", elapsed_time);

    printf("--------------FIM CONJUNTO.--------------\n");

    return;
    }





//Função gotoxy
void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
}

