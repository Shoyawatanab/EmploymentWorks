#pragma once
#ifndef IUI_DEFINED
#define IUI_DEFINED

class CommonResources;


// ICameCameraインタフェースを定義する(GOF Stateパターン)
class IUI
{
public:

	// 初期化する
	virtual void Initialize(CommonResources* resources) = 0;

	// 更新する
	virtual void Update(const float& elapsedTime) = 0;

	//描画
	virtual void Render() = 0;

	//状態に入った時
	virtual void Enter() = 0;
	//状態を抜けた時
	virtual void Exit() = 0;




};

#endif		// ICameCamera_DEFINED
