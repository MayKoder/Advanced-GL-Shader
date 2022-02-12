#include"MaykMath.h"
#include<assert.h>
#include"Globals.h"

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

std::vector<float2> MaykMath::ScatterPoints(float radius, float2 sampleRegionSize, int numSamplesBeforeRejection)
{

	float cellSize = radius / SQRT_OF_TWO;

	int elements = ((int)ceil(sampleRegionSize.x / cellSize)) * ((int)ceil(sampleRegionSize.y / cellSize));
	int* grid = new int[ elements ];
	memset(grid, 0, elements * sizeof(int)); // for automatically-allocated arrays
	std::vector<float2> points;
	std::vector<float2> spawnPoints;
	//i = x + sampleRegionSize.x * y;

	spawnPoints.push_back(sampleRegionSize/2.f);
	while (spawnPoints.size() > 0)
	{
		int spawnIndex = Random(0, spawnPoints.size()-1);
		float2 spawnCenter = spawnPoints[spawnIndex];

		bool candidateAccepted = false;
		for (size_t i = 0; i < numSamplesBeforeRejection; ++i)
		{
			float angle = Random(0.0f, 1.0f) * PI * 2;
			float2 direction(sin(angle), cos(angle));
			float2 candidate = spawnCenter + direction *   Random(radius, radius * 2.0f);
			//float2 candidate = spawnCenter + direction * radius * sqrt(Random(1, 4));

			if (IsScatterValidPoint(candidate, sampleRegionSize, cellSize, radius, points, grid)) {
				points.push_back(candidate);
				spawnPoints.push_back(candidate);

				int id = ((int)(candidate.x / cellSize)) + sampleRegionSize.x * ((int)(candidate.y / cellSize));
				grid[id] = points.size();
				candidateAccepted = true;
				break;
			}


		}

		if (!candidateAccepted) {
			spawnPoints.erase(spawnPoints.begin() + spawnIndex);
		}


	}

	delete[] grid;
	spawnPoints.clear();
	return points;
}

bool MaykMath::IsScatterValidPoint(float2& candidate, float2& sampleRegionSize, float cellSize,float radius, std::vector<float2>& points, int* grid)
{
	if (candidate.x >= 0.0f && candidate.x < sampleRegionSize.x && candidate.y >= 0.0f && candidate.y < sampleRegionSize.y) {
		int cellX = (int)(candidate.x / cellSize);
		int cellY = (int)(candidate.y / cellSize);

		int searchStartX = MAX(0, cellX-2);
		int searchEndX = MIN(cellX+2, ((int)ceil(sampleRegionSize.x / cellSize)) - 1);

		int searchStartY = MAX(0, cellY - 2);
		int searchEndY = MIN(cellY + 2, ((int)ceil(sampleRegionSize.y / cellSize)) - 1);

		for (size_t x = searchStartX; x <= searchEndX; ++x)
		{
			for (size_t y = searchStartY; y <= searchEndY; ++y)
			{
				int id = x + sampleRegionSize.x * y;
				int pointIndex = grid[id] - 1;
				if (pointIndex != -1) {
					float dist = (candidate - points[pointIndex]).LengthSq();
					if (dist < radius*radius) {
						return false;
					}
				}
			}
		}
		return true;
	}

	return false;
}
