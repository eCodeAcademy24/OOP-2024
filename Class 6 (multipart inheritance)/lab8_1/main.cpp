//Следете ги упатствата во кодот.
//
//For example:
//Input
//0
//Result
//Drawing a shape.
//Drawing a rectangle.

#include <iostream>

using namespace std;

class Shape {
public:
    virtual void draw() {
        cout << "Drawing a shape.\n";
    }
};

// Define the Rectangle class inheriting from Shape
class Rectangle : public Shape {
public:
    void draw() override {
        cout << "Drawing a rectangle.\n";
    }
};

int main() {
    Shape* shape;

    // Instantiate an object of the Shape class and let the pointer shape point to it
    shape = new Shape;

    // Call the draw function through the pointer shape
    shape->draw();

    // Instantiate an object of the Rectangle class and let the pointer shape point to it
    delete shape; // Free the memory
    shape = new Rectangle;

    // Call the draw function through the pointer shape
    shape->draw();

    delete shape; // Free the memory

    return 0;
}
