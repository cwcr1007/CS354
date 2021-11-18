#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SHIP{
    int row, column, length;
    char direction;
} SHIP;

typedef struct ATTACK{
    int row, column;
} ATTACK;

// these are the prototype functions developed for our solution.  You are welcome to use them 
// or modify them if you have a different strategy for solving this project.
void Read_Save_Game_File(char *filename, int *rows, int *columns, int *ship_count, SHIP **ships, int *attack_count, ATTACK **attacks);
void Initialize_Board(int rows, int columns, char **board);
void Print_Board(int rows, int columns, char *board);
void Add_Ships(int rows, int columns, char *board, int ship_count, SHIP *ships);
void Process_Attacks(int rows, int columns, char *board, int attack_count, ATTACK *attacks);
void Game_Over(int rows, int columns, char *board);

int main(int argc, char *argv[] ) {

    // verify command line parameters
    if(argc != 2){
        printf("expected usage: %s <save_game_file>", argv[0]);
        exit(1);
    }

    // declare variables - feel free to add additional variables as needed
    char *board = NULL;
    SHIP *ships = NULL;
    ATTACK *attacks = NULL;
    int rows=0, columns=0, ship_count=0, attack_count=0;
    
    // read the save game file
    Read_Save_Game_File(argv[1], &rows, &columns, &ship_count, &ships, &attack_count, &attacks);
    /* Note: Reading the file and using malloc to reserve space for 
     * the data may be easier to do here, in main, rather than in a 
     * function */

    // Generate the board;
    Initialize_Board(rows, columns, &board);
    Print_Board(rows, columns, board);

    // Add Ships to the board;
    Add_Ships(rows, columns, board, ship_count, ships);
    Print_Board(rows, columns, board);
    
    // Process Attacks
    Process_Attacks(rows, columns, board, attack_count, attacks);
    Print_Board(rows, columns, board);
    
    Game_Over(rows, columns, board);
 
    // free memory
    free(board);
    free(ships);
    free(attacks);
    
    return 0;
}

////////////////////////////////////////////
// add comments here
////////////////////////////////////////////
void Game_Over(int rows, int columns, char *board){
    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            if(*(board + i * columns + j) == 'S'){
                printf("Ships remain afloat - game on\n");
                return;
            }
        }
    }
    printf("All ships have been sunk - game over\n");
}

void Process_Attacks(int rows, int columns, char *board, int attack_count, ATTACK *attacks){
    printf("Processing Attacks\n");
    for(int i=0; i<attack_count; i++){
        if((attacks + i)->row > rows || (attacks + i)->row < 0 || (attacks + i)->column > columns || (attacks + i)->column < 0){
            printf("Attack %d is out of bounds - skipping\n", i);
        }
        else{
            if(*(board + (attacks + i)->row * columns + (attacks + i)->column) == 'S'){
                *(board + (attacks + i)->row * columns + (attacks + i)->column) = 'H';
            }
            if(*(board + (attacks + i)->row * columns + (attacks + i)->column) == '.'){
                *(board + (attacks + i)->row * columns + (attacks + i)->column) = 'M';
            }
        }
    }
}

void Add_Ships(int rows, int columns, char *board, int ship_count, SHIP *ships){
    printf("Adding Ships\n");
    for(int i=0; i<ship_count; i++){
        int condition = 1;
        if((ships + i)->direction == 'H'){ // if the ship is horizontal
            for(int j=0; j<(ships + i)->length; j++){
                if((ships + i)->row >= rows || (ships + i)->row < 0 || (ships + i)->column + j >= columns || (ships + i)->column + j < 0){
                    printf("Ship %d is out of bounds - skipping\n", i);
                    condition = 0;
                    break;
                }
                if(*(board + (ships + i)->row * columns + (ships + i)->column + j) == 'S'){
                    printf("Ship %d overlaps another ship - skipping\n", i);
                    condition = 0;
                    break;
                }
            }
            if(condition){
                for(int j=0; j<(ships + i)->length; j++){
                    *(board + (ships + i)->row * columns + (ships + i)->column + j) = 'S';
                }
            }
        }
        else{                               // if the ship is vertical
            for(int j=0; j<(ships + i)->length; j++){
                if((ships + i)->row + j >= rows ||(ships + i)->row + j < 0 || (ships + i)->column >= columns || (ships + i)->column < 0){   
                    printf("Ship %d is out of bounds - skipping\n", i);
                    condition = 0;
                    break;
                }
                if(*(board + (ships + i)->row * columns + j * columns + (ships + i)->column) == 'S'){
                    printf("Ship %d overlaps another ship - skipping\n", i);
                    condition = 0;
                    break;
                }
            }
            if(condition){
                for(int j=0; j<(ships + i)->length; j++){
                    *(board + (ships + i)->row * columns + j * columns + (ships + i)->column) = 'S';
                }
            }
        }   
    }
}

void Initialize_Board(int rows, int columns, char **board){
    printf("Initializing Board\n");
    *board = malloc(rows * columns * sizeof(char));
    // check malloc
    if(*board == NULL){
        printf("Memory allocation failed.\n");
        exit(1);
    }
    for(int i=0; i<rows*columns; i++){
        *(*board + i) = '.';   
    }
}
void Print_Board(int rows, int columns, char *board){
    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            printf("%c", *(board + i * columns + j));
        }
        printf("\n");
    }
    printf("\n");
}


void Read_Save_Game_File(char *filename, int *rows, int *columns, int *ship_count, SHIP **ships, int *attack_count, ATTACK **attacks) {
    printf("Reading Save Game File\n");
    FILE *input = fopen(filename, "r");
    if(!input){
        printf("INPUT File open failed\n");
        exit(1);
    }
    
    // skip the board size line
    char skip_this_text[1000];
    if (!fgets(skip_this_text, 1000, input)) {
        printf("Error reading board size");
        exit(1);}

    // read the board size
    fscanf(input, "%d", rows);
    fscanf(input, "%d", columns);
    fgets(skip_this_text, 1000, input); // read the newline character
    printf("Board Size = (%d, %d)\n",*rows, *columns);

    /*  Complete the rest of the function below - or move the code above to main */
    // read the number of ships
    fgets(skip_this_text, 1000, input); // skip the number of ships line
    fscanf(input, "%d", ship_count);
    fgets(skip_this_text, 1000, input); // read the newline character
    printf("Number of Ships = %d\n",*ship_count);
    
    // allocate memory on heap for SHIP
    *ships = (SHIP*)malloc((*ship_count) * sizeof(SHIP));
    
    // check functionality of malloc
    if (*ships == NULL){
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    
    // read the ship
    char c;
    for (int i=0; i<*ship_count; i++){   
        fscanf(input, "%d", &((*ships + i)->row));
        fscanf(input, "%d", &((*ships + i)->column));
        fscanf(input, "%d", &((*ships + i)->length));
        fscanf(input, "%c", &c);
        fscanf(input, "%c", &c);
        (*ships + i)->direction = c;
        printf("Ship %d: (%d, %d), length = %d, direction %c\n", i, (*ships + i)->row, (*ships + i)->column,(*ships + i)->length, (*ships + i)->direction);
        fgets(skip_this_text, 1000, input); // read the newline character
    }
    // read the attack 
    fgets(skip_this_text, 1000, input); // skip the number of attacks line
    fscanf(input, "%d", attack_count);
    fgets(skip_this_text, 1000, input); // read the newline character
    printf("Number of Attacks = %d\n",*attack_count);
    
    // allocate memory on heap for ATTACK
    *attacks = (ATTACK*)malloc((*attack_count) * sizeof(ATTACK));
    
    // check malloc
    if(*attacks == NULL){
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    
    // read the ATTACK
    for (int i=0; i<*attack_count; i++){
        fscanf(input, "%d", &((*attacks + i)->row));
        fscanf(input, "%d", &((*attacks + i)->column));
        fgets(skip_this_text, 1000, input); // read the newline character
        printf("Attack %d: (%d, %d)\n", i, (*attacks + i)->row, (*attacks + i)->column);     
    }
    printf("\n");
    fclose(input);
}
