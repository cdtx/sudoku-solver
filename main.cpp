#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define BLOCK_SIZE 3
#define SIZE (BLOCK_SIZE*BLOCK_SIZE)

using namespace std;

/* Minimal container for a value from 1 to 9 */
class Cell {
public:
    int value = 0;
    int candidates[SIZE];
    Cell(char &str_value) {
        int value;

        value = str_value - '0';
        if (value != 0) {
            this->fix_value(value);
        }
        else {
            // Initialize all candidates to 1 (all value possibles at start)
            this->value = value;
            fill_n(this->candidates, SIZE, 1);
        }
    }
    int count_candidates(void) {
        int res = 0;
        for(int i=0 ; i<SIZE ; i++) {
            if (this->candidates[i] == 1) {
                res++;
            }
        }
        return res;
    }
    int possible(int value) {
        return this->candidates[value-1];
    }
    void fix_value(int value) {
        if (this->value != 0) {
            cout << "ERROR!" << endl;
        }
        this->value = value;
        for(int i=0 ; i<SIZE ; i++) {
            // No more candidates
            this->candidates[i] = 0;
        }
    }
    // Useful for debug purposes
    void display_candidates(void) {
        for(int i=0 ; i<SIZE ; i++) {
            cout << this->candidates[i];
        }
        cout << endl;
    }
};

/* Combination of 9 Cell, line or square */
class Block {
public:
    Cell *cells[SIZE];

    int reduce(void) {
        int nReduce = 0;    // Number of reduce operations done
        // List fixed values
        int fixed_values[SIZE] = {0};
        for(int i=0 ; i<SIZE ; i++) {
            if (this->cells[i]->value != 0) {
                fixed_values[this->cells[i]->value - 1] = 1;
            }
        }
        // Remove fixed values of every cell candidates
        for(int i=0 ; i<SIZE ; i++) {
            Cell *cell = this->cells[i];
            for(int j=0 ; j<SIZE ; j++) {
                if (fixed_values[j]==1 && cell->candidates[j]==1) {
                    cell->candidates[j] = 0;
                    nReduce += 1;
                }
            }
        }
        return nReduce;

    }

    int fix(void) {
        // A cell has only one candidate -> fix it
        for(int i=0 ; i<SIZE ; i++) {
            Cell *cell = this->cells[i];
            if (cell->count_candidates() == 1) {
                for(int j=0 ; j<SIZE ; j++) {
                    if (cell->candidates[j] == 1) {
                        cell->fix_value(j+1);
                        return 1;
                    }
                }
            }
        }

        // A cell is the only one with a possibility -> fix it
        int possibles[SIZE];
        int nPossibles;
        // For each value from 1 to 9, test all cells in the block to see how many can host the value.
        // If only one can host, bingo !
        for(int value=0 ; value<SIZE ; value++) {
            fill_n(possibles, SIZE, 0);
            nPossibles = 0;
            for(int i=0 ; i<SIZE ; i++) {
                Cell *cell = this->cells[i];
                if (cell->possible(value+1)) {
                    possibles[i] = 1;
                    nPossibles++;
                }
            }
            if (nPossibles == 1) {
                for(int j=0 ; j<SIZE ; j++) {
                    if(possibles[j] == 1) {
                        this->cells[j]->fix_value(value+1);
                        return 1;
                    }
                }
            }
        }


        return 0;
    }

    // Useful for debug purposes
    void display(void) {
        for(int i=0 ; i<SIZE ; i++) {
            cout << this->cells[i]->value;
        }
        cout << endl;
    }
};

class Grid {
public:
    Cell *cells[SIZE*SIZE];
    Block *blocks[3*SIZE];
    string input;

    void fill(void) {
        // Read the whole grid as one line
        for (int i = 0; i < SIZE; i++) {
            string line;
            getline(cin, line);
            this->input += line;
        }
        // For each input value, create a cell
        for (int i = 0; i < SIZE*SIZE; i++) {
            this->cells[i] = new Cell(this->input[i]);
        }
        // Create the Block and assign them Cell
        // lines
        for (int i=0 ; i<SIZE ; i++) {
            Block *blk = new Block();
            blocks[0*SIZE + i] = blk;
            for (int j=0 ; j<SIZE ; j++) {
                Cell *cell = this->cells[i*SIZE + j];
                blk->cells[j] = cell;
            }
            // blk->display();
        }
        // columns
        for (int i=0 ; i<SIZE ; i++) {
            Block *blk = new Block();
            blocks[1*SIZE + i] = blk;
            for (int j=0 ; j<SIZE ; j++) {
                Cell *cell = this->cells[i + j*SIZE];
                blk->cells[j] = cell;
            }
            // blk->display();
        }
        // squares
        for (int i_base=0 ; i_base<BLOCK_SIZE ; i_base++) {
            for (int i_offset=0 ; i_offset<BLOCK_SIZE ; i_offset++) {
                int i = i_base*BLOCK_SIZE + i_offset;

                Block *blk = new Block();
                blocks[2*SIZE + i] = blk;
                for (int j=0 ; j<BLOCK_SIZE ; j++) {
                    for (int k=0 ; k<BLOCK_SIZE ; k++) {
                        Cell *cell = this->cells[i_base*SIZE*BLOCK_SIZE + i_offset*BLOCK_SIZE + j*SIZE + k];
                        blk->cells[j*BLOCK_SIZE + k] = cell;
                    }
                }
                // blk->display();
            }
        }
        
    }

    int reduce(void) {
        int nReduce = 0;
        for (int i=0 ; i<3*SIZE ; i++) {
            nReduce += this->blocks[i]->reduce();
        }
        return nReduce;
    }
    int fix(void) {
        int nFix = 0;
        for (int i=0 ; i<3*SIZE ; i++) {
            nFix = this->blocks[i]->fix();
            if(nFix > 0) {
                break;
            }
        }
        return nFix;
    }

    void display(void) {
        for (int i=0 ; i<SIZE ; i++) {
            for (int j=0 ; j<SIZE ; j++) {
                cout << this->cells[i*SIZE + j]->value;
            }
            cout << endl;
        }
    }
};

int main()
{
    int nOp;

    Grid *grid = new Grid();
    grid->fill();
    cout << "Grid :" << endl;
    grid->display();
    cout << endl;
    
    do {
        nOp = 0;
        nOp += grid->reduce();
        nOp += grid->fix();
    } while(nOp > 0);

    cout << "Grid :" << endl;
    grid->display();
    cout << endl;
}

