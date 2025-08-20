#pragma once
#include "sound/SoundSource.h"
class Loading;
class Title : public IGameObject
{
public:
    Title();
    ~Title();
    //�`��֐��B
    void Render(RenderContext& rc);
    //�X�V�����B
    void Update();
    //�X�v���C�g�����_�\�B
    SpriteRender spriteRender;
    SoundSource* titleBGM; //�^�C�g����BGM�B
    FontRender fonRender;
    float m_color = 0.4f;
    bool m_colorSteto = false;
    
};

