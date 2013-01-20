#ifndef CAMERA_H
#define CAMERA_H

#include "Vector2.h"
#include "Matrix4.h"
#include "Window.h"

class Camera
{
    public:
        Camera();

        void Update(Window* window);
        void Apply();

        void SetTranslationFocus(Vector2 focus);
        void SetRotationFocus(float focus);
        void SetScaleFocus(float focus);

        void SetTranslationSpeed(float speed);
        void SetRotationSpeed(float speed);
        void SetScaleSpeed(float speed);

        void ForceTranslation(Vector2 focus);
        void ForceRotation(float focus);
        void ForceScale(float focus);

        Vector2 WorldToScreen(Vector2 point);
        Vector2 ScreenToWorld(Vector2 point);
    private:
        Vector2 translation;
        float rotation;
        float scale;

        float translationSpeed;
        float rotationSpeed;
        float scaleSpeed;

        Vector2 translationFocus;
        float rotationFocus;
        float scaleFocus;

        Matrix4 transformationMatrix;
        Matrix4 invTransformationMatrix;

        bool needsRecalculating;

        void UpdateTranslation(Window* window);
        void UpdateRotation(Window* window);
        void UpdateScale(Window* window);

        void CalculateMatricies();

        float FloatMod(float number, float modulo);
};

#endif
