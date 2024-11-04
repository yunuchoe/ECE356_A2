#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

typedef struct Process{ // this struct represent our "process"
    int pid; // the unqiue id
    char name[100]; // the name (limited to 100 chars for simplicity)
    int state; // let 0 = ready, 1 = i/o wait and 2 = runnning state respectively

    struct Process *next; // next pointer
    struct Process *previous; // previous pointer
} Process;

// current processs/queue
    Process *current = NULL; // current location of pointer
    Process *head = NULL; // pointer to the head (start)
    Process *tail = NULL; //pointer to tail (end)

// ready queue 
    Process* R_head = NULL;
    Process* R_tail = NULL;

// i/o queue
    Process* I_head = NULL;
    Process* I_tail = NULL;

// functions

void AddProcess(Process *new_process){ // add to ready queue
    new_process->state = 0; // assuming ready is default

    // only worry about ready queue here
    if(R_head == NULL){ //first item
        R_head = new_process;
        R_tail = new_process;
        new_process->next = NULL;
        new_process->previous = NULL;
    }else{ // not first item
        new_process->previous = R_tail;
        new_process->next = NULL;
        R_tail->next = new_process;
        R_tail = new_process;
    }
}

void MoveProcess(Process *new_process){ // add to i/o, remove from ready
    new_process->state = 1; // i/o 

    // add to i/o queue
    if(I_head == NULL){ //first item
        I_head = new_process;
        I_tail = new_process;
        new_process->next = NULL;
        new_process->previous = NULL;
    }else{ // not first item
        new_process->previous = I_tail;
        new_process->next = NULL;
        I_tail->next = new_process;
        I_tail = new_process;
    }

    // remove from ready queue
    Process *pointer = R_head; // temporary pointer to find the node we want

    while(pointer != NULL) {
        if(pointer->pid == new_process->pid){ // found the target
            if (pointer == R_head){ //target is head (easy)
                    R_head = pointer->next; 
                    if (R_head != NULL) {
                        R_head->previous = NULL;
                    }
                } 
            else if(pointer == R_tail){ // target is tail (also easy)
                R_tail = pointer->previous; // Move tail to previous
                if (R_tail != NULL) {
                    R_tail->next = NULL; // Update next of new tail
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

void ReturnProcess(Process *new_process){ //add to ready, remove from i/o
    new_process->state = 0; // ready

    // add to ready queue
    if(I_head == NULL){ //first item
        R_head = new_process;
        R_tail = new_process;
        new_process->next = NULL;
        new_process->previous = NULL;
    }else{ // not first item
        new_process->previous = I_tail;
        new_process->next = NULL;
        R_tail->next = new_process;
        R_tail = new_process;
    }

    // remove from i/o queue
    Process *pointer = I_head; // temporary pointer to find the node we want

    while(pointer != NULL) {
        if(pointer->pid == new_process->pid){ // found the target
            if (pointer == I_head){ //target is head (easy)
                    I_head = pointer->next; 
                    if (I_head != NULL) {
                        I_head->previous = NULL;
                    }
                } 
            else if(pointer == I_tail){ // target is tail (also easy)
                I_tail = pointer->previous; // Move tail to previous
                if (I_tail != NULL) {
                    I_tail->next = NULL; // Update next of new tail
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

void SimulateProcess(Process *new_process){ // add to current, remove from ready
    new_process->state = 2; // running

    //add to current queue
    if(head == NULL){ //first item
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

    // remove from ready queue
    Process *pointer = R_head; // temporary pointer to find the node we want

    while(pointer != NULL) {
        if(pointer->pid == new_process->pid){ // found the target
            if (pointer == R_head){ //target is head (easy)
                    R_head = pointer->next; 
                    if (R_head != NULL) {
                        R_head->previous = NULL;
                    }
                } 
            else if(pointer == R_tail){ // target is tail (also easy)
                R_tail = pointer->previous; // Move tail to previous
                if (R_tail != NULL) {
                    R_tail->next = NULL; // Update next of new tail
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

void InterruptProcess(Process *new_process){ //remove from current, add to ready
    new_process->state = 0; // ready

    // remove from current
    Process *pointer = head; // temporary pointer to find the node we want

    while(pointer != NULL) {
        if(pointer->pid == new_process->pid){ // found the target
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

    // add to ready queue
    if(I_head == NULL){ //first item
        R_head = new_process;
        R_tail = new_process;
        new_process->next = NULL;
        new_process->previous = NULL;
    }else{ // not first item
        new_process->previous = I_tail;
        new_process->next = NULL;
        R_tail->next = new_process;
        R_tail = new_process;
    }

}

void TerminateProcess(Process *new_process){ // remove from all queues
    new_process->state = -1; // special outside case to shwocase termination
    
    // remove from current
    Process *pointer = head; // temporary pointer to find the node we want

    while(pointer != NULL) {
        if(pointer->pid == new_process->pid){ // found the target
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

    // remove from ready queue
    Process *pointer2 = R_head; // temporary pointer to find the node we want

    while(pointer2 != NULL) {
        if(pointer2->pid == new_process->pid){ // found the target
            if (pointer2 == R_head){ //target is head (easy)
                    R_head = pointer2->next; 
                    if (R_head != NULL) {
                        R_head->previous = NULL;
                    }
                } 
            else if(pointer2 == R_tail){ // target is tail (also easy)
                R_tail = pointer2->previous; // Move tail to previous
                if (R_tail != NULL) {
                    R_tail->next = NULL; // Update next of new tail
                }
            } 
            else{ // target is in middle (more complex)
                pointer2->previous->next = pointer2->next;
                if (pointer2->next != NULL) {
                    pointer2->next->previous = pointer2->previous;
                }
            }
        }
        pointer2 = pointer2->next; // move pointer along
    }

    // remove from i/o queue
    Process *pointer3 = I_head; // temporary pointer to find the node we want

    while(pointer3 != NULL) {
        if(pointer3->pid == new_process->pid){ // found the target
            if (pointer3 == I_head){ //target is head (easy)
                    I_head = pointer3->next; 
                    if (I_head != NULL) {
                        I_head->previous = NULL;
                    }
                } 
            else if(pointer3 == I_tail){ // target is tail (also easy)
                I_tail = pointer3->previous; // Move tail to previous
                if (I_tail != NULL) {
                    I_tail->next = NULL; // Update next of new tail
                }
            } 
            else{ // target is in middle (more complex)
                pointer3->previous->next = pointer3->next;
                if (pointer3->next != NULL) {
                    pointer3->next->previous = pointer3->previous;
                }
            }
        }
        pointer3 = pointer3->next; // move pointer along
    }    
}

void Process_Flow_Sim(Process *new_process){

    AddProcess(new_process); // requests i/o
    MoveProcess(new_process); // moves to i/o
    SimulateProcess(new_process); // complete i/o
    InterruptProcess(new_process); // returns to ready

    // not entirely sure if it will work in this order or if I read part 4 of this question wrong

}

int main(){

    Process *test_process = (Process *)malloc(sizeof(Process)); // create new process

    Process_Flow_Sim(test_process);

    return 0;
}