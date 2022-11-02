#include <bits/stdc++.h>
#include <iostream>
#include <cmath>
#include<math.h>
#include <fstream>
using namespace std;
#define OBSTACLE -99

float ** grid;
float ** temp_grid;

int ** gridStatus;

int n=0,m=0,k=0;
int timer_count=0;

int count_available_Edge_grid(int row,int col)
{
    int available_grid_count = 0;

    if(row+1 < n)
    {

        if(gridStatus[row+1][col] != OBSTACLE)
        {
            available_grid_count++;

        }
    }

    if(row-1 >= 0)
    {
        if(gridStatus[row-1][col] != OBSTACLE)
        {
            available_grid_count++;

        }
    }

    if(col+1 < m)
    {
        if(gridStatus[row][col+1] != OBSTACLE)
        {
            available_grid_count++;


        }
    }
    if(col-1 >= 0)
    {
        if(gridStatus[row][col-1] != OBSTACLE)
        {
            available_grid_count++;

        }
    }

    return available_grid_count;

}
int count_available_corner_grid(int row,int col)
{
    int available_grid_count = 0;

    if((row+1 < n ) && (col+1 < m))
    {
        if((gridStatus[row+1][col+1] != OBSTACLE))
        {
            available_grid_count++;
        }
    }
    if((row-1 >=0) && (col-1 >=0))
    {
        if((gridStatus[row-1][col-1] != OBSTACLE))
        {
            available_grid_count++;
        }
    }
    if((row+1 < n) && (col-1 >=0))
    {
        if((gridStatus[row+1][col-1] != OBSTACLE))
        {
            available_grid_count++;
        }

    }
    if((row-1 >=0) &&(col+1 < m))
    {

        if((gridStatus[row-1][col+1] != OBSTACLE))
        {
            available_grid_count++;
        }
    }

    available_grid_count +=1;
    return available_grid_count;

}
float Prob_Sum_From_Shared_Edge(int row, int col)
{

    float sum_prob = 0;
    float p1=0,p2=0,p3=0,p4=0;
    int c1,c2,c3,c4;

    if((row+1) < n)
    {
        c1 = count_available_Edge_grid(row+1,col);
        p1=(grid[row+1][col])*(0.9/c1);

    }

    if((row-1) >= 0)
    {
        c2 = count_available_Edge_grid(row-1,col);
        p2=(grid[row-1][col])*(0.9/c2);

    }


    if((col + 1) < m)
    {

        c3 = count_available_Edge_grid(row,col+1);

        p3=(grid[row][col+1])*(0.9/c3);

    }

    if((col - 1) >= 0)
    {
        c4 = count_available_Edge_grid(row,col-1);
        p4=(grid[row][col-1])*(0.9/c4);

    }

    sum_prob = p1+p2+p3+p4;

    return sum_prob;

}

float corner_and_self_grid_prob_sum(int row,int col)
{
    float sum_prob = 0;
    float p1=0,p2=0,p3=0,p4=0,p5=0;

    if((row+1 < n)&& (col+1 < m))
    {
        int c1 = count_available_corner_grid(row+1,col+1);
        p1=grid[row+1][col+1]*(0.1/c1);
    }

    if((row-1 >= 0)&& (col-1>=0))
    {
        int c2 = count_available_corner_grid(row-1,col-1);
        p2=grid[row-1][col-1]*(0.1/c2);
    }
    if((row+1 < n)&& (col-1>=0))
    {
        int c3 = count_available_corner_grid(row+1,col-1);
        p3=grid[row+1][col-1]*(0.1/c3);
    }

    if((row-1 >= 0)&& (col+1 < m))
    {
        int c4 = count_available_corner_grid(row-1,col+1);
        p4=grid[row-1][col+1]*(0.1/c4);
    }


    int c5 = count_available_corner_grid(row,col);
    p5=grid[row][col]*(0.1/c5);


    sum_prob = p1+p2+p3+p4+p5;

    return sum_prob;
}

void ObserveGrid(int row,int col,int sensor_value)

{
    timer_count++;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            //cout<<"("<<i<<","<<j<<") : "<<endl;

            if(gridStatus[i][j]!=OBSTACLE)
            {

                float total_prob = Prob_Sum_From_Shared_Edge(i,j)+corner_and_self_grid_prob_sum(i,j);
                // cout<<"total_prob:"<<total_prob<<endl;

                if(sensor_value==1)
                {


                    if((i==row && j ==col) || (i==row+1 && j ==col) || (i==row-1 && j ==col) || (i==row && j ==col+1) || (i==row && j == col-1) || (i==row+1 && j == col+1) || (i==row-1 && j == col-1) || (i==row+1 && j == col-1) || (i==row-1 && j == col+1))
                    {
                        temp_grid[i][j]=(0.85)*total_prob;
                    }
                    else
                    {
                        temp_grid[i][j]=(0.15)*total_prob;
                    }
                }
                else
                {
                    if((i==row && j ==col) || (i==row+1 && j ==col) || (i==row-1 && j ==col) || (i==row && j ==col+1) || (i==row && j == col-1) || (i==row+1 && j == col+1) || (i==row-1 && j == col-1) || (i==row+1 && j == col-1) || (i==row-1 && j == col+1))
                    {

                        temp_grid[i][j]=(0.15)*total_prob;
                    }
                    else
                    {
                        temp_grid[i][j]=(0.85)*total_prob;
                    }
                }

            }
        }
    }


    for(int i=0; i<n; i++)
    {

        for(int j=0; j<m; j++)
        {

            grid[i][j]=temp_grid[i][j];

        }

    }


}



void PrintGrid()
{
    float total_sum=0;
    for(int i=0; i<n; i++)
    {

        for(int j=0; j<m; j++)
        {

            total_sum+=grid[i][j];
        }
    }

    cout<<endl;

    float prob_sum =0;
    cout<<"Time : "<<timer_count<<endl;
    cout<<"###########################################################################################################################################"<<endl;
    for(int i=0; i<n; i++)
    {

        for(int j=0; j<m; j++)
        {
            float current_value = (grid[i][j]/total_sum)*100;
            prob_sum+=current_value;
            cout << fixed << setprecision(4) << current_value <<"        ";


        }

        cout<<endl;

    }
cout<<"#############################################################################################################################################"<<endl;
    for(int i=0; i<n; i++)
    cout<<endl;

    cout<<"Total probability sum : "<<prob_sum<<endl;
    cout<<endl;
    cout<<endl;
}

void gridSet(int n,int m,int k)
{

    grid = new float*[n];
    temp_grid = new float*[n];

    for (int i = 0; i < n; i++)
    {

        grid[i] = new float[m];
    }
    for (int i = 0; i < n; i++)
    {

        temp_grid[i] = new float[m];
    }

    gridStatus = new int*[n];

    for (int i = 0; i < n; i++)
    {

        gridStatus[i] = new int[m];
    }



    for(int i=0; i<n; i++)
    {

        for(int j=0; j<m; j++)
        {

            gridStatus[i][j]=1;
        }

    }

}

void Initialize_grid_value()
{

    float available_grid_number = n*m-k ;

    float initial_p =(1/available_grid_number);

    //float initial_p_after_normalize = initial_p*100;


    for(int i=0; i<n; i++)
    {

        for(int j=0; j<m; j++)
        {

            if(gridStatus[i][j]!=OBSTACLE)
            {
                grid[i][j]=initial_p;
            }
            else
            {
                grid[i][j]=0.0;
            }

        }

    }

    for(int i=0; i<n; i++)
    {

        for(int j=0; j<m; j++)
        {

            temp_grid[i][j]=grid[i][j];

        }

    }

}

void MostProbableCell()
{
    float max_value = grid[0][0];
    int x=0,y=0;
    for(int i=0;i<n;i++)
    {

        for(int j=0;j<m;j++)
        {
            if(max_value < grid[i][j])
            {
                max_value=grid[i][j];
                x=i;
                y=j;
            }
        }
    }

    cout<<"Most Probable Cells: {"<<x<<","<<y<<"}"<<endl;


}
int main()
{

    fstream newfile;
    newfile.open("output.txt",ios::out);
    if(newfile.is_open())
    {
        newfile<<"Tutorials point \n";
        newfile.close();
    }
    newfile.open("input.txt",ios::in);
    int idx =0;
    if (newfile.is_open())
    {
        string tp;
        while(getline(newfile, tp))
        {

            if(idx ==0)
            {
                vector<string> tokens;
                stringstream check1(tp);
                string intermediate;
                while(getline(check1,intermediate,' '))
                {
                    tokens.push_back(intermediate);

                }
                stringstream str1(tokens[0]);
                stringstream str2(tokens[1]);
                stringstream str3(tokens[2]);
                str1 >> n;
                str2 >> m;
                str3 >> k;

                gridSet(n,m,k);
                idx++;


            }
            else
            {

                if(idx > k)
                {


                    if(tp[0]=='R')
                    {
                        vector<string> tokens;
                        stringstream check1(tp);
                        string intermediate;
                        while(getline(check1,intermediate,' '))
                        {
                            tokens.push_back(intermediate);

                        }
                        stringstream str2(tokens[1]);
                        stringstream str3(tokens[2]);
                        stringstream str4(tokens[3]);

                        int u =0,v=0,b=0;
                        str2 >> u;
                        str3 >> v;
                        str4 >> b;

                        ObserveGrid(u,v,b);
                        PrintGrid();


                    }
                    else if(tp[0] == 'C')
                    {
                        MostProbableCell();

                    }
                    else if(tp[0] == 'Q')
                    {
                      return 0;
                    }
                }
                else
                {
                    vector<string> tokens;
                    stringstream check1(tp);
                    string intermediate;
                    while(getline(check1,intermediate,' '))
                    {
                        tokens.push_back(intermediate);

                    }
                    stringstream str1(tokens[0]);
                    stringstream str2(tokens[1]);

                    int x=0,y=0;
                    str1 >> x;
                    str2 >> y;
                    gridStatus[x][y]=OBSTACLE;


                    if(idx == k)
                    {
                        Initialize_grid_value();
                        PrintGrid();
                    }

                    idx++;
                }

            }
        }
    }



    return 0;
}
