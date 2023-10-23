#include<iostream> 
#include<unistd.h>
#include<vector>
#include<string> 
#include<fcntl.h>
#include<sys/wait.h>
#define MAX_BYTES 100
using namespace std;

int main(void){
	vector<string> arg;
	string temp;
	char **argv;
	char buf[MAX_BYTES];
	int len;
	int argc;
	pid_t pid;
	while(true){
		cout << "osh> ";
		// cout will only come out at the end if fflush isn't used
		fflush(stdout); //flushes the output buffer and moves the buffered data to console/disk 
		//reads MAX_BYTES bytes from file descriptor STDIN_FILENO into the buffer
		len = read(STDIN_FILENO, buf, MAX_BYTES); //outputs the number of bytes read
		// deals with input
		for(int i=0; i<len; i++){
			//encounters whitespace or the end of command and temp isn't empty
			if((buf[i] == ' ' || i == len-1) && temp.size() != 0){ 
				arg.push_back(temp); //put the space-separated arguments into arg
				temp = "";
			}
			else{
				temp += buf[i];
			}
		}
		argc = arg.size(); // arg count
		argv = new char *[argc+1]; // arg vector 
		// deals with argv           
		for(int i=0; i<argc; i++){
			argv[i] = new char[arg[i].size()];
			strcpy(argv[i], arg[i].c_str());
		}
		argv[argc] = NULL;
		// chekc is command is exit
		if(!strcmp(argv[0], "exit")){
			cout << "Process end\n";
			break;
		}
		// else execute the command after fork
		pid_t pid;
		pid = fork();
		if(pid == 0){ // let child process execute 
			int status = execvp(argv[0], argv);
			if(status == -1){
				cout << "No such command!" << endl; // command not found
			}
			exit(1);
		}
		else { // main waits for child to exit()
			wait(NULL);
		}

		arg.clear();
	}
	return 0;
}