//
// Created by benra on 3/15/2024.
//

#include "Player.h"
#include "MatchFuncts.h"
#include <cstdlib>
Player::Player(int screenWidth, int screenHeight) {
    playerFollowCamera = {0};
    playerFollowCamera.target = { float (screenWidth)/ 2 - 25, float(screenHeight) / 2 - 25 };
    playerFollowCamera.offset = (Vector2){ float(screenWidth)/ 2, float (screenHeight) / 2 };
    playerFollowCamera.rotation = 0.0f;
    playerFollowCamera.zoom = 1.0f;

    playerTextureMap = LoadTexture(R"(C:\Users\benra\CLionProjects\untitled1\Assets/Xmove.png)");

    playerPositionRounded = {50,50};
    playerSize = {33,60};

    movementDirection = {0,0};

    moveSpeed = 500;
}

Camera2D Player::getPlayerCamera() {
    return playerFollowCamera;
}
Player::~Player()= default;
void Player::update(float deltaTime) {
    Vector2 newMovementDirection = {0, 0};
    const float lerpThreshold = 0.2f;
    const float accelerationFactor = 40.0f;
    const float diagonalFactor = 0.5f;
    if (IsKeyDown(KEY_A)) newMovementDirection.x = -1.0f;
    if (IsKeyDown(KEY_D)) newMovementDirection.x = 1.0f;
    if (IsKeyDown(KEY_W)) newMovementDirection.y = -1.0f;
    if (IsKeyDown(KEY_S)) newMovementDirection.y = 1.0f;

    newMovementDirection = MatchFuncts::normalize(newMovementDirection);
    float lerpFactor = accelerationFactor * deltaTime;
    if (movementDirection.x != 0 && movementDirection.y != 0 &&
        (newMovementDirection.x == 0 || newMovementDirection.y == 0)) {
        lerpFactor *= diagonalFactor;
    }
    if (newMovementDirection.x != 0 || newMovementDirection.y != 0) {
        movementDirection = MatchFuncts::Vector2Lerp(movementDirection, newMovementDirection, lerpFactor);
    } else {
        movementDirection = MatchFuncts::Vector2Lerp(movementDirection, {0, 0}, lerpFactor);
    }
    move(movementDirection, deltaTime);

    if (MatchFuncts::Vector2Distance(movementDirection, newMovementDirection) < lerpThreshold) {
        movementDirection = newMovementDirection; // If the difference is small, set directly
    }
    playerFollowCamera.target.y = playerPositionRounded.y;
    playerFollowCamera.target.x = playerPositionRounded.x;
}


void Player::move(Vector2& direction, float deltaTime) {
    playerPositionRounded.x += direction.x * moveSpeed * deltaTime;
    playerPositionRounded.y += direction.y * moveSpeed * deltaTime;

}
void Player::draw() {
    DrawTexturePro(playerTextureMap, {21,16,11,20},{playerPositionRounded.x,playerPositionRounded.y,playerSize.x,playerSize.y},{0,0},0,WHITE);

}

