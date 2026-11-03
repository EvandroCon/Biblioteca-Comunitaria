cmake_minimum_required(VERSION 4.1)
project(Biblioteca-Comunitaria C)

set(CMAKE_C_STANDARD 23)


include(FetchContent)

FetchContent_Declare(
        libprg
        GIT_REPOSITORY https://github.com/EvandroCon/libprg.git
        GIT_TAG origin/main
        # or GIT_TAG 0.0.1

        # You can reference a local directory instead
        #URL file:///${CMAKE_CURRENT_SOURCE_DIR}/../../libprg
)
FetchContent_MakeAvailable(libprg)

add_executable(Biblioteca-Comunitaria main.c
        src/models/livro.c
        src/models/livro.h
        src/models/usuario.c
        src/models/usuario.h
        src/models/emprestimos.c
        src/models/emprestimos.h)

# linking libprg
target_link_libraries(Biblioteca-Comunitaria PUBLIC libprg)