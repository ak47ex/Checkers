#ifndef CELL
#define CELL
struct cell{ //структура для матрицы описания каждой клетки (чья шашка, её статус и т.д.)
    bool isKing;
    char active; //0 - не активна, 1 - в фокусе, 2 - активна
    char side;  // 0 - красные, 1 - зелёные 2 - свободная клетка
    cell(bool king, char side){
        this->isKing=king;
        this->side=side;
        this->active=0;
    }
    cell(){}
};
#endif // CELL

