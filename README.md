# Algorithms
C++ Algortihms and Data Structures for `CC232`.

Almost all algorithms use iterators and the defined data structures use templates, so you can use each algorithm in a variety of containers.


# Usage
There are several examples (in [tests](https://github.com/glozanoa/algorithms/tree/master/tests) directory) that show you how you can use develped algorithms and  data structures.

```
EXAMPLES STRUCTURE
|- base   # This directory contains examples of how to use defined data structures
|- sort   # This directory contains examples of how to use sort algorithms
|- seach  # This directory contains examples of how to use search algorithms
|- data   # This directory contains data to test algorithms efficiency
```


# Compilation

* To compile all examples:
```bash
make all
```

* To compile examples of `sort` algorithms:
```bash
make sort
```

* To compile examples of `search` algorithms:
```bash
make search
```

* To compile examples that test data structures:
```bash
make base
```

# Utilities
In [dgen](https://github.com/glozanoa/algorithms/tree/master/dgen) (*data generator*) directory you can find useful **python** scripts to generate random data to test algorithms efficiency.

To learn more about what does a script do, run:

```bash
    python3 PATH2SCRIPT -h
```

