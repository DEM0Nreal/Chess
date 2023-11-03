#include <math.h>
#include <cstring>
#include <vector>
#include <string>

#include <iostream>

using std::cout;

struct chessData {
    ///*
    char board[8][8] = {
        {'r', ' ', ' ', ' ', 'r', ' ', ' ', ' '},
        {'p', ' ', ' ', ' ', 'P', ' ', ' ', ' '},
        {' ', 'b', ' ', ' ', ' ', ' ', 'k', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', 'p', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', 'P', ' '},
        {'B', 'B', ' ', ' ', ' ', ' ', ' ', ' '},
        {'P', 'P', ' ', ' ', ' ', 'R', 'K', ' '},
        {' ', 'n', ' ', ' ', ' ', ' ', ' ', ' '}
    };
    //*/
    /*
    char board[8][8] = {
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
    };
    */
    
    char turn;

    char castle[4] = {0, 0, 0, 0}; // white short, white long, black short, black long
    // 0 - possible
    // 1 - impossible for now
    // 2 - impossible

    // previous movee
    char prevMove[5] = "\0\0\0\0";
};

struct move {
    char from[2];
    char to[2];
    char promotion=0;
};

void changeTurn(chessData &data){
    data.turn = data.turn == 'w' ? 'b' : 'w';
}

int isEnemy(char d, char t){
    return ((t == 'w' && !isupper(d)) || ((t == 'b' && isupper(d))));
}

int between (int n, int a, int b){
    return (a <= n && n < b);
}

int compareStringArray(char a[], char b[]){
    size_t i = 0;
    while (a[i] != '\0'){
        if (a[i] != b[i]) return 0;
        ++i;
    }

    return 1;
}

int possibleMoves(chessData data, std::vector<move>& moves){
    for (int y = 0; y < 8; ++y){
        for (int x = 0; x < 8; ++x){

            if (data.board[y][x] != ' '){
                move m;
                m.from[0] = 'a'+x;
                m.from[1] = '8'-y;
                if (!isEnemy(data.board[y][x], data.turn)){
                    switch (toupper(data.board[y][x])){
                        case 'K':   // King
                            
                            for (int i = -1; i <= 1; ++i){
                                for (int j = -1; j <= 1; ++j){
                                    if (!(i==0 && j==0)){
                                        if (x+i >= 0 && x+i <= 7){
                                            if (y+j >= 0 && y+j <= 7){
                                                move t = m;
                                                t.to[0] = 'a'+(x+i);
                                                t.to[1] = '8'-(y+j);

                                                char destiny = data.board[y+j][x+i];
                                                if (destiny == ' ' || isEnemy(destiny, data.turn)){
                                                    moves.push_back(t);
                                                }

                                            }
                                        }
                                    }
                                }
                            }

                            break;
                        case 'Q':   // Queen
                        {
                            int tx = x+1, ty = y;

                            // right
                            while (tx < 8){
                                if (data.board[ty][tx] != ' ') {
                                    if(isEnemy(data.board[ty][tx], data.turn)){
                                        move t = m;
                                        t.to[0] = 'a'+(tx);
                                        t.to[1] = '8'-(ty);
                                        moves.push_back(t);
                                    }
                                    break;
                                }else{
                                    move t = m;
                                    t.to[0] = 'a'+(tx);
                                    t.to[1] = '8'-(ty);
                                    moves.push_back(t);
                                }
                                ++tx;
                            }

                            // left
                            tx = x-1;
                            while (tx >= 0){
                                if (data.board[ty][tx] != ' ') {
                                    if(isEnemy(data.board[ty][tx], data.turn)){
                                        move t = m;
                                        t.to[0] = 'a'+(tx);
                                        t.to[1] = '8'-(ty);
                                        moves.push_back(t);
                                    }
                                    break;
                                }else{
                                    move t = m;
                                    t.to[0] = 'a'+(tx);
                                    t.to[1] = '8'-(ty);
                                    moves.push_back(t);
                                }
                                --tx;
                            }

                            // up
                            tx = x;
                            ty = y-1;
                            while (ty >= 0){
                                if (data.board[ty][tx] != ' ') {
                                    if(isEnemy(data.board[ty][tx], data.turn)){
                                        move t = m;
                                        t.to[0] = 'a'+(tx);
                                        t.to[1] = '8'-(ty);
                                        moves.push_back(t);
                                    }
                                    break;
                                }else{
                                    move t = m;
                                    t.to[0] = 'a'+(tx);
                                    t.to[1] = '8'-(ty);
                                    moves.push_back(t);
                                }
                                --ty;
                            }

                            // down
                            ty = y+1;
                            while (ty < 8){
                                if (data.board[ty][tx] != ' ') {
                                    if(isEnemy(data.board[ty][tx], data.turn)){
                                        move t = m;
                                        t.to[0] = 'a'+(tx);
                                        t.to[1] = '8'-(ty);
                                        moves.push_back(t);
                                    }
                                    break;
                                }else{
                                    move t = m;
                                    t.to[0] = 'a'+(tx);
                                    t.to[1] = '8'-(ty);
                                    moves.push_back(t);
                                }
                                ++ty;
                            }
                        }
                        {
                            int tx = x;
                            int ty = y;

                            for (int i = 0; i < 4; ++i){
                                int mx = -1;
                                int my = -1;

                                tx = x;
                                ty = y;

                                switch(i){
                                    case 0:
                                        mx = -1;
                                        my = -1;
                                        break;
                                    case 1:
                                        mx = 1;
                                        my = -1;
                                        break;
                                    case 2:
                                        mx = 1;
                                        my = 1;
                                        break;
                                    default:
                                        mx = -1;
                                        my = 1;
                                        break;
                                }

                                tx+=mx;
                                ty+=my;
                                while (between(tx, 0, 8) && between(ty, 0, 8)){
                                    if (data.board[ty][tx] != ' '){
                                        if (isEnemy(data.board[ty][tx], data.turn)){
                                            move t = m;
                                            t.to[0] = 'a'+tx;
                                            t.to[1] = '8'-ty;
                                            moves.push_back(t);
                                        }
                                        break;
                                    }else{
                                        move t = m;
                                        t.to[0] = 'a'+tx;
                                        t.to[1] = '8'-ty;
                                        moves.push_back(t);
                                    }
                                    tx += mx;
                                    ty += my;
                                }
                            }
                        }
                            break;
                        case 'B':   // Bishop
                        {
                            int tx = x;
                            int ty = y;

                            for (int i = 0; i < 4; ++i){
                                int mx = -1;
                                int my = -1;

                                tx = x;
                                ty = y;

                                switch(i){
                                    case 0:
                                        mx = -1;
                                        my = -1;
                                        break;
                                    case 1:
                                        mx = 1;
                                        my = -1;
                                        break;
                                    case 2:
                                        mx = 1;
                                        my = 1;
                                        break;
                                    default:
                                        mx = -1;
                                        my = 1;
                                        break;
                                }

                                tx+=mx;
                                ty+=my;
                                while (between(tx, 0, 8) && between(ty, 0, 8)){
                                    if (data.board[ty][tx] != ' '){
                                        if (isEnemy(data.board[ty][tx], data.turn)){
                                            move t = m;
                                            t.to[0] = 'a'+tx;
                                            t.to[1] = '8'-ty;
                                            moves.push_back(t);
                                        }
                                        break;
                                    }else{
                                        move t = m;
                                        t.to[0] = 'a'+tx;
                                        t.to[1] = '8'-ty;
                                        moves.push_back(t);
                                    }
                                    tx += mx;
                                    ty += my;
                                }
                            }
                        }
                            break;
                        case 'N':   // kNight
                        {
                            int tx = x, ty = y;

                            int a = 2;
                            int b = 1;

                            for (int i = 0; i < 4; ++i){
                                switch (i){
                                    case 0:
                                        a = 2;
                                        break;
                                    case 1:
                                        a = -2;
                                        break;
                                    case 2:
                                        a = 1;
                                        b = 2;
                                        break;
                                    default:
                                        a = -1;
                                        break;
                                }
                                for (int j = 0; j < 2; ++j){
                                    b *= -1;

                                    if (between(ty+a, 0, 8) && between(tx+b, 0, 8)){
                                        if (data.board[ty+a][tx+b] == ' ' || isEnemy(data.board[ty+a][tx+b], data.turn)){
                                            move t = m;
                                            t.to[0] = 'a'+(tx+b);
                                            t.to[1] = '8'-(ty+a);
                                            moves.push_back(t);
                                        }
                                    }
                                }
                            }
                        }
                            break;
                        case 'R':   // Rook
                        {
                            int tx = x+1, ty = y;

                            // right
                            while (tx < 8){
                                if (data.board[ty][tx] != ' ') {
                                    if(isEnemy(data.board[ty][tx], data.turn)){
                                        move t = m;
                                        t.to[0] = 'a'+(tx);
                                        t.to[1] = '8'-(ty);
                                        moves.push_back(t);
                                    }
                                    break;
                                }else{
                                    move t = m;
                                    t.to[0] = 'a'+(tx);
                                    t.to[1] = '8'-(ty);
                                    moves.push_back(t);
                                }
                                ++tx;
                            }

                            // left
                            tx = x-1;
                            while (tx >= 0){
                                if (data.board[ty][tx] != ' ') {
                                    if(isEnemy(data.board[ty][tx], data.turn)){
                                        move t = m;
                                        t.to[0] = 'a'+(tx);
                                        t.to[1] = '8'-(ty);
                                        moves.push_back(t);
                                    }
                                    break;
                                }else{
                                    move t = m;
                                    t.to[0] = 'a'+(tx);
                                    t.to[1] = '8'-(ty);
                                    moves.push_back(t);
                                }
                                --tx;
                            }

                            // up
                            tx = x;
                            ty = y-1;
                            while (ty >= 0){
                                if (data.board[ty][tx] != ' ') {
                                    if(isEnemy(data.board[ty][tx], data.turn)){
                                        move t = m;
                                        t.to[0] = 'a'+(tx);
                                        t.to[1] = '8'-(ty);
                                        moves.push_back(t);
                                    }
                                    break;
                                }else{
                                    move t = m;
                                    t.to[0] = 'a'+(tx);
                                    t.to[1] = '8'-(ty);
                                    moves.push_back(t);
                                }
                                --ty;
                            }

                            // down
                            ty = y+1;
                            while (ty < 8){
                                if (data.board[ty][tx] != ' ') {
                                    if(isEnemy(data.board[ty][tx], data.turn)){
                                        move t = m;
                                        t.to[0] = 'a'+(tx);
                                        t.to[1] = '8'-(ty);
                                        moves.push_back(t);
                                    }
                                    break;
                                }else{
                                    move t = m;
                                    t.to[0] = 'a'+(tx);
                                    t.to[1] = '8'-(ty);
                                    moves.push_back(t);
                                }
                                ++ty;
                            }
                        }
                            break;
                        case 'P':   // Pawn
                        {
                            int direction = isupper(data.board[y][x]) ? -1 : 1;
                            int ty = y + direction;
                            if (data.board[ty][x] == ' '){
                                move t = m;
                                t.to[0] = 'a' + x;
                                t.to[1] = '8'-ty;
                                moves.push_back(t);
                            }

                            if (between(x - 1, 0, 8) && data.board[ty][x-1] != ' ' && isEnemy(data.board[ty][x - 1], data.turn)) {
                                move t = m;
                                t.to[0] = 'a' + (x - 1);
                                t.to[1] = '8' - ty;
                                moves.push_back(t);
                            }

                            if (between(x + 1, 0, 8) && data.board[ty][x+1] != ' ' && isEnemy(data.board[ty][x + 1], data.turn)) {
                                move t = m;
                                t.to[0] = 'a' + (x + 1);
                                t.to[1] = '8' - ty;
                                moves.push_back(t);
                            }

                            if (isupper(data.board[y][x])){
                                if (y == 6 && data.board[ty][x] == ' ' && data.board[ty+direction][x] == ' '){
                                    move t = m;
                                    t.to[0] = 'a'+x;
                                    t.to[1] = '8' - (ty+direction);
                                    moves.push_back(t);
                                }
                                if (y == 3){
                                    int tx = x-1;
                                    if (between(tx, 0, 8) && data.board[y][tx] == 'p'){
                                        char prevMove[5];
                                        prevMove[0] = 'a' + tx;
                                        prevMove[1] = '7';
                                        prevMove[2] = 'a' + tx;
                                        prevMove[3] = '5';
                                        prevMove[4] = '\0';
                                        if (compareStringArray(data.prevMove, prevMove)){
                                            move t = m;
                                            t.to[0] = 'a'+tx;
                                            t.to[1] = '6';
                                            t.promotion = 'E';
                                            moves.push_back(t);
                                        }
                                        printf("prevMove: %s\t\t%s\n", prevMove, data.prevMove);
                                    }
                                    tx = x+1;
                                    if (between(tx, 0, 8) && data.board[y][tx] == 'p'){
                                        char prevMove[5];
                                        prevMove[0] = 'a' + tx;
                                        prevMove[1] = '7';
                                        prevMove[2] = 'a' + tx;
                                        prevMove[3] = '5';
                                        prevMove[4] = '\0';
                                        if (compareStringArray(data.prevMove, prevMove)){
                                            move t = m;
                                            t.to[0] = 'a'+tx;
                                            t.to[1] = '6';
                                            t.promotion = 'E';
                                            moves.push_back(t);
                                        }
                                    }
                                }
                            }else{
                                if (y == 1 && data.board[ty][x] == ' ' && data.board[ty+direction][x] == ' '){
                                    move t = m;
                                    t.to[0] = 'a'+x;
                                    t.to[1] = '8' - (ty+direction);
                                    moves.push_back(t);
                                }
                                if (y == 4){
                                    int tx = x-1;
                                    if (between(tx, 0, 8) && data.board[y][tx] == 'P'){
                                        char prevMove[5];
                                        prevMove[0] = 'a' + tx;
                                        prevMove[1] = '7';
                                        prevMove[2] = 'a' + tx;
                                        prevMove[3] = '5';
                                        prevMove[4] = '\0';
                                        if (compareStringArray(data.prevMove, prevMove)){
                                            move t = m;
                                            t.to[0] = 'a'+tx;
                                            t.to[1] = '6';
                                            t.promotion = 'E';
                                            moves.push_back(t);
                                        }
                                    }
                                    tx = x+1;
                                    if (between(tx, 0, 8) && data.board[y][tx] == 'P'){
                                        char prevMove[5];
                                        prevMove[0] = 'a' + tx;
                                        prevMove[1] = '2';
                                        prevMove[2] = 'a' + tx;
                                        prevMove[3] = '4';
                                        prevMove[4] = '\0';
                                        if (compareStringArray(data.prevMove, prevMove)){
                                            move t = m;
                                            t.to[0] = 'a'+tx;
                                            t.to[1] = '3';
                                            t.promotion = 'E';
                                            moves.push_back(t);
                                        }
                                    }
                                }
                            }

                            

                        }
                            break;
                        default:
                            break;       
                    }
                }


                //moves.push_back(m);

            }

        }
    } 

    // return 1 if any of the destination (move::to) is onto king's place

    for (unsigned int i = 0; i < moves.size(); ++i){
        int x, y;

        x = moves[i].to[0] - 'a';
        y = '8' - moves[i].to[1];


        if (toupper(data.board[y][x] )== 'K'){
            return 1;
        }
    }

    return 0;
}

chessData movePiece(chessData data, move curMove){
    int x1, y1,  x2, y2;

    x1 = curMove.from[0] - 'a';
    y1 = '8' - curMove.from[1];

    x2 = curMove.to[0] - 'a';
    y2 = '8' - curMove.to[1];

    //std::cout << "x1: " << x1 << "\ny1: " << y1 << "\n\nx2: " << x2 << "\ny2: " << y2 << "\n\n";

    if (toupper(data.board[y1][x1]) == 'K' && curMove.from[0] == 'e' && (curMove.from[1] == '1' || curMove.from[1] == '8')){
        if (abs(x1-x2)==2){
            int rookXf, rookXt;
            if (curMove.to[0] == 'g'){
                rookXt = 'f' - 'a';
                rookXf = 'h' - 'a';
            }else{
                rookXt = 'd' - 'a';
                rookXf = 'a' - 'a';
            }
            data.board[y2][rookXt] = data.board[y1][rookXf];
            data.board[y1][rookXf] = ' ';
        }
    }

    if (toupper(data.board[y1][x1]) == 'P'){
        if (y2 == 0 || y2 == 7){
            curMove.promotion = data.turn=='w' ? toupper(curMove.promotion) : tolower(curMove.promotion);
            data.board[y2][x2] = curMove.promotion!=0 ? curMove.promotion : data.turn=='w' ? 'Q' : 'q';
            data.board[y1][x1] = ' ';
            return data;
        }
    }

    if (curMove.promotion == 'E'){
        int mod = 0;
        if (data.turn == 'w'){
            mod = 1;
        }else{
            mod = -1;
        }
        data.board[y2+mod][x2] = ' ';
    }

    data.board[y2][x2] = data.board[y1][x1];
    data.board[y1][x1] = ' ';

    return data;
}

std::vector<move> legalMoves(chessData data){
    /*
     * iterate through all tiles
     * if empty (' '), skip
     * get all moves not outside of the board
     * can't move on it's own piece
     * stop on enemy's piece/before it's own piece
     * repeat the process as if after making each of the possible moves from previous steps,
     *      if taking king by enemy is possible, remove the move from legal moves
     * return legal moves
     */

    std::vector<move> moves;

    possibleMoves(data, moves);

    
    // check if now is check to allow/disallow castling
    if (data.castle[0] == 1) data.castle[0] = 0;
    if (data.castle[1] == 1) data.castle[1] = 0;
    if (data.castle[2] == 1) data.castle[2] = 0;
    if (data.castle[3] == 1) data.castle[3] = 0;
    if (data.turn == 'w'){
        if (data.board[0][4] != 'K'){
            data.castle[0] = data.castle[1] = 2;
        }
        int ty = 0;
        if (data.castle[0] == 0){
            if (data.board[ty][5] == data.board[ty][6] && data.board[ty][6] == ' '){
                chessData tempData = data;
                tempData.turn = 'b';
                std::vector<move> tempMoves;
                if (possibleMoves(tempData, tempMoves)){
                    data.castle[0] = 1;
                }else{
                    move m;
                    m.from[0] = 'e';
                    m.from[1] = '1';
                    m.to[0] = 'f';
                    m.to[1] = m.from[1];
                    chessData tempData2 = movePiece(tempData, m);
                    if (possibleMoves(tempData2, tempMoves)){
                        data.castle[0] = 1;
                    }else{
                        m.to[0] = 'g';
                        tempData2 = movePiece(tempData, m);
                        if (possibleMoves(tempData2, tempMoves)){
                            data.castle[0] = 1;
                        }
                    }
                }
            }
        }
        if (data.castle[1] == 0){
            if (data.board[ty][1] == data.board[ty][2] && data.board[ty][2] == data.board[ty][3] && data.board[ty][2] == ' '){
                chessData tempData = data;
                tempData.turn = 'b';
                std::vector<move> tempMoves;
                if (possibleMoves(tempData, tempMoves)){
                    data.castle[1] = 1;
                }else{
                    move m;
                    m.from[0] = 'e';
                    m.from[1] = '1';
                    m.to[0] = 'd';
                    m.to[1] = m.from[1];
                    chessData tempData2 = movePiece(tempData, m);
                    if (possibleMoves(tempData2, tempMoves)){
                        data.castle[1] = 1;
                    }else{
                        m.to[0] = 'c';
                        tempData2 = movePiece(tempData, m);
                        if (possibleMoves(tempData2, tempMoves)){
                            data.castle[1] = 1;
                        }
                    }
                }
            }
        }
    }else {
        if (data.board[7][4] != 'K'){
            data.castle[2] = data.castle[3] = 2;
        }
        int ty = 7;
        if (data.castle[2] == 0){
            if (data.board[ty][5] == data.board[ty][6] && data.board[ty][6] == ' '){
                chessData tempData = data;
                tempData.turn = 'w';
                std::vector<move> tempMoves;
                if (possibleMoves(tempData, tempMoves)){
                    data.castle[2] = 1;
                }else{
                    move m;
                    m.from[0] = 'e';
                    m.from[1] = '8';
                    m.to[0] = 'f';
                    m.to[1] = m.from[1];
                    chessData tempData2 = movePiece(tempData, m);
                    if (possibleMoves(tempData2, tempMoves)){
                        data.castle[2] = 1;
                    }else{
                        m.to[0] = 'g';
                        tempData2 = movePiece(tempData, m);
                        if (possibleMoves(tempData2, tempMoves)){
                            data.castle[2] = 1;
                        }
                    }
                }
            }
        }
        if (data.castle[3] == 0){
            if (data.board[ty][1] == data.board[ty][2] && data.board[ty][2] == data.board[ty][3] && data.board[ty][2] == ' '){
                chessData tempData = data;
                tempData.turn = 'w';
                std::vector<move> tempMoves;
                if (possibleMoves(tempData, tempMoves)){
                    data.castle[3] = 1;
                }else{
                    move m;
                    m.from[0] = 'e';
                    m.from[1] = '8';
                    m.to[0] = 'd';
                    m.to[1] = m.from[1];
                    chessData tempData2 = movePiece(tempData, m);
                    if (possibleMoves(tempData2, tempMoves)){
                        data.castle[3] = 1;
                    }else{
                        m.to[0] = 'c';
                        tempData2 = movePiece(tempData, m);
                        if (possibleMoves(tempData2, tempMoves)){
                            data.castle[3] = 1;
                        }
                    }
                }
            }
        }
    }

    move castle;
    if (data.turn == 'w'){
        castle.from[0] = 'e';
        castle.from[1] = '1';
        castle.to[1] = castle.from[1];
        if (data.castle[0] == 0){
            castle.to[0] = 'g';
            moves.push_back(castle);
        }
        if (data.castle[1] == 0){
            castle.to[0] = 'c';
            moves.push_back(castle);
        }
    }else{
        castle.from[0] = 'e';
        castle.from[1] = '8';
        castle.to[1] = castle.from[1];
        if (data.castle[2] == 0){
            castle.to[0] = 'g';
            moves.push_back(castle);
        }
        if (data.castle[3] == 0){
            castle.to[0] = 'c';
            moves.push_back(castle);
        }
    }


    
    // remove all moves that end in capturing the king
    for (unsigned int i = 0; i < moves.size(); ++i){
        chessData tempData = movePiece(data, moves[i]);
        std::vector<move> tempMoves;

        changeTurn(tempData);
        if (possibleMoves(tempData, tempMoves) == 1){
            moves.erase(moves.begin() + i);
            --i;
        }
    }

    cout << "\n#######\n";
    return moves;
}

int main(){
    chessData board1;
    board1.turn = 'w';

    for (int i = 0; i < 8; ++i){
        for (int j = 0; j < 8; ++j){
            std::cout << board1.board[i][j] << " ";
        }
        std::cout << '\n';
    }

    std::cout << "\nlegal move:\n\n";

    std::vector<move> moves = legalMoves(board1);

    for (unsigned int i = 0 ; i < moves.size(); ++i){
        std::cout << moves[i].from << '\t' << moves[i].to << '\n';
    }


    return 0;
}