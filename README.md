# FiniteStateAutomata
 Программа для считывания недетеминированного автомата из файла и применения к нему алгоритма детерминизации.
## Формат файла
     0 1             // алфавит через пробел
    - A 0:B 0:D 1:B  // список состояний, где + означает финальное,
    - B 0:C 1:B 1:C  // на первой строке всегда стартовое, и переходы представлены в виде
    - C 0:D 1:A      // <символ алфавита>:<куда переход>
    + D              // при отсутствии переходов пробел после навзвания состояния лучше не оставлять
## Что можно сделать
### Конструкторы
Можно создать автомат с пустым конструктором и затем вызвать метод readFromFile, но это бессмысленно, поэтому лучше использовать конструктор, который сразу это делает:
    
    FiniteAutomata automata("automata3.txt");

### Методы
На данный момент доступно 3 метода: детерминизация, печать таблицы переходов на экран и проверка слова на принадлежность алфавиту:
    
    automata.determine();
    automata.printTransitionFunction();
    automata.recognize("input string");
