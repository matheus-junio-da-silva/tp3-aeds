#ifndef CARTAS_H_INCLUDED
#define CARTAS_H_INCLUDED


typedef struct {
    int cor;
    int numero;
} Carta;

const char* nomeCor(int cor);
Carta gerarCartaAleatoria();
int lerCartaEspecial(const char* specialCard);


#endif // CARTAS_H_INCLUDED
