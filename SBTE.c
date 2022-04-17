#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

int S1=-1,S2=-1;
char Stack1[10000],Stack2[10000];
char Str[1000],File1[100],File2[100],Status[100];

FILE *fp = NULL;

void saveFile(char St[]){
	int i;
	fp = fopen(St, "w");
   	for(i=0; i<=S1; i++){
        fprintf(fp,"%c",Stack1[i]);
	}
    for(i=S2; i>=0; i--){
        fprintf(fp,"%c",Stack2[i]);
    }
	fclose(fp);
	printf("File saved Sucessfully...!\n");
	strcpy(Status, "Saved");
}

void print(){
    int m;
    for(m=0; m<=S1; m++){
        printf("%c",Stack1[m]);
    }
    printf("|");
    for(m=S2; m>=0; m--){
        printf("%c",Stack2[m]);
    }
    printf("\n");
    printf("----------------------------------------------------------------------------------------\n");
}

void print1(){
    int m;
    printf("%d\n",S1);
    for(m=0; m<=S1; m++){
        printf("%c",Stack1[m]);
    }
    printf("\n");
}

void print2(){
    int m;
    printf("%d\n",S2);
    for(m=S2; m>=0; m--){
        printf("%c",Stack2[m]);
    }
    printf("\n");
}

int main()
{
    int i,j,l;
    strcpy(File1, "NULL");
    strcpy(File2, "NULL");
	strcpy(Status, "Saved");
	
//	printf("----------------------------------------------------------------------------------------\n");
//	printf("<<<<====		S T A C K  B A S E D  T E X T  E D I T O R    		====>>>>\n");
//	printf("----------------------------------------------------------------------------------------\n");
//	goto Start;
    
    Menu:
    //clrscr();
    system("cls");
    printf("----------------------------------------------------------------------------------------\n");
    printf("        	S T A C K  B A S E D  T E X T  E D I T O R    		\n\n");
	printf("Menu:\n");
    printf("1.Insert    2.Left      3.Right     4.Left Delete       5.Right Delete\n");
    printf("6.Open File    	7.New File	8.Save     9.Save As 	0.Exit\n\n");
    printf("File : %s\tStatus : %s\n",File1,Status);
	printf("----------------------------------------------------------------------------------------\n");
	//printf("Contents of your file are...\n");
    print();
    
	Start:
	printf("Enter commmand : ");
    scanf("%d",&i);
    
    switch(i){
    	case 0: //Exit
    		if(strcmp(Status,"Saved") != 0){
    			printf("Do you want to SAVE your file?    1 - YES    0 - NO : ");
    			scanf("%d",&i);
    			if(i==1){
    				if(strcmp(File1,"NULL") != 0){
           				if(fscanf(fp,"%c",&Str[i])>0){
            				fclose(fp);
							printf("Do you want to rewrite the Exsisting File... 1 - YES  0 - NO : ");
            				scanf("%d",&i);
            				if(i==0)
            					goto Menu;
						}
						saveFile(File1);
						exit(1);
					}
					else{
						goto Save;
					}		
				}
				else{
					exit(1);
				}
			}
			else{
				exit(1);
			}
    	
        case 1: //Insert
            printf("Type text and press enter to insert...\n");
            scanf("\n");
            scanf("%[^\n]s",Str);
            
            for(i=0; Str[i]!='\0'; i++){
                Stack1[++S1] = Str[i]; //Stack Push function
            }
            strcpy(Status, "Unsaved");
            goto Menu;
            break;
        
        case 2: //Move Left
            printf("How many positions LEFT do you want to MOVE : ");
            scanf("%d",&l);
            
            for(i=0; i<l && S1>=0; i++){
                Stack2[++S2] = Stack1[S1--];
            }
            
            goto Menu;
            break;
        
        case 3: //Move Right
            printf("How many positions RIGHT do you want to MOVE : ");
            scanf("%d",&l);
            
            for(i=0; i<l && S2>=0; i++){
                Stack1[++S1] = Stack2[S2--];
            }
            
            goto Menu;
            break;
        
        case 4: //Delete left == Backspace
            printf("How many positions LEFT do you want to DELETE : ");
            scanf("%d",&l);
            
            S1 = (S1-l)<-1 ? -1 : S1-l;
            
            strcpy(Status, "Unsaved");
            goto Menu;
            break;
        
        case 5: //Delete right == Delete
            printf("How many positions RIGHT do you want to DELETE : ");
            scanf("%d",&l);
            
            S2 = (S2-l)<-1 ? -1 : S2-l;
            
            strcpy(Status, "Unsaved");
            goto Menu;
            break;
        
        case 6: //Open File
            printf("OPEN FILE...");
			Open:
			printf("Enter the File Name : ");
			scanf("\n");
            scanf("%[^\n]s",File1);
            strcat(File1, ".txt");
			
			fp = fopen(File1, "r");
            if(fp == NULL){ //*
            	printf("File Not Found!\n");
				goto Menu;            	
			}
			S1=-1;
            S2=-1;
            while(fscanf(fp,"%c",&Stack1[++S1])>0);
            S1--;
            fclose(fp);
            
            strcpy(Status, "Saved");
            goto Menu;
            break;
        
        case 7: //Create new file
        	New:
        	printf("NEW FILE...");
        	printf("Enter the File Name : ");
			scanf("\n");
            scanf("%[^\n]s",File1);
            strcat(File1, ".txt");
            
            fp = fopen(File1, "r");
            i=0;
            if(fscanf(fp,"%c",&Str[i])>0){
            	fclose(fp);
				printf("Do you want to rewrite the Exsisting File...    1 - YES    0 - NO : ");
            	scanf("%d",&i);
            	if(i==0)
            		goto Menu;
			}
            
			fp = fopen(File1, "W");
            S1=-1;
            S2=-1;
            fclose(fp);
            strcpy(Status, "Saved");
            goto Menu;
            break;
            
        case 8: //Saving as current version file
        	goto Save1;
        	Save:
        	printf("SAVE FILE...");
			printf("Enter the File Name : ");
			scanf("\n");
            scanf("%[^\n]s",File1);
            strcat(File1, ".txt");
                 
            Save1:
            if(strcmp(File1,"NULL") != 0){
           		if(fscanf(fp,"%c",&Str[i])>0){
            		fclose(fp);
					printf("Do you want to rewrite the Exsisting File... 1 - YES  0 - NO : ");
            		scanf("%d",&i);
            		if(i==0)
            			goto Menu;
				}
				saveFile(File1);
			}
			else{
				goto Save;
			}
            
			goto Menu;
            break;
        
        case 9: //Save as
        	SaveAs:
        	printf("SAVE FILE AS...");
        	printf("Enter the File Name : ");
			scanf("\n");
            scanf("%[^\n]s",File2);
            strcat(File2, ".txt");
            
			fp = fopen(File2, "r");
            i=0;
			     
            if(strcmp(File2,"NULL") != 0){
            	if(fscanf(fp,"%c",&Str[i])>0){
            		fclose(fp);
					printf("Do you want to rewrite the Exsisting File... 1 - YES  0 - NO : ");
            		scanf("%d",&i);
            		if(i==0)
            			goto Menu;
				}
				saveFile(File2);
			}
			else{
				goto SaveAs;
			}
            
			goto Menu;
            break;
		    
		default:
            printf("Invalid COMMAND!\n");
        	goto Menu;
        
    }
    
}
