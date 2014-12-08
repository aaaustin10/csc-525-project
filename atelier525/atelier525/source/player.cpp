#include "includes.h"
const float PI = 3.1415927;
Player::Player():
speed(0),
yaw(PI),
pitch(-0.5),
xpos(0),
ypos(0),
zpos(0),
vAcc(0),
hAcc(0),
lastYaw(false),
g(true){
	for (int i = 0; i < 5; i++){
		dir[i] = false;
	}
	for (int i = 0; i < 5; i++){
		lastDir[i] = false;
	}
}

void Player::goForward(float et, bool useLastYaw){
	float tempYaw = yaw;
	if (useLastYaw){
		tempYaw = lastYaw;
	}
	float newX, newZ, newY;
	newX = getX() + hAcc*et*speed*cos(tempYaw);// *(cos(pitch));
	newZ = getZ() + hAcc*et*speed*sin(tempYaw);// *(cos(pitch));
	//newY = this->getY() + speed*sin(pitch);
	newY = getY();
	setPosition(newX, newY, newZ);
}
void Player::goBackward(float et, bool useLastYaw){
	float tempYaw = yaw;
	if (useLastYaw){
		tempYaw = lastYaw;
	}
	float newX, newZ, newY;
	newX = getX() - hAcc*et*speed*cos(tempYaw);
	newZ = getZ() - hAcc*et*speed*sin(tempYaw);
	newY = getY();
	setPosition(newX, newY, newZ);
}
void Player::goLeft(float et, bool useLastYaw){
	float tempYaw = yaw;
	if (useLastYaw){
		tempYaw = lastYaw;
	}
	float newX, newZ;
	newX = getX() - hAcc*et*speed*cos(tempYaw + PI / 2);
	newZ = getZ() - hAcc*et*speed*sin(tempYaw + PI / 2);
	setPosition(newX, getY(), newZ);
}
void Player::goRight(float et, bool useLastYaw){
	float tempYaw = yaw;
	if (useLastYaw){
		tempYaw = lastYaw;
	}
	float newX, newZ;
	newX = getX() + hAcc*et*speed*cos(tempYaw+PI/2);
	newZ = getZ() + hAcc*et*speed*sin(tempYaw + PI / 2);
	setPosition(newX, getY(), newZ);
}
void Player::goUp(float et){
	setPosition(getX(), getY()+speed*et, getZ());
}
void Player::goDown(float et){
	setPosition(getX(), getY()-speed*et, getZ());
}
void Player::move(float et){
	bool isMove = false;
	bool strafe = false;
	float oldspeed;
	if (dir[0]){
		if (!dir[2]){
			if (dir[1] != dir[3]){
				oldspeed = speed;
				strafe = true;
				setSpeed(speed / 2);
			}
			isMove = true;
			goForward(et);
			lastDir[0] = true;
			lastDir[2] = false;
			if (!dir[1]){ lastDir[1] = false; }
			if (!dir[3]){ lastDir[3] = false; }
		}
	}
	if (dir[2]){
		if (!dir[0]){
			if (dir[1] != dir[3]){
				oldspeed = speed;
				strafe = true;
				setSpeed(speed / 2);
			}
			isMove = true;
			goBackward(et);
			lastDir[0] = false;
			lastDir[2] = true;
			if (!dir[1]){ lastDir[1] = false; }
			if (!dir[3]){ lastDir[3] = false; }
		}
	}
	if (dir[1]){
		if (!dir[3]){
			isMove = true;
			goLeft(et);
			lastDir[1] = true;
			lastDir[3] = false;
		}
		if (!dir[0]){ lastDir[0] = false; }
		if (!dir[2]){ lastDir[2] = false; }
	}

	if (dir[3]){
		if (!dir[1]){
			isMove = true;
			goRight(et);
			lastDir[1] = false;
			lastDir[3] = true;
		}
		if (!dir[0]){ lastDir[0] = false; }
		if (!dir[2]){ lastDir[2] = false; }
	}
	if (strafe){
		setSpeed(oldspeed);
	}
	if (dir[4]){
		jump();
		g = false;
	}
	fall(et);


	if (hAcc > 0 && !isMove){
		float tempOldSpeed = 0;
		bool useOldSpeed = false;
		if (lastDir[0]){
			if (lastDir[1] != lastDir[3]){
				tempOldSpeed = speed;
				speed = speed / 2;
				useOldSpeed = true;
			}
			goForward(et, true);
		}
		if (lastDir[2]){
			if (lastDir[1] != lastDir[3]){
				tempOldSpeed = speed;
				speed = speed / 2;
				useOldSpeed = true;
			}
			goBackward(et, true);
		}
		if (lastDir[3]){
			goRight(et, true);
		}
		if (lastDir[1]){
			goLeft(et, true);
		}
		if (useOldSpeed){
			speed = tempOldSpeed;
		}
	}

	if (isMove){
		lastYaw = yaw;
		if (hAcc < 1){
			hAcc += et * 3.0;
			if (hAcc > 1){
				hAcc = 1;
			}
		}
	}
	else{
		if (hAcc > 0 && g){
			hAcc -= et * 3.0;
			if (hAcc < 0){
				hAcc = 0;
			}
		}
	}
	if (getY() > 0){
		vAcc -= et * 9.8;
	}
}
void Player::jump(){
	vAcc = 3;
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
