// Breno Souza dos Reis             RA: 232246
// Gilberto da Silva Villa Nova     RA: 173050
// Victor Henrique Barbosa Pereira   RA: 245055

//main.c - Projeto Final - SI200

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "header.h"


int main(){
    int menu;
    int RA; char nome[TAM], user[TAM], senha[TAM], codigos[10][10];
    FILE* arquivo;

    arquivo = fopen("Alunos.txt", "r");

    if (arquivo == NULL){
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

        cadastrarAluno(RA, nome, user, senha);
    }

    else{
        char aux[10];
        int key;

        do{
            fclose(arquivo);
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
            Sistema* s = carregaD();

            //Menu
            printf("[Menu de Opcoes]\n");
            printf("1. Cadastro de Alunos\n");
            printf("2. Consulta de Disciplinas\n");
            printf("3. Realizar Matrícula\n");
            printf("4. Atualizar nota e falta\n");
            printf("5. Gerar Relatório para impressão\n");
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

                    cadastrarAluno(RA, nome, user, senha);
                    break;

                case 2:
                    printf("[Consulta de Disciplinas]\n");
                    printf("Digite o código da disciplina: \n");
                    scanf("%s", aux);
                    Disciplina* d = buscarDisciplina(aux, s);
                    if(d == NULL){
                        printf("Não existe\n");
                    }
                    else{
                        printf("\n%s\n", d->nome);
                        printf("Créditos: %d\n", d->credito);
                        printf("Pre Requisitos: %s\n", d->prereq);
                    }
                    break;

                case 3:
                    matricular(user,s);
                    break;

                case 4:
                    atualizar(user, s);
                    break;
                    
                case 5:
                    geraRelatorio(user, s);
                    break;
                default:
                    printf("***Opcao Invalida***\n");
                    break;
            }
        
    }while(menu!=0);

}

    return 0;
}
