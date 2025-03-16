//
// Created by Conrad Stevens  on 2025-03-04.
//
#ifndef MESH_H
#define MESH_H
#include "entity_resources.h"
#include "glfw_ancillary.h"

/**
* @brief Mesh that can be rendered.
*/
template<GLsizei size_v, GLsizei size_b>
class Mesh{
    /**
    * @brief Vertex array object.
    */
    GLuint VAO{};

    /**
    * @brief Vertex buffer object.
    */
    GLuint VBO{};

    /**
    * @brief Index buffer object.
    */
    GLuint ibo{};

    /**
    * @brief Size in bytes of the vertex.
    *
    * @note Array members must be floats or of the same size.
    */
    GLsizeiptr vertex_size_bytes{size_v * sizeof(float)};  // @note Must be after render_vert

    /**
    * @brief Size in bytes of the index buffer
    *
    * @note Array members must be unsigned ints or of the same size.
    */
    GLsizeiptr index_buffer_size_bytes{size_b * sizeof(unsigned int)};  // @note Must be after index_buffer

    /**
    * @brief Vertices only consist of x and y coordinate and so of size 2.
    */
    static constexpr GLsizei stride_count{2};  // 2d points

    /**
    * @brief Both vertices points are floats and so has size 8Bytes
    */
    static constexpr GLsizei vertex_stride{2 * sizeof(float)};

public:
    /**
    * @brief Vertex pointer. Encourages that Vertices are shared among entities.
    */
    std::array<float, size_v>* vert_ptr = nullptr;

    /**
    * @brief Index buffer pointer. Encourages that index buffers are shared among entities.
    */
    std::array<unsigned int, size_b>* index_buffer_ptr = nullptr;

    /**
    * @brief Default constructor. May be used when defining a container
    */
    Mesh() = default;

    /**
    * @brief Default destructor. Data members handle their own destructors.
    */
    ~Mesh() = default;

    /**
    * @brief Creates mesh referring to mesh resource
    */
    template<typename Entity_T>
    explicit Mesh(EntityResource<Entity_T>& mesh_res_);

    /**
    * @brief Creates a Mesh referring to the vertex and buffer memory addresses.
    */
    explicit Mesh(std::array<float, size_v>* verts, std::array<unsigned int, size_b>* buffers);

    /**
    * @brief Copy constructor.
    */
    Mesh(const Mesh<size_v, size_b>& other);

    /**
    * @brief Copy assignment constructor.
    */
    Mesh<size_v, size_b>& operator=(const Mesh<size_v, size_b>& other);

    /**
    * @brief Move constructor.
    */
    Mesh(Mesh<size_v, size_b>&& other) noexcept;

    /**
    * @brief Move assignment constructor.
    */
    Mesh<size_v, size_b>& operator=(Mesh<size_v, size_b>&& other) noexcept;

    /**
    * @brief Return size of vertex buffer
    */
    static GLsizei getVertexSize() {return size_v;};

    /**
    * @brief Return size of index buffer.
    */
    static GLsizei getBufferSize() {return size_b;};

    /**
    * @brief Initialize the OpenGL objects.
    */
    void init();

private:
    /**
    * @brief Bind mesh to GPU friend.
    *
    * @note Mush must be initialized.
    */
    template<typename MeshType>
    friend void glfw_rendering::bindMeshToGPU(MeshType& mesh);
};

template<GLsizei size_v, GLsizei size_b>
template<typename Entity_T>
Mesh<size_v, size_b>::Mesh(EntityResource<Entity_T> &mesh_res_) :
    vert_ptr(&mesh_res_.vert),
    index_buffer_ptr(&mesh_res_.index_buffer){
}

template<GLsizei size_v, GLsizei size_b>
Mesh<size_v, size_b>::Mesh(std::array<float, size_v>* vert_ptr_, std::array<unsigned int, size_b>* index_buffer_ptr_) :
    vert_ptr(vert_ptr_),
    index_buffer_ptr(index_buffer_ptr_){
}

template<GLsizei size_v, GLsizei size_b>
Mesh<size_v, size_b>::Mesh(const Mesh<size_v, size_b> &other) :
    vert_ptr(other.vert_ptr),
    index_buffer_ptr(other.index_buffer_ptr){
}

template<GLsizei size_v, GLsizei size_b>
Mesh<size_v, size_b>& Mesh<size_v, size_b>::operator=(const Mesh<size_v, size_b> &other) {
    if (this != &other) {
        vert_ptr = other.vert_ptr;
        index_buffer_ptr =other.index_buffer_ptr;
        VAO = 0;
        VBO = 0;
        ibo = 0;
    }
    return *this;
}

template<GLsizei size_v, GLsizei size_b>
Mesh<size_v, size_b>::Mesh(Mesh<size_v, size_b> &&other) noexcept :
    vert_ptr(other.vert_ptr),
    index_buffer_ptr(other.index_buffer_ptr),
    VAO(other.VAO),
    VBO(other.VBO),
    ibo(other.ibo){
}

template<GLsizei size_v, GLsizei size_b>
Mesh<size_v, size_b>& Mesh<size_v, size_b>::operator=(Mesh<size_v, size_b> &&other) noexcept {
    if (this != &other) {
        vert_ptr = other.vert_ptr;
        index_buffer_ptr = other.index_buffer_ptr;
        VAO = other.VAO;
        VBO = other.VBO;
        ibo = other.ibo;
    }
    return *this;
}

template<GLsizei size_v, GLsizei size_b>
void Mesh<size_v, size_b>::init() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &ibo);
}

#endif //MESH_H
