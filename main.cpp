#include <iostream>
#include <string>

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
 * Programa: Sistema de Biblioteca
 * Objetivo: Gerenciar livros, empréstimos e reservas.
 * Autor: Bruno Roth
 * Linguagem: C++
 */

int main() {

    cout << "===== SISTEMA DE BIBLIOTECA =====" << endl;

    return 0;
}