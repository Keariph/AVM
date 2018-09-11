#include <stdio.h>
#include <stdlib.h>

void LCS(char *S1,char *S2,int n,int m,int **L);  //Функция для вычисления наибольшей последовательности

	#define MAX(a,b) (((a)>(b))?(a):(b)) //Макрос для нахождение наибольшего числа

	typedef struct LCS_Subsequence //Очередь для хранения наибольшей последовательности
	{
	    char symbol; //символ
	    int size;
	    LCS_Subsequence*head;
	    LCS_Subsequence*next;

	    void (*add)(LCS_Subsequence addArg,LCS_Subsequence *obj); //Функция для добавления символа в очередь
	    void (*print)(LCS_Subsequence *obj);  //Печать очереди
	} Subsequence;

	
 Subsequence *subOne = NULL;//Голова очереди


void add(LCS_Subsequence addArg,LCS_Subsequence *obj)
	{
	    LCS_Subsequence*temp;
	    addArg.next = obj;
	    obj = &addArg;
	    addArg.size = addArg.size + 1;
	}
void print(LCS_Subsequence addArg,LCS_Subsequence *obj)
	{
	    LCS_Subsequence*temp = obj;
	    printf("\n");
	    while(temp->next != NULL)
	    {
		printf("%c",temp->symbol);
		temp->head = temp->next;
	    }
	}
void LCS(char *S1,char *S2,int n,int m,int **L)    //A = {12345} B = {12785}   LCS = {125} - это и вычисляет функция
{
    Subsequence *newArg = (Subsequence*)malloc(sizeof(Subsequence));
    for(int i = n;i>=0;i--)
        for(int j = m;j>=0;j--)
        {
            if(S1[i]=='/0' || S2[j] == '/0')
                L[i][j] = 0;
            //if(i == 0|| j == 0)
                //L[i][j] = 0;    
            else    
            if(S1[i] == S2[j])
                L[i][j] = 1 + L[i+1][j+1];
            else
                L[i][j] = MAX(L[i+1][j],L[i][j+1]);
        }
    for(int i = 0,j = 0;L[i][j]!=0 && i < n && j < m;)
    {

        if(S1[i] == S2[j])
        {
	//Тут нужно допилить иначе вылет	
            //newArg->symbol = S1[i];
            //newArg->add(*newArg,subOne);
            i+=1;
            j+=1;
            //newArg = (Subsequence*)malloc(sizeof(LCS_Subsequence));
        }
        else
        {
            if(L[i][j] == L[i+1][j])
            {
                i+=1;
            }
            else
            {
                j+=1;
            }
        }
    }    
}

main()
{
    FILE *sqc1,*sqc2;
    char *text1,*text2;
    int text_size1 = 0;
    int text_size2 = 0;
    int **L;
    sqc1 = fopen("sequenceOne.txt","r");
    sqc2 = fopen("sequenceTwo.txt","r");

    fseek(sqc1,0,SEEK_END);
    fseek(sqc2,0,SEEK_END);

    text_size1 = ftell(sqc1);
    text_size2 = ftell(sqc2);

    text1 = (char*)malloc(text_size2);
    text2 = (char*)malloc(text_size1);
    L = (int**)malloc(text_size1*sizeof(int*));
    for(int i = 0;i<text_size1;i++)
    {
        L[i] = (int*)malloc(text_size2*sizeof(int));
    }

    fseek(sqc1,0,SEEK_SET);
    fseek(sqc2,0,SEEK_SET);
    
    while(fscanf(sqc1,"%s",text1)!=EOF)
    {
        printf("\n%s",text1);
    }
    while(fscanf(sqc2,"%s",text2)!=EOF)
    {
        printf("\n%s",text2);
    }
    LCS(text1,text2,text_size1-2,text_size2-1,L);
    printf("\n");
    for(int i = 0;i<text_size1;i++)
    {
        for(int j = 0;j<text_size2;j++)
        {
           printf("%d",L[i][j]);
        }
        printf("\n");
    }
    //subOne->print(subOne);
    return 0;
}
