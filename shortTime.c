#include <stdio.h>
#include <conio.h>
#include "shortTime.h"

Clock_tick clock;

// Como ambos os métodos de escalonamento, aqui presentes, utilizam como parametro o tempo restante, foi 
// feito um escalonador generico para realizar o agendamento dos processos
void generic_scheduler(Buffer* buffer){
    if(buffer->current==buffer->last){
        return;
    }

    Process aux;
    int next = buffer->current;
    int i = (next+1)%MAX_SIZE;

    while(i != buffer->last){
        // em caso de impasse, é escolhido o de maior prioridade
        if((buffer->processes[i].time_left < buffer->processes[next].time_left)||
            ((buffer->processes[i].time_left == buffer->processes[next].time_left) &&
            (buffer->processes[i].priority > buffer->processes[next].priority))){
            next=i;
        }
        i = (i+1)%MAX_SIZE;
    }

    aux=buffer->processes[buffer->current];
    buffer->processes[buffer->current]=buffer->processes[next];
    buffer->processes[next]=aux;
}

int add_process(Buffer* buffer, Process processo){
    if((buffer->last+1) % MAX_SIZE == buffer->current){
        return 0;
    }

    buffer->processes[buffer->last] = processo;
    buffer->last = (buffer->last+1) % MAX_SIZE;
    return 1;
}

int remove_process(Buffer* buffer){
    if(buffer->current==buffer->last){
        return -1;
    }

    int aux = buffer->current;
    buffer->current = (buffer->current+1) % MAX_SIZE;
    return aux;
}

// Escalonador Shortest Remaining-Time Next
void scheduler_SRTN(Buffer* buffer){
    if(buffer->processes[buffer->current].time_left==0){ //Processo acababou
        remove_process(buffer);
        generic_scheduler(buffer);
        clock.quantum_size=QUANTUM;
    }else if(clock.quantum_size==0){ //Quantum estourou
        int aux;
        aux = remove_process(buffer);
        if(aux>-1){
            generic_scheduler(buffer);
            add_process(buffer, buffer->processes[aux]);
            clock.quantum_size=QUANTUM;
        }
    }
}

// Escalonador Shortest Process Next
void scheduler_SPN(Buffer* buffer){
    if(buffer->processes[buffer->current].time_left==0){
        if(remove_process(buffer)>-1)
            generic_scheduler(buffer);
    }
}

void init_Buffer(Buffer* buffer, ptrFunc type_scheduler){
    buffer->current = 0;
    buffer->last = 0;
    buffer->scheduler = type_scheduler;
}

void init_clock_tick(){
    clock.count = 0;
    clock.quantum_size = QUANTUM;
}

// Retira os dados de um arquivo salvando-os como processos em um vetor  
void get_dados(Process* queue, char* file_name){
    FILE* arq;
    int request, time, priority, i;
    
    arq = fopen(file_name,"r");
    if(arq == NULL){
        printf("\nErro na leitura do arquivo\nVerifique se o arquivo está vazio ou na mesma pasta que o código fonte");
        fclose(arq);
        return;
    }
    
    i=0;
    while((fscanf(arq, "%d%d%d", &request, &time, &priority)!=-1) && i<MAX_PROCESS){
        queue[i].id = i;
        queue[i].requested = request;
        queue[i].time_left = time;
        queue[i].priority = priority;
        i++;
    }
    printf("\n%d processos foram lidos.", i);
    fclose(arq);
}

void print_status(FILE* file, Buffer* buffer){
    if(buffer->current==buffer->last){
        fprintf(file,"Timing: %d \t[Process buffer is empty]", clock.count);
        fprintf(file,"\n-------------------------------------------------------------------------------\n");
        return;
    }

    fprintf(file,"Timing: %d \t Current process: P%d \t ", clock.count, buffer->processes[buffer->current].id);
    fprintf(file, "Time left: %d", buffer->processes[buffer->current].time_left);
    fprintf(file,"\nUnbuffered waiting processes: ");
    for(int i=(buffer->current+1)%MAX_SIZE;i!=buffer->last;i=(i+1)%MAX_SIZE){
        fprintf(file,"P%d ", buffer->processes[i].id);
    }
    fprintf(file,"\n-------------------------------------------------------------------------------\n");

}

// Metodo de ordenacao (Selection Sort) que ordena pelo tempo de requisição
void stSort(Process* queue){
    int i, j, minIndex;
    Process temp;
    
    for (i = 0; i < MAX_PROCESS - 1; i++) {
        minIndex = i;
        for (j = i + 1; j < MAX_PROCESS; j++) {
            if (queue[j].requested < queue[minIndex].requested) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            temp = queue[i];
            queue[i] = queue[minIndex];
            queue[minIndex] = temp;
        }
    }
}

void kernel(Buffer* buffer, Process* queue, char* file_name){
    int i;
    int last_process = 0; // variavel de controle para adicao de processos ao buffer
    int count_process = MAX_PROCESS; // variavel de controle para encerramento do looping de rotina
    ptrFunc foo = buffer->scheduler;
    FILE* arq = fopen(file_name,"w");
    
    // a fila deve estar ordenada para que os processos sejam adicionados ao
    // buffer de maneira correta
    stSort(queue); 

    while(1){
        i = last_process;
        while(queue[i].requested <= clock.count && i<MAX_PROCESS){
            if(!(add_process(buffer,queue[i])))
                break;
            count_process--;
            i++;
        }
        last_process = i;

        foo(buffer); // Agendamento
        
        print_status(arq, buffer);

        //Avanço do tempo
        clock.count++;
        buffer->processes[buffer->current].time_left--;
        clock.quantum_size--;

        //Finaliza Kernel
        if( !(count_process) && buffer->current==buffer->last){
            printf("\nOperacao finalizada! \nQuantidade de processos que foram ao buffer: %d", MAX_PROCESS-count_process);
            fclose(arq);
            return;
        }
    }
    fclose(arq);
}
