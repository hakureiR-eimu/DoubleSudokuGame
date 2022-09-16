void PrintClauseNode(ClauseNode *c)
{
    int i;
    ClauseNode *c_tmp;
    LiteralNode *p_tmp;
    c_tmp=c;
    printf("\n");
    if(c->num!=0)
    {    
        for(i=0;i<c->num&&c_tmp->down!=NULL;i++){
            c_tmp = c_tmp->down;
            printf("%d ",c_tmp->num);
            if(c_tmp->right!=NULL) p_tmp = c_tmp->right;
            while(p_tmp&&p_tmp->data!=0){ 
                printf("%d ",p_tmp->data);
                p_tmp = p_tmp->right;
            }
            printf("\n");
        }
    }

    //printf("num:%d,fdata:%d\n",c->down->num,c->down->right->data);
    printf("\n%d\n",c->num);
}
ClauseNode* CreateClause(ClauseNode *c_tmp){
    ClauseNode *c_tmp1;
    c_tmp1=(ClauseNode *)malloc(sizeof(ClauseNode));
    c_tmp1->down=NULL;
    c_tmp1->right=NULL;
    c_tmp1->num=0;
    c_tmp->down=c_tmp1;
    return c_tmp1;
}
LiteralNode* CreateLieral(ClauseNode *c_tmp)
{
    LiteralNode *s;
    s=(LiteralNode *)malloc(sizeof(LiteralNode)); 
    s->right=NULL;
    s->data=0;
    c_tmp->right=s;
    return s;
}
LiteralNode* CreateLieralNode(LiteralNode *s_tmp){
    LiteralNode *s;
    s=(LiteralNode *)malloc(sizeof(LiteralNode)); 
    s->data=0;
    s->right=NULL;
    s_tmp->right=s;
    return s;
}

void outputSodu(int *result,int Soduko[2][10][10])
{
    char FileName1[1024];
    printf("reprintf address:\n");
    scanf("%s",FileName1);
    FILE *fp=fopen(FileName1,"w");
    fprintf(fp,"Sodu is below\n");
    int t=0,i=0,j=1,k=1;
    int a[4]={0};
    int temp;
    //system("pause");
    for(t=1;t<=bianyuan;t++)
    {
        //printf("%d\n",bianyuan);
        if(result[t]==1)
        {
            temp=t;
            i=0;j=1;k=1;
            while(temp>729)
            {
                i++;
                temp-=729;
            }
            while(temp>81)
            {
                j++;
                temp-=81;
            }
            while(temp>9)
            {
                k++;
                temp-=9;
            }
            //system("pause");
            Soduko[i][j][k]=temp;
        }
    }

    for(i=0;i<2;i++)
    {
        for(j=1;j<=9;j++)
        {
            for(k=1;k<=9;k++)
            {
                fprintf(fp,"%d ",Soduko[i][j][k]);
                if((k%3)==0) fprintf(fp,"|");
            }
            fprintf(fp,"\n");
            if((j%3)==0) fprintf(fp,"---------------------\n");
        }
        fprintf(fp,"---------------------\n");
    }
    fclose(fp);
    printf("ok\n");
    system("pause");
}
void output(int *result,double timems)
{
    char FileName1[1024];
    printf("reprintf address:\n");
    scanf("%s",FileName1);
    FILE *fp=fopen(FileName1,"w");
    int i;
    fprintf(fp,"truthtable is below:\n");
    for(i=1;i<=bianyuan;i++)
    {
        fprintf(fp,"%d:%d   ",i,result[i]);
        if((i%5)==0) fprintf(fp,"\n");
    }
    fprintf(fp,"The time if:%.2f ms",10*timems);
    printf("OK\n");
    fclose(fp);
}
ClauseNode* input()
{
    printf("Please input the cnf address:");
    scanf("%s",FileName);
    FILE *fp=fopen(FileName,"r");
    if(fp==NULL) 
    {
        printf("wrong FileName\n");
        system("pause");
        return NULL;
    }
    char ch[100];
    do{
        fgets(ch,100,fp);
    }while(ch[0]!='p');
    char chhh1[5],chhh2[5];
    sscanf(ch,"%s%s%d%d",chhh1,chhh2,&bianyuan,&hangshu);
    int i,j,k,num;
    //int data[hangshu+5][bianyuan+5];

    ClauseNode *c, *c_tmp,*p;                              //创造链表
    LiteralNode *e, *e_tmp;
    c= (ClauseNode *)malloc(sizeof(ClauseNode));
    c->right=NULL;
    c->down=NULL;
    c->num=0;
    c_tmp=c;
    for(i=1;i<=hangshu;i++){
        j=1; num=0;
        //c_tmp->down=(ClauseNode *)malloc(sizeof(ClauseNode));'
        c_tmp=CreateClause(c_tmp);
        //c_tmp->right=(LiteralNode *)malloc(sizeof(LiteralNode)); 
        //e=c_tmp->right;
        e=CreateLieral(c_tmp);
        do{
            
            fscanf(fp,"%d",&k);
            e->data=k;
            //e->right=(LiteralNode *)malloc(sizeof(LiteralNode)); 
            //e=e->right;
            if(k!=0) e=CreateLieralNode(e);
            if(k==0) e->right=NULL;
            //data[i][j++]=k;
            j++;
        }while(k!=0);
        e=NULL;
        c_tmp->num=j-2;
        //data[i][0]=j-2;
    }
    c_tmp->down = NULL;
    c->num=hangshu;
    fclose(fp);
    //printf("%d",c->down->down->right->right->data);
    //printf("%d",data[1][1]);
    return c;
}
void output1(int *TruthTable)
{
    int i;
    for(i=1;i<=bianyuan;i++){
        printf("%d ",i);
        if(i%10==0)  printf("\n");
    }
}
void debug_print(ClauseNode *s)
{
    ClauseNode *s_tmp=s;
    LiteralNode *p;
    while(s_tmp!=NULL)
    {
        printf("%d ",s_tmp->num);
        if(s_tmp->right != NULL) {
            p=s_tmp->right;
            while(p!=NULL){
                printf("%d ",p->data);
                p=p->right;
            }
        }
        s_tmp=s_tmp->down;
        printf("\n");
    }
}