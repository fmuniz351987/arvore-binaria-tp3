#pragma once

#include <exception>
#include <iostream>
#include <string>


typedef std::string TipoChave;

struct Registro {
    TipoChave chave;
    char letra;

    Registro(TipoChave, char);
};

struct No {
    Registro *reg;
    No *esq, *dir, *pai;

    No();

    int num_filhos();

    int altura();

    No *inserir(Registro*);

    No *remover();

    No *pesquisar(TipoChave);

    No *max();

    No *min();

    No *antecessor();

    No *sucessor();

    void deletar_arvore();
};

std::ostream &operator<<(std::ostream&, No&);
