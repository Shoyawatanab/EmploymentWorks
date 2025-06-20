//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto
// <製作開始日>		2025/06/12
// <file>			ParticleMath.cpp
// <概要>		　　形状計算
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"pch.h"
#include<random>
namespace ParticleMath
{
	// ランダムエンジン
	inline std::mt19937& GetRNG()
	{
		static std::random_device rd;
		static std::mt19937 rng(rd());
		return rng;
	}

	// 0 1 のランダム値
	inline float Random01()
	{
		std::uniform_real_distribution<float> dist(0.0f,1.0f);
		return dist(GetRNG());
	}

	// -1 , 1 のランダム値
	inline float RandomSigned()
	{
		std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
		return dist(GetRNG());
	}
	
	// 任意範囲のランダム(int)
	inline int RandomRange(int min, int max)
	{
		std::uniform_int_distribution<int> dist(min, max);
		return dist(GetRNG());
	}

	// 任意範囲のランダム(float)
	inline float RandomRange(float min, float max)
	{
		std::uniform_real_distribution<float> dist(min, max);
		return dist(GetRNG());
	}

	// 任意範囲のランダム(Vector2)
	inline DirectX::SimpleMath::Vector2 RandomRange(const DirectX::SimpleMath::Vector2& min, const DirectX::SimpleMath::Vector2& max)
	{
		return{
			RandomRange(min.x , max.x),
			RandomRange(min.y , max.y)
		};
	}

	// 任意範囲のランダム(Vector3)
	inline DirectX::SimpleMath::Vector3 RandomRange(const DirectX::SimpleMath::Vector3& min, const DirectX::SimpleMath::Vector3& max)
	{
		return{
			RandomRange(min.x , max.x),
			RandomRange(min.y , max.y),
			RandomRange(min.z , max.z)
		};
	}

	// 任意範囲のランダム(Vector4)
	inline DirectX::SimpleMath::Vector4 RandomRange(const DirectX::SimpleMath::Vector4& min, const DirectX::SimpleMath::Vector4& max)
	{
		return{
			RandomRange(min.x , max.x),
			RandomRange(min.y , max.y),
			RandomRange(min.z , max.z),
			RandomRange(min.w , max.w)
		};
	}

	// 任意範囲のランダム(Quaternion)
	inline DirectX::SimpleMath::Quaternion RandomRange(const DirectX::SimpleMath::Quaternion& min, const DirectX::SimpleMath::Quaternion& max)
	{
		return{
			RandomRange(min.x , max.x),
			RandomRange(min.y , max.y),
			RandomRange(min.z , max.z),
			RandomRange(min.w , max.w)
		};
	}

	// 任意範囲のランダム(Color)
	inline DirectX::SimpleMath::Color RandomRange(const DirectX::SimpleMath::Color& min, const DirectX::SimpleMath::Color& max)
	{
		return{
			RandomRange(min.x , max.x),
			RandomRange(min.y , max.y),
			RandomRange(min.z , max.z),
			RandomRange(min.w , max.w)
		};
	}




	// 単位平面上のランダムベクトル
	inline DirectX::SimpleMath::Vector3 RandomUnitVector()
	{
		// 正規分布を使い、球面上に分布させる
		std::normal_distribution<float> dist(0.0f, 1.0f);
		DirectX::SimpleMath::Vector3 v(dist(GetRNG()), dist(GetRNG()), dist(GetRNG()));
		v.Normalize();
		return v;
	}

	// 指定方向を中心にしたコーン上のベクトル(ラジアンベクトル)
	inline DirectX::SimpleMath::Vector3 RandomConeVector(const DirectX::SimpleMath::Vector3& direction, float angleRadians)
	{
		// ランダムな角度を取得
		float z = RandomRange(std::cos(angleRadians), 1.0f);
		float theta = RandomRange(0.0f, DirectX::XM_2PI);
		float r = std::sqrt(1.0f - z * z);
		float x = r * std::cos(theta);
		float y = r * std::sin(theta);

		// ローカル座標から目的の方向に回転
		DirectX::SimpleMath::Vector3 localDir(x, y, z);

		// 方向ベクトルが 0 0 1ならそのまま
		DirectX::SimpleMath::Vector3 defaultDir(0, 0 ,1);
		if (direction == defaultDir)
		{
			return localDir;
		}

		// 軸、角度から回転クォータニオンを作成
		auto axis = defaultDir.Cross(direction);
		axis.Normalize();
		auto dot = defaultDir.Dot(direction);
		auto angle = std::acos(dot);

		auto rotation = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(axis, angle);
		return DirectX::SimpleMath::Vector3::Transform(localDir, rotation);
	}

	// 上向き指定方向に向けた半径のベクトル
	inline DirectX::SimpleMath::Vector3 RandomHemiSphereVector(const DirectX::SimpleMath::Vector3& direction)
	{
		DirectX::SimpleMath::Vector3 dir;
		// やり方は球体と同様
		do {
			dir = RandomUnitVector();
		} 
		// 半球のみに制限をする
		while (dir.Dot(direction) < 0.0f);
		
		return dir;
	}
}

// 文献
// いつもつかってるランダムです。分布変更できるのがとてもいいところ
// https://cpprefjp.github.io/reference/random.html