const int MAX_INIT=20000;
const int MIN_INIT=-20000;
const int win =10000;
const int lose = -10000;

    enum direction {UP,DOWN,LEFT,RIGHT};
    struct offset{
        int horizontal,vertical;
    };

class node{
        public:
            int row,col,emergency;
    };

    class Student{
    public:

        void makeMove(int Record[5][6], int Max[5][6], Color color[5][6], Color inputColor);
        // Any Code You Want to Add
        //void minmaxMove(int Record[5][6], int Max[5][6], Color color[5][6], Color inputColor);
        int getX(){
            return x;
            // Your Code
        }
        int getY(){
            return y;
            // Your Code
        }
    private:
        int x;
        int y;
        bool CriticalEnemyNear(Color inputColor, int i, int j, Color color[5][6], int Max[5][6], int Record[5][6]);
        int MoveScore(int Record[5][6], int Max[5][6], Color color[5][6], Color inputColor);
        bool enemyBeside(Color inputColor, int i, int j, Color color[5][6],int Max[5][6], int Record[5][6]);
        int enemySore(Color inputColor, int i, int j, Color color[5][6],int Max[5][6], int Record[5][6]);
        int evaluate(int Record[5][6], int Max[5][6], Color color[5][6], Color myColor,bool isMax);
        int MinMax(int Record[5][6], int Max[5][6], Color color[5][6], Color myColor, int depth, bool isMax,int alpha,int beta);
        void CheckNeighborExplosion(int i, int j, int (&Record)[5][6], int Max[5][6], Color (&color)[5][6]);
        bool CheckExplosion(int (&Record)[5][6], int Max[5][6], Color (&color)[5][6]);
        bool enemyNearBy(Color inputColor, int i, int j, Color color[5][6],int Max[5][6], int Record[5][6]);
        bool friendNearBy(Color inputColor, int i, int j, Color color[5][6]);
        bool IsEnemyColor(Color myColor, Color EnemyColor);
        bool CanAttackEnemy(Color inputColor, int i, int j, Color color[5][6], int Max[5][6], int Record[5][6]);
        void CopyRecordandColor(int sourceRec[5][6], Color sourceCol[5][6], int (&destRec)[5][6], Color (&destCol)[5][6]);
    };

void Student::CopyRecordandColor(int sourceRec[5][6], Color sourceCol[5][6], int (&destRec)[5][6], Color (&destCol)[5][6]){
    for (int i=0; i<5; i++)
        for(int j=0; j<6; j++){
            destRec[i][j]=sourceRec[i][j];
            destCol[i][j]=sourceCol[i][j];
        }  

}  

void Student::makeMove(int Record[5][6], int Max[5][6], Color color[5][6], Color inputColor){
    int best=MIN_INIT;
    node move;
    move.row=-1;
    move.col=-1;
    int tryValue=0;
    int copyRecord[5][6];
    Color copyColor[5][6];
    bool explode=false;
    CopyRecordandColor(Record, color, copyRecord, copyColor);

    for (int i=0; i<5; i++)
        for(int j=0; j<6; j++){
            if (color[i][j]==inputColor || color[i][j] ==White){
                  
                    explode=false;

                    copyRecord[i][j]=copyRecord[i][j]+1;
                    copyColor[i][j]=inputColor;
                    explode=CheckExplosion(copyRecord,Max,copyColor);
                    tryValue = MinMax(copyRecord, Max, copyColor, inputColor, 0, false, MIN_INIT, MAX_INIT);

                    if (explode){
                        CopyRecordandColor(Record, color, copyRecord, copyColor);                        
                    }
                    else{
                        copyRecord[i][j]=Record[i][j];
                        copyColor[i][j]=color[i][j];
                    }

                    if (tryValue> best){

                        move.row=i;
                        move.col=j;
                        best=tryValue;
                    }
            }

        }
    //cout<<"best:"<<best<<endl;
    x=move.row;
    y=move.col;




}


bool Student::enemyBeside(Color inputColor, int i, int j, Color color[5][6],int Max[5][6], int Record[5][6]){
 offset move[4];
            move[UP].horizontal=0;
            move[UP].vertical=-1;
            move[DOWN].horizontal=0;
            move[DOWN].vertical=1;
            move[LEFT].horizontal=-1;
            move[LEFT].vertical=0;
            move[RIGHT].horizontal=1;
            move[RIGHT].vertical=0;
            int  neighbor_row, neighbor_col;  
            int d=0;
                while(d<4){ 
                    neighbor_row=i+move[d].vertical;
                    neighbor_col=j+move[d].horizontal;
                    if (neighbor_row>=0 && neighbor_row<5 && neighbor_col>=0 && neighbor_col< 6  ){
                        if (IsEnemyColor(inputColor, color[neighbor_row][neighbor_col]) ==true )
                            return true;
                    }                    

                    d++;
                }
                return false;

}
int Student::enemySore(Color inputColor, int i, int j, Color color[5][6],int Max[5][6], int Record[5][6]){
            int score=0;
            offset move[4];
            move[UP].horizontal=0;
            move[UP].vertical=-1;
            move[DOWN].horizontal=0;
            move[DOWN].vertical=1;
            move[LEFT].horizontal=-1;
            move[LEFT].vertical=0;
            move[RIGHT].horizontal=1;
            move[RIGHT].vertical=0;
            int  neighbor_row, neighbor_col;  
            int d=0;
                while(d<4){ 
                    neighbor_row=i+move[d].vertical;
                    neighbor_col=j+move[d].horizontal;
                    if (neighbor_row>=0 && neighbor_row<5 && neighbor_col>=0 && neighbor_col< 6  ){
                        if ((IsEnemyColor(inputColor, color[neighbor_row][neighbor_col]) ==true) &&
                            (Record[neighbor_row][neighbor_col] == Max[neighbor_row][neighbor_col]-1)){
                            score=score+(5-Max[neighbor_row][neighbor_col]);
                            }
                    }                    

                    d++;
                }
            return score;
             

}

int Student::evaluate(int Record[5][6], int Max[5][6], Color color[5][6], Color myColor, bool isMax){
    int score=0;
    Color calColor,enemyColor;
    if (myColor==Blue)
        enemyColor=Red;
    else
        enemyColor=Blue;

    calColor=myColor;    
/*
    if (isMax)
        calColor=myColor;
    else
        calColor=enemyColor;*/

    score=MoveScore(Record, Max, color,calColor);

 
    //all black
    bool endgame=true;
    for (int i=0;i<5; i++)
        for(int j=0;j<6; j++){
            if ((color[i][j]== myColor) || (color[i][j] == enemyColor) ){
                endgame=false;
                break;
            }
        }

    

    
    if(endgame && !isMax)
        return win;
    else if (endgame && isMax)
        return lose;

    
    bool allmycolor=true;
    for (int i=0;i<5; i++)
        for(int j=0;j<6; j++){
            if (color[i][j]==enemyColor){
                allmycolor=false;
                break;
            }
        }

    bool allenemycolor=true;
    for (int i=0;i<5; i++)
        for(int j=0;j<6; j++){
            if (color[i][j]==myColor){
                allenemycolor=false;
                break;
            }
        }



    if(allmycolor && (allenemycolor==false))
        score= win;
    else if ((allmycolor==false) && allenemycolor)
        score= lose;        


   /*if (!isMax)
        score=score*(-1);*/

    
    return score;
}

int Student::MinMax(int Record[5][6], int Max[5][6], Color color[5][6], Color myColor, int depth, bool isMax,int alpha,int beta){
    int score=evaluate(Record,Max,color, myColor,isMax);

    int copyRecord[5][6];
    Color copyColor[5][6];

    /*int countWhite=0;

    for(int i=0;i<5;i++)
            for(int j=0;j<6;j++){
                if ( color[i][j] ==White){
                    countWhite++;
                }
            }   

    if (countWhite>9){
        if (depth==2)
            return score;
        
    }   */

    // If Maximizer has won the game return his/her 
    // evaluated score 
    if (score == win) 
        return score; 

    // If Minimizer has won the game return his/her 
    // evaluated score 
    if (score == lose) 
        return score;  

        if (depth==3)
            return score;

    CopyRecordandColor(Record, color, copyRecord, copyColor);
    
    bool explode=false;
    

    //max's move
    if (isMax){
        int best=MIN_INIT;

        //check valid move
        for(int i=0;i<5;i++)
            for(int j=0;j<6;j++){
                if (color[i][j]==myColor || color[i][j] ==White){
                    
                    explode=false;


                    copyRecord[i][j]=copyRecord[i][j]+1;
                    copyColor[i][j]=myColor;
                    explode=CheckExplosion(copyRecord,Max,copyColor);
                    best = max(best, MinMax(copyRecord, Max, copyColor, myColor, depth+1, !isMax, alpha,beta));

                    alpha= max(best, alpha);

                    /*if (best==win)
                        return best;*/

                    if (beta <= alpha)
                        break;

                    if (explode){
                        CopyRecordandColor(Record, color, copyRecord, copyColor);
                    }
                    else{
                        copyRecord[i][j]=Record[i][j];
                        copyColor[i][j]=color[i][j];
                    }                    
                }
            }
        
        return best;


    }
    else{// min's move

        int best=MAX_INIT;
        //check valid move
        for(int i=0;i<5;i++)
            for(int j=0;j<6;j++){
                if (color[i][j]!=myColor &&  color[i][j] !=Black){

                    explode=false;


                    copyRecord[i][j]=copyRecord[i][j]+1;
                    Color opponentColor;
                    if (myColor == Blue)
                        opponentColor=Red;
                    else
                        opponentColor=Blue;
                    copyColor[i][j]=opponentColor;
                    explode=CheckExplosion(copyRecord,Max,copyColor);
                    best = min(best, MinMax(copyRecord, Max, copyColor, myColor, depth+1, !isMax,alpha,beta));
                    beta = min(beta,best);

                    /*if (best==lose)
                        return best;*/

                    if (beta<=alpha)
                        break;

                    if (explode){
                        CopyRecordandColor(Record, color, copyRecord, copyColor);
                    }
                    else{
                        copyRecord[i][j]=Record[i][j];
                        copyColor[i][j]=color[i][j];
                    } 
                }
            }
        
        return best;        
    }
}

    bool NodeCompareLess(node n1, node n2){
        return (n1.emergency < n2.emergency);
    }

    bool NodeCompareLarge(node n1, node n2){
        return (n1.emergency > n2.emergency);
    }


    bool Student::IsEnemyColor(Color myColor, Color EnemyColor ){
            if (EnemyColor != White && EnemyColor != Black && EnemyColor != myColor)
                return true;
            else
                return false;
        }    

    bool Student::friendNearBy(Color inputColor, int i, int j, Color color[5][6]){
            offset move[4];
            move[UP].horizontal=0;
            move[UP].vertical=-1;
            move[DOWN].horizontal=0;
            move[DOWN].vertical=1;
            move[LEFT].horizontal=-1;
            move[LEFT].vertical=0;
            move[RIGHT].horizontal=1;
            move[RIGHT].vertical=0;
            int  neighbor_row, neighbor_col;  
            int d=0;
                while(d<4){ 
                    neighbor_row=i+move[d].vertical;
                    neighbor_col=j+move[d].horizontal;
                    if (neighbor_row>=0 && neighbor_row<5 && neighbor_col>=0 && neighbor_col< 6  ){
                        if (inputColor==color[neighbor_row][neighbor_col])
                            return true;
                    }                    

                    d++;
                }
                return false;

    }

    bool Student::CriticalEnemyNear(Color inputColor, int i, int j, Color color[5][6], int Max[5][6], int Record[5][6]){
            offset move[4];
            move[UP].horizontal=0;
            move[UP].vertical=-1;
            move[DOWN].horizontal=0;
            move[DOWN].vertical=1;
            move[LEFT].horizontal=-1;
            move[LEFT].vertical=0;
            move[RIGHT].horizontal=1;
            move[RIGHT].vertical=0;
            int  neighbor_row, neighbor_col;  
            int d=0;
                while(d<4){ 
                    neighbor_row=i+move[d].vertical;
                    neighbor_col=j+move[d].horizontal;
                    if (neighbor_row>=0 && neighbor_row<5 && neighbor_col>=0 && neighbor_col< 6  ){
                        if ((IsEnemyColor(inputColor, color[neighbor_row][neighbor_col]) ==true) &&
                             (Max[neighbor_row][neighbor_col]-Record[neighbor_row][neighbor_col] == 1))
                            return true;
                    }                    

                    d++;
                }
                return false;

    }
    

    bool Student::enemyNearBy(Color inputColor, int i, int j, Color color[5][6], int Max[5][6], int Record[5][6]){
            offset move[4];
            move[UP].horizontal=0;
            move[UP].vertical=-1;
            move[DOWN].horizontal=0;
            move[DOWN].vertical=1;
            move[LEFT].horizontal=-1;
            move[LEFT].vertical=0;
            move[RIGHT].horizontal=1;
            move[RIGHT].vertical=0;
            int  neighbor_row, neighbor_col;  
            int d=0;
                while(d<4){ 
                    neighbor_row=i+move[d].vertical;
                    neighbor_col=j+move[d].horizontal;
                    if (neighbor_row>=0 && neighbor_row<5 && neighbor_col>=0 && neighbor_col< 6  ){
                        if (IsEnemyColor(inputColor, color[neighbor_row][neighbor_col]) ==true &&
                             Max[neighbor_row][neighbor_col]-Record[neighbor_row][neighbor_col]<= Max[i][j]-Record[i][j])
                            return true;
                    }                    

                    d++;
                }
                return false;

    }

    bool Student::CanAttackEnemy(Color inputColor, int i, int j, Color color[5][6], int Max[5][6], int Record[5][6]){
            offset move[4];
            move[UP].horizontal=0;
            move[UP].vertical=-1;
            move[DOWN].horizontal=0;
            move[DOWN].vertical=1;
            move[LEFT].horizontal=-1;
            move[LEFT].vertical=0;
            move[RIGHT].horizontal=1;
            move[RIGHT].vertical=0;
            int  neighbor_row, neighbor_col;  
            int d=0;
            bool canAttack=false;
                while(d<4){ 
                    neighbor_row=i+move[d].vertical;
                    neighbor_col=j+move[d].horizontal;
                    if (neighbor_row>=0 && neighbor_row<5 && neighbor_col>=0 && neighbor_col< 6  ){
                        if (IsEnemyColor(inputColor, color[neighbor_row][neighbor_col]) ==true ){
                            if ((Max[neighbor_row][neighbor_col]-Record[neighbor_row][neighbor_col]) >= (Max[i][j]-Record[i][j]))
                                canAttack=true;
                            else
                                return false;
                        }

                    }                    

                    d++;
                }
                if (canAttack)
                    return true;
                else
                    return false;

    }
    int Student::MoveScore(int Record[5][6], int Max[5][6], Color color[5][6], Color inputColor){
        int score=0;
            //defend check
            //int emCount=0;
            bool hasEnemy=false;
            for(int i=0;i<5;i++)
                for(int j=0;j<6;j++){
                    if (color[i][j]==inputColor){
                        score++;
                        if (CriticalEnemyNear(inputColor, i,j, color,Max,Record)==true){
                            score=score-enemySore(inputColor, i,j, color,Max,Record);
                        }
                        else{
                            if (Record[i][j]==Max[i][j]-1)
                                score=score+2;
                            if(i==0 && j==0 )
                                score=score+3;
                            else if(i==0 && j==5 )
                                score=score+3;    
                            else if(i==4 && j==0 )
                                score=score+3;                                                        
                            else if(i==4 && j==5 )
                                score=score+3;     
                            else if(i==0  )
                                score=score+2;
                            else if(j==5 )
                                score=score+2;    
                            else if(i==4 )
                                score=score+2;                                                                
                            else if( j==0 )
                                score=score+2;  

                            if (friendNearBy(inputColor, i,j, color)==false)
                                score=score+1; 
                            if (Record[i][j]== Max[i][j]-1)
                                score=score+2*Record[i][j];

                        }

                        
                     }
                }

            
           /*
            if (color[0][0]==inputColor){
                score=score+2;
            }

            if (color[4][0]==inputColor){
                score=score+2;
            }

            if (color[0][5]==inputColor){
                score=score+2;
            }   

            if (color[4][5]==inputColor){
                score=score+2;    
            } */



bool findSafe=false;
//fill to ready fire


           /* for(int i=0;i<5;i++)
                for(int j=0;j<6;j++){
                    if (color[i][j]==inputColor){
                        //if (Record[i][j]== Max[i][j]-1) {
                       // if (enemyNearBy(inputColor, i,j, color,Max, Record)==false && friendNearBy(inputColor, i,j, color)==false){
                        if (friendNearBy(inputColor, i,j, color)==false){
                            score=score+2;
                            //return;
                        }
                    }
                }*/

  

            //find safe
/*
           
            findSafe=false;
            for(int i=0;i<5;i++)
                for(int j=0;j<6;j++){
                    if (color[i][j]==inputColor){
                        if (enemyNearBy(inputColor, i,j, color,Max, Record)==false && friendNearBy(inputColor, i,j, color)==false){
                            score=score+2*Record[i][j];
                            //return;
                        }
                    }
                }



            //attack

            findSafe=false;
            for(int i=0;i<5;i++)
                for(int j=0;j<6;j++){
                    if (color[i][j]==inputColor){
                        if (CanAttackEnemy(inputColor, i,j, color,Max, Record)==true ){
                            score=score+2*Max[i][j];    
                           
                        }
                    }
                }*/

return score;
 //find safe2
/*
            vector<node>().swap(emergencyGroup);
            findSafe=false;
            for(int i=0;i<5;i++)
                for(int j=0;j<6;j++){
                    if (color[i][j]==White){
                        if (enemyNearBy(inputColor, i,j, color,Max, Record)==false ){
                            emNode.row=i;
                            emNode.col=j;
                            emNode.emergency=Max[i][j];
                            emergencyGroup.push_back(emNode);
                            findSafe=true;
                            //return;
                        }
                    }
                }

            if(findSafe==true){
                sort(emergencyGroup.begin(), emergencyGroup.end(), NodeCompareLess);
                x=emergencyGroup[0].row;
                y=emergencyGroup[0].col;
                return;
            }            
            /*for(int i=0;i<5;i++)
                for(int j=0;j<6;j++){
                    if (color[i][j]==White){  
                                          
                            x=i;
                            y=j;
                            return;
                   
                    }
                }*/

           /* vector<node>().swap(emergencyGroup);
            findSafe=false;

            for(int i=0;i<5;i++)
                for(int j=0;j<6;j++){
                    if (color[i][j]==inputColor){  
                            findSafe=true;                   
                            emNode.row=i;
                            emNode.col=j;
                            emNode.emergency=Max[i][j]-Record[i][j];
                            emergencyGroup.push_back(emNode);
                            //return;                   
                    }
                }  

            if (findSafe==true){
                sort(emergencyGroup.begin(), emergencyGroup.end(), NodeCompareLess);
                x=emergencyGroup[0].row;
                y=emergencyGroup[0].col;
                return;
            }          */
            
    }

  


    
    void Student::CheckNeighborExplosion(int i, int j, int (&Record)[5][6], int Max[5][6], Color (&color)[5][6]){
offset move[4];
    move[UP].horizontal=0;
    move[UP].vertical=-1;
    move[DOWN].horizontal=0;
    move[DOWN].vertical=1;
    move[LEFT].horizontal=-1;
    move[LEFT].vertical=0;
    move[RIGHT].horizontal=1;
    move[RIGHT].vertical=0;

    int  neighbor_row, neighbor_col;  
    int d=0;
        while(d<4){ 
            neighbor_row=i+move[d].vertical;
            neighbor_col=j+move[d].horizontal;
            if (neighbor_row>=0 && neighbor_row<5 && neighbor_col>=0 && neighbor_col< 6  && color[neighbor_row][neighbor_col] !=Black){
                color[neighbor_row][neighbor_col]=color[i][j];
                Record[neighbor_row][neighbor_col]=Record[neighbor_row][neighbor_col]+1;
                if (Record[neighbor_row][neighbor_col] == Max[neighbor_row][neighbor_col]){

                    CheckNeighborExplosion(neighbor_row, neighbor_col, Record, Max,color);
                }

                    
            }                    

            d++;
        }
    Record[i][j]=0;
    color[i][j]=Black;
    }
    bool Student::CheckExplosion(int (&Record)[5][6], int Max[5][6], Color (&color)[5][6]){
    
        bool explode=false;
   
        for (int i=0; i<5 ;i++){
            for (int j=0; j<6; j++){
                if (Record[i][j]==Max[i][j] && color[i][j] != Black){
                    explode=true;
                    Record[i][j]=0;
                    CheckNeighborExplosion(i,j,Record, Max, color);
                }
            }
        }
        return explode;

    }



