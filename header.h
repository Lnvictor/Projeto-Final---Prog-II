#ifndef HEADER_H
#define HEADER_H

typedef struct Disciplina{
    char codigo[10];
    char nome[100];
    char prereq[100];
    int credito;
} Disciplina;

typedef struct Aluno{
    int RA;
    char nome[100];
    char login[100];
    char senha[100];
} Aluno;

typedef struct Sistema{
    Disciplina* v;
    int top;
}


Disciplina* newDisciplina();

Aluno* newAluno();

Sistema* carregaD();

int login();

#endif
