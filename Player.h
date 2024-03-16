//
// Created by benra on 3/15/2024.
//

#ifndef UNTITLED1_PLAYER_H
#define UNTITLED1_PLAYER_H
#include "raylib.h"

class Player {
public:
    Vector2 GetPlayerPos();
    Camera2D getPlayerCamera();
    void update(float deltaTime);
    void draw();
    Player(int screenWidth, int screenHeight);
    ~Player();
    void move(Vector2& direction, float deltaTime);
private:
    Texture2D playerTextureMap;
    Vector2 playerPositionRounded;
    Camera2D playerFollowCamera;
    Vector2 playerSize;
    Vector2 movementDirection;
    float moveSpeed;
};


#endif //UNTITLED1_PLAYER_H
