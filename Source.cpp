//CRISTIAN GOLBAN Y JORGE VILLACORTA, FP GRUPO A

#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

using namespace std;

const int TAM_C = 4;

typedef enum { blanco, rojo, azul, verde, morado, amarillo, incorrecto } tColor;
typedef tColor tCodigo[TAM_C];
typedef bool tUsados[TAM_C];

tColor char2color(char c);
tColor int2color(int num);
char color2Char(tColor color);
void codigoAleatorio(tCodigo codigo, bool admiterepetidos);
void compararCodigos(const tCodigo codigo, tCodigo hipotesis, int& colocados, int& descolocados);
void introduceHipotesis(tCodigo hipotesis);
int menu();

int main() {
	srand(time(0));
	int op; // op es la variable opcion del menu e i es la variable contadora de los intentos
	int colocado, descolocado; //colocaod y descolocado son las variables que calculan que colores estan colocados y cuales pertenecen al codigo pero no estan en el orden correcto
	tCodigo code, intento;
	string jugada;
	tUsados comprobados = { false };
	bool repetidos = false;
	cout << endl;
	op = menu();
	while (op != 3) {
		if (op == 1) {
			repetidos = true;
			codigoAleatorio(code, repetidos);
			for (int i = 0; (i < 15) && (colocado != 4); i++) {
				cout << "Intento: " << i + 1 << endl;
				introduceHipotesis(intento);
				compararCodigos(code, intento, colocado, descolocado);
			}
			if (colocado == 4) cout << "Felicidades, has adivinado el codigo! " << endl;
			else cout << "No has encontrado el codigo, suerte la proxima vez! " << endl;
			op = menu();
		}
		else {
			repetidos = false;
			codigoAleatorio(code, repetidos);
			for (int i = 0; (i < 15) && (colocado != 4); i++) {
				cout << "Intento: " << i + 1 << endl;
				introduceHipotesis(intento);
				compararCodigos(code, intento, colocado, descolocado);
			}
			if (colocado == 4) cout << "Felicidades, has adivinado el codigo! " << endl;
			else cout << "No has encontrado el codigo, suerte la proxima vez! " << endl;
			cout << endl;
			cout << endl;
			op = menu();
		}
	}
	system("pause");
	return 0;
}

int menu() {
	int opcion;
	cout << "                           MASTERMIND            " << endl;
	cout << "                           ----------            " << endl;
	cout << endl;
	cout << "Descubre el codigo secreto! En cada partida, pensare un codigo de" << endl;
	cout << "colores que tendras que adivinar. En cada intento que hagas te" << endl;
	cout << "dare pistas, diciendote cuantos colores de los que has dicho estan" << endl;
	cout << "bien colocados, y cuantos no." << endl;
	cout << endl;
	cout << "COLORES" << endl;
	cout << "-------" << endl;
	cout << endl;
	cout << "BLANCO: B" << endl;
	cout << "ROJO: R" << endl;
	cout << "AZUL: A" << endl;
	cout << "VERDE: V" << endl;
	cout << "MORADO: M" << endl;
	cout << "AMARILLO: Z" << endl;
	cout << endl;
	cout << "Averigua el codigo secreto en el menor numero posible de intentos(15 maximo)!" << endl;
	cout << endl;
	cout << "1- Jugar a Mastermind (con repeticion de colores)" << endl;
	cout << "2- Jugar a Mastermind (sin repeticion de colores)" << endl;
	cout << "3- Salir" << endl;
	cout << endl;
	cout << "Introduzca una opcion: ";
	cin >> opcion;
	cout << endl;
	while (opcion < 1 || opcion > 3) {
		cout << "Por favor, introduzca un opcion valida: ";
		cin.clear();
		cin.ignore();
		cin >> opcion;
		cout << endl;
	}
	return opcion;
}

char color2Char(tColor color) {
	char colChar;
	if (color == blanco) colChar = 'B';
	else if (color == rojo) colChar = 'R';
	else if (color == azul) colChar = 'A';
	else if (color == verde) colChar = 'V';
	else if (color == morado) colChar = 'M';
	else colChar = 'Z';
	return colChar;
}

tColor char2color(char c) {
	tColor col;
	if (c == 'B' || c == 'b') col = blanco;
	else if (c == 'R' || c == 'r') col = rojo;
	else if (c == 'A') col = azul;
	else if (c == 'V') col = verde;
	else if (c == 'M') col = morado;
	else if (c == 'Z') col = amarillo;
	else col = incorrecto;
	return col;
}

tColor int2color(int num) {
	tColor code;
	if (num == 0) code = blanco;
	else if (num == 1) code = rojo;
	else if (num == 2) code = azul;
	else if (num == 3) code = verde;
	else if (num == 4) code = morado;
	else code = amarillo;
	return code;
}

void codigoAleatorio(tCodigo codigo, bool admiterepetidos) {
	int numColor = 0, b[TAM_C];
	if (admiterepetidos) {
		for (int i = 0; i < TAM_C; i++) {
			numColor = rand() % 6;
			codigo[i] = int2color(numColor);
		}
	}
	else {
		bool b;
		for (int i = 0; i < TAM_C; i++) {
			b = true;
			while (b) {
				numColor = rand() % 6;
				b = false;
				for (int j = 0; j < i && !b; j++) {
					if (codigo[j] == numColor) b = true;
				}
			}
			codigo[i] = int2color(numColor);
		}
	}
}

void introduceHipotesis(tCodigo hipotesis) {
	bool valido = false;
	string jugada;
	cout << "Por favor, introduce un codigo de 4 letras (B, R, A, V, M ó Z): ";
	cout << endl;
	cin >> jugada;
	while (jugada.length() != 4 || !valido) {
		if (jugada.length() != 4) {
			cout << "La longitud del codigo es invalida" << endl;
			cin >> jugada;
		}
		else {
			int check = 0;
			for (int i = 0; i < jugada.length(); i++) {
				if (islower(jugada[i])) jugada.at(i) = toupper(jugada.at(i));
				if (char2color(jugada[i]) == incorrecto) check++;
			}
			if (check == 0) valido = true;
			else {
				cout << "Codigo invalido, introduzca de nuevo: ";
				cin >> jugada;
			}
		}
		cout << endl;
	}
	for (int i = 0; i < jugada.length(); i++) hipotesis[i] = char2color(jugada.at(i));
	cout << endl;
}

void compararCodigos(const tCodigo codigo, tCodigo hipotesis, int& colocados, int& descolocados) {
	colocados = 0, descolocados = 0;
	tUsados usados = { false };
	for (int i = 0; i < TAM_C; i++) {
		if ((hipotesis[i] == codigo[i]) && usados[i] == false) {
			usados[i] = true;
			colocados++;
		}
		else if (codigo[i] != hipotesis[i]) {
			for (int j = 0; j < TAM_C; j++) {
				if ((hipotesis[i] == codigo[j]) && usados[j] == false) {
					usados[j] = true;
					descolocados++;
				}
			}
		}
	}
	cout << "Colocados: " << colocados << " , Descolocados: " << descolocados << endl;
	cout << endl;
}