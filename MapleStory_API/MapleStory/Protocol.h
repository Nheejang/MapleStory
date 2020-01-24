#pragma once

const unsigned int WORLD_WIDTH = 8;
const unsigned int WORLD_HEIGHT = 8;

const unsigned int SERVER_PORT = 3500;
const unsigned int MAX_USER = 20;
const unsigned int NPC_START = 20;
const unsigned int MAX_OBJECT = 30;
const unsigned short MAX_BUFF_SIZE = 1024;
const unsigned char VIEW_RADIUS = 3;

const unsigned char MAX_STR_SIZE = 100;

const unsigned short CS_UP = 1;
const unsigned short CS_DOWN = 2;
const unsigned short CS_LEFT = 3;
const unsigned short CS_RIGHT = 4;
const unsigned short CS_JUMP = 5;
const unsigned short CS_CHAT = 6;

const unsigned short SC_POS = 1;
const unsigned short SC_PUT_PLAYER = 2;
const unsigned short SC_REMOVE_PLAYER = 3;
const unsigned short SC_CHAT = 4;

#pragma pack (push, 1)

struct cs_packet_up {
	unsigned short size;
	unsigned char type;
};

struct cs_packet_down {
	unsigned short size;
	unsigned char type;
};

struct cs_packet_left {
	unsigned short size;
	unsigned char type;
};

struct cs_packet_right {
	unsigned short size;
	unsigned char type;
};

struct cs_packet_chat {
	unsigned short size;
	unsigned char type;
	WCHAR message[MAX_STR_SIZE];
};

struct sc_packet_pos {
	unsigned short size;
	unsigned char type;
	WORD id;
	int x;
	int y;
};

struct sc_packet_put_player {
	unsigned short size;
	unsigned char type;
	WORD id;
	int x;
	int y;
};
struct sc_packet_remove_player {
	unsigned short size;
	unsigned char type;
	WORD id;
};

struct sc_packet_chat {
	unsigned short size;
	unsigned char type;
	WORD id;
	WCHAR message[MAX_STR_SIZE];
};

#pragma pack (pop)