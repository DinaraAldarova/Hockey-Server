#include "server.h"

void * init (void * param);
void * clock_time(void * param);
void * update (void * param);

Server::Server()
{
    tablo.working = false;

    pthread_create(&thread_clock,NULL,clock_time,this);

    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) <= 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);
    int one = 1;

    setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &one, sizeof(int));

    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(master_socket, SOMAXCONN)< 0) {
        perror("listen\n");
        close(master_socket);
        exit(EXIT_FAILURE);
    }

    pthread_create (&thread_init,NULL,init, this);
}

Server::~Server()
{
    savebackup();
    pthread_cancel(thread_init);
    pthread_cancel(thread_clock);
}

void Server::savebackup()
{

}

bool Server::loadbackup()
{
    return false;
}

void Server::Message(QString message)
{
    mutex.lock();
    //разобрать, что нам пришло
    if (message.contains("start"))
    {
        tablo.time_is_on = true;
    }
    else if (message.contains("stop"))
    {
        tablo.time_is_on = false;
    }
    else if (message.contains("time"))
    {
        bool flag;
        int i = message.indexOf(":")+1;
        QString s = message.mid(i);
        int t = s.toInt(&flag);
        if (flag == true)
        {
            tablo.time = t;
            S_time();
        }
    }
    else if (message.contains("period"))
    {
        bool flag;
        QString s = message.mid(message.indexOf(":")+1);
        int p = s.toInt(&flag);
        if (flag == true)
        {
            tablo.period = p;
            S_period();
        }
    }
    else if (message.contains("team1_name"))
    {
        QString s = message.mid(message.indexOf(":")+1);
        tablo.team1.name = s;
        S_team1_name();
    }
    else if (message.contains("team1_goalsend"))
    {
        tablo.team1.count++;
        S_team1_count();
        Goal g;
        g.num = tablo.team1.count;
        int sec = tablo.time;
        g.time = QString::number(sec/60)+":"+QString::number(sec%60);
        g.Familly = message.mid(message.indexOf(":")+1);
        tablo.team1.goals.push_front(g);
        S_team1_goal();
    }
    else if (message.contains("team1_goaldel"))
    {
        QString s = message.mid(message.indexOf(":")+1);
        QVector<Goal> g = tablo.team1.goals;
        bool end = false;
        int i = 0;
        for (; i < g.size() && !end; i++)
        {
            if (QString::compare(g[i].Familly,s,Qt::CaseInsensitive) == 0)
                end = true;
        }
        if (end)
        {
            tablo.team1.count--;
            S_team1_count();
            i--;
            for (int j = i; j >= 0; j--)
                g[j].num--;
            g.erase(g.begin()+i);
            tablo.team1.goals = g;
            S_team1_goal();
        }
    }
    else if (message.contains("team1_delsend"))
    {
        QString s = message.mid(message.indexOf(":")+1);
        int t = 120;
        if (!tablo.team1.deleted[0].is_it)
        {
            tablo.team1.deleted[0].is_it = true;
            tablo.team1.deleted[0].familly = s;
            tablo.team1.deleted[0].time = t;
            S_team1_delsend1();
        }
        else if (!tablo.team1.deleted[1].is_it)
        {
            tablo.team1.deleted[1].is_it = true;
            tablo.team1.deleted[1].familly = s;
            tablo.team1.deleted[1].time = t;
            S_team1_delsend2();
        }
        else if (!tablo.team1.deleted[2].is_it)
        {
            tablo.team1.deleted[2].is_it = true;
            tablo.team1.deleted[2].familly = s;
            tablo.team1.deleted[2].time = t;
            S_team1_delsend3();
        }
    }
    else if (message.contains("team1_deldel"))
    {
        QString s = message.mid(message.indexOf(":")+1);
        if (QString::compare(tablo.team1.deleted[0].familly,s) == 0)
        {
            tablo.team1.deleted[0].is_it = false;
            tablo.team1.deleted[0].familly = "";
            tablo.team1.deleted[0].time = 0;
            S_team1_deldel1();
        }
        else if (QString::compare(tablo.team1.deleted[1].familly,s) == 0)
        {
            tablo.team1.deleted[1].is_it = false;
            tablo.team1.deleted[1].familly = "";
            tablo.team1.deleted[1].time = 0;
            S_team1_deldel2();
        }
        else if (QString::compare(tablo.team1.deleted[2].familly,s) == 0)
        {
            tablo.team1.deleted[2].is_it = false;
            tablo.team1.deleted[2].familly = "";
            tablo.team1.deleted[2].time = 0;
            S_team1_deldel3();
        }
    }
    else if (message.contains("team2_name"))
    {
        QString s = message.mid(message.indexOf(":")+1);
        tablo.team2.name = s;
        S_team2_name();
    }
    else if (message.contains("team2_goalsend"))
    {
        tablo.team2.count++;
        S_team2_count();
        Goal g;
        g.num = tablo.team2.count;
        int sec = tablo.time;
        g.time = QString::number(sec/60)+":"+QString::number(sec%60);
        g.Familly = message.mid(message.indexOf(":")+1);
        tablo.team2.goals.push_front(g);
        S_team2_goal();
    }
    else if (message.contains("team2_goaldel"))
    {
        QString s = message.mid(message.indexOf(":")+1);
        QVector<Goal> g = tablo.team2.goals;
        bool end = false;
        int i = 0;
        for (; i < g.size() && !end; i++)
        {
            if (QString::compare(g[i].Familly,s,Qt::CaseInsensitive) == 0)
                end = true;
        }
        if (end)
        {
            tablo.team2.count--;
            S_team2_count();
            i--;
            for (int j = i; j >= 0; j-- )
                g[j].num--;
            g.erase(g.begin()+i);
            tablo.team2.goals = g;
            S_team2_goal();
        }
    }    else if (message.contains("team2_delsend"))
    {
        QString s = message.mid(message.indexOf(":")+1);
        int t = 120;
        if (!tablo.team2.deleted[0].is_it)
        {
            tablo.team2.deleted[0].is_it = true;
            tablo.team2.deleted[0].familly = s;
            tablo.team2.deleted[0].time = t;
            S_team2_delsend1();
        }
        else if (!tablo.team2.deleted[1].is_it)
        {
            tablo.team2.deleted[1].is_it = true;
            tablo.team2.deleted[1].familly = s;
            tablo.team2.deleted[1].time = t;
            S_team2_delsend2();
        }
        else if (!tablo.team2.deleted[2].is_it)
        {
            tablo.team2.deleted[2].is_it = true;
            tablo.team2.deleted[2].familly = s;
            tablo.team2.deleted[2].time = t;
            S_team2_delsend3();
        }
    }
    else if (message.contains("team2_deldel"))
    {
        QString s = message.mid(message.indexOf(":")+1);
        if (QString::compare(tablo.team2.deleted[0].familly,s) == 0)
        {
            tablo.team2.deleted[0].is_it = false;
            tablo.team2.deleted[0].familly = "";
            tablo.team2.deleted[0].time = 0;
            S_team2_deldel1();
        }
        else if (QString::compare(tablo.team2.deleted[1].familly,s) == 0)
        {
            tablo.team2.deleted[1].is_it = false;
            tablo.team2.deleted[1].familly = "";
            tablo.team2.deleted[1].time = 0;
            S_team2_deldel2();
        }
        else if (QString::compare(tablo.team2.deleted[2].familly,s) == 0)
        {
            tablo.team2.deleted[2].is_it = false;
            tablo.team2.deleted[2].familly = "";
            tablo.team2.deleted[2].time = 0;
            S_team2_deldel3();
        }
    }
    else
    {
        //пропустить
    }

    mutex.unlock();
}

void Server::init_tablo()
{
    mutex.lock();
    tablo.time_is_on = false;

    tablo.period = 1;
    tablo.time = 1200;
    //tablo.working = false;

    tablo.team1.name = "Команда1";
    tablo.team1.count = 0;
    tablo.team1.goals.clear();

    tablo.team1.deleted[0].is_it = false;
    tablo.team1.deleted[0].familly = "";
    tablo.team1.deleted[0].time = 0;

    tablo.team1.deleted[1].is_it = false;
    tablo.team1.deleted[1].familly = "";
    tablo.team1.deleted[1].time = 0;

    tablo.team1.deleted[2].is_it = false;
    tablo.team1.deleted[2].familly = "";
    tablo.team1.deleted[2].time = 0;

    tablo.team2.name = "Команда2";
    tablo.team2.count = 0;
    tablo.team2.goals.clear();

    tablo.team2.deleted[0].is_it = false;
    tablo.team2.deleted[0].familly = "";
    tablo.team2.deleted[0].time = 0;

    tablo.team2.deleted[1].is_it = false;
    tablo.team2.deleted[1].familly = "";
    tablo.team2.deleted[1].time = 0;

    tablo.team2.deleted[2].is_it = false;
    tablo.team2.deleted[2].familly = "";
    tablo.team2.deleted[2].time = 0;

    mutex.unlock();
}

void * init(void *param)
{
    Server * server = (Server *) param;
    while (!server->tablo.working)
    {
        sleep(0.1);
    }
    int new_socket;
    server->addrlen = sizeof(server->address);
    while(true/*server->work*/)
    {
        if ((new_socket = accept(server->master_socket, (struct sockaddr *)&server->address, (socklen_t*)&server->addrlen))<0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        Client * client = new Client(new_socket);
        QObject::connect(client, SIGNAL(new_message(QString)),server,SLOT(Message(QString)));
        server->clients.append(client);
    }
    pthread_exit(0);
}

void * clock_time(void * param)
{
    Server * server = (Server *) param;

    if (!server->loadbackup())
        server->init_tablo();

    while (!server->tablo.working)
    {
        sleep(0.1);
    }
    server->S_time();
    server->S_period();
    server->S_team1_name();
    server->S_team1_count();
    server->S_team1_goal();
    server->S_team1_deldel1();
    server->S_team1_deldel2();
    server->S_team1_deldel3();
    server->S_team2_name();
    server->S_team2_count();
    server->S_team2_goal();
    server->S_team2_deldel1();
    server->S_team2_deldel2();
    server->S_team2_deldel3();

    while (true)
    {
        sleep(1);
        server->thread_update = pthread_create(&server->thread_update,NULL,update,server);
    }
}

void * update (void * param)
{
    Server * server = (Server *) param;
    server->mutex.lock();
    if (server->tablo.time_is_on)
    {
        server->tablo.time--;
        server->S_time();
        if (server->tablo.team1.deleted[0].is_it)
        {
            server->tablo.team1.deleted[0].time--;
            if (server->tablo.team1.deleted[0].time == 0)
            {
                //удаление заканчивается
                server->tablo.team1.deleted[0].is_it = false;
                server->tablo.team1.deleted[0].familly = "";
                server->tablo.team1.deleted[0].time = 0;
                server->S_team1_deldel1();
            }
            else
                server->S_team1_del1();
        }
        if (server->tablo.team1.deleted[1].is_it)
        {
            server->tablo.team1.deleted[1].time--;
            if (server->tablo.team1.deleted[1].time == 0)
            {
                //удаление заканчивается
                server->tablo.team1.deleted[1].is_it = false;
                server->tablo.team1.deleted[1].familly = "";
                server->tablo.team1.deleted[1].time = 0;
                server->S_team1_deldel2();
            }
            else
                server->S_team1_del2();
        }
        if (server->tablo.team1.deleted[2].is_it)
        {
            server->tablo.team1.deleted[2].time--;
            if (server->tablo.team1.deleted[2].time == 0)
            {
                //удаление заканчивается
                server->tablo.team1.deleted[2].is_it = false;
                server->tablo.team1.deleted[2].familly = "";
                server->tablo.team1.deleted[2].time = 0;
                server->S_team1_deldel3();
            }
            else
                server->S_team1_del3();
        }
        if (server->tablo.team2.deleted[0].is_it)
        {
            server->tablo.team2.deleted[0].time--;
            if (server->tablo.team2.deleted[0].time == 0)
            {
                //удаление заканчивается
                server->tablo.team2.deleted[0].is_it = false;
                server->tablo.team2.deleted[0].familly = "";
                server->tablo.team2.deleted[0].time = 0;
                server->S_team2_deldel1();
            }
            else
                server->S_team2_del1();
        }
        if (server->tablo.team2.deleted[1].is_it)
        {
            server->tablo.team2.deleted[1].time--;
            if (server->tablo.team2.deleted[1].time == 0)
            {
                //удаление заканчивается
                server->tablo.team2.deleted[1].is_it = false;
                server->tablo.team2.deleted[1].familly = "";
                server->tablo.team2.deleted[1].time = 0;
                server->S_team2_deldel2();
            }
            else
                server->S_team2_del2();
        }
        if (server->tablo.team2.deleted[2].is_it)
        {
            server->tablo.team2.deleted[2].time--;
            if (server->tablo.team2.deleted[2].time == 0)
            {
                //удаление заканчивается
                server->tablo.team2.deleted[2].is_it = false;
                server->tablo.team2.deleted[2].familly = "";
                server->tablo.team2.deleted[2].time = 0;
                server->S_team2_deldel3();
            }
            else
                server->S_team2_del3();
        }

        if (server->tablo.time == 0)
        {
            server->tablo.time_is_on = false;
        }
    }
    server->mutex.unlock();
}

void Server::S_time()
{
    int sec = tablo.time;
    QString s = QString::number(sec/60)+":"+QString::number(sec%60);
    emit time(s);
}
void Server::S_period()
{
    int per = tablo.period;
    QString s = QString::number(per)+" период";
    emit period(s);
}

void Server::S_team1_name()
{
    QString s = tablo.team1.name;
    emit team1_name(s);
}
void Server::S_team1_count()
{
    int count = tablo.team1.count;
    QString s = QString::number(count);
    emit team1_count(s);
}
void Server::S_team1_goal()
{
    QStringList q;
    QVector<Goal> g = tablo.team1.goals;
    for (int i = 0; i < g.size(); i++)
    {
        QString s = QString::number(g[i].num) + " "
                + g[i].Familly + " "
                + g[i].time;
        q.push_back(s);
    }
    emit team1_goal(q);
}
void Server::S_team1_delsend1()
{
    QString s1 = tablo.team1.deleted[0].familly;
    int sec = tablo.team1.deleted[0].time;
    QString t1 = QString::number(sec/60)+":"+QString::number(sec%60);
    emit team1_delsend1(s1,t1);
}
void Server::S_team1_delsend2()
{
    QString s1 = tablo.team1.deleted[1].familly;
    int sec = tablo.team1.deleted[1].time;
    QString t1 = QString::number(sec/60)+":"+QString::number(sec%60);
    emit team1_delsend2(s1,t1);
}
void Server::S_team1_delsend3()
{
    QString s1 = tablo.team1.deleted[2].familly;
    int sec = tablo.team1.deleted[2].time;
    QString t1 = QString::number(sec/60)+":"+QString::number(sec%60);
    emit team1_delsend3(s1,t1);
}
void Server::S_team1_del1()
{
    int sec = tablo.team1.deleted[0].time;
    QString s = QString::number(sec/60)+":"+QString::number(sec%60);
    emit team1_del1(s);
}
void Server::S_team1_del2()
{
    int sec = tablo.team1.deleted[1].time;
    QString s = QString::number(sec/60)+":"+QString::number(sec%60);
    emit team1_del2(s);
}
void Server::S_team1_del3()
{
    int sec = tablo.team1.deleted[2].time;
    QString s = QString::number(sec/60)+":"+QString::number(sec%60);
    emit team1_del3(s);
}
void Server::S_team1_deldel1()
{
    emit team1_deldel1();
}
void Server::S_team1_deldel2()
{
    emit team1_deldel2();
}
void Server::S_team1_deldel3()
{
    emit team1_deldel3();
}

void Server::S_team2_name()
{
    QString s = tablo.team2.name;
    emit team2_name(s);
}
void Server::S_team2_count()
{
    int count = tablo.team2.count;
    QString s = QString::number(count);
    emit team2_count(s);
}
void Server::S_team2_goal()
{
    QStringList q;
    QVector<Goal> g = tablo.team2.goals;
    for (int i = 0; i < g.size(); i++)
    {
        QString s = QString::number(g[i].num) + " "
                + g[i].Familly + " "
                + g[i].time;
        q.push_back(s);
    }
    emit team2_goal(q);
}
void Server::S_team2_delsend1()
{
    QString s1 = tablo.team2.deleted[0].familly;
    int sec = tablo.team2.deleted[0].time;
    QString t1 = QString::number(sec/60)+":"+QString::number(sec%60);
    emit team2_delsend1(s1,t1);
}
void Server::S_team2_delsend2()
{
    QString s1 = tablo.team2.deleted[1].familly;
    int sec = tablo.team2.deleted[1].time;
    QString t1 = QString::number(sec/60)+":"+QString::number(sec%60);
    emit team2_delsend2(s1,t1);
}
void Server::S_team2_delsend3()
{
    QString s1 = tablo.team2.deleted[2].familly;
    int sec = tablo.team2.deleted[2].time;
    QString t1 = QString::number(sec/60)+":"+QString::number(sec%60);
    emit team2_delsend3(s1,t1);
}
void Server::S_team2_del1()
{
    int sec = tablo.team2.deleted[0].time;
    QString s = QString::number(sec/60)+":"+QString::number(sec%60);
    emit team2_del1(s);
}
void Server::S_team2_del2()
{
    int sec = tablo.team2.deleted[1].time;
    QString s = QString::number(sec/60)+":"+QString::number(sec%60);
    emit team2_del2(s);
}
void Server::S_team2_del3()
{
    int sec = tablo.team2.deleted[2].time;
    QString s = QString::number(sec/60)+":"+QString::number(sec%60);
    emit team2_del3(s);
}
void Server::S_team2_deldel1()
{
    emit team2_deldel1();
}
void Server::S_team2_deldel2()
{
    emit team2_deldel2();
}
void Server::S_team2_deldel3()
{
    emit team2_deldel3();
}
