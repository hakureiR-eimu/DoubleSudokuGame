int bianyuan,hangshu;
char FileName[256];
int accord[2][10][10]={0};
int question[2][10][10]={0};
int answer[2][10][10]={0};
#include "def.h"
#include "Soduko.h"
#include "ioput.h"
#include "DPLL_solver.h"
int main()
{
    clock_t start,stop;
    int op=1,op_1=1,op_2=1,i,e,k,j;
    int outcome=0;
    ClauseNode *c=NULL;
    while(op)
    {
        system("cls");
        printf("\n\n");
        printf("         Program about SAT problem\n");
        printf("-------------------------------------------------\n");
        printf("     1. SAT example       2. Sudoku game\n");
        printf("     0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    Operation[0-2]: ");
        scanf("%d", &op);

        //SAT 
        if(op == 1)
        {
            while(op_1){
            printf("\n\n");
            printf("-------------------------------------------------\n");
            printf("       1.print data          2.print SAT result\n");
            printf("       0. Exit\n");
            printf("-------------------------------------------------\n");
            printf("       Operation: ");
            scanf("%d",&op_1);
            if(op_1 == 1) 

        
            {
                /*int truth_table[bianyuan+1];
                for(i=1;i<=bianyuan;i++)   truth_table[i]=0;*/
                c=input();    
                //PrintClauseNode(c);
                /*ClauseNode *s1;
                s1=Duplcation(c);
                s1=AddClause(s1,4);
                e=IsUnitClause(s1);
                int DCN=0;
                do{DCN=DeleteClauseNode(s1,4);
                truth_table[4]=1;
                } while(DCN!=0);*/
                if(c!=NULL) PrintClauseNode(c);    //
                //if(CountResult(4,truth_table) == 0) printf("ERROR\n");
                
                //printf("%d \n",s1->down->right->data);
                //if(c->down->right->right->right->right->right==NULL) printf("right");
                //if(c->right==NULL) printf("right");

            }
            if(op_1 == 2)
            {
                //int truth_table[bianyuan+1];
                c=input();
                //debug_print(c);
                int truth_table[bianyuan+1];
                for(i=1;i<=bianyuan;i++)   truth_table[i]=0; //初始化 置0
                start = clock();
                outcome=DPLL(c,truth_table);
                //printf("%d\n",outcome);
                if(outcome == 1) {
                    printf("SAT question is solvable\n");
                    for(j=1;j<=bianyuan;j++) {
                        printf("%d:%d    ",j,truth_table[j]);
                        if((j%5)==0) printf("\n");
                    }
                }
                else if(outcome == -1) printf("SAT question is unsolveable\n");
                //printf("%d\n",outcome);
                stop = clock();
                double duration=(stop-start)/CLK_TCK;
                printf("\nThe time is:%.2f ms\n",1000*duration);
                output(truth_table,duration);
                //output(truth_table,duration);
                //output1(truth_table);
            }
            }
            
        }
        if(op==2)
        {

            accord[0][1][1]=8;
            accord[0][1][8]=4;
            accord[0][2][1]=1;
            accord[0][2][3]=5;
            accord[0][2][4]=7;
            accord[0][2][5]=6;
            accord[0][2][7]=9;
            accord[0][2][8]=2;
            accord[0][3][5]=3;
            accord[0][4][2]=4;
            accord[0][4][5]=5;
            accord[0][4][7]=3;
            accord[0][5][3]=6;
            accord[0][6][1]=9;
            accord[0][6][8]=8;
            accord[0][7][4]=2;
            accord[0][7][5]=4;
            accord[0][8][3]=1;
            accord[0][8][4]=6;
            accord[0][8][5]=9;
            accord[0][8][6]=3;
            accord[0][9][1]=2;
            accord[0][9][6]=1;
            accord[0][9][9]=5;
            accord[1][1][4]=4;
            accord[1][2][7]=1;
            accord[1][3][3]=5;
            accord[1][3][9]=7;
            accord[1][4][2]=4;
            accord[1][4][5]=2;
            accord[1][4][6]=3;
            accord[1][5][3]=2;
            accord[1][5][6]=1;
            accord[1][5][8]=8;
            accord[1][6][4]=7;
            accord[1][6][5]=6;
            accord[1][6][8]=3;
            accord[1][7][3]=1;
            accord[1][7][5]=5;
            accord[1][8][2]=9;
            accord[1][8][5]=1;
            accord[1][8][7]=5;
            accord[1][8][8]=4;
            accord[1][8][9]=2;
            accord[1][9][4]=9;
            accord[1][9][5]=3;

            SodukoPrint(accord);
            for(i=0;i<2;i++){
                for(j=1;j<=9;j++){
                    for(k=1;k<=9;k++) 
                        question[i][j][k]=accord[i][j][k];
                }
            }
            while(1){
            printf("please input your action:\n");
            int a1,a2,a3,a4;
            scanf("%d%d%d%d",&a1,&a2,&a3,&a4);
            if(a4==0) break;
            if(question[a1][a2][a3]!=0){ printf(" wrong\n");  continue; }
            question[a1][a2][a3]=a4;
            if(a1==0&&a2>=7&&a2<=9&&a3>=7&&a3<=9) question[1][a2-6][a3-6]=a4;
            if(a1==1&&a2>=1&&a2<=3&&a3>=1&&a3<=3) question[0][a2+6][a3+6]=a4;
            SodukoPrint(question);
            }       
                SodukoInput(accord);
                c=input();
                //debug_print(c);
                int truth_table[bianyuan+1];
                for(i=1;i<=bianyuan;i++)   truth_table[i]=0; //初始化 置0
                start = clock();
                outcome=DPLL(c,truth_table);
                //printf("%d\n",outcome);
                if(outcome == 1) {
                    printf("SAT question is solvable\n");
                    for(j=1;j<=bianyuan;j++) {
                        printf("%d:%d    ",j,truth_table[j]);
                        if((j%9)==0) printf("\n");
                    }
                }
                else if(outcome == -1) printf("SAT question is unsolveable\n");
                //printf("%d\n",outcome);
                stop = clock();
                double duration=(stop-start)/CLK_TCK;
                printf("\nThe time is:%.2f ms\n",1000*duration);
                system("pause");
                outputSodu(truth_table,answer);
            
        }

    }
    system("pause");
    return 0;
}