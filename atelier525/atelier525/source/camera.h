#ifndef CAMERA_H
	#define CAMERA_H

	class Player;

	class Camera {
	public:
		Camera(float x, float y, float z);
		Camera();

		void updatePosition();
		void apply();

		void attachTo(Player& p)
		{
			player = &p;
		}
	private:
		float x_position, y_position, z_position;
		float x_lookAt, y_lookAt, z_lookAt;

		float yaw;
		float pitch;

		Player* player;
	};

#endif // CAMERA_H
