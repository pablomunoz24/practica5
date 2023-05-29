#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QGraphicsView> //proporciona un widget para mostrar el contenido de un QGraphicsScene
#include <QGraphicsScene> //proporciona una superficie para administrar una gran cantidad de elementos gráficos 2D
#include <QGraphicsItem> //es la clase base para todos los elementos gráficos en un QGraphicsScene
#include <QTimer>  //proporciona temporizadores repetitivos y de disparo único
#include <QVector> //es una clase de plantilla que proporciona una matriz dinámica.



class Game;   //se pone la clase game para utilizarla aqui pero esta en game.h


/*  pacman */
class GameObject : public QGraphicsPixmapItem  //gameobject hereda de qgraphics
{
public:
    enum ObjectType {Ball, Wall, Gate, Pacman, Blank, PowerBall}; //estructura enumerada
    enum Dir {Up = 0, Down = 1, Left = 2, Right = 3, Stop = 4};
    static const int Width = 20;      // tamaño del objeto del juego por píxel

//QPixmap es una representación de imagen fuera de pantalla que se puede utilizar como dispositivo de pintura.

    GameObject(ObjectType, QPixmap);   //constructor
    ~GameObject();                     //destructor
    ObjectType get_type();
    //metodos set:establecer   y  get:obtener
    int get_x();
    int get_y();
    int get_score();   //obtener puntaje

    void set_score(int);   //establecer puntaje
    void set_dir(Dir);
    void set_next_dir(Dir);

    Dir get_dir();
    Dir get_next_dir();

    friend class Game;   //permite q accedan a los miembros de la clase game

protected:
    int _x;
    int _y;                 // coordenadas del mapa
    Dir dir;                    // dirección de movimiento actual
    Dir next_dir;               // siguiente dirección con la tecla w, a, s, d
    ObjectType type;
    int score;                 //puntaje
};


/* Pacman */
class Pacman : public GameObject
{
public:
    Pacman();           //constructor
    void move();        //funcion muevete
    Game *game;                 // el objeto del juego pacman

    friend class Game;   //permite q accedan a los miembros de la clase game

private:
    void moveup();      //mover arriba
    void movedown();    //mover abajo
    void moveleft();    //mover hacia la izquierda
    void moveright();   //mover derecha
    void eat_ball(int, int);   //comer pelota
    bool overlapable(int, int); // comprueba si pacman puede ir al mapa[i][j]

    QVector<QPixmap> anim[4];   // animaciones
    int anim_index;
};

#endif // GAMEOBJECT_H
