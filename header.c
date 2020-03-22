#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "header.h"

int cmp(const void *x, const void *y){

    if (*(double *)y > *(double *)x) 
        return 1;
    if (*(double *) y <  *(double *)x) 
        return -1; 
    return 0;

}
Aluno* newAluno(int RA, char* nome, char* login, char* senha){
    Aluno* A = (Aluno*) malloc (sizeof(Aluno));


    A->RA= RA;
    strcpy(A->nome, nome);
    strcpy(A->login ,login);
    strcpy(A->senha ,senha);

    return A;
}

Aluno* retornaAluno(char* Username){
    char info[100];
    char *nome, *user, *pass;
    int RA;
    int i = 0;

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


void cadastrarAluno(int RA, char* nome, char* login, char* senha){
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
    int loginValid = 0;
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
            loginValid = 1;
            break;
        }
    }while(fscanf(Arquivo, "%c", &aux) != EOF);

    return loginValid;
}

Sistema* newSistema(){
    Sistema* s = (Sistema*) malloc (sizeof(Sistema));
    s->v = (Disciplina*) malloc (TAM * sizeof(Disciplina));
    s->top = 0;

    for(int i = 0; i < TAM; i++){
        strcpy(s->v[i].prereq, "Nenhum");
    }
    return s;
}

Sistema* carregaD(){
    Sistema* s = newSistema();
    char aux[100], *aux2;
    int i = 0;

    FILE* ArquivoD, *ArquivoP;
    ArquivoD = fopen("Disciplinas.txt", "r");
    ArquivoP = fopen("Prerequisitos.txt", "r");

    do{
        i = 0;
        fgets(aux, 100, ArquivoD);
        strcpy(s->v[s->top].codigo,  strtok(aux, ","));
        strcpy(s->v[s->top].nome,  strtok(NULL, ","));
        s->v[s->top].credito = atoi(strtok(NULL, ","));

        while(!i){
            fgets(aux, 100, ArquivoP);
            aux2 = strtok(aux, ",");

            if(strcmp(aux2,    s->v[s->top].codigo) == 0){
                strcpy(s->v[s->top].prereq, strtok(NULL, ","));
                i = 1;
            }
        }
        s->top++;
    }while(s->top < 42);

    fclose(ArquivoP);
    fclose(ArquivoD);

    return s;
}

Disciplina* buscarDisciplina(char* codigo, Sistema*s){
    int i;
    Disciplina* disciplina = NULL;

    for(i = 0; i < s->top; i++){
        if (strcmp(codigo, s->v[i].codigo) == 0){
            disciplina = newDisciplina(s->v[i].codigo, s->v[i].nome, s->v[i].prereq, s->v[i].credito);
            break;
        }
    }

    return disciplina;
}

void matricular(char* user, Sistema* s) {

    char *disP, disP2[10], *disP3, codigos[10][10], aux[100];
    int semestre, w=0, creditos=0, semestreAtual = 0, ra, j=0, k, l, validation = 0;
    float nota, falta;

    Disciplina D[10];
    FILE* arquivo;
    Aluno* A = retornaAluno(user);

    do{
        l=0;
        if (w > 0)
            printf("Semestre Inválido\n");
        printf("Digite o semestre: ");
        scanf("%d", &semestre);

        arquivo = fopen("AlunosDisciplinas.txt", "r");

        if(arquivo != NULL){
            do{
                if (l==0)
                    fgets(aux, 100, arquivo);

                ra = atoi(strtok(aux, ","));
                disP = strtok(NULL, ",");

                if(A->RA == ra){
                    semestreAtual = atoi(strtok(NULL, ","));
                }

                l++;
                fgets(aux, 100, arquivo);
            }while(!feof(arquivo)) ;
            fclose(arquivo);
        }
        else{
            break;
        }
        w++;
    }while(semestre < semestreAtual);


    printf("Digite XX000 para encerrar\n");

    do{
        w=0;
        printf("Digite o código da disciplina: ");
        scanf("%s", codigos[j]);

        for(register int i = 0; i < s->top; i++){
            if(strcmp(codigos[j], s->v[i].codigo) == 0){
                D[j] =  s->v[i];
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
            arquivo = fopen("AlunosDisciplinas.txt", "r");

            if(strcmp(D[i].prereq,"\n\0") != 0){
                //Escrever Lógica de Verificaçãp de prerequisitos denovo
                do{
                    if (!k){
                        fgets(aux, 100, arquivo);
                    }

                    ra = atoi(strtok(aux, ","));
                    disP = strtok(NULL, ",");

                    int v;
                    for(v = 0; v < strlen(D[i].prereq)-1; v++){
                        disP2[v] = D[i].prereq[v];
                    }
                    disP2[v] = '\0';


                    if(A->RA == ra &&  strcmp(disP, disP2) == 0){
                        strtok(NULL, ",");

                        disP = strtok(NULL, ",");
                        disP3 = strtok(NULL, ",");
                        nota = atof(disP);
                        falta = atof(disP3);

                        if(nota > 5 && falta < 25){
                            validation = 1;
                            break;
                        }
                        else{
                            break;
                        }
                    }

                    fgets(aux, 100, arquivo);
                    k++;
                }while(!feof(arquivo));

                fclose(arquivo);
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
            arquivo = fopen("AlunosDisciplinas.txt", "a+");
            fprintf(arquivo, "%d,%s,%d,%d,%d\n", A->RA, D[i].codigo, semestre, 0, 0);
            fclose(arquivo);
        }
        printf("Transação feita com sucesso!\n");

    }

}

void atualizar(char* user, Sistema* s){
    Aluno *a = retornaAluno(user);
    Disciplina* d[100];
    int semestre, semestreAtual, l, w=0, ra, j, TAM_BUFFER, valid=1;
    char aux[100], *codigo, buffer[100][100];
    float nota = 0.0, falta =0.0;
    FILE* arquivo;

    do{
        arquivo = fopen("AlunosDisciplinas.txt", "r");
        if(arquivo == NULL || !valid){
            printf("Você não está matriculado em nenhuma disciplina\n");
            break;
        }

        l=0;
        if (w > 0)
            printf("Semestre Inválido\n");
        printf("Digite o semestre: ");
        scanf("%d", &semestre);



        do{
            if (l==0){
                fgets(aux, 100, arquivo);
            }

            ra = atoi(strtok(aux, ","));
            strtok(NULL, ",");

            if(a->RA == ra){
                semestreAtual = atoi(strtok(NULL, ","));
                valid = 1;
            }
            else{
                valid = 0;
            }

            l++;
            fgets(aux, 100, arquivo);
        }while(!feof(arquivo));
        w++;
    }while(semestre > semestreAtual);

    rewind(arquivo);
    l=0; j=0;

    fgets(aux, 100, arquivo);
    strcpy(buffer[0], aux);
    if (valid){
            do{


            ra = atoi(strtok(aux, ","));
            codigo = strtok(NULL, ",");
            semestreAtual = atoi(strtok(NULL, ","));

            if(a->RA == ra  &&  semestre == semestreAtual){
                w = 0;
                while(w<s->top){
                    if(!strcmp(codigo, s->v[w].codigo)){
                        d[j] = buscarDisciplina(codigo, s);
                        j++;
                    }
                    w++;
                }
            }
            l++;
            fgets(aux, 100, arquivo);
            strcpy(buffer[l], aux);
        }while(!feof(arquivo));
        TAM_BUFFER =l;
        fclose(arquivo);

        for(int i = 0; i < j;i++){
            printf("nome: %s\n", d[i]->nome);
            printf("código: %s\n", d[i]->codigo);
            printf("Creditos: %d\n", d[i]->credito);
            printf("Pre-Requisitos: %s\n", d[i]->prereq);
        }
        w=0;
        while(!w){
            int i;
            if(w>0)
                printf("Você não esteve matriculado nesta disciplina neste semestre\n");
            printf("Digite o codigo da disciplina: \n");
            scanf("%s", aux);

            for (i = 0; i < j; i++) {
                if(!strcmp(d[i]->codigo, aux)){
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

                arquivo = fopen("AlunosDisciplinas.txt", "w");

                for(j = 0; j < TAM_BUFFER;j++){
                    strcpy(aux, buffer[j]);
                    ra = atoi(strtok(aux, ","));
                    if(a->RA == ra && !strcmp(strtok(NULL, ","),d[i]->codigo)){
                        fprintf(arquivo, "%d,%s,%d,%.2f,%.2f\n", a->RA, d[i]->codigo, semestre, nota, falta);
                    }
                    else{
                        fprintf(arquivo, "%s", buffer[j]);
                    }
                }
                fclose(arquivo);
            }
        }

        printf("Transação feita com sucesso!\n");

    }
}
double retornaCR(int RA, Sistema* s){
    FILE* arquivo;
    double nota=0.0;
    int creditos=0, l=0;
    char aux[100];
    Disciplina* d;
    arquivo = fopen("AlunosDisciplinas.txt", "r");

    do{
        if (l == 0)
            fgets(aux, 100, arquivo);

        if (RA == atoi(strtok(aux, ","))) {
            d = buscarDisciplina(strtok(NULL, ","), s);
            strtok(NULL, ",");
            nota = nota + (atof(strtok(NULL, ",")) * d->credito);
            strtok(NULL, ",");
            creditos += d->credito;
        }
        else{
            strtok(NULL, ",");
            strtok(NULL, ",");
            strtok(NULL, ",");
            strtok(NULL, ",");
        }
        fgets(aux, 100, arquivo);
        l++;
    }while (!feof(arquivo));

    fclose(arquivo);
    return creditos > 0 ? nota/creditos : 0;
}

void geraRelatorio(char* username, Sistema* s){
    FILE* arquivo;
    Aluno* a = retornaAluno(username);
    Aluno* b;
    Disciplina* v[100];
    char *filename, aux[100];
    int l=0, qtdeAlunos = 0, posTurma = 1, ra, ra2;
    float notas[100], faltas[100];
    double crAluno;
    double *crTodos;

    arquivo = fopen("AlunosDisciplinas.txt", "r");

    if (arquivo == NULL){
        printf("Aluno não está matriculado em nenhuma disciplina\n");
    }

    else{
        fclose(arquivo);
        crAluno = retornaCR(a->RA, s);

        arquivo = fopen("Alunos.txt", "r");

        do{
            if(!l){
                fgets(aux, 100, arquivo);
                ra = atoi(strtok(aux, ","));
                qtdeAlunos++;
            }
            else{
                ra2 = atoi(strtok(aux, ","));
                if(ra2 != ra){
                    ra = ra2;
                    qtdeAlunos++;
                }
            }
            fgets(aux, 100, arquivo);
            l++;
        }while (!feof(arquivo));

        rewind(arquivo);

        crTodos = (double*) malloc(qtdeAlunos * sizeof(double));

        l=0;int cont = 0;
        do{
            if(l==0)
                fgets(aux, 100, arquivo);

            ra = atoi(strtok(aux, ","));
            strtok(NULL, ",");
            if (ra != a->RA){
                b = retornaAluno(strtok(NULL, ","));
                crTodos[cont++] = retornaCR(b->RA, s);
                strtok(NULL, ",");
            }
            else{
                strtok(NULL, ",");
                strtok(NULL, ",");
            }

            fgets(aux, 100, arquivo);
            l++;
        }while(!feof(arquivo));

        fclose(arquivo);

        qsort(crTodos, qtdeAlunos, sizeof(double), cmp);


        for(int i = 0; i < cont; i++){
            if(crAluno < crTodos[i]){
                posTurma++;
            }
        }

        arquivo = fopen("AlunosDisciplinas.txt", "r");

        l=0; cont = 0;
        do{
            if(!l)
                fgets(aux, 100, arquivo);

            if (atoi(strtok(aux, ",")) == a->RA){
                v[cont] = buscarDisciplina(strtok(NULL, ","), s);

                strtok(NULL, ",");
                notas[cont] = atof(strtok(NULL, ","));
                faltas[cont] = atof(strtok(NULL, ","));
                cont++;
            }
            fgets(aux, 100, arquivo);
            l++;
        }while (!feof(arquivo));

        fclose(arquivo);
        char strRa[7]; sprintf(strRa, "%d", a->RA);
        filename = strcat(strRa, ".txt");

        arquivo = fopen(filename, "w");
        fprintf(arquivo, "Faculdade de Tecnologia - UNICAMP\n\n");
        fprintf(arquivo, "Relatório de  Matrícula\n\n");
        fprintf(arquivo, "Nome Completo: %s\n", a->nome);
        fprintf(arquivo, "RA: %d\n", a->RA);
        fprintf(arquivo, "Coeficiente de Rendimento: %.2lf\n", crAluno);
        fprintf(arquivo, "Classificação na Turma: %d de %d\n\n\n", posTurma, qtdeAlunos);
        fprintf(arquivo,"%-15s%-12s%-15s%s\n", "Disciplina","Nota","Faltas(%%)","Situação:");

        for(int i = 0; i < cont; i++){
            fprintf(arquivo, "%-15s", v[i]->codigo);

            fprintf(arquivo, "%-12.2f%-15.2f", notas[i], faltas[i]);

            if (notas[i] >= 6 && faltas[i] <25)
                fprintf(arquivo,"%s\n","Aprovado");
            else if (notas[i] < 6 && faltas[i] <25)
                fprintf(arquivo,"%s\n","Reprovado por nota");
            else if (notas[i] >= 6 && faltas[i] >25)
                fprintf(arquivo,"%s\n","Reprovado por falta");
            else
                fprintf(arquivo,"%s\n","Reprovado por nota e falta");
        }
        fclose(arquivo);
    }
}