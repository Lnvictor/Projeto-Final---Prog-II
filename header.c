#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "header.h"

int cmp(const void *x, const void *y){

    if (*(double*)y >  *(double*)x) return 1;
    else if (*(double*) y <  *(double*)x) return -1;
    else return 0;

}
Aluno* newAluno(int RA, char* nome, char* login, char* senha){
    Aluno* A = (Aluno*) malloc (sizeof(Aluno));


    A->RA= RA;
    strcpy(A->nome, nome);
    strcpy(A->login ,login);
    strcpy(A->senha ,senha);

    return A;
}

Aluno* RetornaAluno(char* Username){
    char info[100];
    char *nome, *user, *pass;
    int RA;
    register int i = 0;

    FILE* Arquivo;
    Arquivo = fopen("Alunos.txt", "r");

    do{
        if (!i){
            fgets(info, 100, Arquivo);
        }

        RA = atoi(strtok(info, ","));
        nome = strtok(NULL, ",");
        user = strtok(NULL, ",");
        pass = strtok(NULL, ",");

    if(strcmp(user, Username) == 0){
        break;
    }

    if(i!= 0)
        fgets(info, 100, Arquivo);
    }while(info[strlen(info) - 2] !=EOF);

    fclose(Arquivo);
    Aluno *A = newAluno(RA, nome, user, pass);

    return A;
}

Disciplina* newDisciplina(char* codigo, char* nome, char* prereq, int credito){

    Disciplina* D = (Disciplina*) malloc (sizeof(Disciplina));

    strcpy(D->codigo, codigo);
    strcpy(D->nome ,nome);
    strcpy(D->prereq, prereq);
    D->credito = credito;
    return D;
}


void CadastrarAluno(int RA, char* nome, char* login, char* senha){
    FILE* Arquivo;

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
    char aux[100], *aux_2;
    int i = 0;

    FILE* Arquivo_D, *Arquivo_P;
    Arquivo_D = fopen("Disciplinas.txt", "r");
    Arquivo_P = fopen("Prerequisitos.txt", "r");

    do{
        i = 0;
        fgets(aux, 100, Arquivo_D);
        strcpy(S->v[S->top].codigo,  strtok(aux, ","));
        strcpy(S->v[S->top].nome,  strtok(NULL, ","));
        S->v[S->top].credito = atoi(strtok(NULL, ","));

        while(!i){
            fgets(aux, 100, Arquivo_P);
            aux_2 = strtok(aux, ",");

            if(strcmp(aux_2, S->v[S->top].codigo) == 0){
                strcpy(S->v[S->top].prereq, strtok(NULL, ","));
                i = 1;
            }
        }
        S->top++;
    }while(S->top < 42);

    fclose(Arquivo_P);
    fclose(Arquivo_D);

    return S;
}

Disciplina* BuscarDisciplina(char* codigo, Sistema* S){
    int i;
    Disciplina* D = NULL;

    for(i = 0; i < S->top; i++){
        if (strcmp(codigo, S->v[i].codigo) == 0){
            D = newDisciplina(S->v[i].codigo,S->v[i].nome,S->v[i].prereq,S->v[i].credito);
            break;
        }
    }

    return D;
}

void Matricular(char* user, Sistema* S) {
    char aux[100];
    char *dis_p, dis_p2[10], *dis_p3, codigos[10][10];

    register int j=0, k, l;
    int Semestre, w=0, creditos=0, semestre_atual = 0,ra;
    int validation = 0;
    float nota, falta;

    Disciplina D[10];
    FILE* Arquivo;
    Aluno* A = RetornaAluno(user);

    do{
        l=0;
        if (w > 0)
            printf("Semestre Inválido\n");
        printf("Digite o semestre: ");
        scanf("%d", &Semestre);

        Arquivo = fopen("AlunosDisciplinas.txt", "r");

        if(Arquivo != NULL){
            do{
                if (l==0)
                    fgets(aux, 100, Arquivo);

                ra = atoi(strtok(aux, ","));
                dis_p = strtok(NULL, ",");

                if(A->RA == ra){
                    semestre_atual = atoi(strtok(NULL, ","));
                }

                l++;
                fgets(aux, 100, Arquivo);
            }while(!feof(Arquivo)) ;
            fclose(Arquivo);
        }
        else{
            break;
        }
        w++;
    }while(Semestre < semestre_atual);


    printf("Digite XX000 para encerrar\n");

    do{
        w=0;
        printf("Digite o código da disciplina: ");
        scanf("%s", codigos[j]);

        for(register int i = 0; i < S->top; i++){
            if(strcmp(codigos[j], S->v[i].codigo) == 0){
                D[j] =  S->v[i];
                creditos += D[j].credito;
                w=1;
                break;
            }
        }
        if (!w && strcmp(codigos[j],"XX000")){
            printf("Esta disciplina não Existe\n");
        }
        else
            j++;
    }while(strcmp(codigos[j-1],"XX000") != 0);

    if (creditos > 32){
        printf("Quantidade máxima de creditos excedida (32 creditos)\n");
    }

    else{
        for(register int i = 0; i < j-1; i++){
            k=0;
            Arquivo = fopen("AlunosDisciplinas.txt", "r");

            if(strcmp(D[i].prereq,"\n\0") != 0){
                //Escrever Lógica de Verificaçãp de prerequisitos denovo
                do{
                    if (!k){
                        fgets(aux, 100, Arquivo);
                    }

                    ra = atoi(strtok(aux, ","));
                    dis_p = strtok(NULL, ",");

                    register int v;
                    for(v = 0; v < strlen(D[i].prereq)-1; v++){
                        dis_p2[v] = D[i].prereq[v];
                    }
                    dis_p2[v] = '\0';


                    if(A->RA == ra &&  strcmp(dis_p, dis_p2) == 0){
                        strtok(NULL, ",");

                        dis_p = strtok(NULL, ",");
                        dis_p3 = strtok(NULL, ",");
                        nota = atof(dis_p);
                        falta = atof(dis_p3);

                        if(nota > 5 && falta < 25){
                            validation = 1;
                            break;
                        }
                        else{
                            break;
                        }
                    }

                    fgets(aux, 100, Arquivo);
                    k++;
                }while(!feof(Arquivo));

                fclose(Arquivo);
            }
            else{
                validation = 1;
            }

            if(!validation){
                printf("Requisitos necessários não obtidos.\n");
                break;
            }
        }
    }


    if(validation){

        for(register int i = 0; i < j-1;i++){
            Arquivo = fopen("AlunosDisciplinas.txt", "a+");
            fprintf(Arquivo, "%d,%s,%d,%d,%d\n", A->RA, D[i].codigo, Semestre, 0, 0);
            fclose(Arquivo);
        }
        printf("Transação feita com sucesso!\n");

    }

}

void Atualizar(char* user, Sistema* S){
    Aluno *A = RetornaAluno(user);
    Disciplina* D[100];
    int Semestre, semestre_atual, l,w=0,ra,j, TAM_BUFFER, valid=1;
    char aux[100], *codigo, buffer[100][100];
    float nota = 0.0, falta =0.0;
    FILE* Arquivo;

    do{
        Arquivo = fopen("AlunosDisciplinas.txt", "r");
        if(Arquivo == NULL || !valid){
            printf("Você não está matriculado em nenhuma disciplina\n");
            break;
        }

        l=0;
        if (w > 0)
            printf("Semestre Inválido\n");
        printf("Digite o semestre: ");
        scanf("%d", &Semestre);



        do{
            if (l==0){
                fgets(aux, 100, Arquivo);
            }

            ra = atoi(strtok(aux, ","));
            strtok(NULL, ",");

            if(A->RA == ra){
                semestre_atual = atoi(strtok(NULL, ","));
                valid = 1;
            }
            else{
                valid = 0;
            }

            l++;
            fgets(aux, 100, Arquivo);
        }while(!feof(Arquivo));
        w++;
    }while(Semestre > semestre_atual);

    rewind(Arquivo);
    l=0;j=0;

    fgets(aux, 100, Arquivo);
    strcpy(buffer[0], aux);
    if (valid){
            do{


            ra = atoi(strtok(aux, ","));
            codigo = strtok(NULL, ",");
            semestre_atual = atoi(strtok(NULL, ","));

            if(A->RA == ra  &&  Semestre == semestre_atual){
                w = 0;
                while(w<S->top){
                    if(!strcmp(codigo,S->v[w].codigo)){
                        D[j] = BuscarDisciplina(codigo, S);
                        j++;
                    }
                    w++;
                }
            }
            l++;
            fgets(aux, 100, Arquivo);
            strcpy(buffer[l], aux);
        }while(!feof(Arquivo));
        TAM_BUFFER =l;
        fclose(Arquivo);

        for(register int i = 0; i < j;i++){
            printf("nome: %s\n", D[i]->nome);
            printf("código: %s\n", D[i]->codigo);
            printf("Creditos: %d\n", D[i]->credito);
            printf("Pre-Requisitos: %s\n", D[i]->prereq);
        }
        w=0;
        while(!w){
            register int i;
            if(w>0)
                printf("Você não esteve matriculado nesta disciplina neste semestre\n");
            printf("Digite o codigo da disciplina: \n");
            scanf("%s", aux);

            for (i = 0; i < j; i++) {
                if(!strcmp(D[i]->codigo, aux)){
                    w++;
                    break;
                }
            }

            if(w){
                do{
                    printf("Digite a nota: ");
                    scanf("%f", &nota);
                }while(nota< 0 || nota >10);

                do{
                    printf("Digite o percentual de falta: ");
                    scanf("%f", &falta);
                }while(falta<0 || falta > 100);

                Arquivo = fopen("AlunosDisciplinas.txt", "w");

                for(j = 0; j < TAM_BUFFER;j++){
                    strcpy(aux, buffer[j]);
                    ra = atoi(strtok(aux, ","));
                    // printf("%s", buffer[j]);
                    if(A->RA == ra && !strcmp(strtok(NULL, ","),D[i]->codigo)){
                        fprintf(Arquivo, "%d,%s,%d,%.2f,%.2f\n", A->RA, D[i]->codigo, Semestre, nota, falta);
                    }
                    else{
                        fprintf(Arquivo, "%s", buffer[j]);
                    }
                }
                fclose(Arquivo);
            }
        }

        printf("Transação feita com sucesso!\n");

    }
}
double retornaCR(int RA, Sistema* S){
    FILE* Arquivo;
    double nota=0.0;
    int creditos=0, l=0;
    char aux[100];
    Disciplina* D;
    Arquivo = fopen("AlunosDisciplinas.txt", "r");

    do{
        if (l == 0)
            fgets(aux, 100, Arquivo);

        if (RA == atoi(strtok(aux, ","))) {
            D = BuscarDisciplina(strtok(NULL, ","), S);
            strtok(NULL, ",");
            nota = nota + (atof(strtok(NULL, ",")) * D->credito);
            strtok(NULL, ",");
            creditos+=D->credito;
        }
        else{
            strtok(NULL, ",");
            strtok(NULL, ",");
            strtok(NULL, ",");
            strtok(NULL, ",");
        }
        fgets(aux, 100, Arquivo);
        l++;
    }while (!feof(Arquivo));

    fclose(Arquivo);
    return creditos > 0 ? nota/creditos : 0;
}

void geraRelatorio(char* username, Sistema* S){
    FILE* Arquivo;
    Aluno* A = RetornaAluno(username);
    Aluno* B;
    Disciplina* v[100];
    char *filename, aux[100];
    int l=0, qtde_alunos = 0, pos_turma = 1, ra, ra_2;
    float notas[100], faltas[100];
    double cr_aluno = retornaCR(A->RA, S);
    double *cr_todos;

    Arquivo = fopen("Alunos.txt", "r");

    // while(fread(&letra, sizeof(char),1, Arquivo)){
    //     if(letra == fimlinha){
    //         qtde_alunos++;
    //     }
    // }

    do{
        if(!l){
            fgets(aux, 100, Arquivo);
            ra = atoi(strtok(aux, ","));
            qtde_alunos++;
        }
        else{
            ra_2 = atoi(strtok(aux, ","));
            if(ra_2 != ra){
                ra = ra_2;
                qtde_alunos++;
            }
        }
        fgets(aux, 100, Arquivo);
        l++;
    }while (!feof(Arquivo));

    rewind(Arquivo);

    cr_todos = (double*) malloc(qtde_alunos * sizeof(double));

    l=0;int cont = 0;
    do{
        if(l==0)
            fgets(aux, 100, Arquivo);

        ra = atoi(strtok(aux, ","));
        strtok(NULL, ",");
        if (ra != A->RA){
            B = RetornaAluno(strtok(NULL, ","));
            cr_todos[cont++] = retornaCR(B->RA, S);
            strtok(NULL, ",");
        }
        else{
            strtok(NULL, ",");
            strtok(NULL, ",");
        }

        fgets(aux, 100, Arquivo);
        l++;
    }while(!feof(Arquivo));

    fclose(Arquivo);

    qsort(cr_todos, qtde_alunos, sizeof(double), cmp);

    for(register int i = 0; i < cont; i++){
        if(cr_aluno < cr_todos[i]){
            pos_turma++;
        }
    }

    Arquivo = fopen("AlunosDisciplinas.txt", "r");
    l=0; cont = 0;
    do{
        if(!l)
            fgets(aux, 100, Arquivo);

        if (atoi(strtok(aux, ",")) == A->RA){
            v[cont] = BuscarDisciplina(strtok(NULL, ","), S);

            strtok(NULL, ",");
            notas[cont] = atof(strtok(NULL, ","));
            faltas[cont] = atof(strtok(NULL, ","));
            cont++;
        }
        fgets(aux, 100, Arquivo);
        l++;
    }while (!feof(Arquivo));

    fclose(Arquivo);
    char str_ra[7]; sprintf(str_ra, "%d", A->RA);
    filename = strcat(str_ra, ".txt");

    Arquivo = fopen(filename, "w");
    fprintf(Arquivo, "Faculdade de Tecnologia - UNICAMP\n\n");
    fprintf(Arquivo, "Relatório de  Matrícula\n\n");
    fprintf(Arquivo, "Nome Completo: %s\n", A->nome);
    fprintf(Arquivo, "RA: %d\n", A->RA);
    fprintf(Arquivo, "Coeficiente de Rendimento: %.2lf\n", cr_aluno);
    fprintf(Arquivo, "Classificação na Turma: %d de %d\n\n\n", pos_turma, qtde_alunos);
    fprintf(Arquivo,"%-15s%-12s%-15s%s\n", "Disciplina","Nota","Faltas(%%)","Situação:");

    for(register int i = 0; i < cont; i++){
        fprintf(Arquivo, "%-15s", v[i]->codigo);

        fprintf(Arquivo, "%-12.2f%-15.2f", notas[i], faltas[i]);

        if (notas[i] >= 6 && faltas[i] <25)
            fprintf(Arquivo,"%s\n","Aprovado");
        else if (notas[i] < 6 && faltas[i] <25)
            fprintf(Arquivo,"%s\n","Reprovado por nota");
        else if (notas[i] >= 6 && faltas[i] >25)
            fprintf(Arquivo,"%s\n","Reprovado por falta");
        else
            fprintf(Arquivo,"%s\n","Reprovado por nota e falta");
    }
    fclose(Arquivo);
}
