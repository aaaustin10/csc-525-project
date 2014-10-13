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
		void goForward();
		void goBackward();
		void goLeft();
		void goRight();
		void goUp();
		void goDown();
		void stop();
		void addYaw(float d);
		void addPitch(float d);
		void setDist(float d){dist = d;}

		float getX(){ return xpos; }
		float getY(){ return ypos; }
		float getZ(){ return zpos; }
		int getChunkX(){ return (int) floor(xpos/16.0f); }
		int getChunkZ(){ return (int) floor(zpos/16.0f); }
		
		float getYaw(){ return yaw; }
		float getPitch(){ return pitch; }
	private:
		float xpos, ypos, zpos;
		float yaw;
		float pitch;
		float dist;
};
#endif