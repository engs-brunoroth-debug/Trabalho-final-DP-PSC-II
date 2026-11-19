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

/*
 * Funcao: removerLivro
 * Objetivo: Remover um livro da lista usando seu codigo.
 * Parametro: Referencia para o inicio da lista encadeada.
 * Retorno: Nenhum.
 */
void removerLivro(Livro*& inicio, int codigo) {
    Livro* atual = inicio;
    Livro* anterior = nullptr;

    while (atual != nullptr && atual->codigo != codigo) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == nullptr) {
        cout << "\nLivro nao encontrado.\n";
        return;
    }

    if (anterior == nullptr) {
        inicio = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    delete atual;

    cout << "\nLivro removido com sucesso!\n";
}
/*
 * Funcao: emprestarLivro
 * Objetivo: Alterar a disponibilidade de um livro para emprestado.
 * Parametros: Ponteiro para o inicio da lista e codigo do livro.
 * Retorno: Nenhum.
 */
void emprestarLivro(Livro* inicio, int codigo) {
    Livro* atual = inicio;

    while (atual != nullptr) {
        if (atual->codigo == codigo) {
            if (!atual->disponivel) {
                cout << "\nEste livro ja esta emprestado.\n";
                return;
            }

            atual->disponivel = false;
            cout << "\nLivro emprestado com sucesso!\n";
            return;
        }

        atual = atual->proximo;
    }

    cout << "\nLivro nao encontrado.\n";
}

/*
 * Funcao: devolverLivro
 * Objetivo: Alterar a disponibilidade de um livro para disponivel.
 * Parametros: Ponteiro para o inicio da lista e codigo do livro.
 * Retorno: Nenhum.
 */
void devolverLivro(Livro* inicio, int codigo) {
    Livro* atual = inicio;

    while (atual != nullptr) {
        if (atual->codigo == codigo) {
            if (atual->disponivel) {
                cout << "\nEste livro ja esta disponivel.\n";
                return;
            }

            atual->disponivel = true;
            cout << "\nLivro devolvido com sucesso!\n";
            return;
        }

        atual = atual->proximo;
    }

    cout << "\nLivro nao encontrado.\n";
}

int main() {
    Livro* inicio = nullptr;

    cout << "===== SISTEMA DE BIBLIOTECA =====" << endl;

    cadastrarLivro(inicio);
    listarLivros(inicio);

    int codigo;

    cout << "\nDigite o codigo do livro que deseja emprestar: ";
    cin >> codigo;

    emprestarLivro(inicio, codigo);
    listarLivros(inicio);

    cout << "\nDigite o codigo do livro que deseja devolver: ";
    cin >> codigo;

    devolverLivro(inicio, codigo);
    listarLivros(inicio);

    return 0;
}