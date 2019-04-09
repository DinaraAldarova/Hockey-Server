#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include "inclides.h"
#include <signals.h>
#include "client.h"

struct Deleted
{
    bool is_it;
    QString familly;
    int time;
};

struct Goal
{
    QString time;
    QString Familly;
    int num;
};

struct Team
{
    QString name;
    int count;
    QVector<Goal> goals;
    Deleted deleted[3];
};

struct Tablo
{
    int time;
    bool time_is_on;
    int period;
    bool working;

    Team team1, team2;
};

class Server : public QObject
{
    Q_OBJECT
public:
    struct sockaddr_in address; // структура с адресом
    struct hostent* hostinfo;
    int addrlen;
    int master_socket; // создание TCP-сокета
    pthread_t thread_init;
    pthread_t thread_clock;
    pthread_t thread_update;
    QMutex mutex;
    QVector <Client *> clients;
    //bool work = true;

    Tablo tablo;

    Server();
    ~Server();

    void init_tablo();
    void savebackup();
    bool loadbackup();
    //void * init (void * param);
signals:
    void time(QString time);
    void period(QString period);

    void team1_name(QString message);
    void team1_count(QString message);
    void team1_goal(QStringList messages);
    void team1_delsend1(QString message,QString time);
    void team1_delsend2(QString message,QString time);
    void team1_delsend3(QString message,QString time);
    void team1_del1(QString time);
    void team1_del2(QString time);
    void team1_del3(QString time);
    void team1_deldel1();
    void team1_deldel2();
    void team1_deldel3();

    void team2_name(QString message);
    void team2_count(QString message);
    void team2_goal(QStringList messages);
    void team2_delsend1(QString message, QString time);
    void team2_delsend2(QString message, QString time);
    void team2_delsend3(QString message, QString time);
    void team2_del1(QString time);
    void team2_del2(QString time);
    void team2_del3(QString time);
    void team2_deldel1();
    void team2_deldel2();
    void team2_deldel3();

public slots:
    void Message(QString message);

    void S_time();
    void S_period();

    void S_team1_name();
    void S_team1_count();
    void S_team1_goal();
    void S_team1_delsend1();
    void S_team1_delsend2();
    void S_team1_delsend3();
    void S_team1_del1();
    void S_team1_del2();
    void S_team1_del3();
    void S_team1_deldel1();
    void S_team1_deldel2();
    void S_team1_deldel3();

    void S_team2_name();
    void S_team2_count();
    void S_team2_goal();
    void S_team2_delsend1();
    void S_team2_delsend2();
    void S_team2_delsend3();
    void S_team2_del1();
    void S_team2_del2();
    void S_team2_del3();
    void S_team2_deldel1();
    void S_team2_deldel2();
    void S_team2_deldel3();
};

#endif // SERVER_H
