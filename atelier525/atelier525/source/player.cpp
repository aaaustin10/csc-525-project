#include "includes.h"
const float PI = 3.1415927;
Player::Player():
dist(0),
yaw(0),
pitch(0),
xpos(0),
ypos(0),
zpos(0){

}

void Player::goForward(){
	
	float newX, newZ, newY;
	newX = this->getX() + dist*cos(yaw)*(cos(pitch));
	newZ = this->getZ() + dist*sin(yaw)*(cos(pitch));
	newY = this->getY() + dist*sin(pitch);
	setPosition(newX, newY, newZ);
}
void Player::goBackward(){
	
	float newX, newZ, newY;
	newX = getX() - dist*cos(yaw)*(cos(pitch));
	newZ = getZ() - dist*sin(yaw)*(cos(pitch));
	newY = getY() - dist*sin(pitch);
	setPosition(newX, newY, newZ);
}
void Player::goLeft(){
	float newX, newZ;
	newX = getX() - dist*cos(yaw+PI/2);
	newZ = getZ() - dist*sin(yaw+PI/2);
	setPosition(newX, getY(), newZ);
}
void Player::goRight(){
	float newX, newZ;
	newX = getX() + dist*cos(yaw+PI/2);
	newZ = getZ() + dist*sin(yaw+PI/2);
	setPosition(newX, getY(), newZ);
}
void Player::goUp(){
	setPosition(getX(), getY()+dist, getZ());
}
void Player::goDown(){
	setPosition(getX(), getY()-dist, getZ());
}
void Player::stop(){
	
}
void Player::addYaw(float d){
	yaw += d*(PI/180);
	if(yaw > 2 * PI){ yaw = 0; }
	if(yaw < 0){ yaw = 2*PI; }
}
void Player::addPitch(float d){
	pitch += d*(PI/180);
	if(pitch > PI/2.001f){ pitch = PI/2.001f;}
	if(pitch < -PI/2.001f){pitch = -PI/2.001f;}
}
