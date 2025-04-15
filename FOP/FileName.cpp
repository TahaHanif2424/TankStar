#include "raylib.h"
#include "raymath.h"

enum GameState {//here we have made 5 variable to make the 5 states of the game
    MENU,
    GAME,
    OPTION,
    INSTRUCTION,
    ABOUT,
};

int main()
{
    float PosX = 1200.0f, PosY = 680.0f;//position of tank 1
    float PosX1 = 1260.0f, PosY1 = 680.0f;//position of missile 1
    float PosA = 200.0f, PosB = 680.0f;//position of tank 2
    float PosA1 = 300.0f, PosB1 = 680.0f;///position of missile 2
    float X = 1260.0f, Y = 680.0;//position of aim1
    float A = 300.0f, B = 680.0;//position of aim 2
    float rotationAngle1 = 0.0f;//angle of rotationa
    float rotationAngle2 = 0.0f;//angle of rotation by which aim is rotated
    float rotationSpeed = 50.0f;//it is rotation speed  
    float missileSpeed = 15.0f;//speed by which missile is moved
    float missileSpeed2 = 15.0f;
    float missile1Angle = 0.0f;//angle of missile 1
    float missile2Angle = 0.0f;//angle of missile 2
    const int screenwidth = 1600;//screen size
    const int screenheight = 900;
    InitWindow(screenwidth, screenheight, "Tank star");//window screen 
    InitAudioDevice(); // Initialize audio device

    //here we are uploadding the pictures   
    Texture2D backgroundTexture = LoadTexture("mountain.png");//background image
    Texture2D tank1 = LoadTexture("righttank.png");//right tank
    Texture2D tank2 = LoadTexture("lefttank.png");//left tank
    Texture2D wall = LoadTexture("wall.png");//center wall
    Texture2D menu = LoadTexture("Tank_Star.png");//front page
    Texture2D option = LoadTexture("option.png");//option panel
    Texture2D instruction = LoadTexture("instruction.png");//instruction panel
    Texture2D about = LoadTexture("about.png");//about panel
    Texture2D aboutbtn1 = LoadTexture("about1.png");//about button1   
    Texture2D aboutbtn2 = LoadTexture("about2.png");//abohut button2 basically it appears after transation
    Rectangle aboutbtn = { 1230, 690, 230, 70 };//about button rectangle
    Texture2D informationbtn1 = LoadTexture("information1.png");//information button
    Texture2D informationbtn2 = LoadTexture("information2.png");
    Rectangle instructionbtn = { 1230, 490, 230, 70 };//instruction rectangle
    Texture2D multiplayer1 = LoadTexture("multiplayer1.png");//multiplayer button
    Texture2D multiplayer2 = LoadTexture("multiplayer2.png");
    Rectangle multiplayerbtn = { 1230, 290, 230, 70 };//multiplayer rectangle
    Texture2D singleplayer1 = LoadTexture("singleplayer1.png");//select one transition buttons   
    Texture2D singleplayer2 = LoadTexture("singleplayer2.png");
    Rectangle singleplayerbtn = { 1230, 90, 230, 70 };
    Rectangle tank1health = { 1200,100,200,40 };//tank1health
    Rectangle tank2health = { 200,100,200,40 };//tank 2 health
    Rectangle box = { 1240,PosY, 105,50 };//box behind tank by which we check the collision
    Rectangle box2 = { 180,PosB, 115,50 };//box 2 behind the tank 2
    Rectangle fire1 = { PosX1+10,PosY1,20,20 };//fire rectangle whih move behind the missile and checck the collision
    Rectangle fire2 = { PosA1+10,PosB1,20,20 };
    Texture2D missile1 = LoadTexture("missile1.png");//missile texture
    Texture2D missile2 = LoadTexture("missile2.png");
    Texture2D aim = LoadTexture("aim.png");//aim texture
    int n = 1;// variable to  check the pkayer turn
    int fired1 = 0;//condition to handle the erroe inside the code
    int fired2 = 0;
    GameState gamestate = MENU;// we are initiailizing the game state with menu
    int blinkCounter = 0;//a counter to blink the text inside the code
    bool textVisible = true;//function for making the text blink 
    bool missileFired1 = false;//variable for firing
    bool missileFired2 = false;
    int winner = 0;//winning condition initiailizing with 0
    Vector2 missile1Velocity = { 0.0f, 0.0f };//missile velocity for missile 1
    Vector2 missile2Velocity = { 0.0f, 0.0f };//missile velocity for missile 2
    float gravity = 0.2f;//player 1 gravity
    float gravity2 = 0.2f; //constant gravity for moving the missile downwardd
    Vector2 mousepoint;//variable to check the mouse position
    SetTargetFPS(60);//standard fps of the game
    Sound sound;
    sound = LoadSound("WhatsApp Audio 2024-01-07 at 5.00.46 AM.mp3");
    Sound button;
    button = LoadSound("interface-124464-[AudioTrimmer.com].mp3");
    Sound explosion;
    explosion = LoadSound("explosion-42132-[AudioTrimmer.com].mp3");
    Sound fire;
    fire = LoadSound("hq-explosion-6288.mp3");
    int draw = 0;
    int draw2 = 0;
    int count = 0;
    while (!WindowShouldClose()) {//main while loop       
        mousepoint = GetMousePosition();//variable storing the mouse position
        blinkCounter++;
        if (blinkCounter >= 17) {//here we have set fps for blinking the text on the first screen
            SetTargetFPS(30);
            textVisible = !textVisible;
            blinkCounter = 0;
        }

        if (gamestate == MENU) {
            
            if (IsKeyDown(KEY_ENTER)) {//when enter key is pressed then the game state is chaneged to option
                if (count <= 100) {
                    PlaySound(sound);
                    count++;
                }
                
                gamestate = OPTION;
            }
        }
        else if (gamestate == OPTION) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {//in option state we check the collision of the mouse with the multiplayr  or about or  instruction button to change the gamestate
                Vector2 mouseposition1 = GetMousePosition();
                if (CheckCollisionPointRec(mouseposition1, multiplayerbtn)) {
                    PlaySound(button);
                    gamestate = GAME;//collision with multiplayer button change  the gamestate to GAME
                }
            }
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {//it change the gamestate to INSTRUCTION
                Vector2 mouseposition2 = GetMousePosition();
                if (CheckCollisionPointRec(mouseposition2, instructionbtn)) {
                    PlaySound(button);
                    gamestate = INSTRUCTION;
                }
            }
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {//it change the game state to  ABOUT
                Vector2 mouseposition3 = GetMousePosition();
                if (CheckCollisionPointRec(mouseposition3, aboutbtn)) {
                    PlaySound(button);
                    gamestate = ABOUT;
                }
            }
        }
        if (IsKeyDown(KEY_L) && gamestate == INSTRUCTION) {
            gamestate = OPTION;//to return back  to the OPTION press the L key
        }
        if (IsKeyDown(KEY_L) && gamestate == ABOUT) {
            gamestate = OPTION;// to return from about to option
        }
        else if (gamestate == GAME) {//when the game  is over and we press the enter then we will go to main menu
            if (tank1health.width <= 0 || tank2health.width <= 0) {
                if (IsKeyDown(KEY_ENTER)) {
                    tank1health.width = 200;
                    tank2health.width = 200;
                    PosX = 1200.0f, PosY = 680.0f;//position of tank 1
                    PosX1 = 1260.0f, PosY1 = 680.0f;//position of missile 1
                    PosA = 200.0f, PosB = 680.0f;//position of tank 2
                    PosA1 = 300.0f, PosB1 = 680.0f;///position of missile 2
                    rotationAngle1 = 0.0f;//angle of rotation
                    rotationAngle2 = 0.0f;//angle of rotation by which aim is rotated
                    rotationSpeed = 50.0f;//it is rotation speed
                    missileSpeed = 20.0f;//speed by which missile is moved
                    missileSpeed2 = 20.0f;
                    missile1Angle = 0.0f;//angle of missile 1
                    missile2Angle = 0.0f;//angle of missile 2
                    n = 1;
                    fired1 = 0;
                    fired2 = 0;
                    Vector2 missile1Velocity = { 0.0f, 0.0f };
                    Vector2 missile2Velocity = { 0.0f, 0.0f };
                    gravity = 0.3f;
                    gravity2 = 0.3f;
                    gamestate = OPTION;
                    winner = 0;
                    box.x = 1240;
                    box2.x = 190;
                    fire1.x = 1260;
                    fire2.x = 300;
                    X = 1260.0f, Y = 680.0;
                    A = 300.0f, B = 680.0;
                    PlaySound(sound);
                }
                if (IsKeyDown(KEY_SPACE)) {//we press space to play again
                    tank1health.width = 200;
                    tank2health.width = 200;
                    PosX = 1200.0f, PosY = 680.0f;//position of tank 1
                    PosX1 = 1260.0f, PosY1 = 680.0f;//position of missile 1
                    PosA = 200.0f, PosB = 680.0f;//position of tank 2
                    PosA1 = 300.0f, PosB1 = 680.0f;///position of missile 2
                    rotationAngle1 = 0.0f;//angle of rotation
                    rotationAngle2 = 0.0f;//angle of rotation by which aim is rotated
                    rotationSpeed = 50.0f;//it is rotation speed
                    missileSpeed = 20.0f;//speed by which missile is moved
                    missileSpeed2 = 20.0f;
                    missile1Angle = 0.0f;//angle of missile 1
                    missile2Angle = 0.0f;//angle of missile 2
                    n = 1;
                    fired1 = 0;
                    fired2 = 0;
                    Vector2 missile1Velocity = { 0.0f, 0.0f };
                    Vector2 missile2Velocity = { 0.0f, 0.0f };
                    gravity = 0.3f;
                    gravity2 = 0.3f;
                    gamestate = OPTION;
                    gamestate = GAME;
                    winner = 0;
                    box.x = 1240;
                    box2.x = 190;
                    fire1.x = 1260;
                    fire2.x = 300;
                     X = 1260.0f, Y = 680.0;
                     A = 300.0f, B = 680.0;
                     PlaySound(sound);
                }
            }
        }
        if (IsKeyDown(KEY_LEFT)) {//while pressing left key the tank will move left
            PosX -= 12;
            X -= 12;
            box.x -= 12;
            if (!fired1)
            {
                fire1.x -= 12;

                PosX1 -= 12;
            }
            if (PosX < 850) {
                PosX += 12;
                X += 12;
                box.x += 12;

                if (!fired1)
                {
                    fire1.x += 12;
                    PosX1 += 12;

                }
            }
        }
        if (IsKeyDown(KEY_RIGHT)) {//pressing right ket the tank will move right
            PosX += 12;
            X += 12;
            box.x += 12;
            if (!fired1)
            {
                fire1.x += 12;
                PosX1 += 12;
            }
            if (PosX + tank1.width * 0.5 > screenwidth) {
                PosX = screenwidth;
                X -= 12;
                box.x -= 12;
                if (!fired1)
                {
                    fire1.x -= 12;
                    PosX1 -= 12;
                }
            }
        }
        if (IsKeyDown(KEY_A)) {//it will move the player to right when key A is pressed
            PosA -= 12;
            box2.x -= 12;
            A -= 12;
            if (!fired2)
            {
                fire2.x -= 12;
                PosA1 -= 12;

            }
            if (PosA < 0) {
                PosA += 12;
                box2.x += 12;
                A += 12;
                if (!fired2)
                {
                    fire2.x += 12;
                    PosA1 += 12;

                }
            }
        }
        if (IsKeyDown(KEY_D)) {//when D is pressed it will move the tank left
            PosA += 12;
            A += 12;
            box2.x += 12;

            if (!fired2)
            {
                fire2.x += 12;
                PosA1 += 12;

            }
            if (PosA + tank2.width * 0.5 > 800) {
                PosA = 800 - tank2.width * 0.5f;

                box2.x -= 12;
                A -= 12;
                if (!fired2)
                {
                    fire2.x -= 12;
                    PosA1 -= 12;
                }
            }
        }
        if (n % 2 == 1 && winner != 2) {//this if condition check the player turn and its player 1 turn           
           
            if (IsKeyDown(KEY_UP)) {//pressing uo key the ain will move up
                rotationAngle1 += rotationSpeed * GetFrameTime();
                if (rotationAngle1 > 90) {
                    rotationAngle1 -= rotationSpeed * GetFrameTime();
                }
            }
            if (IsKeyDown(KEY_DOWN)) {//pressing down key the aim will move downward 
                rotationAngle1 -= rotationSpeed * GetFrameTime();
                if (rotationAngle1 < 0) {
                    rotationAngle1 += rotationSpeed * GetFrameTime();
                }
            }
            if (IsKeyDown(KEY_P) && !missileFired1) {//pressing p key the tank  1 will fire missile
                draw = 1;//for drawing the missile
                PlaySound(fire);
                missileFired1 = true;
                missile1Velocity = Vector2{ missileSpeed * cosf(rotationAngle1 * DEG2RAD), -missileSpeed * sinf(rotationAngle1 * DEG2RAD) };//this function set the velocity of the missilr 1 by usinf=g cos and sin function
                missile1Angle = rotationAngle1;///it set the missile angle
                fired1 = 1;
            }
            if (missileFired1) {
                SetTargetFPS(60);//when missile 1 is fired the missile will move forward t=with the following change in the x and y component
                fire1.x -= missile1Velocity.x;
                fire1.y += missile1Velocity.y;
                PosX1 -= missile1Velocity.x;
                PosY1 += missile1Velocity.y;
                missile1Velocity.y += gravity;//it will add a gravito of 0.1 in the movement
                fired1 = 1;
            }
            if (CheckCollisionRecs(Rectangle{ fire1.x, fire1.y, 20, 20 }, Rectangle{ box2.x, box2.y, 130, 50 }) && winner != 1 && winner != 2)//this chech the collision of the missilee with player 2 tank
            {
                PlaySound(explosion);
                missileFired1 = false;
                tank2health.width -= 40;// if  the missile hit the tank it decrease its health and change he turn u
                if (tank2health.width <= 0) {//this chech the winning condition of the tank
                    winner = 1;
                }
                n++;
                fire1.x = PosX + 70.0f;//this function set the missile original possition 
                fire1.y = PosY;
                PosX1 = PosX + 60.0f;
                PosY1 = PosY;
                missile1Velocity = Vector2{ 0.0f, 0.0f };//we again set the missile velocity to 0 to use for next turn
                fired1 = 0;
                draw = 0;
            }
            else if ((fire1.x < 0 || fire1.y > screenwidth || fire1.x < 0 || fire1.y > 900)) {//if missile goes out of the screen it will reset the positon of the missile and change the turn
               missileFired1 = false;
                fire1.x = PosX + 70.0f;
                fire1.y = PosY;
                PosX1 = PosX + 60.0f;
                PosY1 = PosY;
                n++;
                missile1Velocity = Vector2{ 0.0f, 0.0f };
                fired1 = 0;
                draw = 0;
            }
            else if (fire1.x <= 830 && fire1.x >= 760 && fire1.y >= 500) {//if missile hits the no hitting area it will change the turn of the player
                missileFired1 = false;
                fire1.x = PosX + 70.0f;
                fire1.y = PosY;
                PosX1 = PosX + 60.0f;
                PosY1 = PosY;
                n++;
                missile1Velocity = Vector2{ 0.0f, 0.0f };
                fired1 = 0;
                draw = 0;
            }
        }
        if (n % 2 == 0 && winner != 1) {// this is the player  2 condition 
           
            if (IsKeyDown(KEY_W)) {//pressing w will move the arrow to upward
                rotationAngle2 += rotationSpeed * GetFrameTime();
                if (rotationAngle2 > 90) {
                    rotationAngle2 = 90;
                }
            }
            if (IsKeyDown(KEY_S)) {//pressing S will move the arrow downwards
                rotationAngle2 -= rotationSpeed * GetFrameTime();
                if (rotationAngle2 < 0) {
                    rotationAngle2 = 0;
                }
            }
            if (IsKeyDown(KEY_R) && !missileFired2) {//pressing r   WILL FIRE THE MISSILE
                draw2 = 1;//drawing missile 2
                PlaySound(fire);

                missileFired2 = true;
                missile2Velocity = Vector2{ missileSpeed2 * cosf((rotationAngle2)*DEG2RAD), -missileSpeed2 * sinf((rotationAngle2)*DEG2RAD) };//if will set the velocitty by using the cos and sine function
                missile2Angle = rotationAngle2;
            }
            if (missileFired2) {//when missile 2 is fired it will change the x and y commponent as follows of missile 2
                SetTargetFPS(60);
                fire2.x += missile2Velocity.x;
                fire2.y += missile2Velocity.y;
                PosA1 += missile2Velocity.x;
                PosB1 += missile2Velocity.y;
                missile2Velocity.y += gravity2;
                fired2 = 1;
            }
            if (CheckCollisionRecs(Rectangle{ fire2.x, fire2.y, 20, 20 }, Rectangle{ box.x, box.y, 130, 50 }) && winner != 1 && winner != 2)//it checck the collision of missil2 with tank 1
            {
                PlaySound(explosion);
                missileFired2 = false;
                tank1health.width -= 40;
                if (tank1health.width <= 0) {
                    winner = 2; // Player 2 winnning condition is checked
                }
                n++;
                fire2.x = PosA + 60.0f;
                fire2.y = PosB;
                PosA1 = PosA + 60.0f;
                PosB1 = PosB;
                missile2Velocity = Vector2{ 0.0f, 0.0f };
                fired2 = 0;
                draw2 = 0;
            }
            if (fire2.x < 0 || fire2.x > screenwidth || fire2.y < 0 || fire2.y > screenheight) {//if the missile goes out of ht ec=sccreen then it will change  the player turn
                missileFired2 = false;
                n++;
                fire2.x = PosA + 60.0f;
                fire2.y = PosB;
                PosA1 = PosA + 60.0f;
                PosB1 = PosB;
                missile2Velocity = Vector2{ 0.0f, 0.0f };
                fired2 = 0;
                draw2 = 0;
            }
            else if (fire2.x >= 760 && fire2.x < 830 && fire2.y >= 500) {//if missile hits the no hitting area then the player turn is changed
                missileFired2 = false;

                n++;
                fire2.x = PosA + 60.0f;
                fire2.y = PosB;
                PosA1 = PosA + 60.0f;
                PosB1 = PosB;
                missile2Velocity = Vector2{ 0.0f, 0.0f };
                fired2 = 0;
                draw2 = 0;
            }
        }
        BeginDrawing();//here we are drawing all the pictures
        if (gamestate == MENU) {//its the  main menu 
            DrawTextureEx(menu, Vector2{ -140,0 }, 0, .85f, WHITE);
            DrawRectangle(570, 830, 430, 70, BLACK);
            if (textVisible) {

                DrawText("Press Enter to continue", 600, 850, 30, WHITE);//this text will blink on the screen
            }
        }
        else if (gamestate == OPTION) {//in option state it will draw the picture on the back and tthe buttond

            DrawTextureEx(option, Vector2{ 0,0 }, 0, 1, WHITE);//it draws the purple menu bar
            DrawRectangle(1090, 0, 700, 900, PURPLE);
            if (CheckCollisionPointRec(mousepoint, Rectangle{ 1230,690,230,70 }))//it check the collision of the button wiht the mouce position and change the button
            {
                DrawTextureEx(aboutbtn2, Vector2{ 1230,685 }, 0, 1, WHITE);

            }
            else {
                DrawTextureEx(aboutbtn1, Vector2{ 1230,690 }, 0, 1.0f, WHITE);
            }
            if (CheckCollisionPointRec(mousepoint, Rectangle{ 1230,490,230,70 }))//it check the collision of the button wiht the mouce position and change the button
            {
                DrawTextureEx(informationbtn1, Vector2{ 1230,485 }, 0, 1.0f, WHITE);
            }
            else {
                DrawTextureEx(informationbtn2, Vector2{ 1230,490 }, 0, 1.0f, WHITE);
            }
            if (CheckCollisionPointRec(mousepoint, Rectangle{ 1230,290,230,70 }))//it check the collision of the button wiht the mouce position and change the button
            {
                DrawTextureEx(multiplayer2, Vector2{ 1230,285 }, 0, 1.0f, WHITE);
            }
            else {
                DrawTextureEx(multiplayer1, Vector2{ 1230,290 }, 0, 1.0f, WHITE);
            }
            if (CheckCollisionPointRec(mousepoint, Rectangle{ 1230,90,230,70 }))//it check the collision of the button wiht the mouce position and change the button
            {
                DrawTextureEx(singleplayer2, Vector2{ 1230,85 }, 0, 1.0f, WHITE);
            }
            else {
                DrawTextureEx(singleplayer1, Vector2{ 1230,90 }, 0, 1.0f, WHITE);
            }
        }
        else if (gamestate == INSTRUCTION) {//here alll the instruction is drawn
            DrawTextureEx(instruction, Vector2{ 0,0 }, 0, 1, WHITE);
            DrawText("Player1", 200, 100, 40, WHITE);
            DrawText("Move Left = Left Key", 200, 200, 40, WHITE);
            DrawText("Move Right =Right Key", 200, 300, 40, WHITE);
            DrawText("Aim Up = Key UP", 200, 400, 40, WHITE);
            DrawText("Aim Down = Key Down", 200, 500, 40, WHITE);
            DrawText("Fire Key = P", 200, 600, 40, WHITE);
            DrawText("Player2", 1100, 100, 40, WHITE);
            DrawText("Move Left = A ", 1100, 200, 40, WHITE);
            DrawText("Move Right = D", 1100, 300, 40, WHITE);
            DrawText("Aim Up = W", 1100, 400, 40, WHITE);
            DrawText("Aim Down = S", 1100, 500, 40, WHITE);
            DrawText("Fire Key = R", 1100, 600, 40, WHITE);
            if (textVisible) {
                DrawText("Press L to go to MENU", 550, 700, 40, WHITE);
            }
        }
        else if (gamestate == ABOUT) {//all about information is drawn here 
            DrawTextureEx(about, Vector2{ 0,0 }, 0, 1, WHITE);
            DrawText("Developer:", 200, 100, 40, WHITE);
            DrawText("Resources:", 200, 200, 40, WHITE);
            DrawText("Taha Bin Hanif (CS Major)", 900, 100, 40, WHITE);
            DrawText("C language & Raylib.h", 900, 200, 40, WHITE);
            DrawText("FOCP END SEMESTER PROJECT", 200, 300, 40, WHITE);
            DrawText("Compiler & IDE:", 200, 400, 40, WHITE);
            DrawText("VISUAL STUDIO", 900, 400, 40, WHITE);
            DrawText("2D Tank War Game", 200, 500, 40, WHITE);
            DrawText("CopyRight 2005-23, Inc-All Right Reserved", 200, 600, 40, WHITE);
            if (textVisible) {
                DrawText("PRESS L TO GO TO MENU", 550, 700, 40, WHITE);
            }
        }
        else if (gamestate == GAME) {//in game state the background i drawn 
            ClearBackground(RAYWHITE);
           
            DrawTextureEx(backgroundTexture, Vector2{ 0,0 }, 0, 2.6f, WHITE);
            DrawTextureEx(tank1, Vector2{ PosX,PosY }, 0, 0.3, WHITE);//tanks are srawn on their picture
            DrawTextureEx(tank2, Vector2{ PosA,PosB }, 0, 0.3, WHITE);
            if (n % 2 == 1) {//texture pro function is used to rotate the aim around the axix for player 1
                Rectangle sourceRec = { 0, 0, aim.width, aim.height };
                Rectangle destRec = { X, Y , aim.width * 0.5f, aim.height * 0.5f };
                Vector2 origin = { aim.width * 0.4f, aim.height * 0.4f };
                DrawTexturePro(aim, sourceRec, destRec, origin, rotationAngle1, WHITE);
            }
            if (n % 2 == 0) {//texture pro function is used to rotatae the aim around fix origin for player 2
                Rectangle sourceRec2 = { 0, 0, aim.width, aim.height };
                Rectangle destRec2 = { A, B, aim.width * 0.5f, aim.height * 0.5f };
                Vector2 origin2 = { aim.width * 0.1f, aim.height * 0.1f };
                DrawTexturePro(aim, sourceRec2, destRec2, origin2, -rotationAngle2, WHITE);//negative sign is used to rotate the aim to opposite direction
            }
            DrawText("PLAYER 1 HEALTH:", 1150, 50, 40, BLACK);//player 1 and 2 health
            DrawText("PLAYER 2 HEALTH:", 150, 50, 40, BLACK);
            
          //  DrawText("\n\n\n   DO\n\n\n\n\n  NOT\n\n\n\n\nSHOOT\n\n\n\n\n HERE", 760, 500, 20, WHITE);
            DrawTextureEx(wall,Vector2{755,510,},0,0.35,WHITE);
            DrawRectangle(760, 500, 70, 400, BLANK);//its a wall between the screen
            DrawRectangleRec(tank1health, GREEN);
            DrawRectangleRec(tank2health, GREEN);
            if (draw==1) {
                DrawTextureEx(missile1, Vector2{ PosX1,PosY1 }, 0, 0.15, WHITE);
            }
            if (draw2 == 1) {
                DrawTextureEx(missile2, Vector2{ PosA1,PosB1 }, 0, 0.15, WHITE);
            }
            DrawRectangleRec(fire1, BLANK);//draw the fire and box behind the tank and missile
            DrawRectangleRec(fire2, BLANK);
            DrawRectangleRec(box, BLANK);
            DrawRectangleRec(box2, BLANK);
            if (winner == 1) {//check the winning condition and print the following text
                if (textVisible) {
                    DrawText("            PLAYER 1 WINS!!!\n\n\n\n    PRESS SPACE TO PLAY AGAIN\n\n\n\nPRESS ENTER TO GO TO MAIN MENU", 470, 130, 40, BLACK);
                }
            }
            else if (winner == 2) {
                if (textVisible) {
                    DrawText("            PLAYER 2 WINS!!!\n\n\n\n    PRESS SPACE TO PLAY AGAIN\n \n\n\nPRESS ENTER TO GO TO MAIN MENU", 470, 130, 40, BLACK);
                }
            }
        }
        EndDrawing();
    }
    CloseAudioDevice(); // Close audio device
    CloseWindow();
    return 0;
}