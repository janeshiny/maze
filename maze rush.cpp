#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int dx[]={1,2,2,1,-1,-2,-2,-1};
int dy[]={2,1,-1,-2,-2,-1,1,2};
bool visited[50][50];


bool valid(int x,int y,int a,int b,int choice);
void solve(int a,int b);

int main(){
	int c;
	cout<<"\t\t\t\t\t\t ************************************************************"<<endl<<endl;
	cout<<"\t\t\t\t\t\t\t\t\t Min-L GAME"<<endl<<endl;
	cout<<"\t\t\t\t\t\t\t\t Choose the level of difficulty :"<<endl<<endl;
	cout<<"\n\t\t\t\t\t\t\t\t 1: EASY ( 4 X 4 GRID)"<<endl;
	cout<<"\n\t\t\t\t\t\t\t\t 2: MEDIUM ( 8 X 8 GRID)"<<endl;
	cout<<"\n\t\t\t\t\t\t\t\t 3: HARD ( 12 X 12 GRID)"<<endl;
	cout<<"\n\t\t\t\t\t\t\t\t 4: QUIT"<<endl<<endl;
	cout<<"\t\t\t\t\t\t ************************************************************"<<endl<<endl;
	cin>>c;
	switch(c){
	case 1:{
	    cout<<"\n\n\n";
            solve(4,4);
            break;
        }
        case 2:{
            cout<<"\n\n\n";
            solve(8,8);
            break;
        }
        case 3:{
            cout<<"\n\n\n";
            solve(12,12);
            break;
        }
        case 4:{            
            cout<<"\n\n\n";
            cout<<"\t\t\t\t\t\tThank you for playing"<<endl;
            break;
        }
        default:{
            cout<<"\n\n\n";
            cout<<"\n \t\t\t\t\t\tNot a valid choice"<<endl;
            break;
        }
    }
	return 0;
}

void solve(int a,int b){
	int distance[50][50],sx,sy,fx,fy;
	int x,y,nx,ny,i,j,z,x1,y1,step,max,invalid=0;
	int t[a+1][b+1],flag=0,ans=1;
	for(i=0;i<a;i++){
		for(j=0;j<b;j++){
			visited[i][j]=false;
			distance[i][j]=0;
		}
	}
//srand=>sets the sart to produce a series of pseudo random int
	srand(time(NULL));
//+1 is used to make sure the index starts from 1
	sx=(rand()%a)+1;
	fx=(rand()%a)+1;
	sy=(rand()%b)+1;
	fy=(rand()%b)+1;
	x1=sx,y1=sy;
//pair function pairs 2 ints as single element
	queue<pair<int,int>> q;
//queue is used for bfs
//bfs to track knight's position
	q.push(make_pair(sx,sy));
	visited[sx][sy]=true;
	distance[sx][sy]=0;
//possible moves from start
	while(!q.empty()){						//GREEDY ALGORITHM (All point shortest distance from single source)
		x=q.front().first;
		y=q.front().second;
		q.pop();
		for(i=0;i<8;i++){
			nx=x+dx[i];					//coordinates of possible x,y from present x,y
			ny=y+dy[i];
			if(valid(nx,ny,a,b,0)){
				distance[nx][ny]=distance[x][y]+1;
				visited[nx][ny]=true;
				q.push(make_pair(nx,ny));
			}
		}
	}
	max=distance[fx][fy]+5;
	for(i=0;i<a;i++){
		for(j=0;j<b;j++){
			visited[i][j]=false;
		}
	}
	cout<<"\t\t\t\t\t\t\t\tMAXIMUM MOVES :"<<distance[fx][fy]+5<<endl;
	cout<<"\n\t\t\t\t\t\t\t\tS: START\n\t\t\t\t\t\t\t\tF:FINISH\n\n"<<endl;
//Printing 1st Grid
	 for(i=1;i<=a;i++)
        {
            cout<<"\t\t\t\t\t\t\t\t";
            for(j=1;j<=b;j++)
            {
                if(sx==i && sy==j)
                    cout<<"[S]"<<" ";
                else if (fx==i && fy==j)
                {
                        cout<<"[F]"<<" ";
                }
                 else if(distance[i][j]==1)
                         cout<<"[1]"<<" ";
                 else
                 {
                     cout<<"[x]"<<" ";
                 }
            }
            cout<<endl;
            cout<<"\t\t\t\t\t\t\t\t";
            for(z=1;z<=a;z++)
            cout<<"----";
            cout<<endl;
        }
        cout<<endl;
	for(step=1;step<=max;step++){
//backtracking
		for(i=0;i<a+1;i++){
			for(j=0;j<b+1;j++)
				t[i][j]=-1;}
		pair<int,int>xy;
        	cout<<"\t\t\t\t\tEnter X-Coordinates :";
        	cin>>xy.first;
        	cout<<"\t\t\t\t\tEnter Y-Coordinates :";
        	cin>>xy.second;
//To find the next valid nodes
        	for(i=0;i<8;i++){
            		nx=xy.first+dx[i];
            		ny=xy.second+dy[i];
            		if(valid(nx,ny,a,b,1))
                		t[nx][ny]=step+1;
        	}
        	for(i=1;i<=a;i++){
            		cout<<"\t\t\t\t\t\t\t\t";
            		for(j=1;j<=b;j++){
               		 if(sx==i && sy==j)
                    			cout<<"[S]"<<" ";
               		 else if (fx==i && fy==j)
                        		cout<<"[F]"<<" ";
                		 else if(t[i][j]!=-1)
                    			cout<<"["<<t[i][j]<<"] ";		//next valid positions
                		 else if(i==xy.first && j==xy.second)
                    			cout<<"["<<step<<"] ";
              			 else
                			cout<<"[x]"<<" ";
            		}
			cout<<endl;
			cout<<"\t\t\t\t\t\t\t\t";
			for(z=1;z<=a;z++)
			cout<<"----";
			cout<<endl;
        	}
        	cout<<endl;
//entered x and y are stored in xy(pairs)
		x=xy.first;
		y=xy.second;
//to check if the entered coordinates are valid
		flag=0;
		for(i=0;i<8;i++){
//valid move
           		if(x==x1+dx[i] && y==y1+dy[i]){
                		flag=1;
               		break;}
        		}
        	if(flag==0){
            		step--;
            		cout<<"\t\t\t\t\tInvalid move"<<endl;
            		invalid=1;
            		break;
            		}
            	else{
            		if(x==fx && y==fy){
                		cout<<"\t\t\t\t\tFound in steps : "<<step<<endl;
                		ans=0;
                		break;
            		}
            		x1=x,y1=y;
        	}
	}
	if(ans==0&&invalid==0){
//to check if we completed in min steps
		if(step==distance[fx][fy]){
		    cout<<"\t\t\t\t\tCONGRATULATIONS !!! YOU HAVE WON \n \t\t\t\t\tCompleted game in "<<step<<" steps"<<endl;
		    cout<<"\t\t\t\t\tYour score: 25"<<endl;
		}
		else{
		    cout<<"\t\t\t\t\tHARD LUCK BUT THERE IS A MORE EFFICIENT WAY TO REACH HERE WITH STEPS :"<<distance[fx][fy]<<endl;
//for each extra step 2 points are reduced
		    cout<<"\t\t\t\t\tYour score:"<<(25-(step-distance[fx][fy])*(2))<<endl;
		}
    }
	else if(invalid==0){
		cout<<"\t\t\t\t\tYOU LOSE !!! YOU EXCEEDED THE MAXIMUM MOVES"<<endl;
		cout<<"\t\t\t\t\tYour score: 0"<<endl;
	    }
    return;
}

bool valid(int x,int y,int a,int b,int choice){
//x and y cant be negative or 0 and cant be greater than size of board
    if(x<1 || y<1 || x>a || y>b)
        return false;
    if(visited[x][y] && choice==0)
        return false;
    return true;
}







