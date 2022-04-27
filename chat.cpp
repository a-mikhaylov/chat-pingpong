#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <thread>
#include <string>

using namespace std;

#define NAMEDPIPE_NAME "/tmp/chatpipe666"
#define BUFSIZE        50

void My_OUT(char *arr) {
	cout << "other console: ";
	for (int i = 0; i < BUFSIZE; i++) {
		cout << arr[i];
	}

	cout << endl;
	return;
}

int main(int argc, char* argv[]) {
	int fd, len;
    char buf[BUFSIZE] = {'f', 'i', 'r', 's', 't'};
    char inp[BUFSIZE];
    string pr;
    string sc;
    
    if (argc == 1) {
    	if ( mkfifo(NAMEDPIPE_NAME, 0777) ) {
            perror("mkfifo");
            return 1;
        } 

        fd = open(NAMEDPIPE_NAME, O_RDWR);

        if ( (len = write(fd, buf, BUFSIZE)) <= 0 ) {
                perror("write");
        }

        this_thread::sleep_for(2000ms);  

        while (1) {
        	memset(inp, '\0', BUFSIZE);
            memset(buf, '\0', BUFSIZE);
            this_thread::sleep_for(100ms);
            if ( (len = read(fd, inp, BUFSIZE)) <= 0 ) {
                perror("write");
        	}        	
        	My_OUT(inp);
        	

        	cin >> sc;
        	if (sc == "quit") {
        		close(fd);
                remove(NAMEDPIPE_NAME);
        		return 0;
        	}

        	for (int i = 0; i < sc.length(); i++) {
        		buf[i] = sc[i];
        	}

			if ( (len = write(fd, buf, BUFSIZE)) <= 0 ) {
                perror("write");
        	}        	
        }
    } else {//------------------------------------------------------------------------------------------------------------------------------------
    	if ( (fd = open(NAMEDPIPE_NAME, O_RDWR)) < 0 ) {
            perror("open");
            return 1;
        }

        while (1) {
        	memset(inp, '\0', BUFSIZE);
            memset(buf, '\0', BUFSIZE);
            this_thread::sleep_for(100ms);
			if ( (len = read(fd, inp, BUFSIZE)) <= 0 ) {
                perror("write");
        	}        	
        	My_OUT(inp);

        	cin >> sc;
        	if (sc == "quit") {
        		close(fd);
                remove(NAMEDPIPE_NAME);
        		return 0;
        	}

        	for (int i = 0; i < sc.length(); i++) {
        		buf[i] = sc[i];
        	}

			if ( (len = write(fd, buf, BUFSIZE)) <= 0 ) {
                perror("write");
        	}
        }

    }//else of argc
}//main