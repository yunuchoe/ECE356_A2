ECE 355 - Assignment 2
By: Yunu Choe - V01008760

For 1-4 and 8-9, see attached .c files for code and comments
For 6-7, see answers in this .txt files

1.  Made a generic function based on parameters I thought would make sense. Should work in theory but 
    there was nothing really to test. I also mentioned that I used an prior assignmnet as refernece to 
    get the doubly linked list. 

2.  Similar to above. I made the functions in a way that made sense. I seperated the queues and cpu into seperated
    heads and tails to simulate three distinct doubly linked lists and modifed them accordingly.

3.  Formatted to print exatly as in the assignment sheet. Not sure if its a bug or something but when I first ran it,
    the results were scrambled but seemingly got fixed upon recompiling. 

4.  Should also operate just as shown in the assignment sheet but notsure how to handle edge cases (i.e 1)
    in a formatting/prinitng sense. However, function works fine to get the result and utilizes piping as disccused 
    in office hours.
    (I did account for integers < 1 however as an edge case)

5.  seems very simple but I think what I have is what is desired. A very simple fork demo

// my short answers
6.  An orphan, as the name suggests, is a child process in which it cannot find its parent process, most likely because
    the parent has been terminated before the child has terminated/ finished its work. A zombie, as the name suggest, is
    almost like its neither alive or dead. Instead it is something else that does not quite make sense. A zomebie is a  
    child process that has finished but the parent is unaware of the fact and was not waited by the parent. To remedy
    this, the parent should always be using the wait() function so that it alwasy knows when a child is finished. Doing
    so will also grant the exit status which may be relevant information in some cases.

7.  If the return value of a fork() or exec() is -1 (can use < 0 for simplicity), then we know that the fork/exec 
    has failed. This is why we alwasy check if the value is < 0 first so that we know we have something to work with.
// end short answers

8.  should work just as in the assignment sheet. I also think I tested all the edge cases.

9.  I picked 10 000 000  as it seemed a good balance between getting 3.14(close to pi) and not taking too long to run
