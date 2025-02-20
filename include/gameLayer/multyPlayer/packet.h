#pragma once
#include <cstdint>
#include <enet/enet.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <chunk.h>
#include "server.h"


using EventCounter = unsigned int;
using RevisionNumber = unsigned int;

struct EventId
{
	EventId() {};
	EventId(EventCounter counter, RevisionNumber revision):counter(counter), revision(revision) {};

	EventCounter counter = 0;
	RevisionNumber revision = 0;
};

struct Packet
{
	int32_t header = 0;
	CID cid = 0;
	char *getData()
	{
		return (char *)((&cid) + 1);
	}
};

enum
{
	headerNone = 0,
	headerReceiveCIDAndData,
	headerRequestChunk,
	headerPlaceBlock,
	headerPlaceBlocks,
	headerRecieveChunk,
	headerValidateEvent,
	headerInValidateEvent,
};

struct Packet_ReceiveCIDAndData
{
};

struct Packet_RequestChunk
{
	glm::ivec2 chunkPosition = {};
};

struct Packet_RecieveChunk
{
	ChunkData chunk = {};
};

struct Packet_ValidateEvent
{
	EventId eventId = {};
};

struct Packet_InValidateEvent
{
	EventId eventId = {};
};

//used by the client to talk to the server
struct Packet_PlaceBlock 
{
	glm::ivec3 blockPos = {};
	uint16_t blockType = {};
	EventId eventId = {}; //event id is used by the player
};

//the server doesn't have a backend for this !!, sent from the server to the player only
struct Packet_PlaceBlocks
{
	glm::ivec3 blockPos = {};
	uint16_t blockType = {};
};



//first channel connection and chunks
//second channel blocks
constexpr static int SERVER_CHANNELS = 2;

void sendPacket(ENetPeer *to, Packet p, const char *data, size_t size, bool reliable, int channel);
char *parsePacket(ENetEvent &event, Packet &p, size_t &dataSize);