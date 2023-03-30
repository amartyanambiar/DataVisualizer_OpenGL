# DataVisualizer Using OpenGL

This is a C program that uses OpenGl to visualize data in a 2D environment. 
### The Data
- Google Search Trends for 3 terms -> Lasagna, Lobster and Shrimp.
- Stored in `.csv` files.

## Installation ( Ubuntu )
1. Clone the repository:
```bash
git clone https://github.com/amartyanambiar/DataVisualizer_OpenGL.git
```

2. Install OpenGL on your system:
```bash
sudo apt-get install freeglut3-dev
```

3. Compile the code:
```bash
gcc dataViz.c -lGL -lGLU -lglut -lm
```

4. Run:
```bash
chmod +x a.out
./a.out
```
## Usage
```
Press 1 to choose Dataset - Lasagna
Press 2 to choose Dataset - Lobster
Press 3 to choose Dataset - Shrimp
Press A (Shift+A) to view all graphs together
Right click to Zoom In and Out
Press h to view help screen
Press q to quit
```

