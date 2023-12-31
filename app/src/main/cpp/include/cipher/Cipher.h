#pragma once

#include <vector>
#include <utility>
#include <string>
#include "../misc/Logger.h"

/* a macro to declare and define:
 * a CipherBase pointer to Fire or Restore when needed
 * a variable to store the address of the function if needed
 * a function pointer to the function that you want to hook
 * and a function to replace that original function using Cipher Hooks methods
 * the macro is used like this:
 * HOOK_DEF(function_return_type, function_name, function_parameter1, function_parameter2, function_parameter_etc)
 * {
 * 		// implementation for the replacement function
 *
 * 		// returning the original function if needed:
 * 		return orig_function_name(arg1, arg2, arg_etc);
 * }
 *
 * note: this macro should be used as any other function definition or implementation
 */
#define HOOK_DEF(ret, func, ...) \
        CipherBase* func##_hook = nullptr;  \
		ret (*orig_##func)(__VA_ARGS__);\
		ret my_##func(__VA_ARGS__)



/* a macro to set up the hook and Fire it then printing a log after it's done
 * you have to put this macro inside Init or inside a function that gets called once only
 * you pass the CipherBase pointer that you have created or was created by the HOOK_DEF macro
 * then pass the original function pointer that you have created or was created by the HOOK_DEF macro
 * then pass the replacement function that you have created or was created by the HOOK_DEF macro
 * and finally pass the address of the function either by using a variable that you create
 * or assigning the address to the variable that the HOOK_DEF macro declares
 * or passing the address as a number directly
 */
#define SETUP_HOOK(cipher_base, orig_func, rep_func, func_addr) \
        if (func_addr) \
		{ \
			cipher_base = (new CipherHook()) \
				->set_Hook((uintptr_t)rep_func) \
				->set_Callback((uintptr_t)&orig_func) \
				->set_Address(func_addr, false)->Fire(); \
			LOGI(TAG_HOOKS, "%s", OBFUSCATE(#cipher_base" is done")); \
		}                                                             \
		else \
			LOGI(TAG_HOOKS, "%s", OBFUSCATE(#cipher_base" failed: address is 0"));



typedef void (*func)();

class Cipher {
public:
	// returns sky version
    static uint32_t getGameVersion();

	// returns a bool to if the game is beta sky or live sky
    static bool isGameBeta();

	// return the address of the start of sky's bootloader
    static uintptr_t get_libBase();

    static const char *get_libName();

	// searches for an address using a pattern inside sky's bootloader
    static uintptr_t CipherScan(const char *pattern, const char *mask);

	// searches for an address in a given range anywhere using a pattern
    static uintptr_t CipherScan(uintptr_t start, const size_t size, const char *pattern, const char *mask);
};


enum FLAGS{
    f_global, f_local
};

enum TYPES{
    e_patch,
    e_hook
};


class CipherBase {
private:
    bool m_isLocked = false;
    const char *m_libName;
    uintptr_t p_Address;


protected:
    uint8_t m_type;
    const char *get_libName();
    bool get_Lock();
    uintptr_t get_address();
    static inline std::vector<CipherBase *> m_InstanceVec;
    uintptr_t p_Backup;

public:
    CipherBase();
    virtual ~CipherBase() = 0;
    CipherBase *set_libName(const char *libName);
    CipherBase *set_Address(const char *Symbol);
    CipherBase *set_Address(uintptr_t address, bool isLocal = true);
    CipherBase *set_Address(const char *pattern, const char *mask);
    CipherBase *set_Lock(bool isLocked);
    virtual CipherBase *Fire() = 0;
    virtual void Restore() = 0;
};

class CipherHook : public CipherBase{
    uintptr_t p_Callback;
    uintptr_t p_Hook;

public:
    CipherHook();
    ~CipherHook() override;

	// sets the replacement function for the hook
    CipherHook *set_Hook(uintptr_t Hook);

	// sets the pointer of the original function that is being hooked
    CipherHook *set_Callback(uintptr_t Callback);

	// starts the hook
    CipherHook *Fire() override;

	// stops the hook
    void Restore() override;
};


class CipherPatch : public CipherBase{
    bool m_fired = false;
    std::string m_opcode;
    uintptr_t p_patch;

public:
    CipherPatch();
    ~CipherPatch() override;
    CipherPatch *Fire() override;
    CipherPatch *set_Opcode(std::string hex);
    void Restore() override;

};

