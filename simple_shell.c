

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

int main(){
	char line[1024];
	int pid, i, argc;
	/*char *args[] = {&line,0};*/
	char *args[1000];
	char *args2[1000];
	int* first_child_error;
	while(1){
		printf("Hello!!>");
		if(!fgets(line,1023,stdin)){
			break;
		}
	        unsigned int len = strlen(line);
                if(line[len-1]=='\n')line[len-1]='\0';


		if(strcmp(line,"exit")==0)break;

		/* Split commands into different parts*/
		char *split;
		split = strtok(line," ");
		int j=0;
		int k=0;
		/*Loop through the tokens in the pointer*/
		while(split){
			if(strcmp(split,"&&")==0){
				split= strtok(NULL," ");
				while(split){
					args2[k]=split;
					split= strtok(NULL," ");
					k++;
				}
				break;
			}else{
				args[j]=split;
				split= strtok(NULL," ");
				j++;
			}
		}
		/* Terminate with a null*/
		args[j]=NULL;
                /* Terminate with a null*/
                args2[k]=NULL;

		pid=fork();
		if(pid==0){
		/*Meaning we are in the child */
			/*Name of the file of program you want to run */
				int status = execvp(line,args);
				if(status==-1){
					printf("Error number is %d\n",errno);
					fprintf(stderr,"Hello!!: %s\n",strerror(errno));
					exit(EXIT_FAILURE);
				}
		}else{
			int check;

			wait(&check);

			if(check==0){
				pid=fork();
				if(pid==0){
					int status = execvp(args2[0],args2);
					fprintf(stderr,"Hello!!: %s\n",strerror(errno));
					exit(EXIT_FAILURE);
				}else{
					wait(1);
				}
			}
		}
	}
	return 0;
}
