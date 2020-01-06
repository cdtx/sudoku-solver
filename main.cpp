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
   int candidates[SIZE] = {1};
   Cell(char &str_value) {
        this->value = str_value - '0';
   }
};

/* Combination of 9 Cell, line or square */
class Block {
public:
    Cell *cells[SIZE];
    // Useful for debug purposes
    void display(void) {
        for(int i=0 ; i<SIZE ; i++) {
            cout << cells[i]->value;
        }
        cout << endl;
    }
};

class Grid {
public:
    Cell *grid[SIZE*SIZE];
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
            grid[i] = new Cell(this->input[i]);
        }
        // Create the Block and assign them Cell
        // lines
        for (int i=0 ; i<SIZE ; i++) {
            Block *blk = new Block();
            blocks[0*SIZE + i] = blk;
            for (int j=0 ; j<SIZE ; j++) {
                Cell *cell = this->grid[i*SIZE + j];
                blk->cells[j] = cell;
            }
            // blk->display();
        }
        // columns
        for (int i=0 ; i<SIZE ; i++) {
            Block *blk = new Block();
            blocks[1*SIZE + i] = blk;
            for (int j=0 ; j<SIZE ; j++) {
                Cell *cell = this->grid[i + j*SIZE];
                blk->cells[j] = cell;
            }
            // blk->display();
        }
        // squares
        for (int i_base=0 ; i_base<BLOCK_SIZE ; i_base++) {
            for (int i_offset=0 ; i_offset<BLOCK_SIZE ; i_offset++) {
                int i = i_base * i_offset;

                Block *blk = new Block();
                blocks[2*SIZE + i] = blk;
                for (int j=0 ; j<BLOCK_SIZE ; j++) {
                    for (int k=0 ; k<BLOCK_SIZE ; k++) {
                        Cell *cell = this->grid[i_base*SIZE*BLOCK_SIZE + i_offset*BLOCK_SIZE + j*SIZE + k];
                        blk->cells[j*BLOCK_SIZE + k] = cell;
                    }
                }
                // blk->display();
            }
        }
        
    }

    void display(void) {
        for (int i=0 ; i<SIZE ; i++) {
            for (int j=0 ; j<SIZE ; j++) {
                cout << grid[i*SIZE + j]->value;
            }
            cout << endl;
        }
    }
};

int main()
{
    Grid *grid = new Grid();
    grid->fill();
    grid->display();
}
