README for Cryptech 
========================
*cryptech* is an open source software. Current version is 0.3.1, built with GTK+ 3.24 in C.

## Launching the app
Navigate to folder:
```bash
$ cd cryptech
```

Then run binary file for the app:
```bash
$ ./cryptech
```

## Notes

*Please don't forget that this is still work in progress and that bugs can lead to complete loss of selected files.*

The goal of this project is to learn how to build GNOME software throught fun and interesting topics such as cyber security.

The encryption techniques used in this version are *OBSOLETE* so be careful out there and dont try anything stupid! 

## Having fun 
If your sole purpose in life is destroying the hard work done by large teams of devs such as no one…
Then you will have a blast messing around with the file [`interface.ui`](./interface.ui) or [main.c](./main.c), at the heart of the app.
Have fun!

## Contribution
If you are still reading this then as the prophecy foretold you must be the chosen one! Keep in mind that this a student project and the goal is to learn how to build an open-source software, but feel free to contribute any way shape or form. The main file is `main.c` please keep the naming of files as they are.

Make sure you have the GTK+3 libraries installed before compiling, it will produce an error otherwise.

Install GTK+3 libraries:

- In Debian-based distributions:
```bash
$ apt-get install libgtk-3-dev
```
- In Arch-based distributions:
```bash
$ pacman -S gtk3
```

Compiling :
```bash
$ make cryptech
```

Don't forget that `git blame` is easy to use so if you try anning stupid, we will look for you, we will find you and we will blame you!
