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
 * Estrutura: Reserva
 * Objetivo: Armazenar uma reserva e apontar para a proxima.
 */
struct Reserva {
    int codigoLivro;
    Reserva* proximo;
};

/*
 * Estrutura: Operacao
 * Objetivo: Armazenar uma operacao no historico da biblioteca.
 */
struct Operacao {
    int codigoLivro;
    string tipo;
    Operacao* proximo;
};


/*
 * Funcao: registrarOperacao
 * Objetivo: Inserir uma operacao no topo da pilha.
 * Parametros: Referencia para a pilha, codigo e tipo da operacao.
 * Retorno: Nenhum.
 */
void registrarOperacao(Operacao*& topo, int codigo, string tipo) {
    Operacao* nova = new Operacao;
    nova->codigoLivro = codigo;
    nova->tipo = tipo;
    nova->proximo = topo;
    topo = nova;
}


/*
 * Funcao: mostrarHistorico
 * Objetivo: Exibir as operacoes do topo para a base da pilha.
 * Parametro: Ponteiro para o topo da pilha.
 * Retorno: Nenhum.
 */
void mostrarHistorico(const Operacao* topo) {
    if (topo == nullptr) {
        cout << "\nHistorico vazio.\n";
        return;
    }

    cout << "\n===== HISTORICO DE OPERACOES =====\n";

    while (topo != nullptr) {
        cout << "Livro: " << topo->codigoLivro;
        cout << " | Operacao: " << topo->tipo << endl;
        topo = topo->proximo;
    }
}


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
void emprestarLivro(Livro* inicio, int codigo, Operacao*& topo) {
    Livro* atual = inicio;

    while (atual != nullptr) {
        if (atual->codigo == codigo) {
            if (!atual->disponivel) {
                cout << "\nEste livro ja esta emprestado.\n";
                return;
            }

            atual->disponivel = false;
registrarOperacao(topo, codigo, "Emprestimo");
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
void devolverLivro(Livro* inicio, int codigo, Operacao*& topo) {
    Livro* atual = inicio;

    while (atual != nullptr) {
        if (atual->codigo == codigo) {
            if (atual->disponivel) {
                cout << "\nEste livro ja esta disponivel.\n";
                return;
            }

            atual->disponivel = true;
registrarOperacao(topo, codigo, "Devolucao");
cout << "\nLivro devolvido com sucesso!\n";
return;
        }

        atual = atual->proximo;
    }

    cout << "\nLivro nao encontrado.\n";
}

/*
 * Funcao: reservarLivro
 * Objetivo: Adicionar uma reserva ao final da fila.
 * Parametros: Lista de livros, inicio e fim da fila e codigo do livro.
 * Retorno: Nenhum.
 */
void reservarLivro(Livro* livros, Reserva*& inicioFila,
                   Reserva*& fimFila, int codigoLivro) {
    Livro* atual = livros;

    while (atual != nullptr && atual->codigo != codigoLivro) {
        atual = atual->proximo;
    }

    if (atual == nullptr) {
        cout << "\nLivro nao encontrado.\n";
        return;
    }

    if (atual->disponivel) {
        cout << "\nLivro disponivel. Nao precisa de reserva.\n";
        return;
    }

    Reserva* nova = new Reserva;
    nova->codigoLivro = codigoLivro;
    nova->proximo = nullptr;

    if (inicioFila == nullptr) {
        inicioFila = nova;
        fimFila = nova;
    } else {
        fimFila->proximo = nova;
        fimFila = nova;
    }

    cout << "\nReserva realizada com sucesso!\n";
}

/*
 * Funcao: mostrarFilaReservas
 * Objetivo: Exibir todas as reservas na ordem de chegada.
 * Parametro: Ponteiro para o inicio da fila.
 * Retorno: Nenhum.
 */
void mostrarFilaReservas(const Reserva* inicioFila) {
    if (inicioFila == nullptr) {
        cout << "\nNao existem reservas na fila.\n";
        return;
    }

    const Reserva* atual = inicioFila;

    cout << "\n===== FILA DE RESERVAS =====\n";

    while (atual != nullptr) {
        cout << "Codigo do livro: " << atual->codigoLivro << endl;
        atual = atual->proximo;
    }
}

/*
 * Funcao: atenderProximaReserva
 * Objetivo: Remover e atender a primeira reserva da fila.
 * Parametros: Referencias para o inicio e o fim da fila.
 * Retorno: Nenhum.
 */
void atenderProximaReserva(Reserva*& inicioFila, Reserva*& fimFila) {
    if (inicioFila == nullptr) {
        cout << "\nNao existem reservas para atender.\n";
        return;
    }

    Reserva* atendida = inicioFila;

    cout << "\nReserva atendida para o livro: "
         << atendida->codigoLivro << endl;

    inicioFila = inicioFila->proximo;

    if (inicioFila == nullptr) {
        fimFila = nullptr;
    }

    delete atendida;
}

int main() {
    Livro* inicio = nullptr;
    Reserva* inicioFila = nullptr;
    Reserva* fimFila = nullptr;
    Operacao* topoHistorico = nullptr;
    cout << "===== SISTEMA DE BIBLIOTECA =====" << endl;

    cadastrarLivro(inicio);
    listarLivros(inicio);

    int codigo;

    cout << "\nDigite o codigo do livro que deseja emprestar: ";
    cin >> codigo;

 emprestarLivro(inicio, codigo, topoHistorico);
    cout << "\nDigite o codigo do livro que deseja reservar: ";
cin >> codigo;

reservarLivro(inicio, inicioFila, fimFila, codigo);
mostrarFilaReservas(inicioFila);

    listarLivros(inicio);

    cout << "\nDigite o codigo do livro que deseja devolver: ";
    cin >> codigo;

  devolverLivro(inicio, codigo, topoHistorico);
    atenderProximaReserva(inicioFila, fimFila);
    mostrarFilaReservas(inicioFila);
    listarLivros(inicio);
    mostrarHistorico(topoHistorico);

    return 0;
}