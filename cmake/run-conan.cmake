option(
    RUN_CONAN
    "Run conan install automatically"
    ON
)

if (RUN_CONAN)
    if (
        NOT
        EXISTS
        "${CMAKE_BINARY_DIR}/conan.cmake"
    )
        message(
            STATUS
                "Downloading conan.cmake from https://github.com/conan-io/cmake-conan"
        )

        file(
            DOWNLOAD
            "https://github.com/conan-io/cmake-conan/raw/master/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake"
        )
    endif ()

    include(${CMAKE_BINARY_DIR}/conan.cmake)

    conan_check(REQUIRED)
    conan_add_remote(
        NAME bincrafters
        INDEX 1
        URL https://api.bintray.com/conan/bincrafters/public-conan
    )
    conan_add_remote(
        NAME imguisfml
        INDEX 1
        URL https://github.com/eliasdaler/imgui-sfml
    )
    conan_cmake_run(CONANFILE conanfile.txt BUILD missing)
endif ()
