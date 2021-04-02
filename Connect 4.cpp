#include<iostream>
#include<cmath>
#include<simplecpp>
using namespace std ;

void outwardIterator(int &i){
    if(i==3){ i=4 ;}
    else if(i==4){ i=2 ;}
    else if(i==2){ i=5 ;}
    else if(i==5){ i=1 ;}
    else if(i==1){ i=6 ;}
    else if(i==6){ i=0 ;}
    else{ i=8 ;}
}

bool gameEnded(int state[7][6]){
    for(int j=0 ; j<6 ; j++){ //horizontal win
        for(int i=0 ; i<4 ; i++){
            if(state[i][j]>0  && state[i+1][j]==state[i][j] && state[i+2][j]==state[i+1][j] && state[i+3][j]==state[i+2][j] ){
                return true ;
            }
        }
    }

    for(int i=0 ; i<7 ; i++){ //vertical win
        for(int j=0 ; j<3 ; j++){
            if(state[i][j]>0 && state[i][j]==state[i][j+1] && state[i][j+1]==state[i][j+2] && state[i][j+2]==state[i][j+3] ){
                return true ;
            }
        }
    }

    for(int i=0; i<4 ; i++){ //diagonal win
        for(int j= 0 ; j<3 ; j++){
            if(state[i][j]>0  && state[i][j]==state[i+1][j+1] && state[i+1][j+1]==state[i+2][j+2] && state[i+2][j+2]==state[i+3][j+3] ){
                return true ;
            }
        }
    }

    for(int i=3; i<7 ; i++){ //diagonal win
        for(int j=0 ; j<3 ; j++){
            if(state[i][j] >0 && state[i][j]==state[i-1][j+1] && state[i-1][j+1]==state[i-2][j+2] && state[i-2][j+2]==state[i-3][j+3] ){
                return true ;
            }
        }
    }

    for(int i=0 ; i<7 ; i++){// game not tied
        for(int j=0 ; j <6 ; j++){
            if(state[i][j]==0){
                return false ;
            }
        }
    }

    return true ;

}

int checkWin(int state[7][6]){ //returns the player who is winning in the current state. At a time only one player can win. If no win then returns 0.

    for(int j=0 ; j<6 ; j++){ //horizontal win
        for(int i=0 ; i<4 ; i++){
            if(state[i][j]>0  && state[i+1][j]==state[i][j] && state[i+2][j]==state[i+1][j] && state[i+3][j]==state[i+2][j] ){
                return state[i][j] ;
            }
        }
    }

    for(int i=0 ; i<7 ; i++){ //vertical win
        for(int j=0 ; j<3 ; j++){
            if(state[i][j]>0 && state[i][j]==state[i][j+1] && state[i][j+1]==state[i][j+2] && state[i][j+2]==state[i][j+3] ){
                return state[i][j] ;
            }
        }
    }

    for(int i=0; i<4 ; i++){ //diagonal win
        for(int j= 0 ; j<3 ; j++){
            if(state[i][j]>0  && state[i][j]==state[i+1][j+1] && state[i+1][j+1]==state[i+2][j+2] && state[i+2][j+2]==state[i+3][j+3] ){
                return state[i][j] ;
            }
        }
    }

    for(int i=3; i<7 ; i++){ //diagonal win
        for(int j=0 ; j<3 ; j++){
            if(state[i][j] >0 && state[i][j]==state[i-1][j+1] && state[i-1][j+1]==state[i-2][j+2] && state[i-2][j+2]==state[i-3][j+3] ){
                return state[i][j] ;
            }
        }
    }

    return 0 ;
}

bool checkDraw(int state[7][6]){ //Called only after checking that there is no win. If there is no win, and the whole board is full, then its a draw.
    for(int i=0 ; i<7 ; i++){// game not tied
        for(int j=0 ; j <6 ; j++){
            if(state[i][j]==0){
                return false ;
            }
        }
    }
    return true ;
}

int checkTrap(int state[7][6]){ //Called only after checking that there is no win or draw.
    /*Types of traps:
    1) _xxx_ type along horizontal or diagonal
    2) The seven trap. Two blocking positions on same vertical with y differing by odd number.
    */
    bool trapBy1 = false ;
    bool trapBy2 = false ;
    for(int i = 0 ; i <7 ; i++){ // 7 type trap
        for(int j=0 ; j<5 ; j++){
                if(state[i][j]==0 && state[i][j+1]==0){
                    bool b1=false,b2=false,b3=false,b4=false ;

                    state[i][j]=1;
                    if(checkWin(state)==1){
                        b1=true;
                    }
                    state[i][j]=2;
                    if(checkWin(state)==2){
                        b2=true;
                    }
                    state[i][j]=0;
                    state[i][j+1]=1;
                    if(checkWin(state)==1){
                        b3=true;
                    }
                    state[i][j+1]=2;
                    if(checkWin(state)==2){
                        b4=true;
                    }
                    state[i][j+1]=0;

                    if(b1&&b3){
                        trapBy1 = true ;
                    }
                    if(b2&&b4){
                        trapBy2 = true ;
                    }
                }
            }
        }

    for(int i=1 ; i < 6 ; i++){ //horizontal trap
        for(int j = 0 ; j<6 ; j++){
            if(state[i][j]>0 && state[i][j]==state[i+1][j] && state[i+1][j]==state[i+2][j] && state[i-1][j]==0 && state[i+3][j]==0){
                if( (j==0) || ( state[i-1][j-1]>0 && state[i+3][j-1] >0 )){
                    if(state[i][j] ==1){
                        trapBy1 = true ;
                    }
                    else if(state[i][j] == 2){
                        trapBy2 = true ;
                    }
                }
            }
        }
    }

    for(int i =1 ; i < 4 ; i++){ //diagonal trap
        for(int j=1; j<3 ; j++){
            if(state[i][j]>0 && state[i][j]==state[i+1][j+1] && state[i+1][j+1]==state[i+2][j+2] && state[i-1][j-1]==0 && state[i+3][j+3]==0){
                if( (j==1 && state[i+3][j+2] > 0) || ( state[i-1][j-2]>0 && state[i+3][j+2] > 0)){
                    if(state[i][j] ==1){
                        trapBy1 = true ;
                    }
                    else if(state[i][j] == 2){
                        trapBy2 = true ;
                    }
                }
            }
        }
    }

    for(int i=3 ; i<6 ; i++){ //diagonal trap
        for(int j=1 ; j<3 ; j++){
            if(state[i][j]>0 && state[i][j]==state[i-1][j+1] && state[i-1][j+1]==state[i-2][j+2] && state[i+1][j-1]==0 && state[i-3][j+3]==0){
                if((j==1 && state[i-3][j+2] > 0) || (state[i+1][j-2] > 0 && state[i-3][j+2] > 0)){
                    if(state[i][j] ==1){
                        trapBy1 = true ;
                    }
                    else if(state[i][j] == 2){
                        trapBy2 = true ;
                    }
                }
            }
        }
    }

    if(trapBy1 && trapBy2){
        return 3;
    }
    else if(trapBy1){
        return 1;
    }
    else if(trapBy2){
        return 2 ;
    }
    else{
        return 0;
    }
}

int checkBlocker(int state[7][6]){ //Called only after checking that there is no win or draw.
    //checks for three in a row to block a fourth position
    bool blockerBy1 = false ;
    bool blockerBy2 = false ;
    for(int i=0 ; i<7 ; i++){
        for(int  j =0 ; j<6 ; j++){
            if(state[i][j]==0){
                state[i][j]=1 ;
                if(checkWin(state)==1){
                   blockerBy1 = true ;
                }
                state[i][j]= 2 ;
                if(checkWin(state)==2){
                    blockerBy2 = true ;
                }
                state[i][j]=0;
            }
        }
    }
    if(blockerBy1&&blockerBy2){
        return 3 ;
    }
    else if(blockerBy1){
        return 1;
    }
    else if(blockerBy2){
        return 2 ;
    }
    else{
        return 0 ;
    }
}

int getStaticValue(int state[7][6]){ //returns the static value of the given state with high values being better for player 1 , lower for player 2

    if(checkWin(state)==1){
        return 10 ;
    }
    else if(checkWin(state)==2){
        return 0 ;
    }
    else if(checkDraw(state)){
        return 5;
    }
    else if(checkTrap(state)==1){
        return 8;
    }
    else if(checkTrap(state)==2){
        return 2;
    }
    else if(checkTrap(state)==3){
        return 5 ;
    }
    else if(checkBlocker(state)==1){
        return 7;
    }
    else if(checkBlocker(state)==2){
        return 3;
    }
    else if(checkBlocker(state)==3){
        return 5;
    }
    else{
        return 5 ;
    }
}

int evaluate(int depth , int state[7][6] , int rowOcc[7] , int compNum , int playerNum , int& x){
    if(depth>1){
        double statVal[7] ;
        for(int i= 0; i < 7 ; i++){
            if(rowOcc[i]<6 ){
                state[i][rowOcc[i]] = compNum ;
                rowOcc[i]++ ;
                if(checkWin(state)==0){
                    statVal[i] = evaluate(depth-1 , state , rowOcc , playerNum , compNum , x) ;
                }
                else{
                    if(compNum==1){
                        statVal[i] = 10 + 0.1*(depth-1) ;
                    }
                    else{
                        statVal[i] = 0 - 0.1*(depth-1);
                    }
                }
                rowOcc[i] -- ;
                state[i][rowOcc[i]] = 0 ;
            }
            else{
                statVal[i] = -1 ;
            }
        }
        if(compNum==1){
            int maxInd = 100;
            double maxStatVal = -1 ;
            for(int i = 3 ; i< 7 ; outwardIterator(i)){
                if(statVal[i]>-1 && statVal[i]>maxStatVal){
                    maxStatVal = statVal[i] ;
                    maxInd = i ;
                }
            }
            x = maxInd ;
            return maxStatVal ;
        }
        else if(compNum==2){
            int minInd=100 ;
            double minStatVal=11 ;
            for(int i = 3 ; i< 7 ; outwardIterator(i)){
                if(statVal[i]>-1 && statVal[i]<minStatVal){
                    minStatVal = statVal[i] ;
                    minInd = i ;
                }
            }
            x = minInd;
            return minStatVal ;
        }
    }
    else{

        int statVal[7] ;
        for(int i= 0; i < 7 ; i++){
            if(rowOcc[i]<6 ){
                state[i][rowOcc[i]] = compNum ;
                rowOcc[i]++ ;
                statVal[i] = getStaticValue(state) ;
                rowOcc[i] -- ;
                state[i][rowOcc[i]] = 0 ;
            }
            else{
                statVal[i] = -1 ;
            }
        }
        if(compNum==1){
            int maxInd = 100;
            double maxStatVal = -1 ;
            for(int i = 3 ; i< 7 ; outwardIterator(i)){
                if(statVal[i]>-1 && statVal[i]>maxStatVal){
                    maxStatVal = statVal[i] ;
                    maxInd = i ;
                }
            }
            x = maxInd ;
            return maxStatVal ;
        }
        else if(compNum==2){
            int minInd=100 ;
            double minStatVal=11 ;
            for(int i = 3 ; i< 7 ; outwardIterator(i)){
                if(statVal[i]>-1 && statVal[i]<minStatVal){
                    minStatVal = statVal[i] ;
                    minInd = i ;
                }
            }
            x = minInd;
            return minStatVal ;
        }
    }
}

int main(){
    initCanvas("Connect 4",1000,1000);
    Rectangle frame(500+20-350/2,500-20+300/2,700/2,600/2);
    frame.imprint();
    Circle coin[7][6] ;
    int rowOcc[7];
    int state[7][6] ;
    int DEPTH = 5 ;
    int numMoves = 0 ;

    for(int i=0 ; i <7 ; i++){
        rowOcc[i] = 0 ;
    }


    for(int i = 0; i<7 ; i++){
        for(int j=0 ; j<6 ; j++){
            coin[i][j]= Circle(100,100,20);
            coin[i][j].moveTo(500-350+50+50*i , 500+300-50-50*j);
            coin[i][j].setFill(true);
            state[i][j] = 0 ;
        }
    }


    int playerNum ;
    int playerColor ;
    int compNum ;
    int compColor ;

    cin >> playerNum ;

    bool playerMove;


    if(playerNum==1){
        playerMove=true;
        playerColor = 0x00bbbb;
        compNum = 2 ;
        compColor = 0x000099;
    }
    else{
        playerMove=false;
        playerColor = 0x000099;
        compNum=1;
        compColor = 0x00bbbb;
    }

    while(gameEnded(state) == false){//
        if(playerMove){

            bool valid = false ;
            while(valid == false){
                int x;
                cin >> x ;
                if(x>=0 && x<=6 && rowOcc[x]<6){
                    coin[x][rowOcc[x]].setColor(playerColor);
                    state[x][rowOcc[x]] = playerNum ;
                    rowOcc[x] ++ ;
                    valid = true ;
                }
            }
            playerMove=false;
            numMoves++;
        }
        else {
            int x ;
            double s = evaluate(DEPTH , state , rowOcc , compNum , playerNum , x ) ; //
            state[x][rowOcc[x]] = compNum ;
            coin[x][rowOcc[x]].setColor(compColor) ;
            rowOcc[x]++;

            playerMove = true ;
            numMoves++;
        }
        if(numMoves>=38){
            DEPTH = 42 - numMoves ;
        }
    }

    if(checkDraw(state)==false){
        if(playerMove){
            cout << "COMPUTER WINS" ;
        }
        else{
            cout << "YOU WIN" ;
        }
    }
    else{
        cout << "GAME TIED" ;
    }
    wait(100);

}
