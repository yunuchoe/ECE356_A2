#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

typedef struct Process{ // this struct represent our "process"
    int pid; // the unqiue id
    char name[100]; // the name (limited to 100 chars for simplicity)
    struct Process *next; // next pointer
    struct Process *previous; // previous pointer
} Process;

Process *current = NULL; // current location of pointer
Process *head = NULL; // pointer to the head (start)
Process *tail = NULL; //pointer to tail (end)

// functions

void AddProcess(int pid, char name[100]){ // add (append) a new process to the end
    Process *new_process = (Process *)malloc(sizeof(Process)); // create new process

    new_process->pid = pid;
    strcpy(new_process->name, name);
    
    if(head == NULL){ //first item
    // disclaimer: ive done a double linked list assignment before in c++ so I recycled a lot of the same ideas
        head = new_process;
        tail = new_process;
        new_process->next = NULL;
        new_process->previous = NULL;
    }else{ // not first item
        new_process->previous = tail;
        new_process->next = NULL;
        tail->next = new_process;
        tail = new_process;
    }
}

void RemoveProcess_pid(int pid){
    Process *pointer = head; // temporary pointer to find the node we want

    while(pointer != NULL) {
        if(pointer->pid == pid){ // found the target
            if (pointer == head){ //target is head (easy)
                    head = pointer->next; 
                    if (head != NULL) {
                        head->previous = NULL;
                    }
                } 
            else if(pointer == tail){ // target is tail (also easy)
                tail = pointer->previous; // Move tail to previous
                if (tail != NULL) {
                    tail->next = NULL; // Update next of new tail
                }
            } 
            else{ // target is in middle (more complex)
                pointer->previous->next = pointer->next;
                if (pointer->next != NULL) {
                    pointer->next->previous = pointer->previous;
                }
            }
        }
        pointer = pointer->next; // move pointer along
    }
}

void RemoveProcess_name(char name[100]){
    Process *pointer = head; // temporary pointer to find the node we want

    while(pointer != NULL) {
        if(strcmp(pointer->name , name) == 0){ // found the target
        //same logic as above
            if(pointer == head){ //target is head (easy)
                    head = pointer->next; 
                    if (head != NULL) {
                        head->previous = NULL;
                    }
                } 
            else if(pointer == tail){ // target is tail (also easy)
                tail = pointer->previous; // Move tail to previous
                if (tail != NULL) {
                    tail->next = NULL; // Update next of new tail
                }
            } 
            else{ // target is in middle (more complex)
                pointer->previous->next = pointer->next;
                if (pointer->next != NULL) {
                    pointer->next->previous = pointer->previous;
                }
            }
        }
        pointer = pointer->next; // move pointer along
    }
}

void FindProcess_pid(int pid){
    Process *pointer = head; // temporary pointer to find the node we want

    while(pointer != NULL) {
        if(pointer->pid == pid){ // found the target
            printf("Found the process. Name: %s and PID: %d", pointer->name, pointer->pid);
        }
        pointer = pointer->next; // move pointer along
    }
}

void FindProcess_name(char name[100]){
    Process *pointer = head; // temporary pointer to find the node we want

    while(pointer != NULL) {
        if(strcmp(pointer->name , name) == 0){ // found the target
        //same logic as above
            printf("Found the process. Name: %s and PID: %d", pointer->name, pointer->pid);  
        }  
        pointer = pointer->next; // move pointer along
    }
}

void TerminateProcess(int pid){ // assuming given pid only
    Process *pointer = head; // temporary pointer to find the node we want

    while(pointer != NULL) {
        if(pointer->pid == pid){ // found the target
            if(pointer == head){ //target is head (easy)
                    head = pointer->next; 
                    if (head != NULL) {
                        head->previous = NULL;
                    }
                } 
            else if(pointer == tail){ // target is tail (also easy)
                tail = pointer->previous; // Move tail to previous
                if (tail != NULL) {
                    tail->next = NULL; // Update next of new tail
                }
            } 
            else{ // target is in middle (more complex)
                pointer->previous->next = pointer->next;
                if (pointer->next != NULL) {
                    pointer->next->previous = pointer->previous;
                }
            }
        }
        pointer = pointer->next; // move pointer along
    }

    //terminate (what is different from remove)
    //this is final so something cant be re addded later
    pointer->name[0] = '\0'; // give null as name to make empty string to simulate termination
    pointer->pid = -1; //give invalid pid value to simulate termination
}

void ProcessNavigation_foward(){
    if(current == NULL) {
        current = head;
    }else{
        current = current->next;
    }
}

void ProcessNavigation_back(){
    if(current == NULL) {
        current = tail;
    }else{
        current = current->previous;
    }
}


int main(){

    // Empty as no test cases are asked for

    return 0;
}