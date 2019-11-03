## Formal languages course, Practice 1, Variant 9

### Statement

You're given a string ***α***, symbol ***x*** and natural number ***k > 0***. ***α*** represents regular expression in Reverse Polish notation. Alphabet is ***{ a, b, c, 1 }***. Possible operators are:

- ***.*** (Concatenation);
- ***+*** (Union);
- ***\**** (Repeat);

Return the smallest size of the word that matches the regular expression that has ***x...xx*** (***k*** times) as substring.

### Algorithm

Let's create ***NDA*** using provided regular expression ***α***.

- The base of induction: every symbol creates an automate such as `<q0, symb> -> q1`, `q0` and `q1` are respectively beginning and the ending state of the automate.
- ***.*** (Concatenation): connect the ending and the beginning states of the *automate 1* and *automate 2* with `1` edge respectively. The new beginning is *automate 1* beginning and the new ending is *automate 2* ending.
- ***+*** (Union): create 2 new nodes. The first one (that is a new beginning node) points to beginning of the *automate 1* and *automate 2*. Then connect *automate 1* ending and *automate 2* ending with new ending node. All connections should be done using `1`.
- ***\**** (Repeat): create 2 new nodes. One node (new beginning node) should be connected with the beginning (forward edge) and ending (reverse edge) of *automate*. Then connect it with new ending edge by forward edge. All connections should be done using `1`.

Then, we should find all pairs `<q1, q2>` such as there exists path with ***x^k***. It can be done by **BFS**: add all nodes to the queue with **len = 1**, **current node = v** and **begin node = v**, and until queue is empty:

- If there exists ***x*** edge **(v, u)** - go to the next state with **new len = len + 1** and **new current node = u**.
- If there exists ***1*** edge **(v, u)** - go to the next state with **new len = len** and **current node = u**.

The next step is to create a matrix with pairwise distances between nodes. It can be done with ease using **Floyd algorithm**.

Finally, we iterate over pairs found in step 2, updating answer as `answer = min(answer, distance[begin_node][pair_begin] + k + distance[pair_end][end_node])`.

### Notes

**Snake case** was used as I prefer it. *Names of main variables are the same as in the statement*. **C++** language was used to implement a solver. I didn't use the fact that nonempty part of alphabet contains only ***{ a, b, c }***.

### Library usage

Compile `console_tester` using `src/CMakeLists.txt`. Input should look as follows: `acb..bab.c.*.ab.ba.+.+*a. b 3`.

### Testing

There are some tests provided with the solver. Go to `testing` and execute `CTest` as follows: `cmake CMakeLists.txt && make && ctest`.