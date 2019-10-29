#ifndef HEADER_H
#define HEADER_H

#define TAM 60

typedef struct Disciplina{
    char codigo[10];
    char nome[100];
    char prereq[10];
    int credito;
} Disciplina;

typedef struct Aluno{
    int RA;
    char nome[100];
    char login[10];
    char senha[10];
} Aluno;

typedef struct Sistema{
    Disciplina* v;
    int top;
}Sistema;


Disciplina* newDisciplina(char* codigo, char* nome, char* prereq, int credito);

Aluno* newAluno(int RA, char* nome, char* login, char* senha);

Sistema* carregaD();

int login(char* username, char* senha);

void CadastrarAluno(int RA, char* nome, char* login, char*senha);

Disciplina* BuscarDisciplina(char* codigo, Sistema* S);

void Matricular(char*user, Sistema* S);

void Atualizar(char* user, Sistema* S);
#endif
