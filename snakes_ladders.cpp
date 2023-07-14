#include<iostream>
#include<bits/stdc++.h>
#include<deque>
using namespace std;

class Cell{
    public:
    int end ;
    bool checkJump;
    
    Cell(int e , bool checkJump){
        this->end = e; 
        this->checkJump = checkJump;
    }
};

class Board{
    public:
    vector<vector<Cell>>V;
    Board(int snakes , int ladders , int boardSize)
    {
        Cell c(0,false);
        V.resize(boardSize, vector<Cell>(boardSize, c));
        intitalizeSnakes(snakes , boardSize);
        intitalizeLadders(ladders , boardSize);
    }
    
    void intitalizeSnakes(int snakes ,int boardSize)
    {
        while(snakes>0)
        {
            int startPos = rand()%(boardSize*boardSize);
            int endPos = rand()%(boardSize*boardSize);
            
            if(endPos >= startPos)
            {
                continue;
            }
            int i = startPos/10;
            int j  = startPos%10;
            Cell c = V[i][j];
            if(c.checkJump == true)
            {
                continue;
            }
            c.end = endPos;
            c.checkJump = true;
            V[i][j] = c;
            snakes--;
            // cout<<"snakes are at pos  start = "<<startPos<<" endpos = "<<endPos<<"\n";
        }
    }
    
    void intitalizeLadders(int ladders ,int boardSize)
    {
        while(ladders>0)
        {
            int startPos = rand()%(boardSize*boardSize);
            int endPos = rand()%(boardSize*boardSize);
            
            if(endPos <= startPos)
            {
                continue;
            }
            int i = startPos/10;
            int j  = startPos%10;
            Cell c = V[i][j];
            if(c.checkJump == true)
            {
                continue;
            }
            c.end = endPos;
            c.checkJump = true;
            V[i][j] = c;
            ladders--;
            // cout<<"ladders are at pos  start = "<<startPos<<" endpos = "<<endPos<<"\n";
        }
    }
};

class Dice {
    public:
    int DiceCount;
    Dice(int count)
    {
        DiceCount = count;
    }
    
    int totalSteps()
    {
        int sum=0;
        for(int i=0;i<DiceCount;i++)
        {
            sum += rand()%6+1;
        }
        return sum;
    }
}; 

class Person{
    public:
    string id;
    int pos;
    
    Person(string id  , int pos)
    {
        this->id = id;
        this->pos = pos;
    }
    
    int finalPos(int steps)
    {
        pos+=steps;
        return pos;
    }
};



class Game{
    private:
    Dice D;
    Board B;
    int boardSize;
    public:
    Game(int diceSize , int snakeCount , int ladderCount , int boardSize) : D(diceSize) , B(snakeCount,ladderCount,boardSize)
    {
        this->boardSize = boardSize;
    }
    
    void StartGame()
    {
        Person P1("1" , 0);
        Person P2("2" , 0);
        Person P3("3" , 0);
        // Person P4("4" , 0);
        deque<Person>Q;
        Q.push_back(P1);
        Q.push_back(P2);
        Q.push_back(P3);
        // Q.push_back(P4);
        int flag =0;
        while(flag == 0)
        {
            Person F = Q.front();
            Q.pop_front();
            // cout<<"turn is of "<<F.id<<"  current pos = "<<F.pos<<"   ";
            int steps = D.totalSteps();
            int finalPos = F.pos + steps ;
            if(finalPos >= boardSize*boardSize)
            {
                flag =1;
                cout<<F.id<<" this is the winner \n";
                break;
            }
            int i = finalPos/10;
            int j = finalPos%10;
            Cell c = B.V[i][j];
            if(c.checkJump == true)
            {
                // cout<<" \n yaaaa to sanp ya to ladder \n";
                F.pos = c.end;
            }
            else
            {
                F.pos = finalPos;
            }
            Q.push_back(F);
            // cout<<"final pos = "<<F.pos<<"\n";
        }
    }
};


int main()
{
    int Dice , snakes , ladders , boardSize;
    // cout<<" enter number of Dice = ";
    cin>>Dice ;
    // cout<<"\n enter number of snakes = ";
    cin>>snakes;
    // cout<<"\n number of ladders = ";
    cin>>ladders;
    // cout<<"\n boardSize = ";
    cin>>boardSize;
    Game G(Dice ,snakes , ladders , boardSize );
    for(int i=0;i<20;i++)
    {
        G.StartGame();
    }
}
