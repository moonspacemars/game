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
        bool enemyNearBy(Color inputColor, int i, int j, Color color[5][6]);
        bool IsEnemyColor(Color myColor, Color EnemyColor);
    };

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

    bool Student::enemyNearBy(Color inputColor, int i, int j, Color color[5][6]){
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

    void Student::makeMove(int Record[5][6], int Max[5][6], Color color[5][6], Color inputColor){
            vector<node> emergencyGroup;

            node emNode;


            
            //defend check
            //int emCount=0;
            bool hasEnemy=false;
            for(int i=0;i<5;i++)
                for(int j=0;j<6;j++){
                    if (color[i][j]==inputColor){
                        if (enemyNearBy(inputColor, i,j, color)==true){
                            x=i;
                            y=j;
                            emNode.row=i;
                            emNode.col=j;
                            emNode.emergency=Max[i][j]-Record[i][j];
                            emergencyGroup.push_back(emNode);
                            hasEnemy=true;
                            //return;
                        }
                    }
                }
            if (hasEnemy==true){
                sort(emergencyGroup.begin(), emergencyGroup.end(), NodeCompareLess); 
                x=emergencyGroup[0].row;
                y=emergencyGroup[0].col;
                return;
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

            vector<node>().swap(emergencyGroup);
            bool findSafe=false;
            for(int i=0;i<5;i++)
                for(int j=0;j<6;j++){
                    if (color[i][j]==White){
                        if (enemyNearBy(inputColor, i,j, color)==false){
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

            vector<node>().swap(emergencyGroup);
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
                sort(emergencyGroup.begin(), emergencyGroup.end(), NodeCompareLarge);
                x=emergencyGroup[0].row;
                y=emergencyGroup[0].col;
                return;
            }          
            
    }