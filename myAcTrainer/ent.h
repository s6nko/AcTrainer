#include <Windows.h>
#include <cstdio>
#include <cstdint>

struct vec3 { float x, y, z; };

using Vector3 = vec3;

class entity
{
public:
	char pad_0000[4]; //0x0000
	Vector3 headPos; //0x0004
	char pad_0010[36]; //0x0010
	Vector3 bodyPos; //0x0034
	Vector3 viewAngles; //0x0040
	char pad_004C[172]; //0x004C
	int32_t health; //0x00F8
	char pad_00FC[296]; //0x00FC
	int8_t bAttack; //0x0224
	char pad_0225[263]; //0x0225
	int32_t currTeam; //0x032C
	char pad_0330[72]; //0x0330
	class weapon* currWeapon; //0x0378
	char pad_037C[1240]; //0x037C
}; //Size: 0x0854


class weapon
{
public:
	char pad_0000[4]; //0x0000
	int32_t id; //0x0004
	class entity* owner; //0x0008
	char pad_000C[4]; //0x000C
	class ammoPtr* ammoReserve; //0x0010
	class ammoPtr* ammoClip; //0x0014
	char pad_0018[44]; //0x0018
}; //Size: 0x0044


class ammoPtr
{
public:
	int32_t ammo; //0x0000
}; //Size: 0x0004
