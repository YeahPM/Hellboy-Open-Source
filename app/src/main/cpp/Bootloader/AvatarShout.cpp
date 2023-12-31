#include "AvatarShout.h"
#include "../memory/hooks.h"

AvatarShout::AvatarShout() = default;

void AvatarShout::DoShout(long avatar_shout, int a2, int a3, bool a4, bool a5, bool a6, long double a7, float a8, float a9, float a10, long double a11, float a12)
{
	orig_AvatarShout_DoShout(avatar_shout, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);
}
