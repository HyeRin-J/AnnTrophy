#pragma once

class Switch :
    public Component
{
private:
    float           m_InteractionTime = 0.f;
    bool            m_PreserveFinish = false;
    Sprite*         m_pSprite;

public:
    GameObject*     m_Gate;
    BoxCollider*    m_Collider;

    virtual void Awake();
    virtual void Update();
    virtual void OnRender();

    void Init();
};

