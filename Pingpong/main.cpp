
#include <iostream>
#include <raylib.h> /// Raylib is a library for making games
#include <fstream>
#include <string.h>
#include <vector>

Color lightBlue = Color{173, 216, 230, 255};    // Light Blue with full opacity
Color mediumDarkBlue = Color{0, 102, 204, 255}; // Medium Dark Blue with full opacity
Color lighterBlue = Color{192, 230, 242, 255};  // Slightly Lighter Blue with full opacity

Color backgroundGradientTop = {30, 60, 114, 255};   // #1E3C72
Color backgroundGradientBottom = {42, 82, 152, 255}; // #2A5298
Color ballColor = {255, 69, 0, 255};                // #FF4500
Color playerPaddleColor = {50, 205, 50, 255};       // #32CD32
Color cpuPaddleColor = {220, 20, 60, 255};          // #DC143C
Color netColor = WHITE;
Color textColor = WHITE;
Color textShadowColor = BLACK;
Color highScoreColor = YELLOW;


using namespace std;
int player_score = 0;
int cpu_score = 0;
int player2_score = 0;

class playgame
{
    public:
    void singleplayer();
    void twoplayer();
};
playgame obj;

class Ball
{
      float x, y;
    int speed_x, speed_y;
    int radius=20;
    int player1 ,player2,round;

public:
    Ball()
    {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;
        speed_x = 6;

        speed_y = 6;
    }
    Ball(float a,float b){
    x=a;
    y=b;
    speed_x=6;
    speed_y=6;
    
}

    void Draw()
    {
        DrawCircle(x, y, radius, YELLOW);
    }
 



    // function to move the ball
    void move()
    {
        x += speed_x;
        y += speed_y;
        static Sound lose = LoadSound("resources/lose.wav");
        static Sound win = LoadSound("resources/win.wav");

        if (y + radius >= GetScreenHeight() || y - radius <= 0)
        {                  // checking if the ball touch the bottom or top of the screen
            speed_y *= -1.05; // changing the direction of the ball in y direction

            if (x + radius >= GetScreenWidth())
            {
                PlaySound(lose);
                cpu_score++; // computer wins
                 player2++;
         round++;
                resetball();
            }

            if (x - radius <= 0)
            {
                PlaySound(win);
                player_score++;
                 player2++;
         round++;
                resetball();
            }
        }
    }
    void collision(){
        speed_x *= -1;

    }
 
    float ballpy()
    {
        return y;
    }
    float ballpx()
    {
        return x;
    }
    float ballpr()
    {
        return radius;
    }
    int player(){
        return player_score;
    }
    int cpu(){
        return cpu_score;
    }

    int rounds(){
        return round;
    }
    int player1r(){
        return player1;
    }
    int player2r(){
        return player2;
    }

    void resetball()
    {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;
        speed_x *= -1;
        speed_y *= -1;
    }
};

class Paddle
{
protected:
  float x, y;
    int speed;
    float width, height;
    void avoidObstruction()
    {

        if (y <= 0)
        {
            y = 0;
        }
        if (y + height >= GetScreenHeight())
        {
            y = GetScreenHeight() - height;
        }
    }

public:
    Paddle (){}
    Paddle(float a, float b,float w, float h)
    {
        x = a;
        y = b;
        speed = 6;
        width = w;
        height = h;
    }

    void Draw()
    {
        DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, WHITE);
    }

    void move()
    {
        if (IsKeyDown(KEY_UP))
        {
            y -= speed;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            y += speed;
        }

        avoidObstruction();
    }
    void draw2()
    {
        DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, GREEN);
    }
    float getx()
    {
        return x;
    }
    float gety()
    {
        return y;
    }
    float getwidth()
    {
        return width;
    }
    float getheight()
    {
        return height;
    }
    int getspeed()
    {
        return speed;
    }
};

class animation 
{
    private:
     float x, y;
    int speed_x=6, speed_y=6;
    int radius=20;

    public:
    animation (){

        x=50;
        y=50;
    }


      void Draw()
    {
        DrawCircle(x, y, radius, WHITE);
    }
       void move2(){
        x += speed_x;
        y += speed_y;

        if (y + radius >= GetScreenHeight() || y - radius <= 0)
        {                  // checking if the ball touch the bottom or top of the screen
            speed_y *= -1; // changing the direction of the ball in y direction
        }
        if (x + radius >= GetScreenWidth() || x-radius<=0)
        {
            speed_x *= -1;
        }
       }

};
animation frontball;

class player3 :public Paddle{

    public:
    player3(){}
    //using concept of constructor in single inheratance
    player3(float a, float b,float w,float h) :Paddle (x,y,width,height){
    
    }

     void move(){
    if (IsKeyDown(KEY_W)){

        y=y-speed;

    }

    if (IsKeyDown(KEY_S)){

        y=y+speed;

    }

    avoidObstruction();
   }

    
};

class cpuPaddle : public Paddle
{

public:
    cpuPaddle(float a, float b, float w, float h)
    {
        x = a;
        y = b;
        speed = 3;
        width = w;
        height = h;
    }
    void move(int bally)
    {
        if (y + height / 2 < bally)
        {
            y += speed;
        }
        if (y + height / 2 > bally)
        {
            y -= speed;
        }

        if (y <= 0)
        {
            y = 0;
        }
        if (y + height >= GetScreenHeight())
        {
            y = GetScreenHeight() - height;
        }
        avoidObstruction();
    }
     void Draw()
    {
        DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, cpuPaddleColor);
    }
};



class AnimateBall
{ // Animation class
public:
    Vector2 position;
    float radius;
    Color color;
    float speed;
    void animation(int temhighscore, int new_highscore, int &player_score, int &life)
    {
        Sound celebration = LoadSound("resources/celebration.mp3");

        int screenWidth = 1280;
        int screenHeight = 720;
        vector<AnimateBall> balls;
        for (int i = 0; i < 40; i++)
        {
            AnimateBall ball;
            ball.position = {(float)GetRandomValue(0, screenWidth), 0};
            ball.radius = (float)GetRandomValue(5, 10); // Reduced size
            ball.color = {(unsigned char)GetRandomValue(100, 255), (unsigned char)GetRandomValue(100, 255), (unsigned char)GetRandomValue(100, 255), 255};
            ball.speed = (float)GetRandomValue(50, 100) / 10.0f;
            balls.push_back(ball);
        }
        PlaySound(celebration);

        while (!WindowShouldClose())
        {
            // Update

            for (auto &ball : balls)
            {
                ball.position.y += ball.speed; // Move balls downwards
                if (ball.position.y > screenHeight + ball.radius)
                {
                    ball.position.y = -ball.radius;                          // Reset position to top if it goes beyond the bottom
                    ball.position.x = (float)GetRandomValue(0, screenWidth); // Randomize horizontal position
                }
            }

            // Draw
            BeginDrawing();
            ClearBackground(netColor);

            for (const auto &ball : balls)
            {
                DrawCircleV(ball.position, ball.radius, ball.color);
            }
            DrawText("Congratulations! You have gain the highscore", screenWidth / 6, screenHeight / 2, 45, highScoreColor); // text x y font size color
            DrawText(TextFormat("Previous record:%i", temhighscore), screenWidth / 6, 460, 45, BLACK);              // text x y font size color
            DrawText(TextFormat("New Record:%i", new_highscore), screenWidth / 6, 560, 45, BLACK);                  // text x y font size color
            DrawText("Press ENTER to continue ,ESC to exit the game", screenWidth / 6, 620, 30, BLACK);             // text x y font size color
            EndDrawing();
            if (IsKeyPressed(KEY_ENTER))
            {
                UnloadSound(celebration);
                player_score = 0;
                life = 2;
                break;
            }
        }
    }

  
};

int main()
{
    cout << "Starting the game" << endl;
    const int screenWidth = 1200;
    const int screenHeight = 700;
    int highscore, newcpu_score;
    int life = 2;
    int temhighscore = 0;
    Ball ball,ball2(600,350);

Paddle player(screenWidth-35,screenHeight/2-50,25,130);
Paddle paddle1(10,screenHeight/2-50,25,130);
Paddle paddle2(screenWidth-40,screenHeight/2-50,25,130);
cpuPaddle cpu(10,screenHeight/2-50,25,130);
AnimateBall aniball;

    fstream file("highscore.txt", ios::in | ios::out);

    // Check if the file opened successfully
    if (!file)
    {
        cerr << "File could not be opened!" << endl;
        return 1;
    }
    file >> highscore;
    temhighscore = highscore;
    // Check if reading was successful
    if (!file)
    {
        cerr << "Error reading the number from the file!" << endl;
        file.close();
        return 1;
    }
    file.close();

    InitWindow(screenWidth, screenHeight, "Ping Pong");
    InitAudioDevice();
    SetTargetFPS(60);/// this function will set the frame per second to 60
     

                                                                                 
    Rectangle button1 = {screenWidth / 2 - 150, screenHeight / 2 - 25, 150, 50}; 
    Rectangle button2 = {screenWidth / 2 +200, screenHeight / 2 - 25, 100, 50};
     Rectangle button3 = {screenWidth/2+30, screenHeight/2-25, 150, 50};


       Font font = LoadFont("sujan.ttf");  // Load a custom font
    Vector2 position = { 300.0f, 200.0f }; 
    float fontSize = 40.0f;                       // Set the size of the font
    float spacing = 2.0f;                         // Set the spacing between characte
    float rotation = 0.0f;                        // Set the rotation of the text in degrees
    Color tint = WHITE;  
      float rotationSpeed = 0.5f; 

    bool button1Clicked = false;
    bool button2Clicked = false;
    bool button3Clicked = false;
   
    // loading of the sound
    Sound strike = LoadSound("resources/strike.wav");
    // this main game loop will run until the window is closed
    while (!WindowShouldClose())
    {
        while (!WindowShouldClose())
        {
            // Update
            if (CheckCollisionPointRec(GetMousePosition(), button1))
            {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    button1Clicked = true;
                }
            }
            else if (CheckCollisionPointRec(GetMousePosition(), button2))
            {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    button2Clicked = true;
                }
            }
            else if (CheckCollisionPointRec(GetMousePosition(), button3))
            {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    button3Clicked = true;
                }
            }
     rotation += rotationSpeed;  // Increment rotation angle by rotation speed

        // Reverse rotation direction at -45 and 45 degrees
        if (rotation >= 20.0f || rotation <= -20.0f) rotationSpeed = -rotationSpeed;

            // Draw
            BeginDrawing();

            ClearBackground(BLACK);
          frontball.Draw();
          frontball.move2();


            if (button3Clicked)
                break;
            else
                DrawRectangleRec(button3, GRAY); // Button2 color when not clicked

            DrawText("Single Player", button1.x + 10, button1.y + 15, 20, BLACK);
            DrawText("Single Player", screenWidth/4,screenHeight/5, 40, BLACK);

            DrawText("Quit", button2.x + 10, button2.y + 15, 20, BLACK);
            DrawText("Multiplayer", button3.x + 10, button3.y + 15, 20, BLACK);
DrawTextPro(font, "PIng POng!", position, (Vector2){0, 0}, rotation, fontSize, spacing, tint);



            EndDrawing();


              if (button1Clicked)
                {
                    player_score = 0;

        
        while (!WindowShouldClose()) // this function will return true if the window is closed

        {

            if (life == 0)
            {
                break;
            }

            BeginDrawing(); // this function creates a blankcanvas so that we can starting drawinng

            ClearBackground(backgroundGradientBottom); // this function will clear the background of the canvas and set it to black
            // slide  and middle lines for the game interface
            DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, BLACK);  // x1 y1 x2 y2 color
            DrawLine(2, 2, screenWidth, 2, BLACK);                               // x1 y1 x2 y2 color
            DrawLine(0, screenHeight - 2, screenWidth, screenHeight - 2, BLACK); // x1 y1 x2 y2 color

            DrawRectangle(screenWidth / 2, 0, 2, screenHeight, BLACK);     // x y width height color
            DrawRectangle(0, 0, screenWidth / 2, screenHeight, backgroundGradientTop);      // x y width height color
            DrawCircle(screenWidth / 2, screenHeight / 2, 150, netColor); // x y radius color
            
            // remember that the coordinate system in raylib starts from the top left corner of the screen updown :y side: x
        
           


            // check for the colloision between the ball and the player
            if (CheckCollisionCircleRec(Vector2{ball.ballpx(), ball.ballpy()}, ball.ballpr(), Rectangle{player.getx(), player.gety(), player.getwidth(), player.getheight()}))
            {
                ball.collision();
                PlaySound(strike);
            }
            if (CheckCollisionCircleRec(Vector2{ball.ballpx(), ball.ballpy()}, ball.ballpr(), Rectangle{cpu.getx(), cpu.gety(), cpu.getwidth(), cpu.getheight()}))
            {
                ball.collision();
                PlaySound(strike);
            }

            ball.Draw();
            ball.move();
            player.Draw();
                player.move();
            cpu.Draw();
             cpu.move(ball.ballpy());
            DrawText("CPU", 300, 20, 50, WHITE);                            // text x y font size color
            DrawText(TextFormat("Player:%i", player_score),3*screenWidth/4-200,20,50,WHITE); // text x y font size color
            DrawText(TextFormat("Enter ESC key to exit at any time"), 5, 5, 20, BLACK); // text x y font size color

            DrawText(TextFormat("HighScore:%i", highscore), screenWidth - 190, 20, 30, BLACK); // text x y font size color
            if (newcpu_score != cpu_score)
            {
                life = life - 1;
                cpu_score = newcpu_score;
            }

            DrawText(TextFormat("Life:%i", life), screenWidth - 190, 50, 30, BLACK);

            EndDrawing(); // this function will end the drawing and display the canva

            if (player_score > highscore)
            {
                highscore = player_score;
                // Open the file in write mode
                ofstream file("highscore.txt", ios::out | ios::trunc);
                if (file.is_open())
                {
                    // Write the updated high score
                    file << highscore;
                    file.close();
                }
                else
                {
                    // Handle error if file cannot be opened
                    cerr << "Unable to open file for writing." << endl;
                }
            }
        }

        while (!WindowShouldClose())
        {
            BeginDrawing();
            ClearBackground(backgroundGradientTop);
            if (player_score > temhighscore)
            {
                aniball.animation(temhighscore, highscore, player_score, life);
                break;

                EndDrawing();
            }
            else
            {
                DrawText("Game Over ", screenWidth / 6, screenHeight / 2, 60, highScoreColor);
                DrawText(TextFormat("Your Score: %i", player_score), screenWidth / 6, 500, 60, textColor);
                DrawText("Press ENTER to play ESC to exit", screenWidth / 6, 600, 40, BLACK);
                EndDrawing();
                if (IsKeyPressed(KEY_ENTER))
                {
                    player_score = 0;
                    life = 2;
                    break;
                }
            }
        }
        
    }
     else{
                DrawRectangleRec(button1, GRAY); // Button1 color when not clicked
     }
     if (button2Clicked)
                break; 
                 else{
                DrawRectangleRec(button2, GRAY); // Button2 color when not clicked   
                 }  
                }
    CloseAudioDevice();

    CloseWindow();

    return 0;
}
}