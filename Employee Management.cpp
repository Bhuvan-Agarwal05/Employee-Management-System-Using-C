#include<stdio.h>
#include<stdlib.h>

struct Address{
	char city[50];
	char street[100];
};

typedef struct Employee{
	int emp_id;
	char name[50];
	int age;
	struct Address address;
}empl;

typedef struct NODE{
	empl employee;
	struct NODE *next;
}node;

node *create(node *);  // For Registering All Employee's Initially
node *insertEmployee(node *);  // For Inserting Details Of A New Employee
node *searchAndDeleteEmployee(node *,int); // For Deleting or, Removing an Employee From The Organization
void displayDetails(node *);  // For Displaying The Details Of All The Employee
void updateDetails(node *,int);  // For Updating Details Of a Particular Employee At a Time
int searchID(node *,int);
char fake_str[1];

int main()
{
	int ch,id_to_delete,id_to_update;
	node *head;
	head=NULL;
	while(1)
	{
		printf("\n1) Register All Employees.\n2) Insert New Employee.\n3) Delete An Employee.\n4) Display The Details Of An Employee.\n5) Update Details Of An Employee.\n6) EXIT.\n");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1: head=create(head);
			        break;
			case 2: head=insertEmployee(head);
			        break;
			case 3: if(head==NULL)
	                     {
							printf("\n***** No Employee Records Found *****\n");
							break;
						}
					printf("\nEnter The Employee ID To Delete:- ");
					scanf("%d",&id_to_delete);
					head=searchAndDeleteEmployee(head,id_to_delete);
			        break;
			case 4: if(head==NULL)
	                     {
							printf("\n***** No Employee Records Found *****\n");
							break;
						}
					displayDetails(head);
			        break;
			case 5: if(head==NULL)
	                     {
							printf("\n***** No Employee Records Found *****\n");
							break;
						}
					printf("\nEnter The Employee ID To Update Details:- ");
					scanf("%d",&id_to_update);
					updateDetails(head,id_to_update);
			        break;
			case 6: exit(0);
			    default:
			    	printf("INVALID CHOICE");
		}
	}
}

// Function To Register or, Add Details Of All Employee's Initially
node *create(node *head)
{
	if(head==NULL)
	{
		int choice=1,flag=0;
		node *new_node,*temp;
		while(choice)
		{
			new_node=(node *)malloc(sizeof(node));
			printf("\nEnter Employee ID:- ");
			scanf("%d",&new_node->employee.emp_id);
			
			flag=searchID(head,new_node->employee.emp_id);
			if(flag==1)
			{
				printf("\nEmployee ID Already Exists...You Need To Enter Other Employee ID To Register.");
				continue;
			}
			
			gets(fake_str); // Buffer Flusher to get String Input After Taking an Integer Input
			printf("\nEnter Employee Name:- ");
			gets(new_node->employee.name);
			printf("\nEnter Employee Age:- ");
			scanf("%d",&new_node->employee.age);
			
			if(new_node->employee.age<=18 || new_node->employee.age>60)
			{
				printf("\n***** Invalid Employee Age... Employee Age For Job Eligibility is 18<= AGE < 60 *****");
				continue;
			}
			gets(fake_str); // Buffer Flusher to get String Input After Taking an Integer Input
			printf("\nEnter The Name of the City where Employee lives:- ");
			gets(new_node->employee.address.city);
			printf("\nEnter The Name of the Street where Employee lives:- ");
			gets(new_node->employee.address.street);
				
			new_node->next=NULL;
				
			if(head==NULL)
				head=temp=new_node;
			else
			{
				temp->next=new_node;
				temp=new_node;
			}
			printf("\nDo You Want To Register Another Employee:- (1/0)? ");
			scanf("%d",&choice);
		}
		return head;
	}
	else
	{
		printf("\nYou Cannot Again Register Any New Employee Using This Method,,, This Function Is Only To Register Employee Initially");
		return head;
	}
}

// Function To Search & Verify Employee ID Before Inserting ...
int searchID(node *head,int id)
{
	int flag=0;
	node *temp;
	temp=head;
	while(temp!=NULL)
	{
		if(temp->employee.emp_id==id)
		    {
		    	flag=1;
		      	break;
			}
		else
			temp=temp->next;
	}
	if(flag==1)
	   return 1;
	else
	   return 0;
}

// Function To Insert or, Add Details Of A New Employee
node *insertEmployee(node *head)
{
	int flag=0;
	node *new_node;
	new_node=(node *)malloc(sizeof(node));
	printf("\nEnter Employee ID:- ");
	scanf("%d",&new_node->employee.emp_id);
	
	flag=searchID(head,new_node->employee.emp_id);
	if(flag==1)
		{
			printf("\nEmployee ID Already Exists...You Need To Enter Other Employee ID To Register.");
			return head;
		}
	
	gets(fake_str); // Buffer Flusher to get String Input After Taking an Integer Input
	printf("\nEnter Employee Name:- ");
	gets(new_node->employee.name);
	printf("\nEnter Employee Age:- ");
	scanf("%d",&new_node->employee.age);
	if(new_node->employee.age<=18 || new_node->employee.age>60)
			{
				printf("\n***** Invalid Employee Age... Employee Age For Job Eligibility is 18<= AGE < 60 *****");
				return head;
			}
	gets(fake_str); // Buffer Flusher to get String Input After Taking an Integer Input
	printf("\nEnter The Name of the City where Employee lives:- ");
	gets(new_node->employee.address.city);
	printf("\nEnter The Name of the Street where Employee lives:- ");
	gets(new_node->employee.address.street);
			
	new_node->next=NULL;
	if(head==NULL)
	{
		head=new_node;
	}
	else
	{
		new_node->next=head;
		head=new_node;
	}
	return head;
}

// Function To Search & Delete Details Of Any Particular Employee ( Search Using Employee ID because it is Unique )
node *searchAndDeleteEmployee(node *head,int id_to_delete)
{
	node *temp,*prev_node;
	temp=prev_node=head;
	
	// If Their is Only One Node then we need to perform these steps
	
	if(head->next==NULL)
	{
		head=NULL;
		free(temp);
		return head;
	}
	
	// If Number Of Nodes or, Employee's Data is for more than 1 Employee then, we need to perform these steps
	
	while(temp!=NULL && temp->employee.emp_id!=id_to_delete)
	{
		prev_node=temp;
		temp=temp->next;
	}
	prev_node->next=temp->next;
	free(temp);
	return head;
}

// Function To Display The Details Of All The Employees
void displayDetails(node *head)
{
	node *temp;
	temp=head;
	printf("\n----------------------------------------------");
	while(temp!=NULL)
	{
		printf("\n\tEmployee ID : %d",temp->employee.emp_id);
		printf("\n\tEmployee Name : %s",temp->employee.name);
		printf("\n\tEmployee Age : %d",temp->employee.age);
		printf("\n\tAddress Of The Employee:\n\t\tCity : %s\n\t\tStreet : %s\n",temp->employee.address.city,temp->employee.address.street);
		
		temp=temp->next;
		printf("\n----------------------------------------------");
	}
}

// Function To Update Details Of Any Particular Employee ( Employee ID is unique )
void updateDetails(node *head,int id_to_update)
{
	int choice;
	node *temp;
	temp=head;
	if(head->next==NULL)
		temp=head;
	else
	{
		while(temp!=NULL && temp->employee.emp_id!=id_to_update)
			{
				temp=temp->next;
			}
	}
	
	printf("\n***** Your Existing Details Are *****");
	printf("\n\tEmployee ID : %d",temp->employee.emp_id);
	printf("\n\tEmployee Name : %s",temp->employee.name);
	printf("\n\tEmployee Age : %d",temp->employee.age);
	printf("\n\tAddress Of The Employee:\n\t\tCity : %s\n\t\tStreet : %s\n",temp->employee.address.city,temp->employee.address.street);
	
	printf("\n1) To Update Name.\n2) To Update Age.\n3) To Update City Name.\n4) To Update Street Name.\n5) Your Data Is Up-to Date.\n");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1: printf("\nEnter New Name:- ");
				gets(fake_str);
		        gets(temp->employee.name);
		        break;
	    case 2: printf("\nEnter New Age:- ");
	            scanf("%d",&temp->employee.age);
	            break;
		case 3: printf("\nEnter City Name:- ");
				gets(fake_str);
				gets(temp->employee.address.city);
				break;
		case 4: printf("\nEnter Street Name:- ");
				gets(fake_str);
				gets(temp->employee.address.street);
				break;
		case 5: break;
		   default:
		   	printf("INVALID CHOICE");
	}
}















/*
Using Array 
void search(int,empl [],int);
int printDetails(empl [],int );

int main()
{
	char fake_str[1];
	int no_of_employee,employee_id;
	printf("\nEnter The Number Of Employees In Your Organization:- ");
	scanf("%d",&no_of_employee);
	
	empl emp[no_of_employee];  // Variable of Employee Type
	
	for(int i=0;i<no_of_employee;i++)
	{
		printf("Enter The Employee Id:-\n");
		scanf("%d",&emp[i].emp_id);
		
		gets(fake_str); // Buffer Flusher to get String Input After Taking an Integer Input
		
		printf("Enter The Employee Name:-\n");
		gets(emp[i].name);
		printf("Enter Age Of The Employee:-\n");
		scanf("%d",&emp[i].age);
		printf("Enter The City Of The Employee:-\n");
		scanf("%s",&emp[i].address.city);
		printf("Enter The Street Name:-\n");
		scanf("%s",&emp[i].address.street);
		printf("\n");
	}
	printf("\n-------------------------------------------------------------------------------------------");
	printf("\n\nEnter The Employee Id For Details:- ");
	scanf("%d",&employee_id);
	
	search(employee_id,emp,no_of_employee);
	
}

void search(int employee_id,empl emp[],int no_of_employee)
{
	int flag=0; 
	
	// We Are Using Linear Search , because if we will try for Binary Search , then we need to sort the Employee_ID
	for(int i=0;i<no_of_employee;i++)
	{
		if(emp[i].emp_id==employee_id)
		{
			flag=printDetails(emp,i);
			break;
		}   
	}
	if(flag==0)
		printf("\nEmployee ID NOT PRESENT!");
}

int printDetails(empl emp[],int i)
{
	printf("Employee Name is:- %s",emp[i].name);
	printf("\nEmployee Id is:- %d",emp[i].emp_id);
	printf("\nEmployee Age is:- %d",emp[i].age);
	printf("\nEmployee's City Name is:- '%s",emp[i].address.city);
	printf("\nEmployee's Street Name is:- '%s",emp[i].address.street);
	return 1;
}


*/
