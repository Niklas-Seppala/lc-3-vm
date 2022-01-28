# LC-3 Virtual Machine

## Virtual machine for Little Computer 3

[LC-3](https://en.wikipedia.org/wiki/Little_Computer_3) is a type of computer educational programming language, an assembly language, which is a type of low-level programming language. [wikipedia]

This was a great learning experience. Thanks belong to [justinmeiners](https://github.com/justinmeiners) and [nomemory](https://github.com/nomemory) for the inital idea and guidance.<br>
I still have assembler and debugger on my todo list.

#### Demo (Linux)
```bash
make
out/lc3vm demos/2048.obj
````
![image](https://user-images.githubusercontent.com/66251857/151396365-865ba8b7-d417-4ef9-9fa6-6b55d97157ff.png)

##### Debug
`
make DEBUG=1
`
##### Runtime memory address, registery & opcode validity asserts
`
make RT_ASSERT=1
`

#### Links
https://www.cs.utexas.edu/users/fussell/courses/cs310h/lectures/Lecture_10-310h.pdf <br>
https://justinmeiners.github.io/lc3-vm/supplies/lc3-isa.pdf <br>
https://www.andreinc.net/2021/12/01/writing-a-simple-vm-in-less-than-125-lines-of-c#the-main-memory
