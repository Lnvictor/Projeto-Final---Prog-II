// Breno Souza dos Reis             RA: 232246
// Gilberto da Silva Villa Nova     RA: 173050
// Victor Henrique Barbosa Pereira   RA: 245055

//main.c - Projeto Final - SI200

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


int main(){
    int menu;
    int RA; char nome[TAM], user[TAM], senha[TAM];
    FILE* Arquivo;

    Arquivo = fopen("Alunos.txt", "r");


    if (Arquivo == NULL){
        printf("[MENU DE CADASTRO]\n" );

        printf("Digite o nome: ");
        fgets(nome, TAM, stdin);
        printf("Digite o RA: ");
        scanf("%d", &RA);
        getchar();
        printf("Digite o Username: ");
        fgets(user, TAM, stdin);
        printf("Digite a senha: ");
        fgets(senha, TAM, stdin);

        CadastrarAluno(RA, nome, user, senha);
    }

    else{
        char aux[10];
        int key;

        do{
            fclose(Arquivo);
            printf("[LOGIN]\n");
            printf("Digite o Username: ");
            fgets(user, TAM, stdin);
            printf("Digite a senha: ");
            fgets(senha, TAM, stdin);

            key = login(user, senha);
            if(key == 0)
                printf("Login Inválido!\n");
        }while(key != 1);

        do{
            Sistema* S = carregaD();
            //Menu
            printf("[Menu de Opcoes]\n");
            printf("1. Cadastro de Alunos\n");
            printf("2. Consulta de Disciplinas\n");
            printf("0. Sair!\n");

            scanf("%d",&menu);

            switch(menu){
                case 0:
                    break;
                case 1:
                    printf("[MENU DE CADASTRO]\n" );
                    getchar();
                    printf("Digite o nome: ");
                    fgets(nome, TAM, stdin);
                    printf("Digite o RA: ");
                    scanf("%d", &RA);
                    getchar();
                    printf("Digite o Username: ");
                    fgets(user, TAM, stdin);
                    printf("Digite a senha: ");
                    fgets(senha, TAM, stdin);

                    CadastrarAluno(RA, nome, user, senha);
                    break;
                case 2:
                    printf("[Consulta de Disciplinas]\n");
                    printf("Digite o código da disciplina: \n");
                    scanf("%s", aux);
                    Disciplina* D = BuscarDisciplina(aux, S);
                    if(D == NULL){
                        printf("Não existe\n");
                    }
                    else{
                        printf("\n%s\n", D->nome);
                        printf("Créditos: %d\n", D->credito);
                    }
                    break;
                default:
                    printf("***Opcao Invalida***\n");
                    break;
        }
    }while(menu!=0);

}

    return 0;
}
