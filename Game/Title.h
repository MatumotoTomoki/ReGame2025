#pragma once
#include "sound/SoundSource.h"
class Loading;
class Title : public IGameObject
{
public:
    Title();
    ~Title();
    //描画関数。
    void Render(RenderContext& rc);
    //更新処理。
    void Update();
    //スプライトレンダ―。
    SpriteRender spriteRender;
    SoundSource* titleBGM; //タイトルのBGM。
    FontRender fonRender;
    float m_color = 0.4f;
    bool m_colorSteto = false;
    
};

