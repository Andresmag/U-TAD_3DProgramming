#pragma once
#include "../lib/entity.h"

class Mesh;
class Model;

typedef void (*CallbackFunc)(Model&, float);

class Model : public Entity
{
    const std::shared_ptr<Mesh> m_Mesh;
    CallbackFunc m_UpdateFunc;

public:
    Model(const std::shared_ptr<Mesh>& mesh);
    void setCallbackFunc(CallbackFunc func);

    virtual void update(float deltaTime) override;
    virtual void draw() override;
};
