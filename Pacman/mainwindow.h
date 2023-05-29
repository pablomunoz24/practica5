#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>       //proporciona una visualización de texto o imagen
#include <QKeyEvent>    //describe un evento clave.
#include <QTimer>       //proporciona temporizadores repetitivos y de disparo único
#include "game.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);  //constructor
    ~MainWindow();                          //destructor
    void initLabels();         //inicializar pantalla
    void keyPressEvent(QKeyEvent*) ;   //evento de pulsación de tecla

private slots:
    void update_score();     //actualizacion de puntaje

private:
    Ui::MainWindow *ui;
    QLabel *score_title;   //titulo del puntaje
    QLabel *score;         //puntaje
    QLabel *win_label;     //texto cuando gana
    QTimer *score_timer;   //tiempo ountaje
    Game *game;
};
#endif // MAINWINDOW_H
