### Proyecto final 2015

### XCode ###

1- Clone the repository
  ```bash
    > git clone git@github.com:ealtamir/pf_experimentos.git
  ```

2- Create command line tool on XCode, setting the language on C++

3- Delete the main.cpp on the created project

3- Drag and drop the folder src to the project and select the "Create Groups" options

4- Drag and drop the folder include to the project and select the "Create Groups" options

5- Move the main.cpp on src folder to the where main.cpp was on the step 3

6- Compile libraries from bullet3 (https://github.com/bulletphysics/bullet3)
  
  [Install CMake](http://www.cmake.org/install/)

  Compile libraries on OSX:
  ```bash
    > git clone git@github.com:bulletphysics/bullet3.git
    > cd bullet3
    > cmake . -G "Unix Makefiles" -DINSTALL_LIBS=ON -DBUILD_SHARED_LIBS=ON \
      -DFRAMEWORK=ON  -DCMAKE_OSX_ARCHITECTURES='i386;x86_64' \
      -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_INSTALL_PREFIX=/Library/Frameworks \
      -DCMAKE_INSTALL_NAME_DIR=/Library/Frameworks -DBUILD_DEMOS:BOOL=OFF
    > make -j4
    > sudo make install
  ```

7- Drag and drop the following libraries installed on '/Library/Frameworks/' to the root of the project:
    -BulletDynamics.framework
    -BulletCollision.framework
    -LinearMath.framework

8- Drag and drop the static libs on the folder 'libraries' to the root of the project

9- Select the root of the project, go to build phases, open 'Link Binary With Libraries' and add:
    -GLUT.framework
    -OpenGL.framework

10- Select the root of the project, go to build phases, open 'Compile Sources' and add all the .cpp files

After all you should get something like this:

![alt tag](https://raw.githubusercontent.com/ealtamir/pf_experimentos/start-genetic-algorithm/readme1.png)
![alt tag](https://raw.githubusercontent.com/ealtamir/pf_experimentos/start-genetic-algorithm/readme2.png)

### FAQ ###

- ** Followed all the steps, tried to compile the project and failed because errors in one specific file. **
Try to remove all files from the compile sources list and add them again. Maybe you missed an important
file the first time. Remember to *clean* de project before retrying compilation.

This project is maintained by [Tomás Mehdi](https://github.com/tomymehdi), [Enzo Altamiranda](https://github.com/ealtamir) and [Teresa Fontanella De Santis](https://github.com/TereFDS).
