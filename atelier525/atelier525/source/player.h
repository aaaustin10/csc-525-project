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

			void goForward(float et);
			void goBackward(float et);
			void goLeft(float et);
			void goRight(float et);
			void goUp(float et);
			void goDown(float et);
			void stop();
			void addYaw(float d);
			void addPitch(float d);
			void setDist(float d){dist = d;}

			float getDist(){ return dist; }
			float getX(){ return xpos; }
			float getY(){ return ypos; }
			float getZ(){ return zpos; }

			void move(float et);
			void jump();
			void fall(float et);
		
			float getYaw(){ return yaw; }
			float getPitch(){ return pitch; }

			bool dir[6]; // 0-w 1-a 2-s 3-d 4-space
		private:
			float xpos, ypos, zpos;
			float vAcc, hAcc;
			bool g;
			float yaw;
			float pitch;
			float dist;
	};
#endif //PLAYER_H