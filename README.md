# easy-cpp-profiler
a simple header file based profiler for c++. still under development!

# how to use?

## to measure runtime:

```c++
...
PROF_START(identifier, comment);
...
PROF_END(identifier);
...
```

example:
```c++
PROF_START(calculatePow, "calculating pow");
pow(12, 58);
PROF_END(calculatePow);
```
if the runtime is bigger than 0.5 sec the output would be, e.g.:
```
PROFILER DURATION           calculating pow 0.7894 SECS
```

## to measure runtime in a loop and overall:

```c++
...
PROF_START(identifier, comment);
for (...) {
  ...
  PROF_LAP(identifier);
}
PROF_END(identifier);
...
```

example:
```c++
PROF_START(calculatePow, "calculating pow");
for (int i = 1; i < 58; i++) {
  pow(i, 58);
  PROF_LAP(calculatePow);
}
PROF_END(calculatePow);
```

if the runtime is bigger than 0.5 sec per iteration or the overall runtime the output would be, e.g.:
```
PROFILER LAP DURATION       calculating pow 0.693 SECS
PROFILER LAP DURATION       calculating pow 0.7027 SECS
...
PROFILER LAP DURATION       calculating pow 0.7894 SECS
PROFILER DURATION           calculating pow 8.3529 SECS
```

## profiling with custom threshold of seconds and not 0.5:

this is very simple, just instead of

```c++
PROF_START(identifier, comment);
```

use

```c++
PROF_START_T(identifier, comment, threshold);
```

example

```c++
PROF_START_T(calculatePow, "calculating pow", 0.3);
pow(12, 58);
PROF_END(calculatePow);
```

now the threshold for the runtime is 0.3 seconds.

## print debug information:

during development it is often useful to print out the file, the function and the line of code where the current execution is.

```c++
PROF_DEBUG();
```

will print out, e.g.:
```
test.cpp : int main(int, char**) : 5
```
