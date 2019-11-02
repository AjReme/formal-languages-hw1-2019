## Formal languages course, Practice 1, Variant 9

### Statement

You're given a string ***α***, symbol ***x*** and natural number ***k > 0***. ***α*** represents regular expression in Reverse Polish notation. Alphabet is ***{ a, b, c }***. Possible operators are:

- ***.*** (Concatenation);
- ***+*** (Union);
- ***\**** (Repeat);

Return the smallest size of the word that matches the regular expression that has ***x...xx*** (***k*** times) as substring.

### Looking through possible cases

First of all, we have to decide what information we should store in the operands. Consider this cases:

- `(aa+a)aaa a 3`, ans is `4`;
- `(aa+a)a a 3`, ans is `3`;
- `aaa(aa+a) a 3`, ans is `4`;
- `a(aa+a) a 3`, ans is `3`;

It is easy to notice that we should store **all possible sizes of prefixes and suffixes**, where **"size"** is number of ***x*** repeating in the beginning and ending of the string.

The next problem is:

- `(aa)*a a 3`, ans is `3`;
- `(aa)*a a 4`, ans is `5`;

That means **answer can not be equal exactly to** ***k***.

Let's take a look at this problem:

- `(aaa+aaaaa)* a 15`, ans is `15`;
- `(aaa+aaaaa)* a 14`, ans is `16`;

Here we should solve the equation such as `Ax + By + Cz + ... = k`. Undoubtedly, the best way is only to **brutforce for the solution of equation**.

The last one is:

- `(ad+aaa)* a 7`, ans is `7`;
- `(baa+aaaa)a* a 7`, ans is `7`;
- `a(baa+aaaa)* a 7`, ans is `9`;

That means **words containing only** ***x*** letter are **special**.

We are ready to discuss the solution.

### Algorithm

We'll use stack to parse the expression (It's quite obvious how to do it. If not, go to [cp-algorithms.com](https://cp-algorithms.com/string/expression_parsing.html)). Also, my solution doesn't use the fact that alphabet is ***{ a, b, c }***. The method uses **divide and conqueror** approach.

Hereinafter ***x*** = `a` for instance.

We store for each operand:

- Sizes of every possible prefix count and if there are more than 1 possible - smallest size. Examples:

	* `aaaax` is `(4 5)`;
	* `at+abb` is `(1 2)`;
	* `aab+aacc+aaac` is `{ (2 3), (3 4) }`;

- Sizes of every possible suffix count and if there are more than 1 possible - smallest size. Examples:

	* `xaa+bbaa` is `(2 3)`;
	* `xyz` is `(0 3)`;

- Sizes of all words containing only ***x***. Examples:

	* `aaaa+aaa+aa+a` is `{ 1, 2, 3, 4 }`;
	* `1` is `{}`;

- Current best answer. Example:

	* `baaab+bbbaaa` is `5` when `k = 3`.

- Current **smallest** word (*any word*) achievable. Example:

	* `(aba+ca)*d` is `1`;

How to update answer for each operator?

- ***.*** (Concatenation):
	
	* Checking if answer exists (by brutforcing all possible pairs **suffix-prefix**, **repeating-prefix**, **suffix-repeating**, **repeating-repeating**) and updating if needed;
	* Union of **prefixes** and **suffixes**;
	* Union of **repeating** words;

- ***+*** (Union):

	* Updating **answer** by smallest possible value;
	* Union of **prefixes** and **suffixes**;
	* Union of **repeating** words;

- ***\**** (Repeat):

	* **Solving equation by brutforce** (*look at third case*). Also bear in mind that there can be any prefix and suffix of the word at the ending.
	* Adding **empty word**.

Base of induction:

- `1`: prefix `{ (0 0) }`, suffix `{ (0 0) }`, containing only ***x*** `{}`, answer is `-1`.
- `C` (some character):

	* Prefix is `{ (0 0) }` if `C != x`, `{}` otherwise;
	* Suffix is `{ (0 0) }` if `C != x`, `{}` otherwise;
	* Containing only ***x*** is `{}` if `C != x`, `{ 1 }` otherwise;
	* Answer is `-1` if `C != x || k > 1`, `1` otherwise;

### Notes

**Snake case** was used as I prefer it. *Names of main variables are the same as in the statement*. **C++** language was used to implement a solver.

### Library usage

