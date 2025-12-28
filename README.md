# Console Workout Tracker (C++)

This is a simple console-based application I built to track my gym workouts. The main goal of this project was to practice **C++ file handling** and working with **data structures**.

## Features
* **Add new workouts:** Records date, exercise name, weight, reps, and sets.
* **Data Persistence:** Automatically saves and loads data using a CSV file (`edzesek.csv`), so data isn't lost after closing the program.
* **List & Delete:** You can view history and delete entries by index.
* **Input handling:** Basic handling of user inputs (e.g. reading strings with spaces).

## How it works
The program uses standard C++ libraries (`<vector>`, `<fstream>`, `<sstream>`).
* Data is stored in a `struct` and managed in a `std::vector` during runtime.
* The CSV parser reads the file line-by-line and splits data by commas.

## How to run
You can compile it with any standard C++ compiler. For example, using g++:

```bash
g++ workout_tracker.cpp -o tracker
./tracker
