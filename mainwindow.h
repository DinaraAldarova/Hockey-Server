#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <signals.h>
#include <server.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_MainWindow_tabifiedDockWidgetActivated(QDockWidget *dockWidget);

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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
