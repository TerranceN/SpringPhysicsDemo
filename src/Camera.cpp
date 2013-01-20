#include "Camera.h"

Camera::Camera()
{
    rotation = 0;
    scale = 1;

    translationSpeed = 1;
    rotationSpeed = 1;
    scaleSpeed = 1;

    rotationFocus = 0;
    scaleFocus = 1;

    transformationMatrix = Matrix4::Identity();
    invTransformationMatrix = Matrix4::Identity();

    needsRecalculating = false;
}

Vector2 Camera::ScreenToWorld(Vector2 point)
{
    if (needsRecalculating)
    {
        CalculateMatricies();
        needsRecalculating = false;
    }

    return invTransformationMatrix.Transform(point);
}

Vector2 Camera::WorldToScreen(Vector2 point)
{
    if (needsRecalculating)
    {
        CalculateMatricies();
        needsRecalculating = false;
    }

    return transformationMatrix.Transform(point);
}

void Camera::Apply()
{
    if (needsRecalculating)
    {
        CalculateMatricies();
        needsRecalculating = false;
    }

    glLoadMatrixf(transformationMatrix.GetData());
}

void Camera::ForceRotation(float focus)
{
    rotation = focus;
    rotationFocus = focus;
}

void Camera::ForceScale(float focus)
{
    scale = focus;
    scaleFocus = focus;
}

void Camera::ForceTranslation(Vector2 focus)
{
    translation = focus;
    translationFocus = focus;
}

void Camera::SetRotationFocus(float focus)
{
    rotationFocus = focus;
}

void Camera::SetRotationSpeed(float speed)
{
    rotationSpeed = speed;
}

void Camera::SetScaleFocus(float focus)
{
    scaleFocus = focus;
}

void Camera::SetScaleSpeed(float speed)
{
    scaleSpeed = speed;
}

void Camera::SetTranslationFocus(Vector2 focus)
{
    translationFocus = focus;
}

void Camera::SetTranslationSpeed(float speed)
{
    translationSpeed = speed;
}

void Camera::Update(Window* window)
{
    needsRecalculating = true;

    UpdateTranslation(window);
    UpdateRotation(window);
    UpdateScale(window);
}

void Camera::UpdateRotation(Window* window)
{
    float destination = rotationFocus;

    while (destination <= rotation)
        destination += 8 * atan(1);

    float difference = destination - rotation;

    if (difference < 4 * atan(1))
    {
        rotation += difference * rotationSpeed * window->GetDeltaTime();
    }
    else
    {
        rotation -= (8 * atan(1) - difference) * rotationSpeed * window->GetDeltaTime();
    }
}

void Camera::UpdateScale(Window* window)
{
    float difference = scaleFocus - scale;

    scale += difference * scaleSpeed * window->GetDeltaTime();
}

void Camera::UpdateTranslation(Window* window)
{
    Vector2 centreScreen = Vector2(window->GetWidth(), window->GetHeight()) / 2;
    Vector2 centreScreenInWorld = ScreenToWorld(centreScreen);

    translation += (centreScreenInWorld - translationFocus) * translationSpeed * window->GetDeltaTime();
}

float Camera::FloatMod(float number, float modulo)
{
    float temp = number;
    if (temp > modulo)
    {
        while (temp > modulo)
        {
            temp -= modulo;
        }
    }
    else if (temp < 0)
    {
        while (temp < 0)
        {
            temp += modulo;
        }
    }

    return temp;
}

void Camera::CalculateMatricies()
{
    transformationMatrix = Matrix4::FromTranslation(Vector2(800, 450))
        * Matrix4::FromScale(scale, scale, 1)
        * Matrix4::FromRotationZ(rotation)
        * Matrix4::FromTranslation(translation);
        //* Matrix4::FromTranslation(Vector2(-800, -450));

    invTransformationMatrix = transformationMatrix.GetInverse();
}

