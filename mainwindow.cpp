#include "mainwindow.h"
#include "qobjectdefs.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pQTimer = new QTimer(this);
    pQTimer->setSingleShot(false);
    reset();
    connect(pQTimer,SIGNAL(timeout()),this,SLOT(timeProgress()));
    connect(ui->TwoMin2, SIGNAL(clicked()), this, SLOT(gameTime()));
    connect(ui->FifeMin5, SIGNAL(clicked()), this, SLOT(gameTime()));
    connect(ui->StopGame,SIGNAL(clicked()),this,SLOT(stopGameClock()));
    connect(ui->StartGame,SIGNAL(clicked()),this,SLOT(startGameClock()));
    connect(ui->SwitchPlayer1,SIGNAL(clicked()),this,SLOT(currentPlayer()));
    connect(ui->SwitchPlayer2,SIGNAL(clicked()),this,SLOT(currentPlayer()));



}

MainWindow::~MainWindow()
{
    ui->InfoLabel->setText("New gane via start button");
    delete ui;
}

void MainWindow::gameTime()
{
    QPushButton * btn = qobject_cast<QPushButton*>(sender());
    QString countdown = btn->objectName();
    int minutes = countdown.last(1).toInt();
    timer = 60 * minutes;
    player1Time = timer;
    player2Time = timer;
    ui->Player1Progress->setRange(0, timer);
    ui->player2Progress->setRange(0, timer);
    updateProgressBar();
    ui->StartGame->setDisabled(false);
    ui->StopGame->setDisabled(true);
    ui->SwitchPlayer1->setDisabled(true);
    ui->SwitchPlayer2->setDisabled(true);
    ui->TwoMin2->setDisabled(true);
    ui->FifeMin5->setDisabled(true);
    ui->InfoLabel->setText("Ready to play");

}
void MainWindow::timeProgress()
{
    if(turn == 1){
       player1Time--;
    }
    else {
        player2Time--;
    }
    if(player1Time == 0 || player2Time == 0 ){
        timeout();
    }
    else {
        updateProgressBar();
    }
}

void MainWindow::progress()
{
    ui->TwoMin2->setDisabled(true);
    ui->FifeMin5->setDisabled(true);
    ui->StopGame->setDisabled(false);
    ui->StartGame->setDisabled(true);
    ui->SwitchPlayer1->setDisabled(true);
    ui->SwitchPlayer2->setDisabled(false);
    ui->InfoLabel->setText("Game ongoing");
}

void MainWindow::startGameClock()
{
   pQTimer->start(1000);
   turn =1;

   timeProgress();
}

void MainWindow::timeout()
{
   if(player1Time <= 0) {
    ui->InfoLabel->setText("Player 2 WON!!!");
    ui->SwitchPlayer1->setDisabled(true);
    ui->SwitchPlayer2->setDisabled(true);
   } else  if(player2Time <=0){
    ui->InfoLabel->setText("Player 1 WON!!!");
    ui->SwitchPlayer1->setDisabled(true);
    ui->SwitchPlayer2->setDisabled(true);
    }
}
void MainWindow::currentPlayer()
{
    if(turn == 1){
        turn = 2;
        ui->SwitchPlayer1->setDisabled(false);
        ui->SwitchPlayer2->setDisabled(true);
    }
    else {
        turn = 1;
        ui->SwitchPlayer1->setDisabled(true);
        ui->SwitchPlayer2->setDisabled(false);
    }
}


void MainWindow::updateProgressBar()
{
    ui->Player1Progress->setValue(player1Time);
    ui->player2Progress->setValue(player2Time);
}
void MainWindow::stopGameClock()
{
    pQTimer->stop();
    reset();
}

void MainWindow::reset()
{
   pQTimer->stop();
   player1Time = 0;
   player2Time = 0;
   ui->TwoMin2->setDisabled(false);
   ui->FifeMin5->setDisabled(false);
   ui->StopGame->setDisabled(true);
   ui->StartGame->setDisabled(true);
   ui->SwitchPlayer1->setDisabled(true);
   ui->SwitchPlayer2->setDisabled(true);
   updateProgressBar();
   ui->InfoLabel->setText("Select playtime and press start game!");

}
