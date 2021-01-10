# FiniteStateAutomata
  This is a base realization with the easiest determinization algorithm, but this solution can be expanded into something more complex.
## File format
     0 1             // Alphabet (space separated)
    - A 0:B 0:D 1:B  // State list, where the first line is starting state;
    - B 0:C 1:B 1:C  // "+" means final state and "-" - non-final;
    - C 0:D 1:A      // transitions are introduced as <symbol>:<target state>;
    + D              // if there are no transitions, don't leave space after state name (maybe someday I will fix this :))
## Functionality
### Constructors
 You can create an automata with an empty constructor and then call the readfromfile method, but this is pointless, so it's better to use a constructor that does this directly:
    
    FiniteAutomata automata("automata3.txt");

### Methods
At the moment, there are only 3 methods available:
    
    automata.determine();
    automata.printTransitionFunction();
    automata.recognize("input string");

I think their names speak for themselves :)
