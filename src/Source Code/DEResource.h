#pragma once

#include<string>

class Resource
{

public:
	enum class Type {
		TEXTURE,
		SHADER,
		UNKNOWN
	};

public:
	Resource(std::string& _uid, Resource::Type _type);
	virtual ~Resource();

	inline Resource::Type GetType() const { return type; }
	inline std::string GetUID() const { return uid; }
	inline const char* GetAssetPath() const { return assetsFile.c_str(); }

	void SetAssetsPath(const char*);


	inline unsigned int GetReferenceCount() const { return referenceCount; }
	inline void IncreaseReferenceCount() { referenceCount++; }
	inline void DecreaseReferenceCount() { referenceCount--; }

	virtual bool LoadToMemory() { return false; }
	virtual bool UnloadFromMemory() { return false; }

protected:

	std::string uid;
	std::string assetsFile;
	Type type = Type::UNKNOWN;
	unsigned int referenceCount;
};