#pragma once



class IFade
{
public:

	virtual ~IFade() = default;

	//更新処理
	virtual bool Update(const float& deltaTime) = 0;
	//描画
	virtual void Render() = 0;
	//入った時
	virtual void Enter() = 0;
	//抜けた時
	virtual void Exit() = 0;

};