#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPushButton>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void timeout();

public slots:
    void startGameClock();
    void stopGameClock();
    void gameTime();
    void currentPlayer();
    void timeProgress();
private:
    Ui::MainWindow *ui;
    QTimer *pQTimer;
    void reset();
    void updateProgressBar();
    void progress();
    short player1Time;
    short player2Time;
    short timer;
    short turn;


};
#endif // MAINWINDOW_H
