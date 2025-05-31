#ifndef SHORT_TIME_SCHEDULER
    #define SHORT_TIME_SCHEDULER
    
    #define MAX_SIZE 10
    #define MAX_PROCESS 20
    #define QUANTUM 3

    /*Definicao do tipo processo:
    - tempo em que foi criado/requisitado
    - tempo necessario para ser concluido
    - prioridade
    */ 
    typedef struct{
        int id;
        int requested; 
        int time_left; 
        int priority; 
    }Process;

    /*Estrutura do Buffer circular:
    - vetor a ser utilizado de forma circular
    - varivel de controle para indicacao do primeiro processo no buffer
    - variavel de controle para indicacao do ultimo processo no buffer
    - ponteiro que retem o escalonador utilizado para aquele buffer
    */
    typedef struct no{
        Process processes[MAX_SIZE];
        int current;
        int last;
        void (*scheduler)(struct no*);
    }Buffer;

    /*Estrutura de controle do quantum:
    - contador
    - tamanho maximo de quantum a ser utilizado por um processo
    */ 
    typedef struct{
        int count;
        int quantum_size;
    }Clock_tick;

    typedef void (*ptrFunc)(Buffer*);

    void scheduler_SRTN(Buffer* buffer);
    void scheduler_SPN(Buffer* buffer);
    void init_Buffer(Buffer* buffer, ptrFunc type_scheduler);
    void init_clock_tick();
    void get_dados(Process* queue, char* file_name);
    void print_status(FILE* file, Buffer* buffer);
    void stSort(Process* queue);
    void kernel(Buffer* buffer, Process* queue, char* file_name);

#endif //SHORT_TIME_SCHEDULER
