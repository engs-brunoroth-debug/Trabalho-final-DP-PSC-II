#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include <vector>

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
 * Estrutura: NoArvore
 * Objetivo: Armazenar o codigo do livro e os filhos da arvore.
 */
struct NoArvore {
    int codigo;
    NoArvore* esquerda;
    NoArvore* direita;
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
 * Funcao: inserirArvore
 * Objetivo: Inserir um codigo na arvore binaria de busca.
 * Parametros: Raiz da arvore e codigo do livro.
 * Retorno: Ponteiro para a raiz atualizada.
 */
NoArvore* inserirArvore(NoArvore* raiz, int codigo) {
    if (raiz == nullptr) {
        NoArvore* novo = new NoArvore;
        novo->codigo = codigo;
        novo->esquerda = nullptr;
        novo->direita = nullptr;
        return novo;
    }

    if (codigo < raiz->codigo) {
        raiz->esquerda = inserirArvore(raiz->esquerda, codigo);
    } else if (codigo > raiz->codigo) {
        raiz->direita = inserirArvore(raiz->direita, codigo);
    }

    return raiz;
}


/*
 * Funcao: buscarArvore
 * Objetivo: Procurar um codigo na arvore recursivamente.
 * Parametros: Raiz da arvore e codigo procurado.
 * Retorno: true se encontrar; false caso contrario.
 */
bool buscarArvore(const NoArvore* raiz, int codigo) {
    if (raiz == nullptr) {
        return false;
    }

    if (raiz->codigo == codigo) {
        return true;
    }

    if (codigo < raiz->codigo) {
        return buscarArvore(raiz->esquerda, codigo);
    }

    return buscarArvore(raiz->direita, codigo);
}


/*
 * Funcao: percorrerEmOrdem
 * Objetivo: Exibir os codigos em ordem crescente.
 * Parametro: Ponteiro constante para a raiz da arvore.
 * Retorno: Nenhum.
 */
void percorrerEmOrdem(const NoArvore* raiz) {
    if (raiz == nullptr) {
        return;
    }

    percorrerEmOrdem(raiz->esquerda);
    cout << raiz->codigo << " ";
    percorrerEmOrdem(raiz->direita);
}
/*
 * Complexidade do Bubble Sort:
 * Melhor caso: O(n), quando a lista ja esta ordenada.
 * Pior caso: O(n²), quando a lista esta em ordem inversa.
 * Caso medio: O(n²).
 * O algoritmo compara elementos vizinhos e troca suas
 * posicoes quando estao fora de ordem.
 */

/*
 * Funcao: ordenarLivros
 * Objetivo: Ordenar os livros pelo codigo usando Bubble Sort.
 * Parametro: Ponteiro para o inicio da lista.
 * Retorno: Nenhum.
 */
void ordenarLivros(Livro* inicio) {
    if (inicio == nullptr) {
        return;
    }

    bool trocou;

    do {
        trocou = false;
        Livro* atual = inicio;

        while (atual->proximo != nullptr) {
            if (atual->codigo > atual->proximo->codigo) {
                swap(atual->codigo, atual->proximo->codigo);
                swap(atual->titulo, atual->proximo->titulo);
                swap(atual->autor, atual->proximo->autor);
                swap(atual->disponivel, atual->proximo->disponivel);
                trocou = true;
            }

            atual = atual->proximo;
        }
    } while (trocou);
}


/*
 * Funcao: buscaSequencial
 * Objetivo: Procurar um livro percorrendo a lista.
 * Retorno: true se encontrar; false caso contrario.
 */
bool buscaSequencial(const Livro* inicio, int codigo,
                     int& comparacoes) {
    comparacoes = 0;

    while (inicio != nullptr) {
        comparacoes++;

        if (inicio->codigo == codigo) {
            return true;
        }

        inicio = inicio->proximo;
    }

    return false;
}

/*
 * Funcao: buscaBinaria
 * Objetivo: Procurar um codigo em um vetor ordenado.
 * Retorno: true se encontrar; false caso contrario.
 */
bool buscaBinaria(const vector<int>& codigos, int codigo,
                  int& comparacoes) {
    int inicio = 0;
    int fim = static_cast<int>(codigos.size()) - 1;
    comparacoes = 0;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        comparacoes++;

        if (codigos[meio] == codigo) {
            return true;
        }

        if (codigos[meio] < codigo) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    return false;
}


/*
 * Funcao: codigoExiste
 * Objetivo: Verificar se um codigo ja esta cadastrado.
 * Parametros: Lista de livros e codigo procurado.
 * Retorno: true se existir; false caso contrario.
 */
bool codigoExiste(const Livro* inicio, int codigo) {
    while (inicio != nullptr) {
        if (inicio->codigo == codigo) {
            return true;
        }
        inicio = inicio->proximo;
    }
    return false;
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

    if (codigoExiste(inicio, novo->codigo)) {
        cout << "\nCodigo ja cadastrado! Tente outro.\n";
        delete novo;
        return;
    }

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
        while (atual->proximo != nullptr)
            atual = atual->proximo;
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

/*
 * Funcao: devolverLivro
 * Objetivo: Alterar a disponibilidade de um livro para disponivel.
 * Parametros: Ponteiro para a lista, codigo e referencia para o historico.
 * Retorno: true se devolver; false caso contrario.
 */
bool devolverLivro(Livro* inicio, int codigo, Operacao*& topo) {
    Livro* atual = inicio;

    while (atual != nullptr) {
        if (atual->codigo == codigo) {
            if (atual->disponivel) {
                cout << "\nEste livro ja esta disponivel.\n";
                return false;
            }

            atual->disponivel = true;
            registrarOperacao(topo, codigo, "Devolucao");
            cout << "\nLivro devolvido com sucesso!\n";
            return true;
        }

        atual = atual->proximo;
    }

    cout << "\nLivro nao encontrado.\n";
    return false;
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
 * Objetivo: Atender a reserva do livro devolvido, se for a primeira.
 * Parametros: Inicio, fim da fila e codigo do livro devolvido.
 * Retorno: Nenhum.
 */
void atenderProximaReserva(
    Reserva*& inicioFila,
    Reserva*& fimFila,
    int codigoDevolvido
) {
    if (inicioFila == nullptr) {
        cout << "\nNao existem reservas para atender.\n";
        return;
    }

    if (inicioFila->codigoLivro != codigoDevolvido) {
        cout << "\nA primeira reserva e de outro livro. "
             << "Ela permanece na fila.\n";
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

/*
 * Funcao: liberarLivros
 * Objetivo: Liberar toda a memoria da lista de livros.
 * Parametro: Referencia para o inicio da lista.
 * Retorno: Nenhum.
 */
void liberarLivros(Livro*& inicio) {
    while (inicio != nullptr) {
        Livro* auxiliar = inicio;
        inicio = inicio->proximo;
        delete auxiliar;
    }
    inicio = nullptr;
}

/*
 * Funcao: liberarReservas
 * Objetivo: Liberar toda a memoria da fila.
 * Parametros: Inicio e fim da fila.
 * Retorno: Nenhum.
 */
void liberarReservas(Reserva*& inicio, Reserva*& fim) {
    while (inicio != nullptr) {
        Reserva* auxiliar = inicio;
        inicio = inicio->proximo;
        delete auxiliar;
    }
    fim = nullptr;
}

/*
 * Funcao: liberarHistorico
 * Objetivo: Liberar toda a memoria da pilha.
 * Parametro: Referencia para o topo.
 * Retorno: Nenhum.
 */
void liberarHistorico(Operacao*& topo) {
    while (topo != nullptr) {
        Operacao* auxiliar = topo;
        topo = topo->proximo;
        delete auxiliar;
    }
    topo = nullptr;
}

/*
 * Funcao: liberarArvore
 * Objetivo: Liberar os nos da arvore recursivamente.
 * Parametro: Referencia para a raiz.
 * Retorno: Nenhum.
 */
void liberarArvore(NoArvore*& raiz) {
    if (raiz == nullptr) {
        return;
    }

    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);

    delete raiz;
    raiz = nullptr;
}

/*
 * Funcao: cadastrarLivrosEArvore
 * Objetivo: Cadastrar varios livros e inserir seus codigos na arvore.
 * Parametros: Referencias para a lista de livros e raiz da arvore.
 * Retorno: Nenhum.
 */
void cadastrarLivrosEArvore(Livro*& inicio, NoArvore*& raiz) {
    char continuarCadastro;

    do {
        cadastrarLivro(inicio);

        cout << "\nDeseja cadastrar outro livro? (s/n): ";
        cin >> continuarCadastro;

    } while (continuarCadastro == 's' || continuarCadastro == 'S');

    Livro* atual = inicio;

    while (atual != nullptr) {
        raiz = inserirArvore(raiz, atual->codigo);
        atual = atual->proximo;
    }
}

/*
 * Funcao: executarEmprestimoEReserva
 * Objetivo: Realizar emprestimo e reserva de livros.
 * Parametros: Lista de livros, fila de reservas e historico.
 * Retorno: Nenhum.
 */
void executarEmprestimoEReserva(
    Livro* inicio,
    Reserva*& inicioFila,
    Reserva*& fimFila,
    Operacao*& topoHistorico
) {
    int codigo;

    cout << "\nDigite o codigo do livro que deseja emprestar: ";
    cin >> codigo;
    emprestarLivro(inicio, codigo, topoHistorico);

    cout << "\nDigite o codigo do livro que deseja reservar: ";
    cin >> codigo;
    reservarLivro(inicio, inicioFila, fimFila, codigo);

    mostrarFilaReservas(inicioFila);
    listarLivros(inicio);
}

 /*
 * Funcao: executarDevolucao
 * Objetivo: Devolver um livro e atender a proxima reserva.
 * Parametros: Lista de livros, fila de reservas e historico.
 * Retorno: Nenhum.
 */
void executarDevolucao(
    Livro* inicio,
    Reserva*& inicioFila,
    Reserva*& fimFila,
    Operacao*& topoHistorico
) {
    int codigo;

    cout << "\nDigite o codigo do livro que deseja devolver: ";
    cin >> codigo;

 if (devolverLivro(inicio, codigo, topoHistorico)) {
    atenderProximaReserva(inicioFila, fimFila, codigo);

}
    mostrarFilaReservas(inicioFila);
    listarLivros(inicio);
    mostrarHistorico(topoHistorico);
}

/*
 * Funcao: executarOrdenacao
 * Objetivo: Ordenar e listar os livros por codigo.
 * Parametros: Inicio da lista de livros.
 * Retorno: Nenhum.
 */
void executarOrdenacao(Livro* inicio) {
    cout << "\n===== LIVROS ORDENADOS POR CODIGO =====\n";

    ordenarLivros(inicio);
    listarLivros(inicio);
}

/*
 * Funcao: criarVetorCodigos
 * Objetivo: Copiar os codigos dos livros para um vetor.
 * Parametro: Ponteiro para o inicio da lista de livros.
 * Retorno: Vetor contendo os codigos dos livros.
 */
vector<int> criarVetorCodigos(const Livro* inicio) {
    vector<int> codigos;
    const Livro* atual = inicio;

    while (atual != nullptr) {
        codigos.push_back(atual->codigo);
        atual = atual->proximo;
    }

    return codigos;
}
/*
 * Funcao: executarBuscas
 * Objetivo: Comparar as buscas sequencial, binaria e na arvore.
 * Parametros: Lista de livros e raiz da arvore.
 * Retorno: Nenhum.
 */
void executarBuscas(Livro* inicio, const NoArvore* raiz) {
   vector<int> codigosOrdenados = criarVetorCodigos(inicio);

    int codigoBusca;
    cout << "\nDigite o codigo que deseja buscar: ";
    cin >> codigoBusca;

    int comparacoesSequencial = 0;
    int comparacoesBinaria = 0;

    bool encontrouSequencial =
        buscaSequencial(inicio, codigoBusca, comparacoesSequencial);

    bool encontrouBinaria =
        buscaBinaria(codigosOrdenados, codigoBusca, comparacoesBinaria);

    cout << "\n===== COMPARACAO DAS BUSCAS =====\n";
    cout << "Busca sequencial: "
         << (encontrouSequencial ? "Encontrado" : "Nao encontrado")
         << " | Comparacoes: " << comparacoesSequencial << endl;

    cout << "Busca binaria: "
         << (encontrouBinaria ? "Encontrado" : "Nao encontrado")
         << " | Comparacoes: " << comparacoesBinaria << endl;

    if (buscarArvore(raiz, codigoBusca)) {
        cout << "\nLivro encontrado na arvore!\n";
    } else {
        cout << "\nLivro nao encontrado na arvore.\n";
    }
}

/*
 * Funcao: executarPercursoArvore
 * Objetivo: Exibir os codigos dos livros em ordem crescente.
 * Parametros: Raiz da arvore binaria.
 * Retorno: Nenhum.
 */
void executarPercursoArvore(const NoArvore* raiz) {
    cout << "\n===== CODIGOS EM ORDEM =====\n";
    percorrerEmOrdem(raiz);
}

/*
 * Funcao: liberarEstruturas
 * Objetivo: Liberar toda a memoria alocada pelo sistema.
 * Parametros: Referencias para as estruturas utilizadas.
 * Retorno: Nenhum.
 */
void liberarEstruturas(
    Livro*& inicio,
    Reserva*& inicioFila,
    Reserva*& fimFila,
    Operacao*& topoHistorico,
    NoArvore*& raiz
) {
    liberarLivros(inicio);
    liberarReservas(inicioFila, fimFila);
    liberarHistorico(topoHistorico);
    liberarArvore(raiz);
}

int main() {
    Livro* inicio = nullptr;
    Reserva* inicioFila = nullptr;
    Reserva* fimFila = nullptr;
    Operacao* topoHistorico = nullptr;
    NoArvore* raiz = nullptr;

    cout << "===== SISTEMA DE BIBLIOTECA =====" << endl;

    cadastrarLivrosEArvore(inicio, raiz);
    listarLivros(inicio);

    executarEmprestimoEReserva(inicio, inicioFila, fimFila, topoHistorico);
    executarDevolucao(inicio, inicioFila, fimFila, topoHistorico);

    executarOrdenacao(inicio);
    executarPercursoArvore(raiz);
    executarBuscas(inicio, raiz);

    liberarEstruturas(inicio, inicioFila, fimFila, topoHistorico, raiz);

    return 0;
}