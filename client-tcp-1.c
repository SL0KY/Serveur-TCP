/*
Exemple sur un client TCP
...
...
*/
#include <stdio.h>
#include <stdlib.h> /* pour exit */

#include <string.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<netinet/in.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>

int main(int nbarg, char *tbarg[]) {
	int sock;
	struct sockaddr_in adresse;
	// socklen_t : an integer type of width of at least 32 bits
	socklen_t longueurAdresse;
	char *ip = tbarg[1];
	int port = atoi(tbarg[2]);

	// Creation de la socket de communication 
	sock = socket(AF_INET, SOCK_STREAM, 0); /* 0 indique que l'on utilisera le protocole associe par defaut a SOCK_STREAM soit TCP */

	if(sock < 0) {
		perror("socket");
		exit(-1);
	}
	
	printf("Socket creee avec succes ! (%d)\n", sock);

	longueurAdresse = sizeof(adresse);

	memset(&adresse, 0x00, longueurAdresse);

	adresse.sin_family = AF_INET;

	adresse.sin_port = htons(port);

	//IPPORT_USERRESERVED
	printf("\n Numero de port choisi est : %d \n", port);

	inet_aton(ip, &adresse.sin_addr);

	if( (connect(sock, (struct sockaddr *)&adresse, longueurAdresse) ) == -1) {
		perror("connect");
		close(sock);
		exit(-2);
	}

	printf("Connexion au serveur reussie !\n");

	close(sock);

	return (EXIT_SUCCESS);
}
