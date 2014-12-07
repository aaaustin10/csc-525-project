
#include "includes.h"

Camera::Camera():
x_position(0.0f),
y_position(0.0f),
z_position(0.0f),
yaw(0.0f),
pitch(0.0f),
player(nullptr),
x_lookAt(0.0f),
y_lookAt(0.0f),
z_lookAt(1.0f)
{
}

Camera::Camera(float x, float y, float z):
x_position(x),
y_position(y),
z_position(z),
yaw(0.0f),
pitch(0.0f),
player(nullptr),
x_lookAt(0.0f),
y_lookAt(0.0f),
z_lookAt(1.0f)
{
}

void Camera::updatePosition()
{
    x_position = player->getX();
	y_position = player->getY();
	z_position = player->getZ();
}

void Camera::apply()
{
	updatePosition();
    yaw = player->getYaw();
	pitch = player->getPitch();
	
	x_lookAt = x_position + cos(yaw)*(cos(pitch));
	y_lookAt = y_position + sin(pitch);
	z_lookAt = z_position + sin(yaw)*(cos(pitch));

    // set the camera
	const float y_offset = 1.63;
	gluLookAt(x_position, y_position + y_offset, z_position,
              x_lookAt, y_lookAt + y_offset, z_lookAt,
              0.0f, 1.0f, 0.0);
}
