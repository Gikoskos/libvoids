# EduDS

A collection of data structures implemented in C (EduDS = Educational Data Structures).

## Building

Create a new `build` folder in the root of the repository, and run

    cmake ..
from inside that folder. For example on a Linux terminal:

```
mkdir build && cd build && cmake ..
```

on Windows cmd.exe:

```
mkdir build & cd build & cmake ..
```

If you'd like to build a DLL/so instead of a static library (which is the default):

```
cmake .. -DBUILD_SHARED_LIBS=ON
```

If you'd like to get MinGW makefiles instead of Visual Studio project files on Windows (which is the default):

```
cmake .. -G "MinGW Makefiles"
```

The Debug build, builds all the tests together with the library, and not separately, and the final binary has debugging symbols:

```
cmake .. -DCMAKE_BUILD_TYPE=Debug
```

## Data Structures

- [x] Singly linked list
- [x] Singly linked list with sentinel
- [x] Doubly linked list
- [x] Doubly linked list with sentinel
- [x] Circular singly linked list
- [x] Circular doubly linked list
- [x] Circular buffer
- [x] FIFO
- [x] Stack
- [ ] Double ended queue (dequeue)
- [x] Binary search tree (unbalanced)
- [x] AVL tree
- [ ] Treap
- [ ] Trie
- [ ] Heap
- [ ] Binomial heap
- [ ] B-tree
- [x] Red black tree
- [x] Association List
- [x] Hashing with chaining
- [x] Hashing with linear probing and optional rehashing
- [x] Hashing with quadratic probing and mandatory rehashing (in case load factor >= 0.5)

## Libs used

C99 standard library

[xxHash for getting a hashcode out of data of arbitrary length (it's built as part of the library, not separately)](https://github.com/Cyan4973/xxHash/)

### LICENSE

MIT License for all files, except xxhash.c and xxhash.h which are BSD licensed.

EduDS (C) 2016-2017 <georgekoskerid@outlook.com>
