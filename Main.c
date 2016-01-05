#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#define tam 3

void jogadahumano(char a[][tam]){
	int l, c;
	char h = 'X';
	printf("Informe a linha: ");						//jogada humano
	scanf_s("%d", &l);
	printf("Informe a coluna: ");
	scanf_s("%d", &c);								// fim jogada humano
	while (l<0 || l >= 3){							//começo validaçao
		printf("Valor invalido! Informe a linha: ");
		scanf_s("%d", &l);
	}
	while (c <0 || c >= 3){
		printf("Valor invalido! Informe a coluna: ");
		scanf_s("%d", &c);							// fim validaçao

	}
	while (a[l][c] != 0){
		printf("Casa previamente prenchida! Informe outra linha: ");						//jogada humano
		scanf_s("%d", &l);
		printf("Casa previamente prenchida! Informe outra coluna: ");
		scanf_s("%d", &c);								// fim jogada humano
		while (l<0 || l >= 3){							//começo validaçao
			printf("Valor invalido! Informe a linha: ");
			scanf_s("%d", &l);
		}
		while (c <0 || c >= 3){
			printf("Valor invalido! Informe a coluna: ");
			scanf_s("%d", &c);							// fim validaçao

		}

	}
	a[l][c] = h;
}
void jogadacpu(char a[][tam]){
	int aux, i, j;
	char cpu = 'O';
	aux = rand() % 10;
	i = aux / 4;	// jogada cpu
	aux = rand() % 10;
	j = aux / 4;

	while (a[i][j] != 0){
		aux = rand() % 10;
		i = aux / 4;	// jogada cpu
		aux = rand() % 10;
		j = aux / 4;
	}
	a[i][j] = cpu;//fim jogada cpu
}
int verificarjogadacpu(char a[][tam]){				////////////// continuar a partir daqui
	int chave = 9, chave2 = 9, chave3 = 9;
	chave = ganharcpu(a);
	if (chave == 1)
		return 1;///
	else if (chave != 1)
		chave2 = impedirhumanoganhar(a);
	if (chave2 == -1){
		jogadacpu(a);
		chave3 = verificarganhador(a);
		if (chave3 == -1)
			return -1;
	}
}
int ganharcpu(char a[][tam]){
	int c, l;
	char cpu = 'O';
	l = verificarcoluna(a);
	c = verificarlinha(a);
	if (c != -1 && l != -1){
		a[l][c] = cpu;
		return 1;
	}
	else{
		l = verficardiagonalpri(a);
		if (l != -1)
			a[l][l] = cpu;
		else{
			l = verificardiagonalseglinha(a);
			c = verificardiagonalsegcoluna(a);
			if (c != -1 && l != -1){
				a[l][c] = cpu;
				return 1;
			}

		}
	}
	return -1;
}
int verificarcoluna(char a[][tam]){
	int c, l, cont = 0;
	for (c = 0; c < tam; c++){
		for (l = 0, cont = 0; l < tam; l++){
			if (a[l][c] == 'O')
				cont++;
			if (cont == 2){
				for (c = 0; c < tam; c++){
					for (l = 0; l < tam; l++){
						if (a[l][c] == 0)
							return l;
					}
				}
			}

		}
	}

	return -1;
}
int verificarlinha(char a[][tam]){
	int c, l, sl;
	for (l = 0; l < tam; l++){
		for (c = 0, sl = 0; c < tam; c++){
			if (a[l][c] == 'O')
				sl++;
			if (sl == 2)
				for (l = 0; l < tam; l++)
					for (c = 0; c < tam; c++){
						if (a[l][c] == 0){
							return c;
						}
					}
		}
	}
	return -1;
}
int verficardiagonalpri(char a[][tam]){
	int c, l, sdp = 0;
	for (c = 0; c < tam; c++)
		for (l = 0; l < tam; l++){
			if (l == c){
				if (a[l][c] == 'O')
					sdp++;
				if (sdp == 2){
					for (c = 0; c < tam; c++)
						for (l = 0; l < tam; l++){
							if (l == c){
								if (a[l][c] == 0){
									return l;
								}
							}
						}
				}
			}
		}

	return -1;
}
int verificardiagonalseglinha(char a[][tam]){
	int c, l, sds = 0;
	for (c = 0; c < tam; c++)
		for (l = 0; l < tam; l++)
			if (l == tam - c - 1){
				if (a[l][c] == 'O')
					sds++;
			}
	if (sds == 2){
		for (c = 0; c < tam; c++)
			for (l = 0; l < tam; l++)
				if (l == tam - c - 1){
					if (a[l][c] == 0)
						return l;
				}
	}
	return -1;
}
int verificardiagonalsegcoluna(char a[][tam]){
	int c, l, sds = 0;
	for (l = 0; l < tam; l++)
		for (c = 0; c < tam; c++)
			if (l == tam - c - 1){
				if (a[l][c] == 'O')
					sds++;
			}
	if (sds == 2){
		for (l = 0; l < tam; l++)
			for (c = 0; c < tam; c++)
				if (c == tam - l - 1){
					if (a[l][c] == 0)
						return c;
				}
	}
	return -1;
}
int impedirhumanoganhar(char a[][tam]){
	int c, l;
	char cpu = 'O';
	c = verificarcolunahum(a);
	l = verificarlinhahum(a);
	if (c != -1 && l != -1){
		a[l][c] = cpu;
		return 1;
	}
	l = verificardiagonalprihum(a);
	if (l != -1){
		a[l][l] = cpu;
		return 1;
	}
	l = verficardiagonalseglinhahum(a);
	c = verificardiagonalsegcoluna(a);
	if (l != -1 && c != -1){
		a[l][c] = cpu;
		return 1;
	}
	return -1;
}
int verificarcolunahum(char a[][tam]){
	int c, l, sc;
	for (c = 0; c < tam; c++){
		for (l = 0, sc = 0; l < tam; l++){
			if (a[l][c] == 'X')
				sc++;
			if (sc == 2){
				for (c = 0; c < tam; c++){
					for (l = 0; l < tam; l++){
						if (a[l][c] == 0)
							return l;
					}
				}
			}

		}
	}

	return -1;
}
int verificarlinhahum(char a[][tam]){
	int c, l, sl;
	for (l = 0; l < tam; l++){
		for (c = 0, sl = 0; c < tam; c++){
			if (a[l][c] == 'X')
				sl++;
			if (sl == 2)
				for (l = 0; l < tam; l++)
					for (c = 0; c < tam; c++){
						if (a[l][c] == 0){
							return c;
						}
					}
		}
	}

	return -1;
}
int verificardiagonalprihum(char a[][tam]){
	int c, l, sdp = 0;
	for (c = 0; c < tam; c++)
		for (l = 0; l < tam; l++){
			if (l == c){
				if (a[l][c] == 'X')
					sdp++;
			}
		}
	if (sdp == 2){
		for (c = 0; c < tam; c++)
			for (l = 0; l < tam; l++){
				if (l == c){
					if (a[l][c] == 0){
						return l;
					}
				}
			}
	}
	return -1;
}
int verficardiagonalseglinhahum(char a[][tam]){
	int c, l, sds = 0;
	for (c = 0; c < tam; c++)
		for (l = 0; l < tam; l++)
			if (l == tam - c - 1){
				if (a[l][c] == 'X')
					sds++;
			}
	if (sds == 2){
		for (c = 0; c < tam; c++)
			for (l = 0; l < tam; l++)
				if (l == tam - c - 1){
					if (a[l][c] == 0)
						return l;
				}
	}
	return -1;
}
int verficardiagonalsegcolunahum(char a[][tam]){
	int c, l, sds = 0;
	for (l = 0; l < tam; l++)
		for (c = 0; c < tam; c++)
			if (l == tam - c - 1){
				if (a[l][c] == 'X')
					sds++;
			}
	if (sds == 2){
		for (l = 0; l < tam; l++)
			for (c = 0; c < tam; c++)
				if (c == tam - l - 1){
					if (a[l][c] == 0)
						return c;
				}
	}
	return -1;
}
void mostrarmatriz(char a[][tam]){
	int c, l;
	for (l = 0; l < tam; l++){ //mostrar matriz resutente
		for (c = 0; c < tam; c++){
			printf("%c|", a[l][c]);
		}
		printf("\n");
	}//fim de mostrar
}
int verificarganhador(char a[][tam]){
	int l, c, conth, contc, contcds = 0, conthds = 0;
	for (l = 0; l < tam; l++){
		for (contc = 0, conth = 0, c = 0; c < tam; c++){
			if (a[l][c] == 'X'){
				conth++;
			}
			else if (a[l][c] == 'O'){	//verificar linha
				contc++;
			}
		}
		if (conth == 3)
			return 0;
		if (contc == 3)
			return 1;
	}
	for (c = 0, conth = 0, contc = 0; c < tam; c++){
		for (l = 0; l < tam; l++){
			if (l == c){			// diagonal principal
				if (a[l][c] == 'X'){
					conth++;     //0 para ganho do humano 
				}
				else if (a[l][c] == 'O'){ // 1 para ganho da cpu 
					contc++;
				}

				if (c == tam - 1 - l){			//diagonal seg
					if (a[l][c] == 'X'){
						conthds++;
					}
					else if (a[l][c] == 'O'){
						contcds++;
					}
				}
			}
		}
	}
	if (conth == 3)
		return 0;
	if (contc == 3)
		return 1;
	if (conthds == 3)
		return 0;
	if (contcds == 3)
		return 1;
	for (c = 0; c < tam; c++){			// verificar coluna
		for (l = 0, contc = 0, conth = 0; l < tam; l++){
			if (a[l][c] == 'X'){
				conth++;
			}
			if (a[l][c] == 'O'){
				contc++;
			}
		}
		if (conth == 3)
			return 0;
		if (contc == 3)
			return 1;
		return -1;			//-1 para ninguem ter ganho
	}
}
int main(){
	char a[tam][tam] = { 0 };
	int esc, vez, aux, partida = 0, chave = 9;//i=linha j=coluna
	printf("Tela inicial\n");
	printf("Escolha um opção\n1-Jogar\n2-Sair\n");
	scanf_s("%d", &esc);
	while (esc != 1 && esc != 2){
		printf("Opção invalida! Escolha uma opção valida:\n1-Jogar\n2-Sair");
		scanf_s("%d", &esc);
	}
	do{
		if (esc == 2)
			return 0;
		else{
			printf("Sorteando quem vai jogar vai começar ");
			srand(time(NULL));
			aux = rand() % 10;
			vez = aux % 2;
			if (vez == 0){
				printf("Tela do jogo\nX-Humano\nO-CPU\n");
				printf("O Computador começa\n");
				jogadacpu(a);
				mostrarmatriz(a);
				while (partida < 6){
					jogadahumano(a);
					verificarjogadacpu(a);
					mostrarmatriz(a);
					chave = verificarganhador(a);
					if (chave == 0)
						printf("O humano venceu!");
					else if (chave == 1)
						printf("O computador venceu!");
					partida++;
				}
				printf(" Empate!");
			}
			else{
				printf("Tela do jogo\nX-Humano\nO-CPU\n");
				printf("O Humano começa\n");
				jogadahumano(a);
				jogadacpu(a);
				mostrarmatriz(a);
				while (partida <= 4){
					jogadahumano(a);
					chave = verificarganhador(a);
					verificarjogadacpu(a);
					mostrarmatriz(a);
					chave = verificarganhador(a);
					if (chave == 0){
						printf("O humano venceu!\n");
						printf("Tela inicial\n");
						printf("Escolha um opção\n1-Jogar\n2-Sair\n");
						scanf_s("%d", &esc);
						while (esc != 1 && esc != 2){
							printf("Opção invalida! Escolha uma opção valida:\n1-Jogar\n2-Sair");
							scanf_s("%d", &esc);
						}
						break;
						if (esc == 2)
							return 0;

					}
					else if (chave == 1){
						printf("O computador venceu!\n");
						printf("Tela inicial\n");
						printf("Escolha um opção\n1-Jogar\n2-Sair\n");
						scanf_s("%d", &esc);
						while (esc != 1 && esc != 2){
							printf("Opção invalida! Escolha uma opção valida:\n1-Jogar\n2-Sair");
							scanf_s("%d", &esc);
						}
						break;
						if (esc == 2)
							return 0;
					}
					partida++;
					if (partida == 4){
						printf(" Empate!\n");
						printf("Tela inicial\n");
						printf("Escolha um opção\n1-Jogar\n2-Sair\n");
						scanf_s("%d", &esc);
						while (esc != 1 && esc != 2){
							printf("Opção invalida! Escolha uma opção valida:\n1-Jogar\n2-Sair");
							scanf_s("%d", &esc);
						}
						if (esc == 2)
							return 0;

					}
				}

			}
		}
	} while (esc == 1);
	return 0;
}
