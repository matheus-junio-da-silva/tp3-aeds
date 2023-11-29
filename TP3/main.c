#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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

typedef struct {
    int cor;
    int numero;
} Carta;

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
        default:
            return "Preta";
    }
}

// Fun��o para imprimir as cartas em colunas
void printCardsColumns(Carta cards[], int n) {
    for (int i = 0; i < n; i++) {
        printf("[%d]%s ", i + 1, nomeCor(cards[i].cor));

        if (cards[i].numero >= 1 && cards[i].numero <= 9) {
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
            }
        }

        printf("\n");
    }
}

// Fun��o para embaralhar as cartas
void shuffleCards(Carta cards[], int n) {
    srand(time(NULL));
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        // Troca as cartas[i] e cartas[j]
        Carta temp = cards[i];
        cards[i] = cards[j];
        cards[j] = temp;
        movimentacoes += 3;  // 3 movimenta��es foram realizadas
    }
}

// Fun��o para gerar uma carta aleat�ria
Carta gerarCartaAleatoria() {
    Carta carta;
    carta.cor = rand() % (PRETO + 1);  // Gera um n�mero aleat�rio de 0 a PRETO

    if (carta.cor == PRETO) {
        // Se for preto, escolhe aleatoriamente entre Coringa e +4
        carta.numero = (rand() % 2 == 0) ? CORINGA : MAIS_QUATRO;
    } else {
        // Se n�o for preto, escolhe aleatoriamente entre 1 e 12
        carta.numero = (rand() % 12) + 1;
    }

    return carta;
}

// Quick Sort
void quickSort(Carta cards[], int low, int high);

// Declara��o da fun��o partition
int partition(Carta cards[], int low, int high) {
    Carta pivot = cards[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        comparacoes++;  // Para cada compara��o
        // Compare primeiro as cores, em caso de igualdade compare os n�meros
        if (cards[j].cor < pivot.cor || (cards[j].cor == pivot.cor && cards[j].numero < pivot.numero)) {
            i++;

            // Troca as cartas[i] e cartas[j]
            Carta temp = cards[i];
            cards[i] = cards[j];
            cards[j] = temp;
            movimentacoes += 3;  // 3 movimenta��es foram realizadas
        }
    }

    // Troca as cartas[i + 1] e cartas[high]
    Carta temp = cards[i + 1];
    cards[i + 1] = cards[high];
    cards[high] = temp;
    movimentacoes += 3;  // 3 movimenta��es foram realizadas

    return i + 1;
}
// Bubble Sort
void bubbleSort(Carta cards[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;  // Para cada compara��o

            // Compare primeiro as cores, em caso de igualdade compare os n�meros
            if (cards[j].cor > cards[j + 1].cor ||
                (cards[j].cor == cards[j + 1].cor && cards[j].numero > cards[j + 1].numero)) {
                // Troca as cartas[j] e cartas[j + 1]
                Carta temp = cards[j];
                cards[j] = cards[j + 1];
                cards[j + 1] = temp;
                movimentacoes += 3;  // 3 movimenta��es foram realizadas
            }
        }
    }
}


// Quick Sort
void quickSort(Carta cards[], int low, int high) {
    if (low < high) {
        int pi = partition(cards, low, high);

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
        comparacoes++;  // Para cada compara��o
        // Compare primeiro as cores, em caso de igualdade compare os n�meros
        if (cards[left].cor > cards[largest].cor ||
            (cards[left].cor == cards[largest].cor && cards[left].numero > cards[largest].numero)) {
            largest = left;
        }
    }

    if (right < n) {
        comparacoes++;  // Para cada compara��o
        // Compare primeiro as cores, em caso de igualdade compare os n�meros
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
        movimentacoes += 3;  // 3 movimenta��es foram realizadas

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
        movimentacoes += 3;  // 3 movimenta��es foram realizadas

        heapify(cards, i, 0);
    }
}
void selectionSort(Carta cards[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;  // Para cada compara��o
            // Compare primeiro as cores, em caso de igualdade compare os n�meros
            if (cards[j].cor < cards[minIndex].cor ||
                (cards[j].cor == cards[minIndex].cor && cards[j].numero < cards[minIndex].numero)) {
                minIndex = j;
            }
        }
        // Troca as cartas[i] e cartas[minIndex]
        Carta temp = cards[i];
        cards[i] = cards[minIndex];
        cards[minIndex] = temp;
        movimentacoes += 3;  // 3 movimenta��es foram realizadas
    }
}

// Insertion Sort
void insertionSort(Carta cards[], int n) {
    for (int i = 1; i < n; i++) {
        Carta key = cards[i];
        int j = i - 1;

        while (j >= 0 && (cards[j].cor > key.cor ||
                          (cards[j].cor == key.cor && cards[j].numero > key.numero))) {
            comparacoes++;  // Para cada compara��o
            // Move as cartas[j] para a posi��o correta
            cards[j + 1] = cards[j];
            movimentacoes++;
            j--;
        }

        cards[j + 1] = key;
        movimentacoes++;  // 1 movimenta��o foi realizada
    }
}

// Merge Sort
void merge(Carta cards[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Cria arrays tempor�rios
    Carta leftArray[n1], rightArray[n2];

    // Copia os dados para os arrays tempor�rios
    for (int i = 0; i < n1; i++)
        leftArray[i] = cards[left + i];
    for (int j = 0; j < n2; j++)
        rightArray[j] = cards[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        comparacoes++;  // Para cada compara��o
        // Compare primeiro as cores, em caso de igualdade compare os n�meros
        if (leftArray[i].cor < rightArray[j].cor ||
            (leftArray[i].cor == rightArray[j].cor && leftArray[i].numero <= rightArray[j].numero)) {
            cards[k] = leftArray[i];
            i++;
        } else {
            cards[k] = rightArray[j];
            j++;
        }
        movimentacoes++;  // 1 movimenta��o foi realizada
        k++;
    }

    // Copia os elementos restantes, se houver
    while (i < n1) {
        cards[k] = leftArray[i];
        movimentacoes++;  // 1 movimenta��o foi realizada
        i++;
        k++;
    }

    while (j < n2) {
        cards[k] = rightArray[j];
        movimentacoes++;  // 1 movimenta��o foi realizada
        j++;
        k++;
    }
}

void mergeSort(Carta cards[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Ordena as duas metades
        mergeSort(cards, left, mid);
        mergeSort(cards, mid + 1, right);

        // Junta as duas metades ordenadas
        merge(cards, left, mid, right);
    }
}

int readCardsFromFile(const char* filename, Carta cards[], int* n) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    fscanf(file, "%d", n);

    for (int conjunto = 0; conjunto < *n; conjunto++) {
        for (int i = 0; i < 10; i++) {
            char corStr[10];
            char numeroStr[5];

            // Leitura de cor e n�mero
            if (fscanf(file, " (%9[^ ] %[^(])", corStr, numeroStr) != 2) {
                printf("Erro ao ler a carta %d do conjunto %d.\n", i + 1, conjunto + 1);
                fclose(file);
                return 0;
            }

            // Tradu��o da cor para o c�digo correspondente
            if (strcmp(corStr, "Azul") == 0) {
                cards[conjunto * 10 + i].cor = AZUL;
            } else if (strcmp(corStr, "Amarelo") == 0) {
                cards[conjunto * 10 + i].cor = AMARELO;
            } else if (strcmp(corStr, "Vermelho") == 0) {
                cards[conjunto * 10 + i].cor = VERMELHO;
            } else if (strcmp(corStr, "Verde") == 0) {
                cards[conjunto * 10 + i].cor = VERDE;
            } else if (strcmp(corStr, "Preto") == 0) {
                // Verificar se � uma carta especial ou normal
                if (strcmp(numeroStr, "Coringa") == 0) {
                    cards[conjunto * 10 + i].cor = PRETO;
                    cards[conjunto * 10 + i].numero = CORINGA;
                } else {
                    char sinal, num;
                    sscanf(numeroStr, "%c%c", &sinal, &num);
                    if (sinal == '+' && num == '4') {
                        cards[conjunto * 10 + i].cor = PRETO;
                        cards[conjunto * 10 + i].numero = MAIS_QUATRO;
                    } else {
                        printf("Erro: Carta preta invalida no arquivo: %s\n", numeroStr);
                        fclose(file);
                        return 0;
                    }
                }
            } else {
                // Se n�o � preto, ent�o � uma carta normal com n�mero
                cards[conjunto * 10 + i].numero = atoi(numeroStr);
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
            mergeSort(cards, 0, n - 1);
            end_time = clock();
            elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
            printf("\nCartas Ordenadas (Merge Sort):\n");
            break;
        default:
            printf("Op��o invalida.\n");
            return;
    }

    printCardsColumns(cards, n);
    printf("\nNumero de Comparacoes: %lld\n", comparacoes);
    printf("Numero de Movimentacoes: %lld\n", movimentacoes);
    printf("Tempo de execucao: %f segundos\n", elapsed_time);
}
void ordenarConjuntos(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    int numConjuntos;
    fscanf(file, "%d", &numConjuntos);

    for (int conjunto = 0; conjunto < numConjuntos; conjunto++) {
        Carta conjuntoCartas[10];

        for (int i = 0; i < 10; i++) {
            char corStr[10];
            char numeroStr[20];

            if (fscanf(file, " (%9[^ ] %[^(])", corStr, numeroStr) != 2) {
                printf("Erro ao ler a carta %d do conjunto %d.\n", i + 1, conjunto + 1);
                fclose(file);
                return;
            }

            if (strcmp(corStr, "Azul") == 0) {
                conjuntoCartas[i].cor = AZUL;
            } else if (strcmp(corStr, "Amarelo") == 0) {
                conjuntoCartas[i].cor = AMARELO;
            } else if (strcmp(corStr, "Vermelho") == 0) {
                conjuntoCartas[i].cor = VERMELHO;
            } else if (strcmp(corStr, "Verde") == 0) {
                conjuntoCartas[i].cor = VERDE;
            } else if (strcmp(corStr, "Preto") == 0) {
                if (strcmp(numeroStr, "Coringa") == 0) {
                    conjuntoCartas[i].cor = PRETO;
                    conjuntoCartas[i].numero = CORINGA;
                } else if (strcmp(numeroStr, "+4") == 0) {
                    conjuntoCartas[i].cor = PRETO;
                    conjuntoCartas[i].numero = MAIS_QUATRO;
                } else {
                    printf("Erro: Carta preta inv�lida no arquivo.\n");
                    fclose(file);
                    return;
                }
            } else {
                conjuntoCartas[i].cor = atoi(corStr);
                conjuntoCartas[i].numero = atoi(numeroStr);
            }
        }

        // Ordena o conjunto de cartas
        // Voc� pode escolher o algoritmo de ordena��o aqui
        // Vou usar o Bubble Sort como exemplo, mas voc� pode substituir por outro
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9 - i; j++) {
                if (conjuntoCartas[j].cor > conjuntoCartas[j + 1].cor ||
                    (conjuntoCartas[j].cor == conjuntoCartas[j + 1].cor &&
                     conjuntoCartas[j].numero > conjuntoCartas[j + 1].numero)) {
                    Carta temp = conjuntoCartas[j];
                    conjuntoCartas[j] = conjuntoCartas[j + 1];
                    conjuntoCartas[j + 1] = temp;
                }
            }
        }

        // Imprime as cartas ordenadas do conjunto
        printf("\nConjunto %d - Cartas Ordenadas:\n", conjunto + 1);
        printCardsColumns(conjuntoCartas, 10);
    }

    fclose(file);
}
int main() {
    Carta cards[100]; // Ajuste o tamanho conforme necess�rio
    int n=10, opcaoAlgoritmo;

    printf("Escolha o modo:\n");
    printf("1 - Modo Interativo\n");
    printf("2 - Modo Arquivo\n");

    int modo;
    scanf("%d", &modo);

    if (modo == 1) {
        for (int i = 0; i < n; i++) {
            cards[i] = gerarCartaAleatoria();
        }
    } else if (modo == 2) {
        if (!readCardsFromFile("teste.txt", cards, &n)) {
            return 1;
        }
    } else {
        printf("Modo inv�lido. Encerrando o programa.\n");
        return 1;
    }

    printf("\nCartas Iniciais:\n");
    printCardsColumns(cards, n);

    // Embaralha as cartas
    shuffleCards(cards, n);
    printf("\nCartas Embaralhadas:\n");
    printCardsColumns(cards, n);

    // Escolhe o algoritmo de ordena��o
    printf("\nEscolha o algoritmo de ordenacao:\n");
    printf("1 - Bubble Sort\n");
    printf("2 - Quick Sort\n");
    printf("3 - Heap Sort\n");
    printf("4 - Selection Sort\n");
    printf("5 - Insertion Sort\n");
    printf("6 - Merge Sort\n");

    scanf("%d", &opcaoAlgoritmo);
    escolherAlgoritmo(cards, n, opcaoAlgoritmo);

    return 0;
}
