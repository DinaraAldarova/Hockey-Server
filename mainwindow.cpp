#include "mainwindow.h"
#include "ui_mainwindow.h"

Server * server;
//Signals * sign;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server = new Server();
    connect(server,SIGNAL(time(QString)),this,SLOT(time(QString)));
    connect(server,SIGNAL(period(QString)),this,SLOT(period(QString)));

    connect(server,SIGNAL(team1_name(QString)),this,SLOT(team1_name(QString)));
    connect(server,SIGNAL(team1_count(QString)),this,SLOT(team1_count(QString)));
    connect(server,SIGNAL(team1_goal(QStringList)),this,SLOT(team1_goal(QStringList)));
    connect(server,SIGNAL(team1_delsend1(QString,QString)),this,SLOT(team1_delsend1(QString,QString)));
    connect(server,SIGNAL(team1_delsend2(QString,QString)),this,SLOT(team1_delsend2(QString,QString)));
    connect(server,SIGNAL(team1_delsend3(QString,QString)),this,SLOT(team1_delsend3(QString,QString)));
    connect(server,SIGNAL(team1_del1(QString)),this,SLOT(team1_del1(QString)));
    connect(server,SIGNAL(team1_del2(QString)),this,SLOT(team1_del2(QString)));
    connect(server,SIGNAL(team1_del3(QString)),this,SLOT(team1_del3(QString)));
    connect(server,SIGNAL(team1_deldel1()),this,SLOT(team1_deldel1()));
    connect(server,SIGNAL(team1_deldel2()),this,SLOT(team1_deldel2()));
    connect(server,SIGNAL(team1_deldel3()),this,SLOT(team1_deldel3()));

    connect(server,SIGNAL(team2_name(QString)),this,SLOT(team2_name(QString)));
    connect(server,SIGNAL(team2_count(QString)),this,SLOT(team2_count(QString)));
    connect(server,SIGNAL(team2_goal(QStringList)),this,SLOT(team2_goal(QStringList)));
    connect(server,SIGNAL(team2_delsend1(QString,QString)),this,SLOT(team2_delsend1(QString,QString)));
    connect(server,SIGNAL(team2_delsend2(QString,QString)),this,SLOT(team2_delsend2(QString,QString)));
    connect(server,SIGNAL(team2_delsend3(QString,QString)),this,SLOT(team2_delsend3(QString,QString)));
    connect(server,SIGNAL(team2_del1(QString)),this,SLOT(team2_del1(QString)));
    connect(server,SIGNAL(team2_del2(QString)),this,SLOT(team2_del2(QString)));
    connect(server,SIGNAL(team2_del3(QString)),this,SLOT(team2_del3(QString)));
    connect(server,SIGNAL(team2_deldel1()),this,SLOT(team2_deldel1()));
    connect(server,SIGNAL(team2_deldel2()),this,SLOT(team2_deldel2()));
    connect(server,SIGNAL(team2_deldel3()),this,SLOT(team2_deldel3()));
    server->tablo.working = true;
}

MainWindow::~MainWindow()
{
    //save backup tablo
    delete ui;
}

void MainWindow::on_MainWindow_tabifiedDockWidgetActivated(QDockWidget *dockWidget)
{

}

void MainWindow::time(QString time)
{
    ui->labelTime->setText(time);
}
void MainWindow::period(QString period)
{
    ui->labelPeriod->setText(period);
}
void MainWindow::team1_name(QString message)
{
    ui->labelTeam1->setText(message);
}
void MainWindow::team1_count(QString message)
{
    ui->labelTeam1_Count->setText(message);
}
void MainWindow::team1_goal(QStringList messages)
{
    ui->listWidgetTeam1->clear();
    ui->listWidgetTeam1->addItems(messages);
}
void MainWindow::team1_delsend1(QString message,QString time)
{
    ui->labelTeam1_Familly1->setText(message);
    ui->labelTeam1_Time1->setText(time);
}
void MainWindow::team1_delsend2(QString message,QString time)
{
    ui->labelTeam1_Familly2->setText(message);
    ui->labelTeam1_Time2->setText(time);
}
void MainWindow::team1_delsend3(QString message,QString time)
{
    ui->labelTeam1_Familly3->setText(message);
    ui->labelTeam1_Time3->setText(time);
}
void MainWindow::team1_del1(QString time)
{
    ui->labelTeam1_Time1->setText(time);
}
void MainWindow::team1_del2(QString time)
{
    ui->labelTeam1_Time2->setText(time);
}
void MainWindow::team1_del3(QString time)
{
    ui->labelTeam1_Time3->setText(time);
}
void MainWindow::team1_deldel1()
{
    ui->labelTeam1_Familly1->clear();
    ui->labelTeam1_Time1->clear();
}
void MainWindow::team1_deldel2()
{
    ui->labelTeam1_Familly2->clear();
    ui->labelTeam1_Time2->clear();
}
void MainWindow::team1_deldel3()
{
    ui->labelTeam1_Familly3->clear();
    ui->labelTeam1_Time3->clear();
}
void MainWindow::team2_name(QString message)
{
    ui->labelTeam2->setText(message);
}
void MainWindow::team2_count(QString message)
{
    ui->labelTeam2_Count->setText(message);
}
void MainWindow::team2_goal(QStringList messages)
{
    ui->listWidgetTeam2->clear();
    ui->listWidgetTeam2->addItems(messages);
}
void MainWindow::team2_delsend1(QString message,QString time)
{
    ui->labelTeam2_Familly1->setText(message);
    ui->labelTeam2_Time1->setText(time);
}
void MainWindow::team2_delsend2(QString message,QString time)
{
    ui->labelTeam2_Familly2->setText(message);
    ui->labelTeam2_Time2->setText(time);
}
void MainWindow::team2_delsend3(QString message,QString time)
{
    ui->labelTeam2_Familly3->setText(message);
    ui->labelTeam2_Time3->setText(time);
}
void MainWindow::team2_del1(QString time)
{
    ui->labelTeam2_Time1->setText(time);
}
void MainWindow::team2_del2(QString time)
{
    ui->labelTeam2_Time2->setText(time);
}
void MainWindow::team2_del3(QString time)
{
    ui->labelTeam2_Time3->setText(time);
}
void MainWindow::team2_deldel1()
{
    ui->labelTeam2_Familly1->clear();
    ui->labelTeam2_Time1->clear();
}
void MainWindow::team2_deldel2()
{
    ui->labelTeam2_Familly2->clear();
    ui->labelTeam2_Time2->clear();
}
void MainWindow::team2_deldel3()
{
    ui->labelTeam2_Familly3->clear();
    ui->labelTeam2_Time3->clear();
}
