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
        // Initialize all candidates to 1 (all value possibles at start)
        fill_n(this->candidates, SIZE, 1);
        this->value = str_value - '0';
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
    int nReduce, nFix;    // Number of operations in a reduce/fix step

    Grid *grid = new Grid();
    grid->fill();
    cout << "Grid :" << endl;
    grid->display();
    cout << endl;
    
    grid->cells[0]->display_candidates();
    nReduce = grid->reduce();
    grid->cells[0]->display_candidates();
}

