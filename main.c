#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct chapaEleicao{
   char nomeChapa[120];
   char nomeCandidato[120];
   char nomeVice[120];
   int numeroChapa;
};

struct Eleitor{
    char nomeEleitor[120];
    char matriculaEleitor[120];
    char cursoEleitor[120];
};

struct Voto{
    char matriculaEleitor[120];
    int votoChapa;
};

void cadastrarChapa(struct chapaEleicao chapa){
    int tamanhoMaximo = 120;
    printf("Cadastre a chapa:\n");
    printf("Digite o nome da chapa: ");
    getchar();
    fgets(chapa.nomeChapa, tamanhoMaximo, stdin);
    printf("Digite o nome do candidato: ");
    fgets(chapa.nomeCandidato, tamanhoMaximo, stdin);
    printf("Digite o nome do vice: ");
    fgets(chapa.nomeVice, tamanhoMaximo, stdin);
    printf("Digite o numero da chapa:");
    scanf("%d", &chapa.numeroChapa);

    char numeroString[3];
    sprintf(numeroString, "%d", chapa.numeroChapa);

    FILE *chapaTextoFile;
    chapaTextoFile = fopen("chapasTexto.txt", "r");
    char line[150];
    while(fgets(line, sizeof(line), chapaTextoFile)){
        if(strstr(line, numeroString)){
            printf("Chapa ja cadastrada\n");
            fclose(chapaTextoFile);
            menu();
        }
    }
    fclose(chapaTextoFile);
    chapaTextoFile = fopen("chapasTexto.txt", "r");
    while(fgets(line, sizeof(line), chapaTextoFile)){
        if(strstr(line, chapa.nomeChapa)){
            printf("Chapa ja cadastrada\n");
            fclose(chapaTextoFile);
            menu();
        }

    }
    fclose(chapaTextoFile);
    chapaTextoFile = fopen("chapasTexto.txt", "a");
    fprintf(chapaTextoFile, " Nome da Chapa: %s Nome do Candidato: %s Nome do Vice: %s Numero da Chapa: %d\n\n", chapa.nomeChapa, chapa.nomeCandidato, chapa.nomeVice, chapa.numeroChapa);
    fclose(chapaTextoFile);

    FILE *chapaFile;
    chapaFile = fopen("chapas.dat", "a");
    fwrite(&chapa, sizeof(struct chapaEleicao), 1, chapaFile);
    fclose(chapaFile);

    printf("\nO nome da chapa cadastrada eh: %s", chapa.nomeChapa);
    printf("O nome do candidato cadastrado eh : %s", chapa.nomeCandidato);
    printf("O nome do vice cadastrado eh : %s", chapa.nomeVice);
    printf("O numero da chapa cadastrado eh: %d\n", chapa.numeroChapa);
}

void mostrarChapas(){
    FILE *chapaTextoFile;
    chapaTextoFile = fopen("chapasTexto.txt", "r");
    char line[150];
    printf("As  chapas cadastradas sao:\n\n");
    while(fgets(line, sizeof(line), chapaTextoFile)){
        printf("%s", line);
    }
    fclose(chapaTextoFile);
}

void cadastrarEleitor(struct Eleitor eleitor){
    int tamanhoMaximo = 120;
    printf("Cadastre-se Eleitor:\n");
    printf("Digite o seu nome: ");
    getchar();
    fgets(eleitor.nomeEleitor, tamanhoMaximo, stdin);
    printf("Digite o seu curso: ");
    fgets(eleitor.cursoEleitor, tamanhoMaximo, stdin);
    printf("Digite a sua matricula: ");
    fgets(eleitor.matriculaEleitor, tamanhoMaximo, stdin);

    FILE *eleitorTextoFile;
    eleitorTextoFile = fopen("eleitoresTexto.txt", "r");
    char line[150];
    while(fgets(line, sizeof(line), eleitorTextoFile)){
        if(strstr(line, eleitor.matriculaEleitor)){
            printf("Eleitor ja cadastrado\n");
            fclose(eleitorTextoFile);
            menu();
        }
    }
    fclose(eleitorTextoFile);
    eleitorTextoFile = fopen("eleitoresTexto.txt", "a");
    fprintf(eleitorTextoFile, " Nome do Eleitor: %s Curso do Eleitor: %s Matricula do Eleitor: %s\n\n", eleitor.nomeEleitor, eleitor.cursoEleitor, eleitor.matriculaEleitor);
    fclose(eleitorTextoFile);

    FILE *eleitorFile;
    eleitorFile = fopen("eleitores.dat", "a");
    fwrite(&eleitor, sizeof(struct Eleitor),1, eleitorFile);
    fclose(eleitorFile);

    printf("\nO nome cadastrado eh: %s", eleitor.nomeEleitor);
    printf("O nome curso cadastrado eh : %s", eleitor.cursoEleitor);
    printf("A matricula cadastrada eh : %s", eleitor.matriculaEleitor);

}

void mostrarEleitores(){
    FILE *eleitorTextoFile;
    eleitorTextoFile = fopen("eleitoresTexto.txt", "r");
    char line[150];
    printf("Os eleitores cadastrados sao:\n\n");
    while(fgets(line, sizeof(line), eleitorTextoFile)){
        printf("%s", line);
    }
    fclose(eleitorTextoFile);
}

void votar(struct Voto voto){
    int encontreiEleitor = 0, encontreiChapa = 0;
    int tamanhoMaximo = 120;
    mostrarChapas();
    printf("Vote Eleitor:\n");
    getchar();
    printf("Digite a sua matricula: ");
    fgets(voto.matriculaEleitor, tamanhoMaximo, stdin);
    printf("Digite o numero da chapa: ");
    scanf("%d", &voto.votoChapa);

    char votoString[3];
    sprintf(votoString, "%d", voto.votoChapa);

    FILE *votoTextoFile;
    votoTextoFile = fopen("votosTexto.txt", "r");
    char line[150];
    while(fgets(line, sizeof(line), votoTextoFile)){
        if(strstr(line, voto.matriculaEleitor)){
            printf("Voce ja votou!!!\n");
            fclose(votoTextoFile);
            menu();
        }
    }
    fclose(votoTextoFile);

    FILE *eleitoresTextoFile;
    eleitoresTextoFile = fopen("eleitoresTexto.txt", "r");
    while(fgets(line, sizeof(line), eleitoresTextoFile)){
        if(strstr(line, voto.matriculaEleitor)){
            encontreiEleitor = 1;
            break;
        }
    }
    fclose(eleitoresTextoFile);
    if(encontreiEleitor == 0){
        printf("Eleitor nao cadastrado\n");
        menu();
    }

    FILE *chapaTextoFile;
    chapaTextoFile = fopen("chapasTexto.txt", "r");
    while(fgets(line, sizeof(line), chapaTextoFile)){
        if(strstr(line, votoString)){
            encontreiChapa = 1;
            break;
        }

    }
    fclose(chapaTextoFile);
    if(encontreiChapa == 0){
        printf("Chapa Inexistente\n");
        menu();
    }

    votoTextoFile = fopen("votosTexto.txt", "a");
    fprintf(votoTextoFile, " Matricula do Eleitor: %s Voto do Eleitor: %d\n\n", voto.matriculaEleitor, voto.votoChapa);
    fclose(votoTextoFile);

    FILE *votoFile;
    votoFile = fopen("votos.dat", "a");
    fwrite(&voto, sizeof(struct Voto), 1, votoFile);
    fclose(votoFile);

    printf("A sua matricula eh : %s", voto.matriculaEleitor);
    printf("O numero da chapa escolhida foi: %d\n", voto.votoChapa);
}

void abrirUrna(){
    FILE *votoTextoFile;
    votoTextoFile = fopen("votosTexto.txt", "r");
    char line[150];
    printf("Os votos cadastrados sao:\n\n");
    while(fgets(line, sizeof(line), votoTextoFile)){
        printf("%s", line);
    }
    fclose(votoTextoFile);
}

void divulgarResultado(){
   int maisVotado;
   struct Voto votoLeitura;

   int *votos;
   size_t votosSize = 0;
   votos = calloc(votosSize, sizeof(int));

   FILE *votosFile;
   votosFile = fopen("votos.dat", "r");

   while(fread(&votoLeitura, sizeof(struct Voto), 1, votosFile)){
        votosSize++;
        votos = realloc(votos, votosSize *sizeof(int));
        votos[votosSize-1] = votoLeitura.votoChapa;
   }
   fclose(votosFile);
    int maxCount = 0;
    for(int i = 0;i<votosSize;i++){
        int count = 0;
        for(int j = i+1;j<votosSize;j++){
            if(votos[i] == votos[j]){
                count++;
            }
        }
        if(count > maxCount){
            maxCount = count;
            maisVotado = votos[i];
        }
    }
    free(votos);

    struct chapaEleicao chapaLeitura;
    char chapaVencedora[150];

    FILE *chapaFile;
    chapaFile = fopen("chapas.dat", "r");
    while(fread(&chapaLeitura, sizeof(struct chapaEleicao), 1, chapaFile)){
        if(chapaLeitura.numeroChapa == maisVotado){
            strcpy(chapaVencedora, chapaLeitura.nomeChapa);
        }
    }
    fclose(chapaFile);
    printf("A chapa vencedora foi: %s\n", chapaVencedora);
    remove(votosFile);
    votosFile= fopen("votos.dat", "w");
    fclose(votosFile);
    FILE *votoTextoFile;
    votoTextoFile = fopen("votosTexto.txt", "r");
    fclose(votoTextoFile);
    remove(votoTextoFile);
    votoTextoFile = fopen("votosTexto.txt", "w");
    fclose(votoTextoFile);
}

void menu(){
	int opcao;
    struct chapaEleicao chapa;
    struct Eleitor eleitor;
    struct Voto voto;

	while(1){
		printf("\nBem vindo ao Sistema de Controle das Eleicoes Internas da UFU");
        printf("\nOpcoes para o Perfil Administrador:");
        printf("\n1- Cadastrar Chapa");
        printf("\n2- Mostrar Chapas");
        printf("\n3- Mostrar Eleitores");
        printf("\n4- Abrir Urna");
        printf("\nOpcoes para o Perfil Eleitor:");
        printf("\n5- Cadastrar Eleitor");
        printf("\n6- Votar");
        printf("\nOpcoes para o Perfil Geral:");
        printf("\n7- Divulgar Resultado");
		printf("\n9- Sair ");
		printf("\nDigite opção: ");
		scanf("%d", &opcao);

		if(opcao == 1) cadastrarChapa(chapa);
		if(opcao == 2) mostrarChapas();
		if(opcao == 3) mostrarEleitores();
		if(opcao == 4) abrirUrna();
		if(opcao == 5) cadastrarEleitor(eleitor);
		if(opcao == 6) votar(voto);
		if(opcao == 7) divulgarResultado();
		if(opcao == 9) return;
	}
}


int main(){
	menu();
}
