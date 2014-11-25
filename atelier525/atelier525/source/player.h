#ifndef PLAYER_H
	#define PLAYER_H
	class Player{
		public:
			Player();
			void setPosition(float x, float y, float z){ 
				xpos = x;
				ypos = y;
				zpos = z;
			}
			void setX(float x){ xpos = x; }
			void setY(float y){ ypos = y; }
			void setZ(float z){ zpos = z; }

			void goForward(float et, bool useLastYaw = false);
			void goBackward(float et, bool useLastYaw = false);
			void goLeft(float et, bool useLastYaw = false);
			void goRight(float et, bool useLastYaw = false);
			void goUp(float et);
			void goDown(float et);
			void stop();
			void addYaw(float d);
			void addPitch(float d);
			void setSpeed(float d){speed = d;}

			float getSpeed(){ return speed; }
			float getX(){ return xpos; }
			float getY(){ return ypos; }
			float getZ(){ return zpos; }

			void move(float et);
			void jump();
			void fall(float et);
		
			float getYaw(){ return yaw; }
			float getPitch(){ return pitch; }

			bool dir[5]; // 0-w 1-a 2-s 3-d 4-space
		private:
			float xpos, ypos, zpos;
			float vAcc, hAcc;
			bool lastDir[5];
			float lastYaw;
			float speed; // m/s
			bool g;
			float yaw;
			float pitch;
	};
#endif //PLAYER_H