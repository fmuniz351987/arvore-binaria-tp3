#include "arvore.hpp"

int maximo(int x, int y) {
    if (x > y) return x;
    else return y;
}

Registro::Registro(TipoChave chave_, char letra_) {
    // inicializa um registro (letra e codigo morse correspondente)
    chave = chave_;
    letra = letra_;
}

int No::num_filhos() {
    // retorna 0, 1 ou 2 indicando quantos filhos tem o nó atual.
    return (!!esq + !!dir);
}

int No::altura() {
    // retorna a altura de uma arvore, onde um no sem nenhum filho tem altura = 0.
    int h;

    switch (num_filhos()) {
        case 0:
            h = 0;
            break;
        case 1:
            if (esq) h = esq->altura() + 1;
            else h = dir->altura() + 1;
            break;
        case 2:
            h = maximo(esq->altura(), dir->altura()) + 1;
            break;
    }
    return h;
}

No::No() {
    // inicializa o no de uma arvore com ponteiros nulos
    reg = nullptr;
    esq = nullptr;
    dir = nullptr;
    pai = nullptr;
}

No* No::inserir(Registro* novo_reg) {
    // insere recursivamente um registro na arvore.
    No **prox_no;

    if (reg == nullptr) {
        reg = novo_reg;
        return this;
    }
    else if (novo_reg->chave < reg->chave) prox_no = &esq;
    else if (novo_reg->chave > reg->chave) prox_no = &dir;
    else return nullptr;

    if (*prox_no == nullptr) {
        // cria um novo nó
        *prox_no = new No;
        (*prox_no)->pai = this;
    }
    return (*prox_no)->inserir(novo_reg);
}

No* No::remover() {
    // remove um nó da árvore mantendo as propriedades de arvore binária de pesquisa.
    // retorna o novo nó que substitui o lugar do antigo.
    // codigo extraido do livro-texto do Cormen
    
    No *x, *y;

    if (num_filhos() < 2) y = this;
    else y = sucessor();

    if (y->esq) x = y->esq;
    else x = y->dir;

    if (x) x->pai = y->pai;

    if (y->pai) {
        if (y == y->pai->esq) y->pai->esq = x;
        else y->pai->dir = x;
    }

    if (y != this) reg = y->reg;

    return y;
}

No* No::pesquisar(TipoChave chave_) {
    // retorna o ponteiro para um registro com a chave passada
    if (reg->chave == chave_) return this;
    else if (chave_ < reg->chave && esq != nullptr) return esq->pesquisar(chave_);
    else if (chave_ > reg->chave && dir != nullptr) return dir->pesquisar(chave_);
    else return nullptr;
}

No* No::max() {
    // retorna o maior valor na (sub)arvore atual.
    No *max = this;
    while (max->dir != nullptr) max = max->dir;
    return max;
}

No* No::min() {
    // retorna o menor valor na (sub)arvore atual.
    No *min = this;
    while (min->esq != nullptr) min = min->dir;
    return min;
}

No* No::antecessor() {
    // retorna o antecessor do no atual
    if (esq != nullptr) return esq->max();
    return nullptr;
}

No* No::sucessor() {
    // retorna o sucessor do no atual
    if (dir != nullptr) return dir->min();
    return nullptr;
}

void No::deletar_arvore() {
    // libera a memoria ocupada por uma arvore.
    if (esq != nullptr) esq->deletar_arvore();
    if (dir != nullptr) dir->deletar_arvore();
    delete reg;
    delete this;
}

std::ostream &operator<<(std::ostream &out, No& no) {
    // usa std::ostream para imprimir em PRÉ-ORDEM.
    if (no.reg == nullptr) return out;
    out << no.reg->letra << ' ' << no.reg->chave << '\n';
    if (no.esq != nullptr) out << *no.esq;
    if (no.dir != nullptr) out << *no.dir;
    return out;
}
