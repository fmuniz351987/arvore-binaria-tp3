#include <iostream>
#include <fstream>
#include <string>

#include "arvore.hpp"

void ler_codigo_morse(No *arvore) {
    // faz a leitura do arquivo morse.txt e constroi a arvore.
    
    std::ifstream morse;
    std::string linha;
    Registro *registro;
    TipoChave chave;
    char letra;

    morse.open("src/morse.txt");

    if (!morse) {
        std::cerr << "Erro na abertura do arquivo morse.txt.\n";
        exit(1);
    }

    for (int i = 0; i < 36; i++) {  //lendo as 36 linhas do arquivo
        morse >> letra;
        morse >> chave;
        registro = new Registro(chave, letra);
        arvore->inserir(registro);
    }
    registro = new Registro("/", ' ');  //inserindo o espaço entre palavras com a chave "/" no codigo morse
    arvore->inserir(registro);

    morse.close();
}

std::string ler_entrada(No *arvore) {
    // lê o texto de entrada codificado em morse, e retorna a string com o texto
    // decodificado.

    TipoChave chave;
    char letra;
    std::string mensagem = "";
    No *no;

    while (true) {
        std::cin >> chave;
        if (std::cin.fail()) break;
        no = arvore->pesquisar(chave);
        if (!no) break;
        letra = no->reg->letra;
        mensagem += letra;
        if (std::cin.peek() == '\n') mensagem += '\n';
    }
    return mensagem;
}

int main(int argc, char *argv[]) {
    No* arvore = new No;
    std::string mensagem, parametro_opcional;

    ler_codigo_morse(arvore);
    mensagem = ler_entrada(arvore);
    std::cout << mensagem;

    if (argc > 1) {
        parametro_opcional = argv[1];
        if (parametro_opcional == "-a") {
            std::clog << *arvore << '\n';        
        }
    }

    arvore->deletar_arvore();
    return 0;
}
