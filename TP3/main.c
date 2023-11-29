#include "cartas.h"
#include "funcoes.c"

int main() {
    printf("\n\n");
    gotoxy(55,19);
    printf("       dP     dP 888888ba   .88888.  \n");
    gotoxy(55,20);
    printf("       88     88 88    `8b d8'   `8b \n");
    gotoxy(55,21);
    printf("       88     88 88     88 88     88          \n");
    gotoxy(55,22);
    printf("       88     88 88     88 88     88        \n");
    gotoxy(55,23);
    printf("       Y8.   .8P 88     88 Y8.   .8P         \n");
    gotoxy(55,24);
    printf("       Y8.   .8P 88     88 Y8.   .8P         \n");
    gotoxy(55,25);
    printf("       `Y88888P' dP     dP  `8888P'   \n");
    gotoxy(55,26);
    printf("       oooooooooooooooooooooooooooooo     \n\n");

    Carta cards[100]; // Ajuste o tamanho conforme necessário
    int n=10, opcaoAlgoritmo; // n = 10 é o tamanho do conjunto

    printf("Escolha o modo:\n");
    printf("1 - (Ponto extra) Modo Interativo: escolher algoritmo individualmente\n");
    printf("2 - (Ponto extra) Modo Arquivo: Todos conjuntos ordenados juntos\n");
    printf("3 - Modo Arquivo: Cada conjunto ordenado separadamente aplicando todas ordenacoes\n");
    printf("4 - Modo Interativo: Aplicando todas ordenacoes no conjunto criado\n");

    int modo;
    scanf("%d", &modo);

    if (modo == 1) {
        for (int i = 0; i < n; i++) {
            cards[i] = gerarCartaAleatoria();
        }

        printf("\nCartas Iniciais:\n");
        printf("%d", n);
        PrintarCartas(cards, n);

        // Embaralha as cartas
        embaralhar(cards, n);
        printf("\nCartas Embaralhadas:\n");
        PrintarCartas(cards, n);

        // Escolhe o algoritmo de ordenação
        printf("\nEscolha o algoritmo de ordenacao:\n");
        printf("1 - Bubble Sort\n");
        printf("2 - Quick Sort\n");
        printf("3 - Heap Sort\n");
        printf("4 - Selection Sort\n");
        printf("5 - Insertion Sort\n");
        printf("6 - Shell Sort\n");

        scanf("%d", &opcaoAlgoritmo);
        escolherAlgoritmo(cards, n, opcaoAlgoritmo);

    } else if (modo == 2) {
        if (!LerCartasArquivo("teste.txt", cards, &n)) {
            return 1;
        }

        printf("\nCartas Iniciais:\n");
        printf("%d", n * 10);
        PrintarCartas(cards, n * 10); // n aqui é 3 pelo arquivo * 10 do conjunto

        // Embaralha as cartas
       embaralhar(cards, n * 10);
        printf("\nCartas Embaralhadas:\n");
        PrintarCartas(cards, n * 10);

        // Escolhe o algoritmo de ordenação
        printf("\nEscolha o algoritmo de ordenacao:\n");
        printf("1 - Bubble Sort\n");
        printf("2 - Quick Sort\n");
        printf("3 - Heap Sort\n");
        printf("4 - Selection Sort\n");
        printf("5 - Insertion Sort\n");
        printf("6 - Shell Sort\n");

        scanf("%d", &opcaoAlgoritmo);
        escolherAlgoritmo(cards, n * 10, opcaoAlgoritmo);

    } else if (modo == 3) {
        if (!LerCartasArquivo("teste.txt", cards, &n)) {
            return 1;
        }


        // Loop para processar cada conjunto individualmente
        for (int conjunto = 0; conjunto < n; conjunto++) {
            printf("\n--------------(Conjunto %d):--------------\n", conjunto + 1);
            PrintarCartas(cards + conjunto * 10, 10);
            // Embaralha as cartas do conjunto atual
            embaralhar(cards + conjunto * 10, 10);

            printf("\nCartas Embaralhadas (Conjunto %d):\n", conjunto + 1);
            PrintarCartas(cards + conjunto * 10, 10);

            // Escolhe o algoritmo de ordenação para o conjunto atual
            printf("\n-------------- APLICANDO ORDENACAO ---------------- \n");

            aplicar_algoritmo(cards + conjunto * 10, 10);
        }


    } else if (modo == 4) {
        for (int i = 0; i < n; i++) {
            cards[i] = gerarCartaAleatoria();
        }

        printf("\nCartas Iniciais:");
        printf("%d\n", n);
        PrintarCartas(cards, n);

        // Embaralha as cartas
        embaralhar(cards, n);
        printf("\nCartas Embaralhadas:\n");
       PrintarCartas(cards, n);

        printf("\n-------------- APLICANDO ORDENACAO ---------------- \n");
        aplicar_algoritmo(cards, n);

    } else {
        printf("Modo invalido. Encerrando o programa.\n");
        return 1;
    }

    return 0;
}
