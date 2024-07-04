#define _XOPEN_SOURCE 700
#include<SFML/Graphics.hpp>
#include<unistd.h>
#include<string>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<pthread.h>
#include<ctime>
#include<iostream>
#include<chrono>
#include<X11/Xlib.h>
#include<SFML/Audio.hpp>

using namespace std;
using namespace sf;

struct greenOBJ{
    sf::Sprite* green1;
    int width;
    int height;
};

struct redOBJ{
    sf::Sprite* red1;
    int width;
    int height;
};
void delay(int milliseconds)
{
    auto start = std::chrono::steady_clock::now();
    while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() < milliseconds);
}
void* Green_movement(void* argz){
    greenOBJ* g1=(greenOBJ*)argz;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && g1->green1->getPosition().x > 30)
    {
       // cout << "A" << endl;
        g1->green1->move(-(g1->width), 0.f);
        delay(200);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && g1->green1->getPosition().x < 550)
    {
        //cout << "D" << endl;
        g1->green1->move(g1->width, 0.f);
        delay(200);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && g1->green1->getPosition().y > 0)
    {
        //cout << "W" << endl;
        g1->green1->move(0.f, (-g1->height));
        delay(200);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && g1->green1->getPosition().y < 540)
    {
        //cout << "S" << endl;
        g1->green1->move(0.f, (g1->height));
        delay(200);
    }
    pthread_exit(NULL);
}
void* Red_movement(void* argz1){
    redOBJ* red1=(redOBJ*)argz1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && red1->red1->getPosition().x > 10)
    {
        //cout << "Left" << endl;
        red1->red1->move(-(red1->width), 0.f);
        delay(200);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && red1->red1->getPosition().x < 550)
    {
       // cout << "Right" << endl;
        red1->red1->move((red1->width), 0.f);
        delay(200);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && red1->red1->getPosition().y > 0)
    {
        //cout << "Up" << endl;
        red1->red1->move(0.f, (-(red1->height)));
        delay(200);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && red1->red1->getPosition().y < 540)
    {
        //cout << "Down" << endl;
        red1->red1->move(0.f, ((red1->height)));
       delay(200);
    }
    pthread_exit(NULL);
}

int calculate_size(){
     srand(time(0));
int x= rand()%90 + 10;
x=x*4; //as 4 is last digit of my roll num
int roll=0704;
roll=roll/x;
roll=roll%25;
if(roll<10){
roll+=15;
}
return roll;
}

void create_board(){
        sf::RenderWindow window(sf::VideoMode(800, 600), "AMONG GEMS");
        window.clear(sf::Color(128,128,128));
    bool alternate=false,not_drawn=true;
    int n= calculate_size(); //total blocks are n by n
    cout<<"The number of blocks are: "<<n<<"x"<<n<<endl;
    
    // sf::RectangleShape board[n][n];
    int block_width=600/n; //width of each block
    int block_height=600/n; //height of each block
    // cout<<"block_width is: "<<block_width<<endl;
    // cout<<"block_height is: "<<block_height<<endl; 
    // for(int i=0;i<n;i++){ 
    //             for(int j=0;j<n;j++){
    //                 board[i][j]=sf::RectangleShape(sf::Vector2f(block_width,block_height));
    //                 board[i][j].setPosition(i*block_height,j*block_width);
    //             if((i+j)%2==0){   //if false create white box
    //                     board[i][j].setFillColor(Color::Black);
    //                     window.draw(board[i][j]); 
    //             }
    //             else{       //else create black box
    //                 board[i][j].setFillColor(Color::White);
    //                 window.draw(board[i][j]); 
    //             }
    //         }
    // } 
   //PLAYER1 = RED
    sf::Texture Red_Player;
    Red_Player.loadFromFile("Red2.png");
    sf::Sprite red1;
    red1.setTexture(Red_Player);
    red1.setPosition((0*block_height),0*block_width);
    float red_width=(block_width*1.0)/217.0;
    float red_height=(block_height*1.0)/233.0;
    //cout<<red_width;
    //cout<<red_height;
    red1.setScale(red_width,red_height);
    window.draw(red1);
    
    //PLAYER2 = GREEN
    sf::Texture Green_Player;
    Green_Player.loadFromFile("Green1.png");
    sf::Sprite green1;
    green1.setTexture(Green_Player);
    green1.setPosition(((n-1)*block_height),(n-1)*block_width);
    float green_width=(block_width*1.0)/800.0;
    float green_height=(block_height*1.0)/800.0;
    green1.setScale(green_width,green_height);
    window.draw(green1);    

    //GEM OBJECTS BELOW
    //PLAYER2 = GREEN
    sf::Texture GEM[25];
    sf::Sprite gems[25];
   for(int i=0;i<25;i++){
    GEM[i].loadFromFile("gem.jpeg");
    int random_x=rand()%(n);
    int random_y=rand()%(n);
    gems[i].setTexture(GEM[i]);
    gems[i].setPosition(random_x*block_height+(block_height/4),random_y*block_width+(block_width/4));
    float gem_width=(block_width*1.0)/0.0;
    float gem_height=(block_height*1.0)/0.0;
    //cout<<"\nRandomX:"<<random_x<<"RandomY:"<<random_y<<endl;
    gems[i].setScale(green_width*2,green_height*2);
    window.draw(gems[i]);    
   }
        //font for message of red player
        sf::Font score1;
        score1.loadFromFile("arial.ttf");
        sf::Text red_score("Player1 Score: ",score1,24);
        red_score.setPosition(600,200);
        red_score.setFillColor(sf::Color::Red);

        //font for message of green player
        sf::Font score2;
        score2.loadFromFile("arial.ttf");
        sf::Text green_score("Player2 Score: ",score2,24);
        green_score.setPosition(600,400);
        green_score.setFillColor(sf::Color::Green);

        //font for message of WINNER player1
        sf::Font gameend;
        gameend.loadFromFile("arial.ttf");
        sf::Text winner1("PLAYER1 WINS!", gameend,24);
        winner1.setPosition(620,100);
        winner1.setFillColor(sf::Color::Red);

        sf::Text winner2("PLAYER2 WINS!", gameend,24);
        winner2.setPosition(620,100);
        winner2.setFillColor(sf::Color::Green);

        int gem_count=25;
        int player1_score=0;
        int player2_score=0;

        sf::Font ScoreOutput_Red;
        ScoreOutput_Red.loadFromFile("arial.ttf");
        
       sf::Font ScoreOutput_Green;
        ScoreOutput_Green.loadFromFile("arial.ttf");

        //movement code here
        pthread_t t1; //for red
        pthread_attr_t attr1;
        pthread_attr_init(&attr1);
        pthread_attr_setdetachstate(&attr1,PTHREAD_CREATE_DETACHED);


        pthread_t t2; //for green
        pthread_attr_t attr2;
        pthread_attr_init(&attr2);
        pthread_attr_setdetachstate(&attr2,PTHREAD_CREATE_DETACHED);
        
        greenOBJ* G1 = new greenOBJ;
        redOBJ* R1 = new redOBJ;
        
        G1->green1=&green1;
        G1->width=block_width;
        G1->height=block_height;

        R1->red1=&red1;
        R1->width=block_width;
        R1->height=block_height;

    //SOUND EFFECT FOR GEM COLLECTION BELOW
  
    sf::SoundBuffer buffer;
    buffer.loadFromFile("gem_sound.wav");
    sf::Sound sound;
    sound.setBuffer(buffer);

    while (window.isOpen())
    {     
       window.clear();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        sf::RectangleShape board[n][n];
    int block_width=600/n; //width of each block
    int block_height=600/n; //height of each block
   // cout<<"block_width is: "<<block_width<<endl;
   // cout<<"block_height is: "<<block_height<<endl; 
    for(int i=0;i<n;i++){ 
                for(int j=0;j<n;j++){
                    board[i][j]=sf::RectangleShape(sf::Vector2f(block_width,block_height));
                    board[i][j].setPosition(i*block_height,j*block_width);
                if((i+j)%2==0){   //if false create white box
                        board[i][j].setFillColor(Color::Black);
                        window.draw(board[i][j]); 
                }
                else{       //else create black box
                    board[i][j].setFillColor(Color::White);
                    window.draw(board[i][j]); 
                }
            }
    } 
       
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            window.close();
            break;
        }
        
        pthread_create(&t1,&attr1,Red_movement,(void*)R1);
        pthread_create(&t2,&attr2,Green_movement,(void*)G1);

        delay(200);


        //SCORE RELATED CONDITONS BELOW
        for(int i=0;i<25;i++){
        if(red1.getPosition().x==((gems[i].getPosition().x)-(block_height/4)) && red1.getPosition().y==((gems[i].getPosition().y)-(block_width/4))){
            gems[i].setColor(sf::Color::Transparent);
            gems[i].setPosition(700,700);
            player1_score+=10;
            gem_count--;
             sound.play();
            delay(200);
            break;
        }
        if(green1.getPosition().x==((gems[i].getPosition().x)-(block_height/4)) && green1.getPosition().y==((gems[i].getPosition().y)-(block_width/4))){
            gems[i].setColor(sf::Color::Transparent);
            gems[i].setPosition(700,700);
            player2_score+=10;
            gem_count--;
            sound.play();
            delay(200);
            break;
        }
        }
        //window.draw(obj1);
        for(int i=0;i<25;i++){
            window.draw(gems[i]);
        }
       //UPDATING Red SCORE CODE BELOW
        sf::Text red_scoreOutput(to_string(player1_score),ScoreOutput_Red,22);
        red_scoreOutput.setPosition(750,200);
        red_scoreOutput.setFillColor(sf::Color::Red);

        //UPDATING Green SCORE CODE BELOW
        sf::Text green_scoreOutput(to_string(player2_score),ScoreOutput_Green,22);
        green_scoreOutput.setPosition(750,400);
        green_scoreOutput.setFillColor(sf::Color::Green);

       if(gem_count==0){
            if(player1_score>player2_score){
                window.draw(winner1);
            }
            else{
                window.draw(winner2);
            }
       }
       window.draw(red1); 
       window.draw(green1); 
       window.draw(red_score);
       window.draw(green_score);
       window.draw(red_scoreOutput);
       window.draw(green_scoreOutput);
        window.display();
    }
}

int main() {
    XInitThreads();
    create_board();
    return 0;
}
