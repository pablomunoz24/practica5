#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)  //constructor
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);     //configurar la interfaz de usuario
    setWindowTitle(tr("PACMAN")); //establecer el titulo de la ventana

    /* Initialize graphicsview and game scene */
    ui->graphicsView->setStyleSheet("QGraphicsView {border: none;}"); //establecer hoja de estilo
    ui->graphicsView->setBackgroundBrush(Qt::black); //establecer pincel de fondo

    int map_height = 31, map_width = 28;
    int x = 50, y = 50;                             // coordenadas del laberinto
    int w = (map_width * GameObject::Width);   //ancho * el tamaño por pixel
    int h = (map_height * GameObject::Width);  //alto * el tamaño por pixel

    ui->graphicsView->setGeometry(x, y, w, h); //establecer geometria
    game = new Game(x, y, map_width, map_height, ":/new/prefix2/objectos/laberinto.txt"); //asignar memoria para el objeto
    ui->graphicsView->setScene(game);  //establecer scena del juego
    initLabels();   //llama la funcion initlabels
    game->start();
}


/* Initialize UI */
void MainWindow::initLabels()
{
    score_title = new QLabel(this);  //asignar memoria al objeto
    score_title->setText("puntaje");
    score_title->setStyleSheet("QLabel {font-family: Fixedsys;color: black;font-size: 16px;}"); //establecer hoja de estilo
    score_title->setGeometry(50, 12, 60, 26);   //establecer geometría

    score = new QLabel(this);
    score->setText("0");
    score->setStyleSheet("QLabel {font-family: Fixedsys;color: black;font-size: 16px;}");
    score->setGeometry(110, 12, 150, 26);

    win_label = new QLabel(this);
    win_label->hide();       //ocultar
    win_label->setText("Game over");
    win_label->setStyleSheet("QLabel {font-family: Fixedsys;color: red;font-size: 18px;}");
    win_label->setGeometry(310, 12, 150, 26);

    score_timer = new QTimer(this);
    score_timer->start(25);    //25milisegundos
    connect(score_timer, SIGNAL(timeout()), this , SLOT(update_score()));
}


/* Update score UI */
void MainWindow::update_score()    //actualizar puntaje
{
    score->setText(QString::number(game->get_score())); //establecer texto
    if (game->stat == Game::Win) {
        win_label->show();
        score_timer->stop();
    }
}


void MainWindow::keyPressEvent(QKeyEvent *r) {
    switch (r->key()) {
    case Qt::Key_W:
        game->pacman_next_direction(GameObject::Up);
        break;
    case Qt::Key_A:
        game->pacman_next_direction(GameObject::Left);
        break;
    case Qt::Key_S:
        game->pacman_next_direction(GameObject::Down);
        break;
    case Qt::Key_D:
        game->pacman_next_direction(GameObject::Right);
        break;
    }
}


MainWindow::~MainWindow()     //destructor
{
    delete ui;
}

