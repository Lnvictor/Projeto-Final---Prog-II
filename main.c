#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 50

int main(){
    int menu;

    do{
        printf("[Menu de Opcoes]\n");
        printf("1. Cadastro de Alunos\n");
        printf("2. Consulta de Disciplinas\n");
        printf("0. Sair!\n");

        scanf("%d",&menu);

        switch(menu){
            case 0:
                break;
            case 1:
                printf("[Cadastro de Alunos]\n");
                break;
            case 2:
                printf("[Consulta de Disciplinas]\n");
                break;
            default:
                printf("***Opcao Invalida***\n");
                break;
        }
    }while(menu!=0);



    return 0;
}
