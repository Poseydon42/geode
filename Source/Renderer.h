#pragma once

#include <cstdint>
#include <mutex>

namespace Geode
{
    struct Camera;
    struct Film;
    struct World;

	struct RenderTile
	{
		uint32_t StartX;
		uint32_t StartY;
		uint32_t Width;
		uint32_t Height;

		const Geode::Film* Film;
		const Geode::Camera* Camera;
		const Geode::World* World;

		const RenderTile* Next;
	};

	struct WorkQueue
	{
		const RenderTile* First;
		std::mutex Lock;
	};

	void WorkerRenderThread(WorkQueue* Queue);

	void RenderSingleTile(const RenderTile& Tile);

    void Render(const Film& Film, const Camera& Camera, const World& World);
}