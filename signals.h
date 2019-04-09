#ifndef SIGNALS_H
#define SIGNALS_H

#include <QObject>

class Signals : public QObject
{
    Q_OBJECT
public:
    //explicit Signals(QObject *parent = nullptr);

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

};

#endif // SIGNALS_H
