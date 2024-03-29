C++ sudoku solver for the game at https://www.codingame.com/ide/puzzle/sudoku-solver

To satisfy the online IDE, the whole dev will be done in one file

# To build
```
$ make clean all
```

# To test
```
make test_0x
```
and for all tests
```
make tests
```

# Work timeline
I choosed to host the projet on github, so it's easier to track evolutions and validate basics of my git knowledges.

Of course I didn't searched neither the solution neither any clue on Google.

## First idea
- I call **Cell** the minimal container for a value from 1 to 9
- I call **Block** a combination of 9 **Cell**, line or square
- A same **Cell** will be part of 3 **Block** (2 lines and a square)

For each **Cell**, I will keep track of the possible values (candidates), starting at 123456789, and then reduce the list by iterating every **Block**.

### Algo
For each **Block**
- Reduce()
        - List fixed values
        - Remove fixed values from all **Cell** candidates
- Fix()
  - A cell has one candidate -> fix it
  - A cell is the only one with a candidate across the block -> fix it

I'm aware that this method will block if it becomes necessary to choose "randomly" between 2 scenarios. So I'm not sure it will solve the most difficults sudoku. However, after having played some grids, it does not happen on easy ones.

So I choose to implement this and see later if improvemensts are necessary.

### Step
I wrote the classes and the code that parses the input, spreads values into **Cells**, and create **Block**

Quite scolar job, as usual picking values in an array is an index mess...

### Step
Wrote the *reduce* method in the **Block** class.

In order to not embed a List library, I choosed to not use dynamic length lists, instead every cell's candidates list is static, size=9, and values from 1 to 9 is a value 0/1 at the index given by the value.
(1111111111 for all values possibles, 0111111111 for the value 1 no more a candidate)

The reduce procedure works for lines and squares.

I quick tested it by watching the first cell's candidates after a run 

### Step
Implemented the fix method as imagined above.

It *almost worked* quickly. Then I losed some time figuring out why the same value appeared sometime twice on the same line. Until I understood I have to stop the *fix* process imediately a value is set, and revaluate all the candidates.

I now can see the test 01 working fine.



