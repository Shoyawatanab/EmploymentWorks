#pragma once

class ButtonComponent;


class UIManager
{
public:
	//�R���X�g���N
	UIManager();
	//�f�X�g���N�^
	~UIManager();

	//�X�V����
	void Update(const float& deltaTime);

	void AddButtomComponent(ButtonComponent* buttom);

private:
	//�͈͓���
	bool CheckInRange(const DirectX::SimpleMath::Vector2& mousePosition,ButtonComponent* buttom);

private:

	std::vector<ButtonComponent*> m_buttom;

};


