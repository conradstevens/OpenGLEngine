// //
// // Created by Conrad Stevens  on 2025-03-03.
// //
//
// #include "entities/entity.h"
//
//
// Entity::Entity(const Entity& other) :
//     mesh(other.mesh){
// }
//
// Entity& Entity::operator=(const Entity& other) {
//     if (this != &other) {
//         mesh = other.mesh;
//     }
//     return *this;
// }
//
// Entity::Entity(Entity &&other) noexcept :
//     mesh(std::move(other.mesh)){
// }
//
// Entity& Entity::operator=(Entity &&other) noexcept {
//     if (this != &other) {
//         mesh = std::move(other.mesh);
//     }
//     return *this;
// }
