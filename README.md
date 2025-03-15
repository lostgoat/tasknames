# tasknames

Build and run:
```
make && gdb threadnames
```

Printing thread names results in:
```
(gdb) info thread
  Id   Target Id                                           Frame 
* 1    Thread 0x7ffff7d91740 (LWP 91744) "threadnames"     0x00007ffff7e31be2 in ?? () from /usr/lib/libc.so.6
  2    Thread 0x7ffff7d906c0 (LWP 91747) "NameThatIsTooLo" 0x00007ffff7e31be2 in ?? () from /usr/lib/libc.so.6
  3    Thread 0x7ffff758f6c0 (LWP 91748) "NameThatIsTooLo" 0x00007ffff7e31be2 in ?? () from /usr/lib/libc.so.6
  4    Thread 0x7ffff6d8e6c0 (LWP 91749) "NameThatIsTooLo" 0x00007ffff7e31be2 in ?? () from /usr/lib/libc.so.6
  5    Thread 0x7ffff658d6c0 (LWP 91750) "NameThatIsTooLo" 0x00007ffff7e31be2 in ?? () from /usr/lib/libc.so.6
  6    Thread 0x7ffff5d8c6c0 (LWP 91751) "NameThatIsTooLo" 0x00007ffff7e31be2 in ?? () from /usr/lib/libc.so.6
  7    Thread 0x7ffff558b6c0 (LWP 91752) "NameThatIsTooLo" 0x00007ffff7e31be2 in ?? () from /usr/lib/libc.so.6
  8    Thread 0x7ffff4d8a6c0 (LWP 91753) "NameThatIsTooLo" 0x00007ffff7e31be2 in ?? () from /usr/lib/libc.so.6
  9    Thread 0x7fffeffff6c0 (LWP 91754) "NameThatIsTooLo" 0x00007ffff7e31be2 in ?? () from /usr/lib/libc.so.6
```

Ideally this would instead produce the full name for the task, e.g.:
```
NameThatIsTooLongForComm[91753]
```
