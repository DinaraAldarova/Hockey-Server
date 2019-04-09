#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include "inclides.h"

class Client : public QObject
{
    Q_OBJECT
public:
    //explicit Client(QObject *parent = nullptr);
    Client(int new_socket);
    ~Client();

    int socket;
    pthread_t thread;
    char buff[200];
signals:
    void new_message(QString message);
public slots:
    void Message(QString message);
};

#endif // CLIENT_H
