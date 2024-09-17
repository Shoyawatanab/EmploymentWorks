#pragma once
#ifndef IUI_DEFINED
#define IUI_DEFINED

class CommonResources;


// ICameCamera�C���^�t�F�[�X���`����(GOF State�p�^�[��)
class IUI
{
public:

	// ����������
	virtual void Initialize(CommonResources* resources) = 0;

	// �X�V����
	virtual void Update(const float& elapsedTime) = 0;

	//�`��
	virtual void Render() = 0;

	//��Ԃɓ�������
	virtual void Enter() = 0;
	//��Ԃ𔲂�����
	virtual void Exit() = 0;




};

#endif		// ICameCamera_DEFINED
