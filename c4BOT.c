#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

int C;
int R;

int mejorJugada(int casosOk[][3], int casosNOok[][3]);
int prometedorCol(char tablero[][C], int j,int i,char fichaJug);
int prometedorFila(char tablero[][C], int i, int j,char fichaJug);
int prometedorDiagonal(char tablero[][C], int i, int j, char dir, char fichaJug);
int analizaEstados(char tablero[][C], char fichaBot, char fichaJug, int jugadas[][3],char Usuario);

int main(){

//ESTAS VARAIABLES ES NECESARIO QUE SEAN GLOBALES  -  EN CASO CONTRARIO CONTACTE CON EL CREADOR
    C = 7;
    R = 6;

    char tablero[R][C];//Definicion del Tablero

	for (int i = 0; i < R; ++i){/////////ES RECOMENDABLE INICIALIZAR LA MATRIZ CON UN CARACTER EN CONCRETO
		for (int j = 0; j < C; ++j){
				tablero[i][j] = '-';
		}
	}

    char fichaBot      = 'X';
    char fichaJugador  = 'O';

//EL DESEMPEÑO DE ALGORITMO EMPIEZA AQUÍ, obiamente se llamaran a las siguinetes funciones para cada turno del BOT
    //En primer lugar definmos dos vectores casosOk y casosNOok
    //Para obtener los las mejores jugadas llamaremos dos veces a cada funcion

//ESTUDIO DE LOS CASOS FAVORABLES PARA EL BOT
	int casosOk[4][3];
	analizaEstados(tablero,fichaBot,fichaJugador,casosOk,'B');
    //Los Atributos que se le pasa son los siguinetes
        //El primer atriuto es el tablero
        //El seguno atributo es la ficha del BOT
        //El tercer atributo es la ficha del JUGADOR
        //El tercer atributo es el vector donde guardaremos los casos estudiados
        //El ultimo atributo es B en le caso de lo llamemos para el BOT  o  J en caso de que lo llamos para el JUGADOR


//ESTUDIO DE LOS CASOS NO FAVORABLES PARA EL BOT
	int casosNOok[4][3];
	analizaEstados(tablero,fichaJugador,fichaBot,casosNOok,'J');
    //En este Caso llamos a la funcion intercambiando las ficahs de de posicion

//LLAMAMOS A ESTA FUNCION Y OBTENEMOS LA MEJOR JUGADA
	int columna = mejorJugada(casosOk,casosNOok);
    //EL VALOR DE RETORNO ES LA COLUMNA DE LA MEJOR JUGADA

    return 1;
}

int analizaEstados(char tablero[][C], char fichaBot, char fichaJug, int jugadas[][3],char Usuario){//buscamos las posibles combianciones de ganar


	//Buscar por columnas
	int posCol;
	int numColFich = 0; //numeor de ficahs faborable en la jugada
	for (int j = 0; j < C; j++){
		for (int i = 0; i < R-3; i++){
			if (prometedorCol(tablero,j,i,fichaJug)){

				int numColFichaux = 0;
				for  (int x = i; x < i+4; x++){
					if (tablero[x][j] == fichaBot)
						numColFichaux++;
				}

				if (numColFich <= numColFichaux){
							posCol = j;
							numColFich = numColFichaux;
				}
			}
		}
	}

	//Buscar por filas
	int posFila;// columna pra introducir la ficah de la mejor jugada del escaneo por columnas
	int minFil = 35000;//guardamos le numeorminimo de oviemientos para realizar la jugada
	int numFilFich = 0; //numeor de ficahs faborable en la jugada
	for (int i = 0; i < R; i++ ){
		for (int j = 0; j < C-3; j++ ){
			if (prometedorFila(tablero,i,j,fichaJug) ){
				int numFilFichaux = 0;
				for  (int y = j; y < j+4; y++){
					if (tablero[i][y] == fichaBot)
						numFilFichaux++;
				}

				int numMov;
				for (int y = j; y < j+4; y++){
					numMov = 0;
					for (int x = i; x < R; x++)
						if (tablero[x][y] != fichaJug && tablero[x][y] != fichaBot){
							numMov++;
						}

					if (numMov % 2 == 1 && Usuario == 'B' ){
						if (numFilFich <= numFilFichaux){
							if (numMov <= 3){
								posFila = y;
								minFil = numMov;
								numFilFich = numFilFichaux;
							}
						}
					}else if (Usuario == 'J' && numMov != 0){
							if (numFilFich <= numFilFichaux){
								if (numMov <= 3){
									posFila = y;
									minFil = numMov;
									numFilFich = numFilFichaux;
								}
							}
					}
				}
			}
		}
	}

//Busacr por diagonales
/////////////////////////////
	int posDigDer;//sera el valos de la columan en el que se quiera insetrar la ficha par a la jugada
	int minDigDer = 35000;
	int numFichDer = 0;
	for (int i = 3; i < R; ++i){
		for (int j = 0; j < C-3; ++j){
			if (prometedorDiagonal(tablero,i,j,'D', fichaJug) ){
				int numMov;
				int numFichaux;
				for (int x = 0; x <= 3; x++){//se compreuba una posible diagonal y se busca la ficaha que mjor staisfagaalafuncion fitness
					numMov = 0;
					numFichaux = 0;
					for (int pos = i-x; pos < R; pos++){//recorremos las columnas
						if (tablero[pos][j+x] != fichaJug && tablero[pos][j+x] != fichaBot){
							numMov++;
						}
					}
					for (int x = 0; x <= 3; x++){
						if (tablero[i-x][j+x] == fichaBot)
							numFichaux++;
					}

					if (numMov % 2 == 1 && Usuario == 'B'){
						if (numFichaux >= numFichDer)
							if (numMov <= minDigDer || numFichaux >= 3){
								minDigDer = numMov;
								posDigDer = j+x;
								numFichDer =numFichaux;
							}
					}else if (Usuario == 'J' && numMov != 0){
						if (numFichaux >= numFichDer)
							if (numMov <= minDigDer || numFichaux >= 3){
								minDigDer = numMov;
								posDigDer = j+x;
								numFichDer =numFichaux;
							}
					}
				}
			}
		}
	}

////////////////////////////
	int posDigIzq;//sera el valos de la columan en el que se quiera insetrar la ficha par a la jugada
	int minDigIzq = 35000;
	int numFichIzq = 0;
	for (int i = 0; i < R-3; ++i){
		for (int j = 0; j < C-3; ++j){
			if (prometedorDiagonal(tablero,i,j,'I', fichaJug) ){
				//Buscamos cauntas ficahs hacen falta para cada completar cada pscion de la diagonal
				//Sera  faborable si el numero de fiuchas par una poscion es impar o 1
				int numMov;
				int numFichaux;
				for (int x = 0; x <= 3; x++){//se compreuba una posible diagonal y se busca la ficaha que mjor staisfagaalafuncion fitness
					numMov = 0;
					numFichaux = 0;
					for (int pos = i+x; pos < R; pos++){//recorremos las columnas
						if (tablero[pos][j+x] != fichaJug && tablero[pos][j+x] != fichaBot){
							numMov++;
						}
					}
					for (int x = 0; x <= 3; x++){
						if (tablero[i+x][j+x] == fichaBot)
							numFichaux++;
					}

					if ((numMov % 2 == 1) && (Usuario == 'B')){
						if (numFichaux >= numFichIzq)
							if (numMov <= minDigIzq || numFichaux >= 3){
								minDigIzq = numMov;
								posDigIzq = j+x;
								numFichIzq =numFichaux;
							}
					}else if ((Usuario == 'J') && numMov != 0){
							if (numFichaux >= numFichIzq)
								if (numMov <= minDigIzq || numFichaux >= 3){
									minDigIzq = numMov;
									posDigIzq = j+x;
									numFichIzq =numFichaux;
								}
					}
				}
			}
		}
	}

	jugadas[0][0] = posCol;
	if (numColFich == 3)
		jugadas[0][1] = 1;
	else
		jugadas[0][1] = 2;
	jugadas[0][2] = numColFich;

	jugadas[1][0] = posFila;
	jugadas[1][1] = minFil;
	jugadas[1][2] = numFilFich;

	jugadas[2][0] = posDigDer;
	jugadas[2][1] = minDigDer;
	jugadas[2][2] = numFichDer;

	jugadas[3][0] = posDigIzq;
	jugadas[3][1] = minDigIzq;
	jugadas[3][2] = numFichIzq;
	return 1;
}

int prometedorDiagonal(char tablero[][C], int i, int j, char dir,char fichaJug){
	if (dir == 'D'){
		for (int x = 0; x <= 3; x++){
			if (tablero[i-x][j+x] == fichaJug)
				return 0;
		}
		return 1;
	}else if (dir == 'I'){
		for (int x = 0; x <= 3; x++){
			if (tablero[i+x][j+x] == fichaJug)
				return 0;
		}
		return 1;
	}
	return 0;
}

int prometedorFila(char tablero[][C], int i,int j,char fichaJug){
	int count = 0;
	for  (int y = j; y < j+4; y++){
		if (tablero[i][y] == fichaJug){
			count = 0;
		}else
			count++;
	}
	if (count > 3)
		return 1;
	else
		return 0;
}

int prometedorCol(char tablero[][C], int j,int i,char fichaJug){
	int count = 0;
	for  (int x = i; x < i+4; x++){
		if (tablero[x][j] == fichaJug){
			count = 0;
		}else
			count++;
	}
	if (count > 3)
		return 1;
	else
		return 0;
}

int mejorJugada(int casosOk[][3], int casosNOok[][3]){
	for (int i = 0; i < 4; i++){
		if (casosNOok[i][1] == 1 && casosNOok[i][2] == 3){
			return casosNOok[i][0];
		}
	}
	for (int i = 0; i < 4; i++){
		if (casosOk[i][1] == 1 && casosOk[i][2] == 3){
			return casosOk[i][0];
		}
	}
	for (int i = 0; i < 4; i++){
		if (casosNOok[i][1] == 1 && casosNOok[i][2] >= 2){
			return casosNOok[i][0];
		}
	}
	for (int i = 0; i < 4; i++){
		if (casosOk[i][1] == 1 && casosOk[i][2] >= 2){
			return casosOk[i][0];
		}
	}
	for (int i = 0; i < 4; i++){
		if (casosOk[i][1] == 1 && casosOk[i][2] > 0){
			return casosOk[i][0];
		}
	}
	
	srand(time(NULL));
	return casosOk[rand() % 5][0];
}
