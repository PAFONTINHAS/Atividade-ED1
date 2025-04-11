#include "biblioteca_estatica.h"
#include <string.h>
#include <stdio.h>


void inicializarBiblioteca(Biblioteca* b) {
    b->totalLivros = 0;
}


// Implemente a função de cadastro: verificar se há espaço, preencher os dados e adicionar ao vetor

int cadastrarLivro(Biblioteca* b, char* titulo, char* autor, int ano, char* isbn) {
    if (b->totalLivros >= MAX_LIVROS) return 0;
    // Aponta para o próximo espaço
    Livro* novo = &b->livros[b->totalLivros];

    // Copia os dados para o novo livro
    strcpy(novo->titulo, titulo);
    strcpy(novo->autor, autor);


    novo->ano = ano;

    // Copia o ISBN para o novo livro
    strcpy(novo->isbn, isbn);

    // Inicializa o status e os campos de usuário e data de empréstimo
    novo->status = DISPONIVEL;

    // Inicializa o usuário e a data de empréstimo como strings vazias
    novo->usuario[0] = '\0';
    novo->dataEmprestimo[0] = '\0';

    // Incrementa o total de livros na biblioteca
    b->totalLivros++;

    return 1;
}


void listarTodosLivros(Biblioteca* b) {
    // Percorre todos os livros na biblioteca e imprime os dados
    for (int i = 0; i < b->totalLivros; i++) {
        printf("%s - %s - %d - %s\n", b->livros[i].titulo, b->livros[i].autor, b->livros[i].ano, b->livros[i].isbn);
    }

}


// Implemente: buscar livro pelo ISBN e alterar status

int emprestarLivro(Biblioteca* b, char* isbn, char* usuario, char* data) {

    // Verifica se o livro está disponível e altera o status para emprestado
    // Copia o usuário e a data de empréstimo para o livro
    for (int i = 0; i < b->totalLivros; i++) {
        if (strcmp(b->livros[i].isbn, isbn) == 0 && b->livros[i].status == DISPONIVEL) {

            b->livros[i].status = EMPRESTADO;

            strcpy(b->livros[i].usuario, usuario);
            strcpy(b->livros[i].dataEmprestimo, data);

            return 1;
        }
    }

    return 0;
}


int devolverLivro(Biblioteca* b, char* isbn) {

    // Verifica se o livro está emprestado e altera o status para disponível
    for (int i = 0; i < b->totalLivros; i++) {
        // Se o ISBN do livro for igual ao ISBN passado e o status for EMPRESTADO
        if (strcmp(b->livros[i].isbn, isbn) == 0 && b->livros[i].status == EMPRESTADO) {

            // Altera o status do livro para DISPONIVEL
            b->livros[i].status = DISPONIVEL;

            // Limpa os campos de usuário e data de empréstimo
            b->livros[i].usuario[0] = '\0';

            // Limpa a data de empréstimo
            b->livros[i].dataEmprestimo[0] = '\0';

            return 1;

        }

    }

    return 0;

}


Livro* consultarLivroPorISBN(Biblioteca* b, char* isbn) {

    for (int i = 0; i < b->totalLivros; i++) {
        if (strcmp(b->livros[i].isbn, isbn) == 0) {
            printf("%s - %s - %d - %s\n", b->livros[i].titulo, b->livros[i].autor, b->livros[i].ano, b->livros[i].isbn);
            return &b->livros[i];
        }
    }

    return NULL;

}
