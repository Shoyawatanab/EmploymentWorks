#pragma once


// IObserver�C���^�[�t�F�[�X���`����
template <typename T>
class IObserver2 
{
public:
	//�ʒm���ɌĂяo�����
	virtual void FunctionExecution(T type,void* datas) = 0;

};

