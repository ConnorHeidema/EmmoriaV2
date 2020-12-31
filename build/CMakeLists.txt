cmake_minimum_required(VERSION 3.10)

project(Emmoria)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../output)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ADDITIONAL_CFLAGS} -g")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

link_directories(../ext/bin/SFML ../ext/bin/sfemovie)

add_executable(Emmoria
				../main.cpp

				# Core
                ../src/core/Application.cpp
                ../src/core/TileMap.cpp

                # Config Items
                ../src/config/ConfigItems.cpp

                # Component map
                ../src/component/InteractStringMap.cpp

                # Tilemap
                ../src/TileMap/TileMapIndexes.cpp

                # Utility classes
                ../src/util/Mediamap.cpp
                ../src/util/Entitymap.cpp
                ../src/util/MediatoEntitymap.cpp
                ../src/util/ApplicationParameters.cpp
                ../src/util/MouseUtils.cpp
                ../src/util/EntityLoaderUtils.cpp
                ../src/util/Helper.cpp
                ../src/util/SystemList.cpp
                ../src/util/OverlapUtils.cpp
                ../src/util/AnimationMappings.cpp
                ../src/util/Latch.cpp
                ../src/util/PositionUtils.cpp
                ../src/util/EnttUtils.cpp
                ../src/util/DialogParameters.cpp
                ../src/util/TextureContainer.cpp
                ../src/util/FontContainer.cpp

                # System implementations
                ../src/system/System.cpp
                ../src/system/RebootSys.cpp
                ../src/system/ReloadSys.cpp
                ../src/system/ConfigSys.cpp
                ../src/system/MovementSys.cpp
                ../src/system/MovieRenderSys.cpp
                ../src/system/GameRenderSys.cpp
                ../src/system/LoadingSys.cpp
                ../src/system/ButtonSys.cpp
                ../src/system/ClickableSys.cpp
                ../src/system/DialogSys.cpp
                ../src/system/PersistentSys.cpp
                ../src/system/HealthSys.cpp
                ../src/system/InteractingSys.cpp
                ../src/system/TileMapSys.cpp
                ../src/system/AnimationSys.cpp
                ../src/system/SceneLoadSys.cpp
                ../src/system/BowSys.cpp
                ../src/system/LifespanSys.cpp
                ../src/system/DoorSys.cpp
                ../src/system/SwitchSys.cpp
                ../src/system/MusicSys.cpp

                # Enemy system implementations
                ../src/system/enemy/BlobSys.cpp

                # Entity factory
                ../src/entity/EntityLoaderFactory.cpp
)

target_include_directories(Emmoria PRIVATE ../ext/inc)
target_include_directories(Emmoria PRIVATE ../inc)

target_link_libraries(Emmoria sfeMovie-d)
target_link_libraries(Emmoria avcodec)
target_link_libraries(Emmoria avdevice)
target_link_libraries(Emmoria avfilter)
target_link_libraries(Emmoria avformat)
target_link_libraries(Emmoria avutil)
target_link_libraries(Emmoria swresample)
target_link_libraries(Emmoria swscale)

target_link_libraries(Emmoria sfml-graphics-d)
target_link_libraries(Emmoria sfml-window-d)
target_link_libraries(Emmoria sfml-system-d)
target_link_libraries(Emmoria sfml-audio-d)
target_link_libraries(Emmoria sfml-network-d)

target_link_libraries(Emmoria stdc++fs)
