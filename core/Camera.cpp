#include <Camera.h>

CameraActor::Camera(
    const std::string& name,
    glm::vec3 position,
    glm::quat rotation,
    float aspectRatio,
    float nearPlane,
    float farPlane,
    float fieldOfView,
    float maxMovementSpeed,
    float accelerationSpeed,
    float dampingFactor)
    : Actor(name),
    mMaxMovementSpeed(maxMovementSpeed),
    mAccelerationSpeed(accelerationSpeed),
    mDampingFactor(dampingFactor),
    mAspectRatio(aspectRatio),
    mNearPlane(nearPlane),
    mFarPlane(farPlane),
    mFieldOfView(fieldOfView)
{
    SetPosition(position);
    SetRotation(rotation);
    UpdateProjectionMatrix();
}

void CameraActor::UpdateVelocity(float dt)
{
    mVelocity += mAcceleration * dt;

    if (glm::length(mVelocity) > mMaxMovementSpeed) 
    {
        mVelocity = glm::normalize(mVelocity) * mMaxMovementSpeed;
    }
}

void CameraActor::UpdateDamping(float dt)
{
    float dampingFactor = glm::length(mVelocity) > 0 ? mDampingFactor : 0.0f;

    mVelocity -= mVelocity * dampingFactor * dt;

    if (glm::length(mVelocity) < 0.001f) 
    {
        mVelocity = glm::vec3(0.0f);
    }
}

void CameraActor::UpdatePosition(float dt)
{
    glm::vec3 front = GetFront();
    glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
    glm::vec3 up = glm::cross(right, front);

    SetPosition(GetPosition() + mVelocity.x * dt * right + mVelocity.y * dt * up + mVelocity.z * dt * front);
}

void CameraActor::Update(float dt)
{
    UpdateVelocity(dt);
    UpdatePosition(dt);
    UpdateDamping(dt);
}

void CameraActor::AddVelocity(const glm::vec3& velocity)
{
    mVelocity += velocity;
}

void CameraActor::SetAspectRatio(float aspectRatio)
{
    mAspectRatio = aspectRatio;
    UpdateProjectionMatrix();
}

void CameraActor::SetVelocity(const glm::vec3& velocity)
{
    mVelocity = velocity;
}

void CameraActor::SetAccelerationSpeed(float accelerationSpeed)
{
    mAccelerationSpeed = accelerationSpeed;
}

void CameraActor::SetAcceleration(const glm::vec3& acceleration)
{
    mAcceleration = acceleration;
}

void CameraActor::SetMaxMovementSpeed(float movementSpeed)
{
    mMaxMovementSpeed = movementSpeed;
}

glm::mat4 CameraActor::GetViewMatrix() const
{
    return glm::lookAt(GetPosition(), GetPosition() + GetFront(), glm::vec3(0.0f, 1.0f, 0.0f));
}

const glm::mat4& CameraActor::GetProjectionMatrix() const
{
    return mProjectionMatrix;
}

glm::vec3 CameraActor::GetFront() const
{
    return glm::rotate(GetRotation(), glm::vec3(0.0f, 0.0f, -1.0f));
}

glm::vec3 CameraActor::GetUp() const
{
    return glm::rotate(GetRotation(), glm::vec3(0.0f, 1.0f, 0.0f));
}

const glm::vec3& CameraActor::GetVelocity() const
{
    return mVelocity;
}

float CameraActor::GetMaxMovementSpeed() const { return mMaxMovementSpeed; }
float CameraActor::GetAspectRatio() const { return mAspectRatio; }
float CameraActor::GetNearPlane() const { return mNearPlane; }
float CameraActor::GetFarPlane() const { return mFarPlane; }
float CameraActor::GetFieldOfView() const { return mFieldOfView; }
float CameraActor::GetAccelerationSpeed() const{ return mAccelerationSpeed; }
const glm::vec3& CameraActor::GetAcceleration() const{ return mAcceleration; }

glm::mat4 CameraActor::GetVPMatrix() const
{
    return mProjectionMatrix * GetViewMatrix();
}

void CameraActor::UpdateProjectionMatrix()
{
    mProjectionMatrix = glm::perspective(glm::radians(mFieldOfView), mAspectRatio, mNearPlane, mFarPlane);
}