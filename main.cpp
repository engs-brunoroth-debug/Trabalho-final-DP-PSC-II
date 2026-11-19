#include <iostream>
#include <string>
#include <limits>

using namespace std;
/*
 * Estrutura: Livro
 * Objetivo: Armazenar os dados de um livro e o endereço do próximo.
 */
struct Livro {
    int codigo;
    string titulo;
    string autor;
    bool disponivel;
    Livro* proximo;
    
};
/*
 * Funcao: cadastrarLivro
 * Objetivo: Cadastrar um livro e adiciona-lo ao final da lista.
 * Parametro: Referencia para o inicio da lista encadeada.
 * Retorno: Nenhum.
 */
void cadastrarLivro(Livro*& inicio) {
    Livro* novo = new Livro;

    cout << "\nDigite o codigo do livro: ";
    cin >> novo->codigo;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Digite o titulo: ";
    getline(cin, novo->titulo);

    cout << "Digite o autor: ";
    getline(cin, novo->autor);

    novo->disponivel = true;
    novo->proximo = nullptr;

    if (inicio == nullptr) {
        inicio = novo;
    } else {
        Livro* atual = inicio;
        while (atual->proximo != nullptr) {
            atual = atual->proximo;
        }
        atual->proximo = novo;
    }

    cout << "\nLivro cadastrado com sucesso!\n";
}
/*
 * Funcao: listarLivros
 * Objetivo: Exibir todos os livros cadastrados na lista.
 * Parametro: Ponteiro para o inicio da lista encadeada.
 * Retorno: Nenhum.
 */
void listarLivros(const Livro* inicio) {
    if (inicio == nullptr) {
        cout << "\nNenhum livro cadastrado.\n";
        return;
    }

    const Livro* atual = inicio;

    cout << "\n===== LIVROS CADASTRADOS =====\n";

    while (atual != nullptr) {
        cout << "\nCodigo: " << atual->codigo;
        cout << "\nTitulo: " << atual->titulo;
        cout << "\nAutor: " << atual->autor;
        cout << "\nDisponibilidade: ";

        if (atual->disponivel) {
            cout << "Disponivel\n";
        } else {
            cout << "Emprestado\n";
        }

        atual = atual->proximo;
    }
}

int main() {
    Livro* inicio = nullptr;

    cout << "===== SISTEMA DE BIBLIOTECA =====" << endl;

    cadastrarLivro(inicio);
    listarLivros(inicio);

    return 0;
}
