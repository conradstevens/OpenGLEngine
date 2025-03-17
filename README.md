# OpenGl Rendering Engine

### Description
This is an over engineered OpenGl rendering engine. It can easily be scaled up to accomodate many more meshes and scenes while maintaining a high performance. All resources are loaded on seperate threads at compile time, using templated sizing for each entity type. This allows for stack allocated resources and better cache management. 

All the dependencies are linked dynamically using the origianl repos submodulos. They can be found in the `external` folder. The code is built using a series of CMakeLists.txt files and tested using the Google Test framework. Here is a short video simulating some falling shapes. 

[<img width="500" alt="OpenGL Rendering Demo Thumb Nail" src="https://github.com/user-attachments/assets/3e927f75-9c1c-4739-a5fc-507cdb54ef6a" />](https://www.youtube.com/watch?v=8kMXkVgPZKw)

### Build
Building the project should be failry streight forwards as all dependencies are dynamically linked via their submodulo. Further, OpenGL for the most part is cross platform. 

Clone project and submodulos.

`git clone --recurse-submodules https://github.com/conradstevens/OpenGLEngine.git`

Enter repository

`cd OpenGLEngine`


Build Project.

`mkdir build`

`cmake -S . -B build` May take a minute

`cmake --build build` This may take a while


Run the program!

`./build/OpenGLEngine`
