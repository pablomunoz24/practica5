#include "game.h"
#include <QString>
#include <QFile>
#define W (GameObject::Width)

Game::Game(int x, int y, int map_w, int map_h, QString map_src) //constructor
    : QGraphicsScene(x, y, W * map_w, W * map_h)
{
    geo_x = x;    //50
    geo_y = y;    //50
    stat = Playing;

    /* Inicializar punteros de mapa */
    map_size = map_w * map_h;  //28*31
    map_width = map_w;         //28
    map_height = map_h;        //31
    map = new GameObject**[map_height]; //asignar memoria para el objeto de 31 filas
    for (int i = 0; i < map_height; i++) { //0   hasta 31
        map[i] = new GameObject*[map_width];  //asignar memoria para el objeto de 28 columnas
        for (int j = 0; j < map_width; j++) //0 hasta 28
            map[i][j] = nullptr;   //valor nulo
    }

    /* Inicializar gráficos de mapa */
    ball_num =0;
    eat_num = 0;
    score = 0;
    QPixmap wallpix(":/new/prefix2/objectos/pared.png");  //pared
    QPixmap ballpix(":/new/prefix2/objectos/punto.png");    //pelota
    QPixmap powerballpix(":/new/prefix2/objectos/super_punto.png");  //super pelota
    QPixmap gatepix(":/new/prefix2/objectos/puerta.png");
    QPixmap blankpix;     //vacio
    QFile mapfile(map_src);   //archivo de mapa
    mapfile.open(QIODevice::ReadOnly|QIODevice::Text); //abrir

    pacman = new Pacman();  //asignar memoria para el objeto pacman

    for (int i = 0; i < map_h; i++) {  //0 hasta 31
        QByteArray line = mapfile.readLine();  //QByteArray proporciona una matriz de bytes
        for (int j = 0; j < map_w; j++) { //0 hasta 28
            int tmp_x = x + (j * W);   //50 + (j*20)
            int tmp_y = y + (i * W);   //50 + (i*20)
            switch (line[j]) {
            case '1':
                map[i][j] = new GameObject(GameObject::Wall, wallpix);  //pared
                map[i][j]->setPos(tmp_x, tmp_y);   //establecer posición
                addItem(map[i][j]);  //añadir artículo
                break;
            case '0':
                map[i][j] = new GameObject(GameObject::Ball, ballpix);   //pelota
                map[i][j]->set_score(BALL_SCORE);  //llama al metodo set_score -valor de la pelota
                map[i][j]->setPos(tmp_x, tmp_y);   //establecer posición
                addItem(map[i][j]);
                ball_num++;
                break;
            case '4':
                map[i][j] = new GameObject(GameObject::PowerBall, powerballpix); //super pelota
                map[i][j]->set_score(POWERBALL_SCORE);  // valor de la super pelota
                map[i][j]->setPos(tmp_x, tmp_y);
                addItem(map[i][j]);
                powerball.push_back(map[i][j]);  //agrega el elemento al final del vector
                ball_num++;
                break;
            case '3':
                map[i][j] = new GameObject(GameObject::Blank, blankpix); //bloque vacio
                break;
            case '2':
                map[i][j] = new GameObject(GameObject::Gate, gatepix);  //puerta
                map[i][j]->setPos(tmp_x, tmp_y);
                addItem(map[i][j]);
                break;
            case 'p':                          //pacman

                pacman->game = this;
                pacman->setPos(tmp_x, tmp_y);
                addItem(pacman);
                map[i][j] = pacman;
                break;
            }
            if (map[i][j]) {
                map[i][j]->_x = j;
                map[i][j]->_y = i;
            }
        }
    }
}


void Game::start()   //funcion comenzar
{
    powerball_flash_timer = new QTimer(this);
    connect(powerball_flash_timer, SIGNAL(timeout()), this , SLOT(powerball_flash()));
    powerball_flash_timer->start(FLASH_INTERVAL);

    pacman_timer = new QTimer(this);
    connect(pacman_timer, SIGNAL(timeout()), this , SLOT(pacman_handler()));
    pacman_timer->start(INTERVAL);
}


void Game::stop()   //parar
{
    pacman_timer->stop();     //el pacman se detiene
    powerball_flash_timer->stop();  //las super bolas se detienen
}


void Game::powerball_flash()  //intermitencia de la super pelota
{

    if (flash_tick) {
        for (int i = 0; i < powerball.size(); i++) {
            powerball.at(i)->show();
        }
        flash_tick = 0;
    }
    else {
        for (int i = 0; i < powerball.size(); i++) {
            powerball.at(i)->hide();
        }
        flash_tick = 1;
    }
}

void Game::pacman_handler()  //manipulador del pacman
{
    pacman->move();
    if (stat == Win) {     //si gano detengase
        stop();           //llama la funcion stop
    }
}

void Game::pacman_next_direction(GameObject::Dir d)  //proxima direccion del pacman
{
    pacman->set_next_dir(d);
}

int Game::get_score()  //obtener puntaje
{
    return score;
}

Game::~Game()    //destructor
{
    for (int i = 0; i < map_height; i++) {  // 0 hasta 31
        for (int j = 0; j < map_width; j++) {  //0 hasta 29
            if (map[i][j] != nullptr)   //si es diferente
                delete map[i][j];       //libere
        }
        delete[] map[i];
    }
    delete[] map;
    delete pacman_timer;
    delete powerball_flash_timer;
}
