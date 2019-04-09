#include "client.h"

void * work (void * param);

//Client::Client(QObject *parent) : QObject(parent)  {}
Client::Client (int new_socket)
{
    socket = new_socket;
    pthread_create (&thread,NULL,work, this);
}

Client::~Client()
{
    pthread_cancel(thread);
}

void Client::Message(QString message)
{
    emit new_message(message);
}

void * work (void * param)
{
    Client * client = (Client *) param;
    while (recv(client->socket,&client->buff, sizeof(client->buff),NULL) > 0)
    {
        QString s = QString::fromUtf8(client->buff,strlen(client->buff));
        client->Message(s);
    }
    delete (client);
    pthread_exit(0);
}
