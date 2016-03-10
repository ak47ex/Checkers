#ifndef PIECE
#define PIECE
struct piece{ //структура для матрицы описания каждой клетки (чья шашка, её статус и т.д.)
    double x, y;
    int king;
    piece(){ this->x=-1;this->y=-1; this->king=-1;}
};
#endif // PIECE

