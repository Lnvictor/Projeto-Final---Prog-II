#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

Disciplina* newDisciplina(char* codigo, char* nome, char* prereq, int credito){

    Disciplina* D = (Disciplina*) malloc (sizeof(Disciplina));

    strcpy(D->codigo, codigo);
    strcpy(D->nome ,nome);
    strcpy(D->prereq, prereq);
    D->credito = credito;
    return D;
}

Aluno* newAluno(int RA, char* nome, char* login, char* senha){
    Aluno* A = (Aluno*) malloc (sizeof(Aluno));


    A->RA= RA;
    strcpy(A->nome, nome);
    strcpy(A->login ,login);
    strcpy(A->senha ,senha);

    return A;
}

void CadastrarAluno(int RA, char* nome, char* login, char* senha){
    FILE* Arquivo;
    Aluno* A = newAluno(RA, nome, login, senha);

    //Removendo "\n"
    nome[strlen(nome) - 1] = '\0';
    login[strlen(login) - 1] = '\0';
    senha[strlen(senha) - 1] = '\0';

    Arquivo = fopen("Alunos.txt", "a+");

    fprintf(Arquivo, "%d,%s,%s,%s\n", RA, nome, login, senha);
    fclose(Arquivo);

    printf("Aluno cadastrado com sucesso!\n");
}

int login(char* username, char* senha){
    int login_Valid = 0;
    char *user, *pass, aux;
    char info[100];

    FILE* Arquivo;
    Arquivo = fopen("Alunos.txt", "r");

    username[strlen(username) - 1] = '\0';

    do{
        fgets(info, 100, Arquivo);
        strtok(info, ",");
        strtok(NULL, ",");
        user = strtok(NULL, ",");
        pass = strtok(NULL, ",");

        if(strcmp(user, username) == 0 && strcmp(pass, senha) == 0){
            login_Valid = 1;
            break;
        }

    }while(fscanf(Arquivo, "%c", &aux) != EOF);

    return login_Valid;
}

Sistema* newSistema(){
    Sistema* S = (Sistema*) malloc (sizeof(Sistema));
    S->v = (Disciplina*) malloc (TAM * sizeof(Disciplina));
    S->top = 0;

    for(int i = 0; i < TAM; i++){
        strcpy(S->v[i].prereq, "Nenhum");
    }
    return S;
}

Sistema* carregaD(){
    Sistema* S = newSistema();
    char* token;
    char aux[100];

    FILE* Arquivo_D, *Arquivo_P;
    Arquivo_D = fopen("Disciplinas.txt", "r");
    Arquivo_P = fopen("Prerequisitos.txt", "r");

    do{
        fgets(aux, 100, Arquivo_D);
        strcpy(S->v[S->top].codigo,  strtok(aux, ","));
        strcpy(S->v[S->top].nome,  strtok(NULL, ","));
        S->v[S->top].credito = atoi(strtok(NULL, ","));

        fgets(aux, TAM, Arquivo_P);
        strtok(aux, ",");
        strcpy(S->v[S->top].prereq, strtok(NULL, ","));
        S->top++;
    }while(S->top < 41);

    fclose(Arquivo_P);
    fclose(Arquivo_D);

    return S;
}

Disciplina* BuscarDisciplina(char* codigo, Sistema* S){
    int i,j;
    Disciplina* D = NULL;

    for(i = 0; i < S->top; i++){
        if (strcmp(codigo, S->v[i].codigo) == 0){
            D = newDisciplina(S->v[i].codigo,S->v[i].nome,S->v[i].prereq,S->v[i].credito);
            break;
        }
    }

    return D;
}

// void MatricularAluno(Aluno* A, char* codigo){
//
//     FILE* Arquivo;
//     Arquivo = fopen("Matriculas.txt", "a+");
//
//     fclose(Arquivo)
// }
