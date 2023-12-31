#pragma once

#include <unistd.h>
#include "../hellboy/Hellboy.h"
//#include "AvatarShout.h"

class Avatar{

private:
	uintptr_t this_ptr;
	bool bot;
	int m_count;

public:

	Avatar(uintptr_t addr, int count) : this_ptr(addr), m_count(count) {}

	Avatar() {}

	uintptr_t GetAvatar() const;
	uintptr_t GetAvatarShout() const;

	bool IsBot() const;

	vec3* GetPos() const;


	void Teleport(vec3 cords, bool center = false) const;

	float GetHeight() const;

	float *SetHeight() const;

	bool IsActive(bool is_bot) const;// fix

	void DoShout() const;

public:
	float ShoutColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	bool CustomShoutColor = false;

	vec3 GetCenter() const;
};

extern std::map<std::string, Avatar> avatars;



