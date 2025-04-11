#include <stdio.h>
#include "biblioteca_encadeada.h"
#include <time.h>
int main()
{

    Biblioteca b;

    printf("Inicializando a biblioteca\n");
    inicializarBiblioteca(&b);

    clock_t inicio = clock();

    printf("Cadastrando livros\n");

    for (int i = 0; i < 5000; i++)
    {
        char titulo[100], autor[100], isbn[14];
        sprintf(titulo, "Livro %d", i);
        sprintf(autor, "Autor %d", i);
        sprintf(isbn, "%d", i);

        cadastrarLivro(&b, titulo, autor, 2020, isbn);
    }

    printf("Livros cadastrados\n");

    printf("Listando todos os livros\n");

    listarTodosLivros(&b);

    printf("\nLivros listados\n");

    printf("Consultando livro \n");

    NoLivro* livro = consultarLivroPorISBN(&b, "3869");

    if (livro != NULL)
    {
        printf("%s - %s - %d - %s\n", livro->livro.titulo, livro->livro.autor, livro->livro.ano, livro->livro.isbn);
    }

    printf("\nLivro consultado\n");

    clock_t fim = clock();

    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de execucao do programa com 500 livros: %.4f segundos\n", tempo);

    // TEMPO DE EXECUÇÃO PARA 50 LIVROS: 0.0170 SEGUNDOS
    // TEMPO DE EXECUÇÃO PARA 500 LIVROS: 0.4940 SEGUNDOS
    // TEMPO DE EXECUÇÃO PARA 5000 LIVROS: 2.4850 SEGUNDOS

    printf("Destruindo Biblioteca \n");
    destruirBiblioteca(&b);
    printf("Biblioteca destruida\n");

    return 0;




}
