cmake_minimum_required(VERSION 3.19.0)

#set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE Release)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    #add_definitions(-DRELEASE_MODE)
    set(CMAKE_C_VISIBILITY_PRESET hidden)
    set(CMAKE_CXX_VISIBILITY_PRESET hidden)
endif()


#tests
#set_target_properties(${TARGET_NAME} PROPERTIES COMPILE_OPTIONS "-Os" LINK_FLAGS "-s -Wl,--gc-sections")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
#set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -DNDEBUG")


set(CIPHER_PATH ${CMAKE_SOURCE_DIR}/include/cipher/libciphered.so)
set(StbImage_PATH ${CMAKE_SOURCE_DIR}/include/StbImage/libstb_image.a)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fvisibility=hidden" )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden" )
file(DOWNLOAD ${CIPHER_URL} ${CIPHER_PATH} STATUS LIBCIPHER_DOWNLOAD_STATUS)
add_link_options(-Wl,--unresolved-symbols=ignore-all)

project("userlib")

file(READ ${CMAKE_HOME_DIRECTORY}/config.json MY_JSON_STRING) #reads soname from config
string(JSON CUR_NAME GET ${MY_JSON_STRING} name)
string(LENGTH ${CUR_NAME} CUR_NAME_LEN)
string(SUBSTRING ${CUR_NAME} 3 ${CUR_NAME_LEN} CUR_NAME) #ugly but there's no lazy regex support
string(REPLACE ".so" "" CUR_NAME ${CUR_NAME})

file(GLOB RESOURCE_FILE_LIST RELATIVE ${CMAKE_SOURCE_DIR}/resources/ ${CMAKE_SOURCE_DIR}/resources/* )
foreach(RESOURCE_FILE ${RESOURCE_FILE_LIST})
    STRING(REGEX REPLACE "\\.[a-zA-Z0-9_]*" "" FILE_OBJ_NAME ${RESOURCE_FILE})
    add_custom_command(OUTPUT "${CMAKE_SOURCE_DIR}/objects/${FILE_OBJ_NAME}.o"
            DEPENDS ${CMAKE_SOURCE_DIR}/resources/${RESOURCE_FILE}
            COMMAND ${CMAKE_LINKER}
            ARGS -r -b binary -m aarch64elf ${RESOURCE_FILE} -o ${CMAKE_SOURCE_DIR}/objects/${FILE_OBJ_NAME}.o
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/resources
            COMMENT "Generating ${FILE_OBJ_NAME}.o"
            )
endforeach()

set(INC_RES_LIST
        logo
        #logo_xmas
        #logo_x
        )

foreach(INC_RES_OBJ ${INC_RES_LIST})
    set(INC_RES_OBJ_LIST ${INC_RES_OBJ_LIST} objects/${INC_RES_OBJ}.o)
endforeach()


add_library( # Sets the name of the library.
        ${CUR_NAME}
        SHARED
        main.cpp
        memory/memory.cpp
        memory/HellAddress.cpp
        memory/AddressesBase.cpp
        memory/SkyConst.cpp
        memory/HellPatch.cpp
        #memory/Live_Editor/MemObserver.cpp
        hellboy/HellWidget.cpp
        hellboy/SkySong.cpp
        hellboy/Hellboy.cpp
        hellboy/HellboyIO.cpp
        hellboy/ChatBox.cpp
        Bootloader/Avatar.cpp
        #Bootloader/AvatarShout.cpp
        Bootloader/CheckpointBarn.cpp
        #Bootloader/HttpClientRequestArgs.cpp
        #Bootloader/HttpClient.cpp
        memory/hooks.cpp
        include/StbImage/create_texture.cpp

        menu/Avatars.cpp
        menu/ChangeLevel.cpp
        menu/Inventory.cpp
        menu/Farming.cpp
        menu/Command.cpp
        menu/Music.cpp
        menu/Settings.cpp
        menu/Magic.cpp
        menu/Styles.cpp
        menu/Debug.cpp

        ${INC_RES_OBJ_LIST}
        )

find_library(
        log-lib
        log)

target_link_libraries(
        ${CUR_NAME}
        EGL
        GLESv3
        "${StbImage_PATH}"
        "${CIPHER_PATH}"
        ${log-lib})

add_custom_command(
        TARGET ${CUR_NAME}
        POST_BUILD
        COMMAND ${CMAKE_OBJCOPY}
        ARGS --add-section .config=${CMAKE_HOME_DIRECTORY}/config.json --set-section-flags .config=readonly,contents,data $<TARGET_FILE:${CUR_NAME}>
)
