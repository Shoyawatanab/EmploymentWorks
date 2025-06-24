#pragma once



class IFade
{
public:

	virtual ~IFade() = default;

	//�X�V����
	virtual bool Update(const float& deltaTime) = 0;
	//�`��
	virtual void Render() = 0;
	//��������
	virtual void Enter() = 0;
	//��������
	virtual void Exit() = 0;

};