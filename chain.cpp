
    enum direction {UP,DOWN,LEFT,RIGHT};

    struct offset{
        int horizontal,vertical;
    };

    class Student{
    public:
        bool IsEnemyColor(Color myColor, Color EnemyColor ){
            if (EnemyColor != White && EnemyColor != Black && EnemyColor != myColor)
                return true;
            else
                return false;
        }
        bool enemyNearBy(Color inputColor, int i, int j, Color color[5][6]){
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
                        if (IsEnemyColor(inputColor, color[neighbor_row][neighbor_col]) ==true)
                            return true;
                    }                    

                    d++;
                }
                return false;

        }

        void makeMove(int Record[5][6], int Max[5][6], Color color[5][6], Color inputColor){
            
            //defend check
            for(int i=0;i<5;i++)
                for(int j=0;j<6;j++){
                    if (color[i][j]==inputColor){
                        if (enemyNearBy(inputColor, i,j, color)==true){
                            x=i;
                            y=j;
                            return;
                        }
                    }
                }
            
            if (color[0][0]==White){
                x=0;
                y=0;
                return;
            }

            if (color[4][0]==White){
                x=4;
                y=0;
                return;
            }

            if (color[0][5]==White){
                x=0;
                y=5;
                return;
            }   

            if (color[4][5]==White){
                x=4;
                y=5;
                return;
            } 

            //find safe
            for(int i=0;i<5;i++)
                for(int j=0;j<6;j++){
                    if (color[i][j]==White){
                        if (enemyNearBy(inputColor, i,j, color)==false){
                            x=i;
                            y=j;
                            return;
                        }
                    }
                }


            for(int i=0;i<5;i++)
                for(int j=0;j<6;j++){
                    if (color[i][j]==White){                   
                            x=i;
                            y=j;
                            return;
                   
                    }
                }

            for(int i=0;i<5;i++)
                for(int j=0;j<6;j++){
                    if (color[i][j]==inputColor){                   
                            x=i;
                            y=j;
                            return;
                   
                    }
                }
            

                    

                        



            
            // Your Code
        }
        // Any Code You Want to Add
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
    };