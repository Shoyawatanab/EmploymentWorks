#pragma once



namespace WataLib
{
	class CSV final
	{
	private:

		std::string  m_nodeCsv;


	public:

		//ブーメランの軌道の座標の取得
		static std::vector<DirectX::SimpleMath::Vector3> LoadCSVBoomerang();



	};
}
