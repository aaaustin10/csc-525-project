#include "includes.h"
const float PI = 3.1415927;
Player::Player():
dist(0),
yaw(0),
pitch(0),
xpos(0),
ypos(0),
zpos(0),
vAcc(0),
hAcc(0),
g(true){
	for (int i = 0; i < 5; i++){
		dir[i] = false;
	}
}

void Player::goForward(float et){
	
	float newX, newZ, newY;
	newX = getX() + et*dist*cos(yaw);// *(cos(pitch));
	newZ = getZ() + et*dist*sin(yaw);// *(cos(pitch));
	//newY = this->getY() + dist*sin(pitch);
	newY = getY();
	setPosition(newX, newY, newZ);
}
void Player::goBackward(float et){
	
	float newX, newZ, newY;
	newX = getX() - et*dist*cos(yaw);// *(cos(pitch));
	newZ = getZ() - et*dist*sin(yaw);// *(cos(pitch));
	//newY = getY() - dist*sin(pitch);
	newY = getY();
	setPosition(newX, newY, newZ);
}
void Player::goLeft(float et){
	float newX, newZ;
	newX = getX() - et*dist*cos(yaw+PI/2);
	newZ = getZ() - et*dist*sin(yaw+PI/2);
	setPosition(newX, getY(), newZ);
}
void Player::goRight(float et){
	float newX, newZ;
	newX = getX() + et*dist*cos(yaw+PI/2);
	newZ = getZ() + et*dist*sin(yaw+PI/2);
	setPosition(newX, getY(), newZ);
}
void Player::goUp(float et){
	setPosition(getX(), getY()+dist*et, getZ());
}
void Player::goDown(float et){
	setPosition(getX(), getY()-dist*et, getZ());
}
void Player::move(float et){
	bool isMove = false;
	bool strafe = false;
	float oldDist;
	if (dir[0]){
		if (!dir[2]){
			if (dir[1] != dir[3]){
				oldDist = dist;
				strafe = true;
				setDist(dist / 2);
			}
			isMove = true;
			goForward(et);
		}
	}
	if (dir[2]){
		if (!dir[0]){
			if (dir[1] != dir[3]){
				oldDist = dist;
				strafe = true;
				setDist(dist / 2);
			}
			isMove = true;
			goBackward(et);
		}
	}
	if (dir[1]){
		if (!dir[3]){
			isMove = true;
			goLeft(et);
		}
	}

	if (dir[3]){
		if (!dir[1]){
			isMove = true;
			goRight(et);
		}
	}
	if (strafe){
		setDist(oldDist);
	}
	if (dir[4]){
		jump();
		g = false;
	}
	fall(et);
	if (getY() > 0){
		vAcc -= et * 9.8;
	}
}
void Player::jump(){
	vAcc = 9.8;
}
void Player::fall(float et){
	if (!g){
		float temp = getY() + vAcc*et;
		if (temp > 0){
			setY(temp);
		}
		else{
			setY(0);
			g = true;
		}
	}
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
