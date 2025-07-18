#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <cmath>
#include <fstream>

// Global variables
int t = 0; // Global variable to keep track of the current iteration
int timerInterval = 90; // Set the timer interval to 90 milliseconds (0.09 seconds)
int score = 0; // Score variable
int maxScore = 0; // Maximum score

float oTriangleX = 1.5; // Initial x-coordinate of oTriangle
float oBrickX = 1.5; // Initial x-coordinate of oBrick
float skullBrickY = 1.0; // Initial y-coordinate of the skull brick
bool isJumping = false; // Flag to track if the skull brick is jumping
float jumpSpeed = 0.08; // Speed of the jump
float jumpHeight = 0.5; // Maximum height of the jump
float initialSkullBrickY = 1.0; // Initial Y position for the skull brick

bool collisionDetected = false; // Flag to track collision
int collisionCount = 0; // Counter for collisions

// Function prototypes
void oTriangle();
void oBrick();
void drawBrick();
void drawSkullBrick();
void display();
void timer(int value);
void keyboard(unsigned char key, int x, int y);
void checkGameOver();
void writeMaxScoreToFile(int maxScore);


// Obstacle Triangle (moving)
void oTriangle() {
    glLineWidth(1.0); // Set line width for border

    // Draw border
    glColor3f(1.0, 1.0, 1.0); // White color for border
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.7, -0.775, 0.1); // Adjusted x-coordinate for the first vertex
    glVertex3f(-0.65, -0.525, 0.1); // Adjusted x-coordinate for the second vertex
    glVertex3f(-0.60, -0.775, 0.1); // Adjusted x-coordinate for the third vertex
    glEnd();

    // Draw fill
    glColor3f(0.0, 0.0, 0.0); // Black color for fill
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.7, -0.775, 0.1); // Adjusted x-coordinate for the first vertex
    glVertex3f(-0.65, -0.525, 0.1); // Adjusted x-coordinate for the second vertex
    glVertex3f(-0.60, -0.775, 0.1); // Adjusted x-coordinate for the third vertex
    glEnd();
}

// Obstacle Brick (moving)
void oBrick() {
    glLineWidth(1.0); // Set line width for border

    // Draw border
    glColor3f(1.0, 1.0, 1.0); // White color for border
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.85, -0.85, 0.1);
    glVertex3f(-0.75, -0.85, 0.1);
    glVertex3f(-0.75, -0.75, 0.1);
    glVertex3f(-0.85, -0.75, 0.1);
    glEnd();

    // Draw fill
    glColor3f(0.0, 0.0, 0.0); // Black color for fill
    glBegin(GL_QUADS);
    glVertex3f(-0.85, -0.85, 0.1);
    glVertex3f(-0.75, -0.85, 0.1);
    glVertex3f(-0.75, -0.75, 0.1);
    glVertex3f(-0.85, -0.75, 0.1);
    glEnd();
}

void drawBrick() {
    glLineWidth(2.0); // Set line width for border

    // Draw border
    glColor3f(1.0, 1.0, 1.0); // White color for border
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.9, -0.9, 0.1);
    glVertex3f(-0.8, -0.9, 0.1);
    glVertex3f(-0.8, -0.8, 0.1);
    glVertex3f(-0.9, -0.8, 0.1);
    glEnd();

    // Draw fill
    glColor3f(0.0, 0.0, 0.0); // Black color for fill
    glBegin(GL_QUADS);
    glVertex3f(-0.9, -0.9, 0.1);
    glVertex3f(-0.8, -0.9, 0.1);
    glVertex3f(-0.8, -0.8, 0.1);
    glVertex3f(-0.9, -0.8, 0.1);
    glEnd();
}

void drawSkullBrick() {
    glLineWidth(1.0); // Set line width for border

    // Draw border
    glColor3f(1.0, 1.0, 1.0); // White color for border
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.85, -0.85, 0.1);
    glVertex3f(-0.75, -0.85, 0.1);
    glVertex3f(-0.75, -0.75, 0.1);
    glVertex3f(-0.85, -0.75, 0.1);
    glEnd();

    // Draw fill
    glColor3f(0.0, 0.0, 0.0); // Black color for fill
    glBegin(GL_QUADS);
    glVertex3f(-0.85, -0.85, 0.1);
    glVertex3f(-0.75, -0.85, 0.1);
    glVertex3f(-0.75, -0.75, 0.1);
    glVertex3f(-0.85, -0.75, 0.1);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    // Check if the game is over
    checkGameOver();

    if (collisionDetected) {
        // Display the game over page
        glColor3f(1.0, 1.0, 1.0); // White color for text
        std::stringstream gameOverText;
        gameOverText << "Game Over";
        glRasterPos2f(-0.3, 0.0); // Position the text
        for (char c : gameOverText.str()) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }

        std::stringstream scoreText;
        scoreText << "Score: " << score;
        glRasterPos2f(-0.3, -0.1); // Position the score text
        for (char c : scoreText.str()) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }
    }
    else {
        // Draw the game objects and score
        float yb = 0.20;
        for (int i = 0; i <= 2; i++) {
            yb += 0.15;
            float nb = 0;
            float xb = 0;
            if (t % 2 == 0)
                if (i % 2 == 0)
                    xb = 0.8;
                else
                    xb = 0.5;
            else
                if (i % 2 == 0)
                    xb = 0.5;
                else
                    xb = 0.8;
            for (int j = 0; j <= 11; j++) {
                // Draw brick
                glPushMatrix();
                glTranslatef(xb + nb, yb, 0.8); // Translate the brick
                nb += 0.2;
                glScalef(2, 1.5, 1.5); // Scale down the brick
                drawBrick();
                glPopMatrix();
            }
        }

        if (t % 50 == 0) {
            //oTriangleX = 1.5;
            oBrickX = 1.5;
        }

        //oTriangleX -= 0.05; // Adjust the speed of movement as needed
        oBrickX -= 0.05; // Adjust the speed of movement as needed

        // Draw the oTriangle at the updated x-coordinate
        glPushMatrix();
        glTranslatef(1.5 - 0.5 * (t*20 % 1000)/1000, 0.183, 0.0);
        glScalef(0.75, 0.75, 1.0);
        oTriangle();
        glPopMatrix();

        // Draw the oBrick at the updated x-coordinate
        glPushMatrix();
        glTranslatef(oBrickX, 1.0, 0.0);
        glScalef(0.9, 1.65, 1.0);
        oBrick();
        glPopMatrix();

        glLineWidth(2.0); // Set line width for border

        // Draw border
        glColor3f(1.0, 1.0, 1.0); // White color for border
        glBegin(GL_LINE_LOOP);
        glVertex3f(-1, -0.40, 0.1);
        glVertex3f(1, -0.40, 0.1);
        glVertex3f(1, -0.55, 0.1);
        glVertex3f(-1, -0.55, 0.1);
        glEnd();

        // Draw fill
        glColor3f(0.0, 0.0, 0.0); // Black color for fill
        glBegin(GL_QUADS);
        glVertex3f(-1, -0.40, 0.1);
        glVertex3f(1, -0.40, 0.1);
        glVertex3f(1, -0.55, 0.1);
        glVertex3f(-1, -0.55, 0.1);
        glEnd();

        // Draw the brick with skull design
        glPushMatrix();
        glTranslatef(0.43, skullBrickY, 0.0);
        glScalef(0.9, 1.65, 1.0); // Adjust the scaling factor to match the oBrick
        drawSkullBrick();
        glPopMatrix();

        // Draw the score
        glColor3f(1.0, 1.0, 1.0); // White color for the score
        std::stringstream scoreText;
        scoreText << "Score: " << score;
        glRasterPos2f(-0.95, 0.95); // Position the score at the top left corner
        for (char c : scoreText.str()) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }

        // Draw the collision count
        std::stringstream collisionText;
        collisionText << "Collisions: " << collisionCount;
        glRasterPos2f(-0.95, 0.90); // Position the collision count below the score
        for (char c : collisionText.str()) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }
    }

    glFlush();
}

void timer(int value) {
    if (collisionDetected) return; // Stop the timer if collision is detected

    t++; // Increment the iteration counter
    score += 1; // Increase the score by 1 every iteration

    // Update the skull brick's position if it's jumping
    if (isJumping) {
        skullBrickY += jumpSpeed;
        if (skullBrickY >= initialSkullBrickY + jumpHeight || skullBrickY <= initialSkullBrickY) {
            jumpSpeed = -jumpSpeed; // Reverse the jump direction
        }
        if (skullBrickY <= initialSkullBrickY) {
            skullBrickY = initialSkullBrickY; // Reset to initial position
            isJumping = false; // Stop jumping
            jumpSpeed = fabs(jumpSpeed); // Reset jump speed to positive value
        }
    }

    glutPostRedisplay(); // Request a redisplay of the window
    glutTimerFunc(timerInterval, timer, 0); // Set the timer to trigger again after the specified interval
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 32) { // Space bar key code
        if (!isJumping) {
            isJumping = true;
        }
    }
}


void checkGameOver() {
    // Check collision with oTriangle
    float skullBrickLeft = 0.43 - 0.1; // Adjusted the calculation for the SkullBrick's left boundary
    float skullBrickRight = 0.43 + 0.1; // Adjusted the calculation for the SkullBrick's right boundary
    float skullBrickBottom = skullBrickY - 0.5; // Adjusted the calculation for the SkullBrick's bottom boundary
    float skullBrickTop = skullBrickY + 0.5; // Adjusted the calculation for the SkullBrick's top boundary

    float BrickLeft = oTriangleX - 0.05; // Adjusted the calculation for the oTriangle's left boundary
    float BrickRight = oTriangleX - 0.05; // Adjusted the calculation for the oTriangle's right boundary
    float BrickBottom = 0.183 - 0.775; // Adjusted the calculation for the oTriangle's bottom boundary
    float BrickTop = 0.183 + 0.525; // Adjusted the calculation for the oTriangle's top boundary
    
    //if (skullBrickRight >= triangleLeft) {
    //    collisionDetected = true;
    //}
    /*oBrickX*/



     if (skullBrickRight >= BrickLeft && skullBrickLeft <= BrickRight && skullBrickBottom <= BrickTop) {
        // Game over condition triggered by collision with oTriangle
        collisionDetected = true;
        collisionCount++;
        // Update maximum score if necessary
        if (score > maxScore) {
            maxScore = score;
        }
        // Write the maximum score to a file
        writeMaxScoreToFile(maxScore);
    }
}

void writeMaxScoreToFile(int maxScore) {
    std::ofstream file("max_score.txt");
    if (file.is_open()) {
        file << maxScore;
        file.close();
    }
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1920, 1080);
    glutCreateWindow("Geometry Shapes");

    glClearColor(0.26, 0.26, 0.26, 1.0);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    // Seed the random number generator with the current time
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Set the timer function to trigger at the specified interval
    glutTimerFunc(timerInterval, timer, 0);

    glutMainLoop();
    return 0;
}
