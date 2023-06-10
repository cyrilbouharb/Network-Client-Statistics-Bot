#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
void swap(int* num1, int* num2)
{
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}
 

void selectionSort(int arr[], int length)
{
    int i, j, min_index;
    for (i = 0; i < length - 1; i++) {
        min_index = i;
        for (j = i + 1; j < length; j++)
            if (arr[j] < arr[min_index])
                min_index = j;
 
    
        swap(&arr[min_index], &arr[i]);
    }
}

 int main(int argc, char *argv[]) {
     int sock = 0;
     struct sockaddr_in serv_addr;


     if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
     }
     
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_port = htons(atoi(argv[2]));
     if( inet_pton(AF_INET, argv[3], &serv_addr.sin_addr)<= 0) {
         printf("\n Invalid address / Address not supported \n");
         return -1;
     }
  
     if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
         printf("\n Conncetion Failed \n");
         return -1;
     }
  
     printf("Successfully connected to the server.\n");
     


    char buff[100];
    strcpy(buff, "cs230 HELLO ");
    strcat(buff, argv[1]);
    strcat(buff, "\n");
    send(sock, buff, strlen(buff), 0);
  while(1) {
    int len = recv(sock, buff, 100, 0);
    buff[len] = '\0';
    printf("received: %s\n", buff);
    
    printf("Ignoring first value: %s\n", strtok(buff," "));
    char status[40];
    strcpy(status, strtok(NULL, " "));
    if(strcmp(status, "STATUS") != 0) {
      close(sock);
      return -1;
    } else {
     printf("Status is fine: %s\n", status);


    char operator[20];
    int i;
    strcpy(operator, strtok(NULL, " "));
    if(strcmp(operator, "min") == 0) {
       i = 0;
    } else if(strcmp(operator, "max") == 0){
       i = 4;
    } else {
      i = 2;
    }
    printf("The operator is: %s\n", operator);



   int numbers[5];
   for( int j = 0; j < 5; ++j) {
      numbers[j] = atoi(strtok(NULL, " "));
   }

   selectionSort(numbers, 5);
   int number = numbers[i];
   char buff[100];
   char final_answer[10];
   sprintf(final_answer, "%d", number);

   strcpy(buff, "cs230 ");
   strcat(buff, final_answer);
   strcat(buff, "\n");
   send(sock, buff, strlen(buff), 0);  
 
  }
 }
   return 0;
}
    
