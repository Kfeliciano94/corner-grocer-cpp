# Corner Grocer Item Tracker

A C++ console application developed for **CS 210: Programming Languages** at Southern New Hampshire University. It reads a grocery purchase list and helps users review how frequently each item was purchased.

## Features
- Search for an item's purchase frequency (case-insensitive)
- Display the purchase count for every item
- View a text-based histogram using asterisks
- Automatically write a frequency backup to `frequency.dat`
- Validate menu selections and report file errors

## Technologies
C++ standard library, file input/output, `std::map`, loops, functions, and classes.

## How to run
From the folder containing `main.cpp` and `CS210_Project_Three_Input_File.txt`:

```bash
g++ -std=c++11 main.cpp -o corner-grocer
./corner-grocer
```

On Windows, run `corner-grocer.exe` instead of `./corner-grocer`.

The program expects the input file in the **current working directory** and generates `frequency.dat` there.

## What I practiced
Reading and writing text files, counting items with a map, organizing program logic into a class and functions, and handling invalid input.

## About
Academic coursework project. Source code is provided for portfolio review; check course academic-integrity requirements before publishing publicly.
