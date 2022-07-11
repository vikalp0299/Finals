#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MAX 150
typedef struct RECORD{
	size_t size;
	size_t item_size;
	void** items;

}record_T;



record_T* init_RECORD(size_t item_size)
{
	record_T* list  = calloc (1,sizeof(struct RECORD));
	list->item_size = item_size;
	list->size = 0;
	list->items = (void*) 0;
	return list;
}


void RECORD_append(record_T* record, void* item){

	record->size +=1;
	if(record->items == (void*) 0){
		record->items = calloc(record->size,record->item_size);
	}else{
		record->items = realloc(record->items,record->size * record->item_size);
	}

	record->items[record->size-1] = item;
}


typedef struct DETAILS{
	char* whatHappend;
	char* whenHappend;
	char* whereHappend;
	char* complaint_type;
	char* date;
	char* complainant_name;
	int victimORwitness, ComplaintNumber;
	
}details_T;



details_T* init_DETAILS(const char* CName,const char* WAH,const char* WEH,const char* WEN,const char* TYPE,const char* DATE,int VOW,int CNO){
	details_T* detail = calloc (1,sizeof(struct DETAILS));
	
	detail->complainant_name = calloc(strlen(CName) + 1,sizeof(char));
	strcpy(detail->complainant_name, CName);	
	
	detail->whatHappend = calloc(strlen(WAH) + 1, sizeof(char));
	strcpy(detail->whatHappend,WAH);

	detail->whenHappend = calloc(strlen(WEN) + 1, sizeof(char));
	strcpy(detail->whenHappend,WEN);

	detail->whereHappend = calloc(strlen(WEH) + 1, sizeof(char));
	strcpy(detail->whereHappend,WEH);
	
	detail->complaint_type = calloc(strlen(TYPE)+1,sizeof(char));
	strcpy(detail->complaint_type,TYPE);

	detail->date = calloc(strlen(DATE)+1,sizeof(char));
	strcpy(detail->date,DATE);
	
	detail->victimORwitness = VOW;
	detail->ComplaintNumber = CNO;
	

	return detail;
}

void record_search_by_complaint_number(record_T* list,int complaint_number){
		
		for(int i=0; i<list->size; i++){

			if(complaint_number == ((details_T*)list->items[i])->ComplaintNumber){
						if(((details_T*)list->items[i])->victimORwitness== 1){
							printf("DATE: %s\nCOMPLAINT NUMBER: %d\nCOMPLAINT TYPE: %s\nThe Witness, %ssaw that %s%saround %shrs\n",((details_T*)list->items[i])->date,((details_T*)list->items[i])->ComplaintNumber,((details_T*)list->items[i])->complaint_type,((details_T*)list->items[i])->complainant_name,((details_T*)list->items[i])->whatHappend,((details_T*)list->items[i])->whereHappend,((details_T*)list->items[i])->whenHappend);
						}
						else{
							printf("DATE: %s\nCOMPLAINT NUMBER: %d\nCOMPLAINT TYPE: %s\nThe Victim, %ssaid that %s%saround %shrs\n",((details_T*)list->items[i])->date,((details_T*)list->items[i])->ComplaintNumber,((details_T*)list->items[i])->complaint_type,((details_T*)list->items[i])->complainant_name,((details_T*)list->items[i])->whatHappend,((details_T*)list->items[i])->whereHappend,((details_T*)list->items[i])->whenHappend);

						}
			break;
			}
		}
}

void record_search_by_who_what_and_date(record_T* list, const char* who, const char* what,const char* date){
	int count=0,i;
	
	for(int j=0; j<list->size; j++){
		if(((strcmp(who,((details_T*)list->items[j])->complainant_name))==0) && ((strcmp(what,((details_T*)list->items[j])->whatHappend))==0) && ((strcmp(date,((details_T*)list->items[j])->date))==0)){
			count++;
			i=j;
		}
	}
	if(count ==0){
		printf("NO SUCH CASE\n");
		return ;

}
	else{
		if(((details_T*)list->items[i])->victimORwitness== 1){
							printf("DATE: %s\nCOMPLAINT NUMBER: %d\nCOMPLAINT TYPE: %s\nThe Witness, %ssaw that %s%saround %shrs\n",((details_T*)list->items[i])->date,((details_T*)list->items[i])->ComplaintNumber,((details_T*)list->items[i])->complaint_type,((details_T*)list->items[i])->complainant_name,((details_T*)list->items[i])->whatHappend,((details_T*)list->items[i])->whereHappend,((details_T*)list->items[i])->whenHappend);
						}
						else{
							printf("DATE: %s\nCOMPLAINT NUMBER: %d\nCOMPLAINT TYPE: %s\nThe Victim, %ssaid that %s%saround %shrs\n",((details_T*)list->items[i])->date,((details_T*)list->items[i])->ComplaintNumber,((details_T*)list->items[i])->complaint_type,((details_T*)list->items[i])->complainant_name,((details_T*)list->items[i])->whatHappend,((details_T*)list->items[i])->whereHappend,((details_T*)list->items[i])->whenHappend);

						}
	}

}
void swaps(record_T* list,int j ,int min_idx){
	int i,i2;
	i = ((details_T*)list->items[j])->ComplaintNumber;
	i2= ((details_T*)list->items[min_idx])->ComplaintNumber;
	//printf("THE I=%d\n",i);
	//printf("THE I2=%d\n",i2);
	((details_T*)list->items[j])->ComplaintNumber =i2;
	((details_T*)list->items[min_idx])->ComplaintNumber =i;
	char wht1[100],wht2[100];
	char whn1[10],whn2[10];
	char whr1[40],whr2[40];
	char type1[50],type2[50];
	char date1[11],date2[11];
	char name1[20],name2[20];
	int vow1,vow2;
	vow1= ((details_T*)list->items[j])->victimORwitness;
	vow2= ((details_T*)list->items[min_idx])->victimORwitness;
	((details_T*)list->items[min_idx])->victimORwitness =vow1;
	((details_T*)list->items[j])->victimORwitness =vow2;

	strcpy(wht1,((details_T*)list->items[j])->whatHappend);
	strcpy(wht2,((details_T*)list->items[min_idx])->whatHappend);
	strcpy(((details_T*)list->items[j])->whatHappend,wht2);
	strcpy(((details_T*)list->items[min_idx])->whatHappend,wht1);
	
	strcpy(whn1,((details_T*)list->items[j])->whenHappend);
	strcpy(whn2,((details_T*)list->items[min_idx])->whenHappend);
	strcpy(((details_T*)list->items[j])->whenHappend,whn2);
	strcpy(((details_T*)list->items[min_idx])->whenHappend,whn1);
	
	strcpy(whr1,((details_T*)list->items[j])->whereHappend);
	strcpy(whr2,((details_T*)list->items[min_idx])->whereHappend);
	strcpy(((details_T*)list->items[j])->whereHappend,whr2);
	strcpy(((details_T*)list->items[min_idx])->whereHappend,whr1);

	strcpy(type1,((details_T*)list->items[j])->complaint_type);
	strcpy(type2,((details_T*)list->items[min_idx])->complaint_type);
	strcpy(((details_T*)list->items[j])->complaint_type,type2);
	strcpy(((details_T*)list->items[min_idx])->complaint_type,type1);

	strcpy(date1,((details_T*)list->items[j])->date);
	strcpy(date2,((details_T*)list->items[min_idx])->date);
	strcpy(((details_T*)list->items[j])->date,date2);
	strcpy(((details_T*)list->items[min_idx])->date,date1);

	strcpy(name1,((details_T*)list->items[j])->complainant_name);
	strcpy(name2,((details_T*)list->items[min_idx])->complainant_name);
	strcpy(((details_T*)list->items[j])->complainant_name,name2);
	strcpy(((details_T*)list->items[j])->complainant_name,name1);
	//printf("CHANGED\n");
	//printf("NEW I:%d\n",((details_T*)list->items[j])->ComplaintNumber);
	//printf("NEW I2:%d\n",((details_T*)list->items[min_idx])->ComplaintNumber);
}
void sort_by_complaint_number(record_T* list){
	int min_idx,i,k,j;
	for(i=0; i<list->size-1;i++){
			min_idx=i;		
		for(j=i+1;j<list->size;j++){
			if(((details_T*)list->items[j])->ComplaintNumber < ((details_T*)list->items[min_idx])->ComplaintNumber){
				min_idx = j;
				
				//printf("%d\n",((details_T*)list->items[j])->ComplaintNumber);
			}
			swaps(list,i,min_idx);
		}
	//printf("%d\n",((details_T*)list->items[j])->ComplaintNumber );	
	}
		//printf("%d\n",((details_T*)list->items[i])->ComplaintNumber);

for(int i=0; i<list->size ;i++){
						if(((details_T*)list->items[i])->victimORwitness== 1){
							printf("DATE: %s\nCOMPLAINT NUMBER: %d\nCOMPLAINT TYPE: %s\nThe Witness, %ssaw that %s%saround %shrs\n",((details_T*)list->items[i])->date,((details_T*)list->items[i])->ComplaintNumber,((details_T*)list->items[i])->complaint_type,((details_T*)list->items[i])->complainant_name,((details_T*)list->items[i])->whatHappend,((details_T*)list->items[i])->whereHappend,((details_T*)list->items[i])->whenHappend);
						}
						else{
							printf("DATE: %s\nCOMPLAINT NUMBER: %d\nCOMPLAINT TYPE: %s\nThe Victim, %ssaid that %s%saround %shrs\n",((details_T*)list->items[i])->date,((details_T*)list->items[i])->ComplaintNumber,((details_T*)list->items[i])->complaint_type,((details_T*)list->items[i])->complainant_name,((details_T*)list->items[i])->whatHappend,((details_T*)list->items[i])->whereHappend,((details_T*)list->items[i])->whenHappend);

}	
}
	
}
	
	



int main(){

	record_T* list = init_RECORD(sizeof(struct DETAILS*));
	char name[20],when[10],where[40],what[100],date[11],type[50];
	int VOW,CNO,swtsig;
	
	do{
		printf("HERE IS THE LIST OF OPTIONS: -\n1.INSERT A NEW COMPLAINT\n2.DISPLAY THE DETAILS OF ALL COMPLAINTS\n3.SORT THE COMPLAINTS USING COMPLAINT NUMBER\n4.SEARCH FOR COMPLAINT AND DISPLAY COMPLAINT DETAILS\n5.EXIT\n");
		scanf("%d",&swtsig);
		getchar();
			switch(swtsig){
				case 1:{
					printf("PLEASE ENTER EVERYTHING IN UPPERCASE...\n");
					printf("Complainant Name...\n");
					fgets(name,MAX,stdin);
					
					printf("Victim or Witness...\n");
					scanf("%d",&VOW);
					getchar();
					printf("Complaint Number...\n");	
					CNO = (1+rand())%100;	
					printf("%d\n",CNO);
					
					printf("Complaint Type...\n");
					fgets(type,MAX,stdin);
					
					printf("Date...\n");
					fgets(date,MAX,stdin);

					printf("What happened...\n");
					fgets(what,MAX,stdin);
					
					printf("When did it happen...\n");
					fgets(when,MAX,stdin);
					
					printf("Where did it happen...\n");
					fgets(where,MAX,stdin);
						
					RECORD_append(list,init_DETAILS(name,what,where,when,type,date,VOW,CNO));	
					break;				
				}
				case 2:{
					for(int i=0; i<list->size ;i++){
						if(((details_T*)list->items[i])->victimORwitness== 1){
							printf("DATE: %s\nCOMPLAINT NUMBER: %d\nCOMPLAINT TYPE: %s\nThe Witness, %ssaw that %s%saround %shrs\n",((details_T*)list->items[i])->date,((details_T*)list->items[i])->ComplaintNumber,((details_T*)list->items[i])->complaint_type,((details_T*)list->items[i])->complainant_name,((details_T*)list->items[i])->whatHappend,((details_T*)list->items[i])->whereHappend,((details_T*)list->items[i])->whenHappend);
						}
						else{
							printf("DATE: %s\nCOMPLAINT NUMBER: %d\nCOMPLAINT TYPE: %s\nThe Victim, %ssaid that %s%saround %shrs\n",((details_T*)list->items[i])->date,((details_T*)list->items[i])->ComplaintNumber,((details_T*)list->items[i])->complaint_type,((details_T*)list->items[i])->complainant_name,((details_T*)list->items[i])->whatHappend,((details_T*)list->items[i])->whereHappend,((details_T*)list->items[i])->whenHappend);

}
					}			
	
						break;
				}
				case 3:{
						//sort_by_complaint number
							sort_by_complaint_number(list);
						
						break;
				}
				case 4:{
						int cno,ques;
						printf("Do you have complaint number?\nType 1 for Yes and 0 for No\n");
						scanf("%d",&ques);
						if(ques == 1){
							//record_search_by_complaint_number
							printf("PLEASE Enter the Complaint Number\n");
							scanf("%d",&cno);
							record_search_by_complaint_number(list,cno);
						}
						else{
							//record_search_by_who_what_and_date
							getchar();
							char whom[20],whatcase[100],dates[11];
							printf("ENTER THE FOLLOWING IN UPPERCASE...\n");
							printf("Who filed the complained?\n");
							fgets(whom,MAX,stdin);
							printf("What was the complaint?\n");
							fgets(whatcase,MAX,stdin);
							printf("When the complaint was registered?\n");
							fgets(dates,MAX,stdin);
							record_search_by_who_what_and_date(list,whom,whatcase,dates);
						}

					break;
				}
				case 5:{
					printf("EXITING...\n");
					exit(0);
				}
			printf("\n\n\n");
		}
	}while(1);			
	printf("%ld\n",list->size);

	if(VOW == 1){
	printf("DATE: %s\nCOMPLAINT NUMBER: %d\nCOMPLAINT TYPE: %s\nThe Witness, %ssaw that %s%saround %shrs",date,CNO,type,name,what,where,when);
}
	else{
	printf("DATE: %s\nCOMPLAINT NUMBER: %d\nCOMPLAINT TYPE: %s\nThe Victim, %ssaid that %s%saround %shrs",date,CNO,type,name,what,where,when);
		
	}
	return 0;

}
