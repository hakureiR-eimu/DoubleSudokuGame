#define CORRECT 0
#define WRONG -1
static int T = 0;

void SodukoPrint(const int Soduko[2][10][10])
{
    int i,j,k,t,m,n;
    for(i=0;i<2;i++)
    {
        for(j=1;j<=9;j++)
        {
            for(k=1;k<=9;k++)
            {
                printf("%d ",Soduko[i][j][k]);
                if((k%3)==0) printf("|");
            }
            printf("\n");
            if((j%3)==0) printf("---------------------\n");
        }
        printf("---------------------\n");
    }
    system("pause");
}

void SodukoInput(const int accord[2][10][10])
{
    FILE *fp=fopen("Sodukoko.cnf","w");
    fprintf(fp,"p SAT 1458 24178\n");
    int i,j,k,t,s,m,n,a,x,y;
    for(i=1;i<=2;i++)
    {
        for(j=1;j<=9;j++)
        {
            for(k = 1;k <=9;k++)
            {
                if(accord[i-1][j][k]!=0){
                    fprintf(fp,"%d 0\n",(i-1)*729+(j-1)*81+(k-1)*9+accord[i-1][j][k]); //已有格子
                }
            }
        }
    }
    for(i=1;i<=2;i++)
    {
        for(j=1;j<=9;j++)
        {
            for(k = 1;k <=9;k++)
            {
                for(t=1;t<=9;t++) fprintf(fp,"%d ",(i-1)*729+(j-1)*81+(k-1)*9+t);   //单个格子
                fprintf(fp,"0\n");
                for(t=1;t<=8;t++){
                    for(s=t+1;s<=9;s++){
                        fprintf(fp,"-%d -%d ",(i-1)*729+(j-1)*81+(k-1)*9+t,(i-1)*729+(j-1)*81+(k-1)*9+s); //单个格子
                        fprintf(fp,"0\n");
                    }
                }
            }
        }
    }
    for(i=1;i<=2;i++)
    {
        for(j=1;j<=9;j++)
        {
            for(t = 1;t <= 9 ;t++){
                for(k = 1;k <=9; k++){
                    fprintf(fp,"%d ",(i-1)*729+(j-1)*81+(k-1)*9+t);  //行规则 j行含有t
                }
                fprintf(fp,"0\n");
                for(k = 1;k <=8 ;k++){
                    for(s = k+1;s <= 9;s++){
                        fprintf(fp,"-%d -%d 0\n",(i-1)*729+(j-1)*81+(k-1)*9+t,(i-1)*729+(j-1)*81+(s-1)*9+t);
                    }
                }
            }
        }
    }

    for(i=1;i<=2;i++)       //列规则
    {
        for(k = 1;k <= 9;k++)
        {
            for(t=1;t<=9;t++)
            {
                for(j=1;j<=9;j++){
                    fprintf(fp,"%d ",(i-1)*729+(j-1)*81+(k-1)*9+t);
                }
                fprintf(fp,"0\n");
                for(j = 1;j <= 8;j++){
                    for(s = j+1;s <=9;s ++)
                    {
                        fprintf(fp,"-%d -%d 0\n",(i-1)*729+(j-1)*81+(k-1)*9+t,(i-1)*729+(s-1)*81+(k-1)*9+t);   //不同时为t
                    }
                }
            }
        }
    }
    for(i = 1;i <= 2;i++)      //9宫格
    {
        for(j=1;j <= 9;j+=3){
            for(k = 1;k <=9 ;k+=3){
                for(t = 1;t<=9;t++){
                    for(m=0;m<3;m++){
                        for(n=0;n<3;n++){
                            fprintf(fp,"%d ",(i-1)*729+(j-1+m)*81+(k-1+n)*9+t);
                        }
                    }
                    fprintf(fp,"0\n");
                    for(m=0;m<3;m++){
                        for(n=0;n<3;n++){
                            for(x=0;x<3;x++){
                                for(y=0;y<3;y++){
                                    if(m!=x||n!=y) {
                                        if((i-1)*729+(j-1+m)*81+(k-1+n)*9+t<(i-1)*729+(j-1+x)*81+(k-1+y)*9+t)
                                        fprintf(fp,"-%d -%d 0\n",(i-1)*729+(j-1+m)*81+(k-1+n)*9+t,(i-1)*729+(j-1+x)*81+(k-1+y)*9+t);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    for(j=7;j<=9;j++){
        for(k=7;k<=9;k++){
            m=j-6;
            n=k-6;
            for(t=1;t<=9;t++){
                fprintf(fp,"-%d %d 0\n",(j-1)*81+(k-1)*9+t,729+(m-1)*81+(n-1)*9+t);
                fprintf(fp,"%d -%d 0\n",(j-1)*81+(k-1)*9+t,729+(m-1)*81+(n-1)*9+t);
            }
        }
    }
    fclose(fp);
}


