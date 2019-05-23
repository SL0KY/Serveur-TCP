#include <stdio.h>
#include <stdlib.h> /* pour exit */
#include <unistd.h> /* pour sleep */
#include <string.h> /* pour memset */
#include <sys/types.h> /* pour socket */
#include <sys/socket.h>
#include <netinet/in.h> /* pour struct sockaddr_in */
#include <arpa/inet.h> /* pour htons et inet_aton */
#define PORT IPPORT_USERRESERVED // = 5000

int main() {
	int socketEcoute;
	struct sockaddr_in adresse; /* adresse d’attachement locale */
	socklen_t longueurAdresse;

	socketEcoute = socket(AF_INET, SOCK_STREAM, 0);

	if(socketEcoute < 0) {
		perror("socket");
		exit(-1);
	}
	printf("Socket creee avec succes ! (%d)\n", socketEcoute);

	// On prépare l’adresse d’attachement locale
	longueurAdresse = sizeof(struct sockaddr_in);
	memset(&adresse, 0x00, longueurAdresse);
	adresse.sin_family = AF_INET;
	adresse.sin_addr.s_addr = htonl(INADDR_ANY);
	adresse.sin_port = htons(PORT); // = 5000

	// On demande l’attachement local de la socket
	if(( bind(socketEcoute, (struct sockaddr *)&adresse, longueurAdresse) ) < 0) {
		perror("bind");
		exit(-2);
	}
	printf("Socket attachee avec succes !\n");

	// La taille de la file d’attente est fixee a 5
	if(listen(socketEcoute, 5) < 0) {
		perror("listen");
		exit(-3);
	}

	printf("Socket placee en ecoute passive ...\n");
	
	// On ferme la ressource avant de quitter
	close(socketEcoute);
	return EXIT_SUCCESS;
}