#pragma once

class ActionController;

class ActionManager
{
public:
	//�R���X�g���N�^
	ActionManager();
	//�f�X�g���N�^
	virtual ~ActionManager();
	//�X�V���� true:���s�I��   false:���s��
	bool Update(const float& deltaTime);

	void SetStartAction(const std::string& name);

	//�s���̕ύX
	void ChangeAction(const std::string& actionName);
	//�s���̒ǉ�
	void AddAction(const std::string& name, std::unique_ptr<ActionController> action);

private:
	//���s�A�N�V����
	std::pair<std::string, ActionController*> m_action;
	//�A�N�V�����̕ۑ��ϐ�
	std::unordered_map<std::string, std::unique_ptr<ActionController>> m_actionList;


};