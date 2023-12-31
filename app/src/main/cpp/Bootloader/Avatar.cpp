#include "Avatar.h"
#include "../memory/AddressesBase.h"
#include "../memory/hooks.h"

std::map<std::string, Avatar> avatars;

bool Avatar::IsBot() const
{
	return m_count > 7;
}

vec3 *Avatar::GetPos() const
{
	return (vec3*)*(uintptr_t *)(this_ptr + 0x18);
}

void Avatar::Teleport(vec3 cords, bool center) const
{
	((void(*)(uintptr_t, vec3*, bool))(functions->Avatar_Teleport.get_address()))(this_ptr, &cords, center);
}

uintptr_t Avatar::GetAvatar() const
{
	return this_ptr;
}

uintptr_t Avatar::GetAvatarShout() const
{
	return *(uintptr_t*)(this->this_ptr + 0x60);
}

float Avatar::GetHeight() const
{
	return 0.9 * *(float*)(*(long*)(this_ptr + 24) + 200LL);
}

float* Avatar::SetHeight() const
{
	return (float*)(*(long*)(this_ptr + 24) + 200LL);
}

bool Avatar::IsActive(bool is_bot) const
{
	uint32_t* v2;
	v2 = (uint32_t*)(this_ptr + 120);
	if (v2 != nullptr && *v2)
		if (is_bot != 0)
			return true;
	return *((unsigned char*)(this_ptr + 55154)) / 8;

}

vec3 Avatar::GetCenter() const
{
	long double ret = ((long double (*)(uint64_t)) (hellboy->bootloader + 0x51C5E0))(this_ptr);
	return *((vec3*) &ret);
}

void Avatar::DoShout() const
{
	orig_AvatarShout_DoShout(*(long*)(this->this_ptr + 0x60), 0, 0, 0, 0, 0, 0, 0, 0, 0, *(long double*)this->ShoutColor, 0.0);
}
