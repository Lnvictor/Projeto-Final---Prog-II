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

void cadastrarAluno(int RA, char* nome, char* login, char*senha);

Disciplina* buscarDisciplina(char* codigo, Sistema* S);

void matricular(char*user, Sistema* S);

void atualizar(char* user, Sistema* S);

double retornaCR(int RA, Sistema* S);

void geraRelatorio(char* username, Sistema* S);
#endif
