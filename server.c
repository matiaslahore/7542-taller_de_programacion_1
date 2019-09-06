/*
   Ejemplo de un echo server.
   Este ejemplo TIENE UN BUG (en realidad son 2 combinados).

   La idea de un echo server es la siguiente:
      1) El cliente se conecta a este server y le envia un numero
         de 2 digitos (en texto) que representa la longitud del
         mensaje que le sigue.
      2) El cliente luego envia ese mensaje de esa longitud
      3) El server lee ese mensaje y luego se lo reenvia al cliente.

   Se compila con
      gcc -std=c99 -o echoserver echoserver.c

   Se ejecuta como
      ./echoserver PORT PASSWORD

   donde PORT es el nombre de un servicio ("http" por ejemplo) o el numero
   de puerto directamente (80 por ejemplo)
   PASSWORD es un string que representa algo secreto. No tiene nada que
   ver con el echo server y es borrado de la memoria con free
   Asi que no deberia haber ningun problema en, por ejemplo, que pongas
   tu password de facebook/clave bancaria, no?
*/

#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include "socket.h"

/*
   Hacemos un procesamiento a un password.
   Como liberamos la memoria el password es eliminado asi que es seguro, no?
                                                que podria salir mal?
*/
#define REPEATS 64   //agregar mas repeticiones si es necesario

void process(char *password) {
    int i;

    const char *msg = "Your secret password is: %s!";
    int msg_len = strlen(msg) - 2; // no contar el "%s" (2 bytes)
    int password_len = strlen(password);

    char *buf[REPEATS];
    int buf_size = password_len + msg_len + 1;

    for (i = 0; i < REPEATS; ++i) {
        buf[i] = (char *) malloc(sizeof(char) * buf_size);

        snprintf(buf[i], buf_size, msg, password);
        buf[i][buf_size - 1] = 0;
    }

    for (i = 0; i < REPEATS; ++i) {
        free(buf[i]);
    }
}

#define MAX_SMALL_BUF_LEN 3   //2 bytes

int main(int argc, char *argv[]) {

    //unsigned short len = 0;
    //bool continue_running = true;
    bool is_the_accept_socket_valid = true;

    char small_buf[MAX_SMALL_BUF_LEN];
    //char *tmp;
    //int peerskt = 0;

    socket_t skt;
    socket_t accepted_skt;
    socket_create(&skt);
    socket_bind_and_listen(&skt, NULL);

    socket_accept(&skt, &accepted_skt);
    socket_receive(&accepted_skt, small_buf, MAX_SMALL_BUF_LEN - 1);
    printf("Bytes  %zu \n", sizeof(small_buf));
    printf("recive: %s\n", small_buf);

/*
    while (continue_running) {
        if (peerskt == -1) {
            printf("Error: %s\n", strerror(errno));
            continue_running = false;
            is_the_accept_socket_valid = false;
        } else {
            printf("New client\n");
            memset(small_buf, 0, MAX_SMALL_BUF_LEN);
            socket_receive(&skt, small_buf, MAX_SMALL_BUF_LEN - 1);

            len = atoi(small_buf);
            printf("Echo %i bytes\n", len);

            if (len == 0) {
                printf("Zero bytes. Bye!\n");
                continue_running = false;
            } else {
                tmp = (char *) malloc(sizeof(char) * len);

                printf("Received %i/%i bytes\n", socket_receive(&skt, tmp, len), len);
                printf("Sent %i/%i bytes\n\n", socket_send(&skt, tmp, len), len);
                free(tmp);
            }

            shutdown(peerskt, SHUT_RDWR);
            close(peerskt);
        }
    }
    */

    shutdown(skt.skt, SHUT_RDWR);
    close(skt.skt);

    if (is_the_accept_socket_valid) {
        return 1;
    } else {
        return 0;
    }

}
