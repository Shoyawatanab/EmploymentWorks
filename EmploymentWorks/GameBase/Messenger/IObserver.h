#pragma once


// IObserver�C���^�[�t�F�[�X���`����
template <typename T>
class IObserver 
{
public:
	//�ʒm���ɌĂяo�����
	virtual void Notify(T type,void* datas) = 0;

};

