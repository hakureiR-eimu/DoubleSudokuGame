status DPLLSolver(ClauseNode *s);
ClauseNode* AddClause(ClauseNode* s, int var);        // 增加单子句
status IsUnitClause(ClauseNode* s);              // 判断是否存在单子句
status Print(ClauseNode* s);                          // 打印表
status IsEmptyClause(ClauseNode* s);                  // 判断是否存在空子句
int DeleteClauseNode(ClauseNode *s,int tmp);
int SearchClause(ClauseNode *s,int *result);
int GetVar1(ClauseNode *s,int *result);
int GetVar2(ClauseNode *s,int *result);
//我需要什么功能?   
//删除永真链表
//删除链表永假值
//删除单子句链表并返回真值
//分裂规则
status IsEmptyClause(ClauseNode* s)
{
    int i;
    ClauseNode* s_tmp;
    if(s->down == NULL) return 0;
    else if(s->num !=0)
    {
        for(i=0;i<s->num&&s_tmp->down!=NULL;i++)
        {
            s_tmp=s_tmp->down;
            if(s_tmp->num==0) return 1;
        }
    }
    return 0;
    
}
ClauseNode* AddClause(ClauseNode *s, int var)   //添加单子句
{
    if(var == 0) return s;
    ClauseNode *s_tmp,*p;
    LiteralNode *v;
    p=(ClauseNode *)malloc(sizeof(ClauseNode));
    p->num=1;
    v=(LiteralNode *)malloc(sizeof(LiteralNode));
    v->data=var;
    v->right=NULL;
    p->right=v;
    s_tmp=s;
    p->down=s->down;
    s->down=p;
    s->num++;
    return s;
}
int IsUnitClause(ClauseNode* s)   //判断并且删除单子句   
{
    ClauseNode *p=s,*s_tmp=s->down;
    int temp;
    if(s_tmp->num==1)
    {
        //free(s_tmp->right->right);
        p->down=s_tmp->down;
        temp=s_tmp->right->data;
        //free(s_tmp->right);
        //free(s_tmp);
        s->num--;
        return temp;
    }
    else 
    {while(s_tmp!=NULL)
    {
        p=p->down;
        s_tmp=p->down;

        if(s_tmp == NULL) return 0;
        if(s_tmp->num==1)
        {
            temp=s_tmp->right->data;
            p->down=s_tmp->down;
            //free(s_tmp->right->right); 
            //free(s_tmp->right);
            //free(s_tmp);
            s->num--;
            return temp;
        }
    }
    return 0;}
}


int DeleteClauseNode(ClauseNode *s,int tmp){    //相同删除整句,相反删除节点
    int i,j,k;
    ClauseNode* s_tmp=s,* s_tmp1;
    LiteralNode* r_tmp;
    int number=s->num;
    /*
    if(s->down!=NULL&&s->down->right!=NULL&&s->down->right->data==tmp)
    {
        s->down=s->down->down;
        return 1;
    }
    */
    for(i=0;i<number&&s_tmp->down!=NULL;i++){
        if(s_tmp->down!=NULL&&s_tmp->down->right!=NULL) 
            {s_tmp1=s_tmp->down;
            //先排查相同整句
            r_tmp=s_tmp1->right;
            if(r_tmp->data == tmp){
                s_tmp->down=s_tmp1->down;
                s->num--;
                return 1;
            }
            if(r_tmp->data == -tmp){
                if(s_tmp1->num==1||r_tmp->right->data==0){
                    return -1;
                }
                s_tmp1->right=r_tmp->right;
                s_tmp1->num--;
                return 1;
            }
            else{
                while(r_tmp->right!=NULL&&r_tmp->right->data!=0){
                    if(r_tmp->right->data == tmp){
                        s_tmp->down=s_tmp1->down;
                        s->num--;
                        return 1;
                    }
                    if(r_tmp->right->data == -tmp){
                        r_tmp->right=r_tmp->right->right;
                        s_tmp1->num--;
                        return 1;
                    }
                    r_tmp=r_tmp->right;
                }
            }
            //排查相反整句
            s_tmp=s_tmp->down;  //向下
            }
        else return 0;
    }
    return 0;
}

int CountResult(int single,int *result)
{
    if(single == 0) return 0;
    else if(single>=0)  
    {
        if(result[single]>=0) {
            result[single]=1;
            return 1;
        }
        else if(result[single]==-1) return -1;
    }
    else if(single<0)
    {
        if(result[-single]<=0){
            result[-single] = -1;
            return 1;
        }
        else if(result[-single] == 1) return -1;
    }
    return 0;
}
int GetVar1(ClauseNode *s,int *result)
{
    return s->down->right->data;
}
int GetVar2(ClauseNode *s,int *result)
{
    int var=SearchClause(s,result);
    return var;
}
int SearchClause(ClauseNode *s,int *result)
{
    int num1=0;
    
    int CountTable[bianyuan+1]={0};
    int i,j,k;
    for(i=1;i<=bianyuan;i++)
    {
        if(result[i]==0) num1++;
        if(num1<=50)  return GetVar1(s,result); 
    }
    ClauseNode* s_tmp=s;
    LiteralNode* r_tmp;
    int number = s->num;
    for(i = 0;i <number&&s_tmp->down!=NULL;i++){
        s_tmp = s_tmp->down;
        r_tmp=s_tmp->right;
        while(r_tmp!=NULL&&r_tmp->data!=0)
        {
            if(r_tmp->data>0) CountTable[r_tmp->data]++;
            else if(r_tmp->data<0) CountTable[-r_tmp->data]++;
            r_tmp=r_tmp->right;
        }
    }
    int maxnumer,Maxn=0;
    for(i=1;i<=bianyuan;i++)
    {
        if(CountTable[i]>=Maxn)
        {
            Maxn=CountTable[i];
            maxnumer=i;
        }
    }
    return maxnumer;
}
ClauseNode* Duplcation(ClauseNode *s)
{
    int i,j,k=0;
    ClauseNode *s1,*s_tmp,*s_cop;
    LiteralNode *e,*e_tmp;
    s_tmp=s;  
    s1=(ClauseNode *)malloc(sizeof(ClauseNode));
    s1->right=NULL;
    s1->down=NULL;
    s1->num = s->num;
    s_cop=s1;
    for(i=1;i<=s1->num;i++){
        s_tmp=s_tmp->down;
        s_cop=CreateClause(s_cop);
        s_cop->num=s_tmp->num;
        e=CreateLieral(s_cop);
        e_tmp=s_tmp->right;
        do{
            k=e_tmp->data;
            e->data=k;
            if(k!=0) e=CreateLieralNode(e);
            if(k==0) e->right=NULL;
            if(e_tmp->right!=NULL) e_tmp=e_tmp->right;
        }while(k!=0);
        e=NULL;
    }
    //printf("%d\n\n",s_tmp->right->data);
    s_cop->down = NULL;
    return s1;
}
int IsTrueClause(ClauseNode *s)
{
    if(s->num==0) return 1;
    else if(s->down==NULL||s->down->num==0) return 1;
    return 0;
}
status DPLL(ClauseNode *s,int *result)
{
    ClauseNode *test=s;

    //system("pause");
    while(test->down!=NULL) {
        test=test->down;
    }
    //printf("%d\n",test->right->data);
    //printf("       -----------------      \n");       //debug
    //printf("       -----------------      \n");
    //PrintClauseNode(s);
    ClauseNode *p=s;
    ClauseNode *s_tmp;
    int single=0;
    int res=0;
    int DCN=0;
    while((single=IsUnitClause(s))!=0)
    {
        //if(single == -28) PrintClauseNode(s);
        //res = CountResult(single,result);
        //if(res == -1) return -1;        
        single>0?result[single]=1:result[-single]=-1;
        DCN=0;
        //printf("why\n");
        do{
            /*
            if(single == -28)
            {
                system("pause");
                PrintClauseNode(s);
                return -1;
            }*/
            //system("pause");
            //printf("%d\n",DCN);
            DCN=DeleteClauseNode(s,single);
            if(DCN == -1) return -1;
            //printf("%d\n",DCN);
        }while(DCN!=0);
        if(s->down == NULL) return 1;
        //if(single == -28) return -1;
        //if(IsTrueClause(s)) return 1;
        else if(IsEmptyClause(s)) return -1;
        //else if(IsSingleClause(s,result)) return FALSE;
    }
    //printf("down\n");
    int Var = GetVar1(s,result);
    ClauseNode* temp = Duplcation(s);
    ClauseNode* s1 = AddClause(s,Var);
    //if((s->num==0)&&(s->down==NULL||s->down->num==0)) return TRUE;
    if(DPLL(s1,result)==1) return 1;
    else {
        //printf("right here\n");
        //system("pause");
        //printf("       -----------------      \n");       //debug
        //printf("       -----------------      \n");
        //PrintClauseNode(s);
        ClauseNode* s2 = AddClause(temp,-Var);
        return DPLL(s2,result);
    }
    return -1;
}
