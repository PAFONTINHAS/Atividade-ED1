#include "biblioteca_encadeada.h"

#include <stdlib.h>

#include <string.h>

#include <stdio.h>

void inicializarBiblioteca(Biblioteca *b)
{

    b->primeiro = NULL;

    b->totalLivros = 0;
}

int cadastrarLivro(Biblioteca *b, char *titulo, char *autor, int ano, char *isbn)
{
    // Check if ISBN already exists
    NoLivro *atual = b->primeiro;
    while (atual != NULL)
    {
        if (strcmp(atual->livro.isbn, isbn) == 0)
        {
            return 0; // ISBN already exists
        }
        atual = atual->proximo;
    }

    // Create a new node
    NoLivro *novo = (NoLivro *)malloc(sizeof(NoLivro));
    if (novo == NULL)
    {
        return 0; // Memory allocation failed
    }

    // Fill in the book details
    strncpy(novo->livro.titulo, titulo, MAX_TITULO);
    strncpy(novo->livro.autor, autor, MAX_AUTOR);
    novo->livro.ano = ano;
    strncpy(novo->livro.isbn, isbn, MAX_ISBN);
    novo->livro.status = DISPONIVEL;
    novo->livro.usuario[0] = '\0';
    novo->livro.dataEmprestimo[0] = '\0';

    // Insert at the beginning of the list
    novo->proximo = b->primeiro;
    b->primeiro = novo;
    b->totalLivros++;

    return 1; // Success
}

void listarTodosLivros(Biblioteca *b)
{
    NoLivro *atual = b->primeiro;
    while (atual != NULL)
    {
        printf("%s - %s - %d - %s\n", atual->livro.titulo, atual->livro.autor, atual->livro.ano, atual->livro.isbn);

        // printf("Título: %s\n", atual->livro.titulo);
        // printf("Autor: %s\n", atual->livro.autor);
        // printf("Ano: %d\n", atual->livro.ano);
        // printf("ISBN: %s\n", atual->livro.isbn);
        // printf("Status: %s\n", atual->livro.status == DISPONIVEL ? "Disponível" : "Emprestado");
        // if (atual->livro.status == EMPRESTADO)
        // {
        //     printf("Usuário: %s\n", atual->livro.usuario);
        //     printf("Data de Empréstimo: %s\n", atual->livro.dataEmprestimo);
        // }
        printf("\n");
        atual = atual->proximo;
    }
}

int emprestarLivro(Biblioteca *b, char *isbn, char *usuario, char *data)
{
    NoLivro *atual = b->primeiro;
    while (atual != NULL)
    {
        if (strcmp(atual->livro.isbn, isbn) == 0)
        {
            if (atual->livro.status == DISPONIVEL)
            {
                atual->livro.status = EMPRESTADO;
                strncpy(atual->livro.usuario, usuario, MAX_USUARIO);
                strncpy(atual->livro.dataEmprestimo, data, MAX_DATA);
                return 1; // Success
            }
            return 0; // Book is already borrowed
        }
        atual = atual->proximo;
    }
    return 0; // ISBN not found
}

int devolverLivro(Biblioteca *b, char *isbn)
{
    NoLivro *atual = b->primeiro;
    while (atual != NULL)
    {
        if (strcmp(atual->livro.isbn, isbn) == 0)
        {
            if (atual->livro.status == EMPRESTADO)
            {
                atual->livro.status = DISPONIVEL;
                atual->livro.usuario[0] = '\0';
                atual->livro.dataEmprestimo[0] = '\0';
                return 1; // Success
            }
            return 0; // Book is not borrowed
        }
        atual = atual->proximo;
    }
    return 0; // ISBN not found
}

NoLivro *consultarLivroPorISBN(Biblioteca *b, char *isbn)
{
    NoLivro *atual = b->primeiro;
    while (atual != NULL)
    {
        if (strcmp(atual->livro.isbn, isbn) == 0)
        {
            return atual; // Found
        }
        atual = atual->proximo;
    }
    return NULL; // Not found
}

void destruirBiblioteca(Biblioteca *b)
{
    NoLivro *atual = b->primeiro;
    while (atual != NULL)
    {
        NoLivro *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    b->primeiro = NULL;
    b->totalLivros = 0;
}
