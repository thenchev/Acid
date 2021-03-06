#include "ModelDisk.hpp"

#include "Maths/Maths.hpp"
#include "Resources/Resources.hpp"
#include "Models/VertexDefault.hpp"

namespace acid
{
std::shared_ptr<ModelDisk> ModelDisk::Create(const Metadata &metadata)
{
	auto resource = Resources::Get()->Find(metadata);

	if (resource != nullptr)
	{
		return std::dynamic_pointer_cast<ModelDisk>(resource);
	}

	auto result = std::make_shared<ModelDisk>(0.0f, 0.0f);
	Resources::Get()->Add(metadata, std::dynamic_pointer_cast<Resource>(result));
	metadata >> *result;
	result->Load();
	return result;
}

std::shared_ptr<ModelDisk> ModelDisk::Create(const float &innerRadius, const float &outerRadius, const uint32_t &slices, const uint32_t &loops)
{
	auto temp = ModelDisk(innerRadius, outerRadius, slices, loops, false);
	Metadata metadata = Metadata();
	metadata << temp;
	return Create(metadata);
}

ModelDisk::ModelDisk(const float &innerRadius, const float &outerRadius, const uint32_t &slices, const uint32_t &loops, const bool &load) :
	m_innerRadius(innerRadius),
	m_outerRadius(outerRadius),
	m_slices(slices),
	m_loops(loops)
{
	if (load)
	{
		ModelDisk::Load();
	}
}

void ModelDisk::Load()
{
	if (m_innerRadius == 0.0f && m_outerRadius == 0.0f)
	{
		return;
	}

	std::vector<VertexDefault> vertices;
	std::vector<uint32_t> indices;
	// TODO: Reserve.

	for (uint32_t i = 0; i < m_slices; i++)
	{
		float iDivSlices = static_cast<float>(i) / static_cast<float>(m_slices);
		float alpha = iDivSlices * 2.0f * Maths::Pi;
		float xDir = std::cos(alpha), yDir = std::sin(alpha);

		for (uint32_t j = 0; j < m_loops + 1; j++)
		{
			float jDivLoops = static_cast<float>(j) / static_cast<float>(m_loops);
			float radius = m_innerRadius + jDivLoops * (m_outerRadius - m_innerRadius);

			Vector3f position = Vector3f(radius * xDir, 0.0f, radius * yDir);
			Vector2f uvs = Vector2f(1.0f - iDivSlices, 1.0f - jDivLoops);
			Vector3f normal = Vector3f(0.0f, 1.0f, 0.0f);
			vertices.emplace_back(VertexDefault(position, uvs, normal));
		}
	}

	for (uint32_t i = 0; i < m_slices; i++)
	{
		for (uint32_t j = 0; j < m_loops; j++)
		{
			uint32_t first = i * (m_loops + 1) + j;
			uint32_t second = (first + m_loops + 1) % (m_slices * (m_loops + 1));

			indices.emplace_back(second + 1);
			indices.emplace_back(first + 1);
			indices.emplace_back(first);
			indices.emplace_back(second);
			indices.emplace_back(second + 1);
			indices.emplace_back(first);
		}
	}

	Initialize(vertices, indices);
}

const Metadata &operator>>(const Metadata &metadata, ModelDisk &model)
{
	metadata.GetChild("Inner Radius", model.m_innerRadius);
	metadata.GetChild("Outer Radius", model.m_outerRadius);
	metadata.GetChild("Slices", model.m_slices);
	metadata.GetChild("Loops", model.m_loops);
	return metadata;
}

Metadata &operator<<(Metadata &metadata, const ModelDisk &model)
{
	metadata.SetChild<std::string>("Type", "ModelDisk");
	metadata.SetChild("Inner Radius", model.m_innerRadius);
	metadata.SetChild("Outer Radius", model.m_outerRadius);
	metadata.SetChild("Slices", model.m_slices);
	metadata.SetChild("Loops", model.m_loops);
	return metadata;
}
}
