#include "MapRenderer.hpp"

#include "Field.hpp"
#include "FieldProperties.hpp"
#include "LaneProperties.hpp"
#include "MapGenerator.hpp"
#include "Railway.hpp"
#include "RailwayProperties.hpp"
#include "River.hpp"
#include "RiverProperties.hpp"
#include "Road.hpp"
#include "RoadProperties.hpp"
#include "UserSession.hpp"
#include "UtilitySave.hpp"

#include <memory>

MapRenderer::MapRenderer(TextureManager &textures, ViewGroup &foreground,
                         unsigned int map_width, unsigned int map_max_height,
                         unsigned int level, bool isLoad)
    : m_textures(textures),
      m_foreground(foreground),
      m_sizes(map_width, map_max_height),
      m_width(m_sizes.x),
      m_max_height(m_sizes.y),
      m_level(level)
{
    if (!isLoad) 
        initialize();
    else
        loadLanes("data/" + UserSession::getInstance().getCurrentUser().getUsername());
}

void MapRenderer::moveView()
{
    if (m_lanes.size() < 10)
    {
        return;
    }

    // popLane();
    pushLane(0);
}

MapRenderer::LaneList const &MapRenderer::getLanes() const
{
    return m_lanes;
}

void MapRenderer::initialize()
{
    m_map_generator =
        std::make_unique<MapGenerator>(m_width, m_max_height, m_level);
    for (int i = 0; i < m_max_height; ++i)
    {
        pushLane(1);
    }
}

void MapRenderer::pushLane(bool initializing_p)
{
    m_map_generator->moveView(initializing_p);
    m_lanes.push_back(convertPropertiesToLane(m_map_generator->getCurrLane()));
}

void MapRenderer::saveLanes(const std::string &filepath)
{
    std::error_code err;
    if (!CreateDirectoryRecursive(filepath, err))
    {
        std::cerr << "SAVE FAILURE, ERR: " << err << std::endl;
    }
    std::ofstream outf(filepath + "/save.data", std::ios::binary);
    int laneSize = m_lanes.size();
    outf.write(reinterpret_cast<const char *>(&laneSize), sizeof(laneSize));
    if (m_lanes.size() > 0)
    {
        for (auto it = m_lanes.begin(); it != m_lanes.end(); ++it)
        {
            Lane *lane = *it;
            lane->saveLaneData(outf);
        }
    }
}

void MapRenderer::loadLanes(const std::string& filepath)
{
    std::ifstream inf(filepath + "/save.data", std::ios::binary);

    int laneSize;
    inf.read(reinterpret_cast<char *>(&laneSize), sizeof(laneSize));
    for (int i = 0; i < laneSize; ++i)
    {
        int laneType;
        bool laneIsReverse;
        inf.read(reinterpret_cast<char *>(&laneType), sizeof(laneType));
        inf.read(reinterpret_cast<char *>(&laneIsReverse), sizeof(laneIsReverse));

        // std::unique_ptr<Lane> lane;
        Lane* lane;
        switch (static_cast<Lane::Type>(laneType))
        {
        case Lane::Type::Road:
            unsigned int vehiclesCnt, animalsCnt, vehicleType, animalType;
            float velocity;
            inf.read(reinterpret_cast<char *>(&vehiclesCnt), sizeof(vehiclesCnt));
            inf.read(reinterpret_cast<char *>(&animalsCnt), sizeof(animalsCnt));
            inf.read(reinterpret_cast<char *>(&vehicleType), sizeof(vehicleType));
            inf.read(reinterpret_cast<char *>(&animalType), sizeof(animalType));
            inf.read(reinterpret_cast<char *>(&velocity), sizeof(velocity));
            lane = new Road(&m_textures, laneIsReverse, vehiclesCnt, animalsCnt, static_cast<Vehicle::Type>(vehicleType), static_cast<Animal::Type>(animalType), velocity, true);
            lane->loadLaneData(inf);
            break;
        case Lane::Type::River:
            float logVelocity;
            inf.read(reinterpret_cast<char *>(&logVelocity), sizeof(logVelocity));
            lane = new River(&m_textures, laneIsReverse, logVelocity, true);
            lane->loadLaneData(inf);
            break;
        case Lane::Type::Field:
            lane = new Field(&m_textures, laneIsReverse, true);
            lane->loadLaneData(inf);
            break;
        case Lane::Type::Railway:
            lane = new Railway(&m_textures, &m_foreground, laneIsReverse, true);
            lane->loadLaneData(inf);
            break;
        default:
            throw std::runtime_error("LOAD ERR: Lane type not found");
        }
        m_lanes.push_back(lane);
    }
}

void MapRenderer::popLane()
{
    m_lanes.pop_front();
}

Lane *
MapRenderer::convertPropertiesToLane(LaneProperties const &properties) const
{
    switch (properties.getType())
    {
    case Lane::Type::Field:
        return convertPropertiesToLane(
            dynamic_cast<FieldProperties const &>(properties));

    case Lane::Type::Railway:
        return convertPropertiesToLane(
            dynamic_cast<RailwayProperties const &>(properties));

    case Lane::Type::Road:
        return convertPropertiesToLane(
            dynamic_cast<RoadProperties const &>(properties));

    case Lane::Type::River:
        return convertPropertiesToLane(
            dynamic_cast<RiverProperties const &>(properties));

    default:
        return nullptr;
    }
}

Field *
MapRenderer::convertPropertiesToLane(FieldProperties const &properties) const
{
    auto field = new Field(&m_textures);
    for (auto const &[index, green_type] : properties.getGreens())
    {
        auto green = std::make_unique<Green>(green_type, m_textures);
        field->add(std::move(green), index);
    }
    return field;
}

Railway *
MapRenderer::convertPropertiesToLane(RailwayProperties const &properties) const
{
    return new Railway(&m_textures, &m_foreground, properties.isReverse());
}

Road *
MapRenderer::convertPropertiesToLane(RoadProperties const &properties) const
{
    auto road = new Road(
        &m_textures, properties.isReverse(), properties.getVehiclesCnt(),
        properties.getAnimalsCnt(), properties.getVehicleType(),
        properties.getAnimalType(), properties.getVelocity());
    return road;
}

River *
MapRenderer::convertPropertiesToLane(RiverProperties const &properties) const
{
    auto river = new River(&m_textures, properties.isReverse(),
                           properties.getVelocity());
    river->setLogVelocity(properties.getVelocity());
    return river;
}
