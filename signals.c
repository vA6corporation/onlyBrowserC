// Para las funciones pause y alarm:
#include <unistd.h>
// Para las constantes SIGALRM y similares
#include <signal.h>

#include <stdio.h>

// Esta función es la que vamos a usar como controlador de la señal SIGINT
void despedida() {
	printf("------------------------\n");
	printf("¿Por qué me interrumpes?\n");
	printf("------------------------\n");
	raise(SIGTERM);
}

int main() {

	// Asociamos la señal SIGINT con la funcion "senal"
	signal(SIGINT, despedida);

	// Comenzamos un bucle que hará que el programa muestre sin
	// parar el mensaje "Nada nuevo por aquí"
	while(1) {
		printf("Nada nuevo por aquí.\n");
	}
}
