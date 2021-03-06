# Master's Degree in Video game programming at U-Tad
## 3D Programming

Practices for the subject 3D Programming.

* Practice 1: Rotating triangles. Basic primitives.
* Practice 2: The World and its entities. Texture loading.
* Practice 3: Mesh loading.
* Practice 4: Illumination.

Every practice is an improvement from the last one so a lot of the code is reused.
But you should look at it closely because sometimes although it's really similar it has a little change.

### Instructions to compile and run the code
* Folder structure must be:
  * data
  * lib
  * project
  * src
* Lib folder outside the practices contains the glfw and glm and glew libraries so it must be **included and combined** within the lib folder in **every practice** (I've uploaded it this way not to upload the libraries 4 times). **stb_image.h** is needed from practice 2 onwards (included).
* **tinyobjloader** library is needed from practice 3 onwards (included) in order to read the obj files of the meshes. You can download and see it documentation at its [repository](https://github.com/tinyobjloader/tinyobjloader). Then you just have to include the whole (tiny) folder inside the lib folder of the practice to make it work.
* To run the code, be sure to **compile it for x64**. Any other way it will fail.
