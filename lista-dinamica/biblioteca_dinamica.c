#include "biblioteca_dinamica.h"

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#define INICIAL 10

void inicializarBiblioteca(Biblioteca *b)
{

    b->livros = (Livro *)malloc(INICIAL * sizeof(Livro));

    b->capacidade = INICIAL;

    b->totalLivros = 0;
}

// Esta função realoca o vetor de livros com nova capacidade

void redimensionarBiblioteca(Biblioteca *b, int novaCapacidade)
{
    b->livros = (Livro *)realloc(b->livros, novaCapacidade * sizeof(Livro));
    if (b->livros == NULL)
    {
        printf("Erro ao redimensionar a biblioteca.\n");
        exit(1);
    }
    b->capacidade = novaCapacidade;
}

// Cadastrar livro (com verificação de ISBN e redimensionamento automático)

int cadastrarLivro(Biblioteca *b, char *titulo, char *autor, int ano, char *isbn)
{
    for (int i = 0; i < b->totalLivros; i++)
    {
        if (strcmp(b->livros[i].isbn, isbn) == 0)
        {
            printf("Livro com ISBN %s já cadastrado.\n", isbn);
            return 0;
        }
    }

    if (b->totalLivros == b->capacidade)
    {
        redimensionarBiblioteca(b, b->capacidade * 2);
    }

    Livro novoLivro;
    strncpy(novoLivro.titulo, titulo, MAX_TITULO);
    strncpy(novoLivro.autor, autor, MAX_AUTOR);
    novoLivro.ano = ano;
    strncpy(novoLivro.isbn, isbn, MAX_ISBN);
    novoLivro.status = DISPONIVEL;
    b->livros[b->totalLivros++] = novoLivro;

    return 1;
}

// Listar todos os livros

void listarTodosLivros(Biblioteca *b)
{
    for (int i = 0; i < b->totalLivros; i++)
    {
        Livro *livro = &b->livros[i];
        printf("%s - %s - %d - %s\n", livro->titulo, livro->autor, livro->ano, livro->isbn);

        // printf("Título: %s, Autor: %s, Ano: %d, ISBN: %s, Status: %s\n",
        //        livro->titulo, livro->autor, livro->ano, livro->isbn,
        //        livro->status == DISPONIVEL ? "Disponível" : "Emprestado");
    }
}

// Emprestar livro

int emprestarLivro(Biblioteca *b, char *isbn, char *usuario, char *data)
{
    for (int i = 0; i < b->totalLivros; i++)
    {
        if (strcmp(b->livros[i].isbn, isbn) == 0)
        {
            if (b->livros[i].status == EMPRESTADO)
            {
                printf("Livro já emprestado.\n");
                return 0;
            }
            b->livros[i].status = EMPRESTADO;
            strncpy(b->livros[i].usuario, usuario, MAX_USUARIO);
            strncpy(b->livros[i].dataEmprestimo, data, MAX_DATA);
            return 1;
        }
    }
    printf("Livro com ISBN %s não encontrado.\n", isbn);
    return 0;
}

// Devolver livro

int devolverLivro(Biblioteca *b, char *isbn)
{
    for (int i = 0; i < b->totalLivros; i++)
    {
        if (strcmp(b->livros[i].isbn, isbn) == 0)
        {
            if (b->livros[i].status == DISPONIVEL)
            {
                printf("Livro já está disponível.\n");
                return 0;
            }
            b->livros[i].status = DISPONIVEL;
            b->livros[i].usuario[0] = '\0';
            b->livros[i].dataEmprestimo[0] = '\0';
            return 1;
        }
    }
    printf("Livro com ISBN %s não encontrado.\n", isbn);
    return 0;
}

// Buscar livro pelo ISBN

Livro *consultarLivroPorISBN(Biblioteca *b, char *isbn)
{
    for (int i = 0; i < b->totalLivros; i++)
    {
        if (strcmp(b->livros[i].isbn, isbn) == 0)
        {
            printf(" %s - %s - %d - %s\n", b->livros[i].titulo, b->livros[i].autor, b->livros[i].ano, b->livros[i].isbn);
            return &b->livros[i];
        }
    }
    return NULL;
}

// Liberar memória

void destruirBiblioteca(Biblioteca *b)
{

    free(b->livros);

    b->livros = NULL;

    b->capacidade = 0;

    b->totalLivros = 0;
}
