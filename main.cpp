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
 * Programa: Sistema de Biblioteca
 * Objetivo: Gerenciar livros, empréstimos e reservas.
 * Autor: Bruno Roth
 * Linguagem: C++
 */

int main() {
    Livro* inicio = nullptr;

    cout << "===== SISTEMA DE BIBLIOTECA =====" << endl;

    cadastrarLivro(inicio);

    return 0;
}