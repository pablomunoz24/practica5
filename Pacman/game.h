#ifndef GAME_H
#define GAME_H

#include <QGraphicsView> //proporciona un widget para mostrar el contenido de un QGraphicsScene
#include <QGraphicsScene> //proporciona una superficie para administrar una gran cantidad de elementos gráficos 2D
#include <QGraphicsItem>   //es la clase base para todos los elementos gráficos en un QGraphicsScene
#include <QTimer> //proporciona temporizadores repetitivos y de disparo único
#include "gameobject.h"

#define BALL_SCORE      10          // puntaje de la pelota
#define POWERBALL_SCORE 30          // puntaje de la super pelota
#define INTERVAL        10
#define FLASH_INTERVAL 200

/* Game control class */
class Game : public QGraphicsScene //clase game hereda QGraphi
{
    Q_OBJECT

public:
    enum GameStatus {Playing, Win};  //tipo enumeracion
    Game(int, int, int, int, QString);            //constructor
    ~Game();                                     //destructor
    void start();                                //funcion comenzar
    void stop();                                 //funcion detener
    void pacman_next_direction(GameObject::Dir); //funcion proxima direccion
    int get_score();                            //funcion obtener puntaje

    GameObject ***map;              // el mapa del juego pacman
    Pacman *pacman;                 // Puntero de pacman
    QVector<GameObject*> powerball;
    GameStatus stat;                //estadística: win playing pause

    friend class Pacman;    //permite q accedan a los miembros de la clase pacman


private slots:
    void pacman_handler();    //manipulador del pacman
    void powerball_flash();  //funcion intermitencia de la superbola

private:
    int map_height;     //alto
    int map_width;      // ancho
    int map_size;       // ancho del mapa * alto del mapa
    int ball_num;       //pelota
    int eat_num;         //comer
    int score;         //puntaje
    int geo_x;
    int geo_y;               // coordenada geométrica

    QTimer *pacman_timer;
    QTimer *powerball_flash_timer;
    bool flash_tick;      //tipo boleana

};

#endif // GAME_H
