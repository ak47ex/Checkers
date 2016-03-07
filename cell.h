#ifndef CELL
#define CELL
struct cell{ //структура для матрицы описания каждой клетки (чья шашка, её статус и т.д.)
    bool isKing;
    char active; //0 - не активна, 1 - в фокусе, 2 - активна, 3 - под боем
    char side;  // 0 - свободная клетка, 1 - зелёные 2 - красные
    cell(bool king, char side){
        this->isKing=king;
        this->side=side;
        this->active=0;
    }
    cell(){
        this->isKing = 0;
        this->active = 0;
        this->side = 0;
    }
};
#endif // CELL

