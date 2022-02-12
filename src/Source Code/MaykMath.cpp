#include"MaykMath.h"
#include<assert.h>

void MaykMath::Init()
{
	srand(time(NULL));
}

//ASK: Is this good?
int MaykMath::Random(int minV, int maxV)
{
	assert(minV <= maxV);
	return (rand() % (maxV - minV + 1)) + minV;
}

float MaykMath::Random(float minV, float maxV)
{
	assert(minV <= maxV);
	float random = ((float)rand()) / (float)RAND_MAX;
	return minV + (random * (maxV - minV));
}

std::string MaykMath::VersionToString(int major, int minor, int patch)
{
	std::string ret(std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch));
	return ret;
}

void MaykMath::FindCentroid(float* A, float* B, float* C, float* r)
{
	for (int i = 0; i < 3; ++i)
	{
		r[i] = (A[i] + B[i] + C[i]) / 3;
	}
}

void MaykMath::GeneralDataSet(float* dest, float* src, size_t vecSize)
{
	for (size_t i = 0; i < vecSize; i++)
	{
		dest[i] = src[i];
	}

}

std::vector<float2> MaykMath::ScatterPoints(float radius, float2 sampleRegionSize)
{









	return std::vector<float2>();
}
