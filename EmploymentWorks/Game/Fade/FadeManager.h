#pragma once
#include "Libraries/WataLib/Singleton.h"
#include "Game/Fade/IFade.h"

class Camera;
class IFade;
class NormalFade;

class FadeManager : public Singleton<FadeManager>
{
	friend class Singleton<FadeManager>;

public:
	//�t�F�[�h�̏��
	enum class FadeState
	{
		NONE                //�ʏ�
		,FADE_IN    	    //�t�F�[�h�C��
		,FADE_IN_END	    //�t�F�[�h�C���I��
		,FADE_OUT		    //�t�F�[�h�A�E�g
	};

	//�t�F�[�h�C���̎��
	enum  class FadeInKinds
	{

		NORMAL_FADE_IN                 //�m�[�}���t�F�[�h�C��

	};
	//�t�F�[�h�A�E�g�̎��
	enum  class FadeOutKinds
	{

		NORMAL_FADE_OUT			   //�m�[�}���t�F�[�h�A�E�g

	};


public:

	//�t�F�[�h��Ԃ̎擾
	FadeState GetFadeState() { return m_fadeState; }
	//�t�F�[�h���s�����̎擾�@true�F���s���@false�F�����s
	bool GetIsFade() const { return m_isFade; }



public:
	//�R���X�g���N
	FadeManager();
	//�f�X�g���N�^
	~FadeManager() override;
	//�X�V����
	void Update(const float& deltaTime);
	//�`��
	void Render();
	//�t�F�[�h�C���̃X�^�[�g
	void StartFadeIn(FadeInKinds kinds);
	//�t�F�[�h�C���̃X�^�[�g�@�m�[�}���t�F�[�h
	void StartFadeIn();
	//�t�F�[�h�A�E�g�̃X�^�[�g
	void StartFadeOut(FadeOutKinds kinds);
	//�t�F�[�h�A�E�g�̃X�^�[�g�@�m�[�}���t�F�[�h
	void StartFadeOut();

private:

	//�t�F�[�h�C���̒ǉ�
	void AddFadeIn(FadeInKinds kinds, std::unique_ptr<IFade> fade);
	//�t�F�[�h�A�E�g�̒ǉ�
	void AddFadeOut(FadeOutKinds kinds, std::unique_ptr<IFade> fade);
	//�t�F�[�h�̐؂�ւ�
	void ChangeFade(IFade* fade);
private:
	//���s�t�F�[�Y
	IFade* m_currentFade;
	//�t�F�[�h���
	FadeState m_fadeState;

	//�t�F�[�h�C���z��
	std::unordered_map<FadeInKinds, std::unique_ptr<IFade>> m_fadeInList;
	//�t�F�[�h�A�E�g�z��
	std::unordered_map<FadeOutKinds, std::unique_ptr<IFade>> m_fadeOutList;
	//�t�F�[�h���s�����@true�F���s���@false�F�����s
	bool m_isFade;

};




