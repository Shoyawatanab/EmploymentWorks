//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto
// <����J�n��>		2025/06/12
// <file>			ParticleMath.cpp
// <�T�v>		�@�@�`��v�Z
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include<random>
namespace ParticleMath
{
	// �����_���G���W��
	inline std::mt19937& GetRNG()
	{
		static std::random_device rd;
		static std::mt19937 rng(rd());
		return rng;
	}

	// 0 1 �̃����_���l
	inline float Random01()
	{
		std::uniform_real_distribution<float> dist(0.0f,1.0f);
		return dist(GetRNG());
	}

	// -1 , 1 �̃����_���l
	inline float RandomSigned()
	{
		std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
		return dist(GetRNG());
	}
	
	// �C�Ӕ͈͂̃����_��(int)
	inline int RandomRange(int min, int max)
	{
		std::uniform_int_distribution<int> dist(min, max);
		return dist(GetRNG());
	}

	// �C�Ӕ͈͂̃����_��(float)
	inline float RandomRange(float min, float max)
	{
		std::uniform_real_distribution<float> dist(min, max);
		return dist(GetRNG());
	}

	// �C�Ӕ͈͂̃����_��(Vector2)
	inline DirectX::SimpleMath::Vector2 RandomRange(const DirectX::SimpleMath::Vector2& min, const DirectX::SimpleMath::Vector2& max)
	{
		return{
			RandomRange(min.x , max.x),
			RandomRange(min.y , max.y)
		};
	}

	// �C�Ӕ͈͂̃����_��(Vector3)
	inline DirectX::SimpleMath::Vector3 RandomRange(const DirectX::SimpleMath::Vector3& min, const DirectX::SimpleMath::Vector3& max)
	{
		return{
			RandomRange(min.x , max.x),
			RandomRange(min.y , max.y),
			RandomRange(min.z , max.z)
		};
	}

	// �C�Ӕ͈͂̃����_��(Vector4)
	inline DirectX::SimpleMath::Vector4 RandomRange(const DirectX::SimpleMath::Vector4& min, const DirectX::SimpleMath::Vector4& max)
	{
		return{
			RandomRange(min.x , max.x),
			RandomRange(min.y , max.y),
			RandomRange(min.z , max.z),
			RandomRange(min.w , max.w)
		};
	}

	// �C�Ӕ͈͂̃����_��(Quaternion)
	inline DirectX::SimpleMath::Quaternion RandomRange(const DirectX::SimpleMath::Quaternion& min, const DirectX::SimpleMath::Quaternion& max)
	{
		return{
			RandomRange(min.x , max.x),
			RandomRange(min.y , max.y),
			RandomRange(min.z , max.z),
			RandomRange(min.w , max.w)
		};
	}

	// �C�Ӕ͈͂̃����_��(Color)
	inline DirectX::SimpleMath::Color RandomRange(const DirectX::SimpleMath::Color& min, const DirectX::SimpleMath::Color& max)
	{
		return{
			RandomRange(min.x , max.x),
			RandomRange(min.y , max.y),
			RandomRange(min.z , max.z),
			RandomRange(min.w , max.w)
		};
	}




	// �P�ʕ��ʏ�̃����_���x�N�g��
	inline DirectX::SimpleMath::Vector3 RandomUnitVector()
	{
		// ���K���z���g���A���ʏ�ɕ��z������
		std::normal_distribution<float> dist(0.0f, 1.0f);
		DirectX::SimpleMath::Vector3 v(dist(GetRNG()), dist(GetRNG()), dist(GetRNG()));
		v.Normalize();
		return v;
	}

	// �w������𒆐S�ɂ����R�[����̃x�N�g��(���W�A���x�N�g��)
	inline DirectX::SimpleMath::Vector3 RandomConeVector(const DirectX::SimpleMath::Vector3& direction, float angleRadians)
	{
		// �����_���Ȋp�x���擾
		float z = RandomRange(std::cos(angleRadians), 1.0f);
		float theta = RandomRange(0.0f, DirectX::XM_2PI);
		float r = std::sqrt(1.0f - z * z);
		float x = r * std::cos(theta);
		float y = r * std::sin(theta);

		// ���[�J�����W����ړI�̕����ɉ�]
		DirectX::SimpleMath::Vector3 localDir(x, y, z);

		// �����x�N�g���� 0 0 1�Ȃ炻�̂܂�
		DirectX::SimpleMath::Vector3 defaultDir(0, 0 ,1);
		if (direction == defaultDir)
		{
			return localDir;
		}

		// ���A�p�x�����]�N�H�[�^�j�I�����쐬
		auto axis = defaultDir.Cross(direction);
		axis.Normalize();
		auto dot = defaultDir.Dot(direction);
		auto angle = std::acos(dot);

		auto rotation = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(axis, angle);
		return DirectX::SimpleMath::Vector3::Transform(localDir, rotation);
	}

	// ������w������Ɍ��������a�̃x�N�g��
	inline DirectX::SimpleMath::Vector3 RandomHemiSphereVector(const DirectX::SimpleMath::Vector3& direction)
	{
		DirectX::SimpleMath::Vector3 dir;
		// �����͋��̂Ɠ��l
		do {
			dir = RandomUnitVector();
		} 
		// �����݂̂ɐ���������
		while (dir.Dot(direction) < 0.0f);
		
		return dir;
	}
}

// ����
// ���������Ă郉���_���ł��B���z�ύX�ł���̂��ƂĂ������Ƃ���
// https://cpprefjp.github.io/reference/random.html